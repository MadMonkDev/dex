#include <stdio.h>
#include "dex/manual.h"

void show_manual() {
  printf ("dex - Directory Explorer CLI Tool\n");
  printf("=================================\n");
  printf ("\n");
  printf("Usage:\n");
  printf("  dex [options] <directory>\n");
  printf("\n");
  printf("If no directory is specified, current directory is used.\n");
  printf("\n");
  printf("Options:\n");
  printf("  -h, --help             Show this manual.\n");
  printf("  -d, --show-dotfiles    Include hidden files and directories (dotfiles) in the tree.\n");
  printf("  --sort=alpha           Sort directory contents alphabetically (default).\n");
  printf("  --sort=size            Sort directories by total size (recursively).\n");
  printf("  --ignore <name> ...    Ignore specific files/directories. Accepts multiple names.\n");
  printf("  -p, --path <dir>       Explicitly specify the directory path to explore.\n");
  printf("\n");
  printf("Examples:\n");
  printf("  dex                             Show tree of current directory.\n");
  printf("  dex -d                          Show tree including dotfiles.\n");
  printf("  dex --sort=size                 Sort directories by size.\n");
  printf("  dex --ignore build .git        Ignore 'build' and '.git' folders.\n");
  printf("  dex --path ~/Downloads         Explore a given directory.\n");
  printf("\n");
  printf("Description:\n");
  printf("  dex recursively displays a tree-like structure of the specified directory.\n");
  printf("  It supports filtering, sorting, and dotfile visibility options.\n");
  printf("\n");
  printf("Documentation:\n");
  printf("  https://github.com/MadMonkDev/dex\n");
    }
