
#include <dex/main.h>

int main (int argc, char* argv[]) {

  if (argc <= 1) {
    explorer(".");
    return 0;
  }

  for (int argi = 1; argi < argc; argi++) {
    if (strcmp(argv[argi], "-h") == 0 || strcmp(argv[argi], "--help") == 0 || (strcmp(argv[argi], "man")) == 0) 
      manual();
    else if (strcmp(argv[argi], "-v") == 0 || strcmp(argv[argi], "--version") == 0)
        printf ("version ===> %s\n", VERSION);
    else 
      explorer(argv[argi]);
  }
  return 0;
}
