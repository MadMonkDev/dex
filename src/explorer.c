#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "dex/explorer.h"

typedef struct entry {
    char *name;
    int is_dir;
    off_t size;
    struct entry *next;
} entry_t;

static int should_ignore(const char *name, char **ignore_list, int ignore_count) {
    for (int i = 0; i < ignore_count; i++) {
        if (strcmp(name, ignore_list[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

static off_t calculate_size(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return 0;

    struct dirent *entry;
    off_t total_size = 0;
    char full_path[4096];

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.') continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        struct stat st;
        if (stat(full_path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                total_size += calculate_size(full_path);
            } else {
                total_size += st.st_size;
            }
        }
    }

    closedir(dir);
    return total_size;
}

void walk_directory(const char *directory, const char *prefix, counter_t *counter,
                    int show_dotfiles, sort_mode_t sort_mode,
                    char **ignore_list, int ignore_count) {
    DIR *dir = opendir(directory);
    if (!dir) {
        fprintf(stderr, "Cannot open directory \"%s\"\n", directory);
        return;
    }

    counter->dirs++;

    struct dirent *entry;
    entry_t *head = NULL, *cur, *iter;
    size_t count = 0;

    while ((entry = readdir(dir)) != NULL) {
        const char *name = entry->d_name;

        if (!show_dotfiles && name[0] == '.') continue;
        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) continue;
        if (should_ignore(name, ignore_list, ignore_count)) continue;

        cur = malloc(sizeof(entry_t));
        cur->name = strdup(name);
        cur->is_dir = (entry->d_type == DT_DIR);
        cur->size = 0;
        cur->next = NULL;

        if (sort_mode == SORT_SIZE && cur->is_dir) {
            char full_path[4096];
            snprintf(full_path, sizeof(full_path), "%s/%s", directory, name);
            cur->size = calculate_size(full_path);
        }

        if (!head || (sort_mode == SORT_ALPHA && strcmp(cur->name, head->name) < 0) ||
            (sort_mode == SORT_SIZE && cur->size < head->size)) {
            cur->next = head;
            head = cur;
        } else {
            iter = head;
            while (iter->next && ((sort_mode == SORT_ALPHA && strcmp(cur->name, iter->next->name) > 0) ||
                                  (sort_mode == SORT_SIZE && cur->size > iter->next->size))) {
                iter = iter->next;
            }
            cur->next = iter->next;
            iter->next = cur;
        }

        count++;
    }

    closedir(dir);

    for (size_t i = 0; head; i++) {
        char *pointer = (head->next == NULL) ? "└── " : "├── ";
        char *segment = (head->next == NULL) ? "    " : "│   ";
        printf("%s%s%s\n", prefix, pointer, head->name);

        if (head->is_dir) {
            char next_dir[4096];
            snprintf(next_dir, sizeof(next_dir), "%s/%s", directory, head->name);

            char next_prefix[4096];
            snprintf(next_prefix, sizeof(next_prefix), "%s%s", prefix, segment);

            walk_directory(next_dir, next_prefix, counter, show_dotfiles, sort_mode, ignore_list, ignore_count);
        } else {
            counter->files++;
        }

        entry_t *temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
}
