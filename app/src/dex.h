
/* All Header files */
#include <cstddef>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

typedef struct size_count {
  size_t dir;
  size_t files;
} count_t ;

typedef struct entry_dir {
  char *dir_name;
  bool is_dir;
  struct entry_dir *next;
} entry_t ;


