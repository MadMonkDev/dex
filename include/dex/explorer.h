
// include/dex/explorer.h
#ifndef EXPLORER_H
#define EXPLORER_H

void explorer(void);

#endif

/* All Header files */
#include <stdio.h>
#include <string.h>
#include <dirent.h>

typedef struct size_count {
  size_t dir;
  size_t files;
} count_t ;

typedef struct entry_dir {
  char *dir_name;
  int is_dir;
  struct entry_dir *next;
} entry_t ;


