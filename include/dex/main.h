#ifndef MAIN_H
#define MAIN_H

#define VERSION_DEX "0.0.10a"

typedef enum {
    SORT_ALPHA,
    SORT_SIZE
} sort_mode_t;

void parse_arguments(int argc, char *argv[], const char **path,
                     int *show_dotfiles, sort_mode_t *sort_mode,
                     char ***ignore_list, int *ignore_count);

#endif
