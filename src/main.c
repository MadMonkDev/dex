#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wordexp.h>
#include "dex/main.h"
#include "dex/explorer.h"
#include "dex/manual.h"

int main(int argc, char *argv[]) {
    const char *raw_path = NULL;
    int show_dotfiles = 0;
    sort_mode_t sort_mode = SORT_ALPHA;
    char **ignore_list = NULL;
    int ignore_count = 0;

    parse_arguments(argc, argv, &raw_path, &show_dotfiles, &sort_mode, &ignore_list, &ignore_count);

    if (!raw_path) {
        raw_path = ".";
    }

    wordexp_t expanded;
    if (wordexp(raw_path, &expanded, 0) != 0 || expanded.we_wordc < 1) {
        fprintf(stderr, "Failed to expand path: %s\n", raw_path);
        return 1;
    }

    const char *path = expanded.we_wordv[0];

    if (access(path, F_OK) != 0) {
        fprintf(stderr, "Directory does not exist: %s\n", path);
        wordfree(&expanded);
        return 1;
    }

    counter_t counter = {0, 0};
    printf("%s\n", path);
    walk_directory(path, "", &counter, show_dotfiles, sort_mode, ignore_list, ignore_count);
    printf("\n%d directories, %d files\n", counter.dirs, counter.files);

    wordfree(&expanded);
    free(ignore_list);
    return 0;
}

void parse_arguments(int argc, char *argv[], const char **path,
                     int *show_dotfiles, sort_mode_t *sort_mode,
                     char ***ignore_list, int *ignore_count) {
    *ignore_list = malloc(sizeof(char*) * 256);
    *ignore_count = 0;

    int in_ignore_mode = 0;
    int ignore_end_index = -1;

    for (int i = 1; i < argc; i++) {
        
        if ((strcmp(argv[i], "-h") == 0) || (strcmp(argv[i], "--help") == 0)) {
            show_manual();
            exit(0);
        }
        
        else if ((strcmp(argv[i], "-v") == 0) || (strcmp(argv[i], "--version") == 0)) {
            printf("dex version %s\n", VERSION_DEX);
            exit(0);
        } 
        
        else if ((strcmp(argv[i], "-d") == 0) || (strcmp(argv[i], "--show-dotfiles") == 0)) {
            *show_dotfiles = 1;
            in_ignore_mode = 0;
        }
        
        else if ((strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--path") == 0 || strcmp(argv[i], "--dir") == 0) && i + 1 < argc) {
            *path = argv[++i];
            in_ignore_mode = 0;
        }
        
        else if (strncmp(argv[i], "--sort=", 7) == 0) {
            const char *val = argv[i] + 7;
            if (strcmp(val, "size") == 0)
                *sort_mode = SORT_SIZE;
            else if (strcmp(val, "alpha") == 0)
                *sort_mode = SORT_ALPHA;
            else {
                fprintf(stderr, "Invalid sort mode: %s\n", val);
                exit(1);
            }
            in_ignore_mode = 0;
        } else if (strcmp(argv[i], "--ignore") == 0 || strcmp(argv[i], "-i") == 0) {
            in_ignore_mode = 1;
            ignore_end_index = i; // track start of ignore list
        } else if (argv[i][0] == '-') {
            in_ignore_mode = 0;
        } else if (in_ignore_mode) {
            wordexp_t we;
            if (wordexp(argv[i], &we, 0) == 0 && we.we_wordc > 0) {
                (*ignore_list)[(*ignore_count)++] = strdup(we.we_wordv[0]);
                wordfree(&we);
            } else {
                (*ignore_list)[(*ignore_count)++] = strdup(argv[i]);
            }
        }
    }

    // If path wasn't explicitly set with -p/--path/--dir,
    // try to auto-detect the last argument as path
    if (*path == NULL) {
        for (int i = argc - 1; i >= 1; i--) {
            if (argv[i][0] == '-') continue;

            // Check if it's already in ignore_list
            int is_ignored = 0;
            for (int j = 0; j < *ignore_count; j++) {
                if (strcmp(argv[i], (*ignore_list)[j]) == 0) {
                    is_ignored = 1;
                    break;
                }
            }

            if (!is_ignored) {
                *path = argv[i];
                break;
            }
        }
    }
}
