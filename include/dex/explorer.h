#ifndef EXPLORER_H
#define EXPLORER_H

#include "main.h"

typedef struct {
    int files;
    int dirs;
} counter_t;

void walk_directory(const char* path, const char* prefix, counter_t* counter,
                    int show_dotfiles, sort_mode_t sort_mode,
                    char **ignore_list, int ignore_count);

#endif
