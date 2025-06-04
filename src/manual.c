#include <stdio.h>
#include "dex/manual.h"

void show_manual(const char *path) {
    FILE *file = fopen(path, "r");
    if (!file) {
        perror("Failed to open manual file");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}
