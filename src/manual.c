
#include <dex/manual.h>

void manual(void) {
    FILE *fp = fopen(MANUAL_PATH, "r");
    if (!fp) {
        perror("Could not open manual");
        return;
    }

    int ch;
    while ((ch = fgetc(fp)) != EOF) {
        putchar(ch);
    }
    fclose(fp);
}
