
#include "dex.h"

void dex_func(const char *path, int depth, long *size);

int main (int argc, char *argv[]) {
  
  if (argc < 2) {
    fprintf(stderr, "Usage : %s <directory>\n", argv[0]);
    return 1;
  }

  long size = 0;
  printf ("  %s\n", argv[1]);
  dex_func(argv[1], 1, &size);
  printf ("\nTotal size : %.2ld KB\n", size);

  return 0;
}

void dex_func(const char *path, int depth, long *size) {

  DIR *dir = opendir(path);
  if (!dir) {
    perror("opendir");
    return;
  }

  struct dirent *entry;
  entry = readdir(dir);
  while (entry != NULL) {

    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;

    char fullpath[PATH_MAX];
    snprintf(fullpath, sizeof(fullpath), "%s%s", path, entry->d_name);

    for (int index = 0; index < depth; ++index)
      printf("  ");

    struct stat statics;
    if (stat(fullpath, &statics) == -1) {
      perror("stat");
      continue;
    }

    if (S_ISDIR(statics.st_mode)) {
      printf("  %s\n", entry->d_name);
      dex_func(fullpath, depth + 1, size);
      *size += statics.st_size;
    } else if (S_ISREG(statics.st_mode)) {
      float kb = statics.st_size / 1024.0;
      printf("  %s size : %f\n", entry->d_name, kb);
      size += statics.st_size;
    }

    closedir(dir);
  }
}

