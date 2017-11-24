#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

#define DIMC_VERSION "0.050"

extern int opterr;

int main (int argc, char *argv[]) {
  int opt;

  bool use_post_copy = false;
  char *output_file_path;
  char *input_file_path;

  opterr = 0;

  while ((opt = getopt(argc, argv, "Vco:")) != -1) {
    switch(opt) {
      case 'c':
        use_post_copy = true;
        break;

      case 'o':
        output_file_path = optarg;
        break;

      case 'V':
        printf("dimc version %s\n", DIMC_VERSION);
        exit(0);

      case '?':
        if (optopt == 'o')
          fprintf(stderr, "Option -%c requires an argument\n", optopt);
        else
          fprintf(stderr, "Unknown option -%c\n", optopt);
        return 1;

      default:
        fprintf(stderr, "Usage: %s [-c] [-o output_file] input_file\n", argv[0]);
        exit(1);
    }
  }

  if (optind >= argc) {
    fprintf(stderr, "One input file is required..");
    exit(1);
  } else {
    input_file_path = argv[optind];
  }

  if (use_post_copy == true)
    printf("Post-process copy is on\n");

  printf("Input file: %s\n", input_file_path);
  printf("Output file: %s\n", output_file_path);

  FILE *input_file, *output_file;

  input_file = fopen(input_file_path, "r");

  if (input_file == NULL) {
    fprintf(stderr, "Can't open source file %s\n", input_file_path);
    exit(1);
  }

  fseek(input_file, 0, SEEK_END);
  long in_file_size = ftell(input_file);
  fseek(input_file, 0, SEEK_SET);

  char *in_file_content = malloc(in_file_size);
  fread(in_file_content, 1, in_file_size, input_file);

  fclose(input_file);

  /*output_file = fopen(output_file_path, "w");

  if (output_file == NULL) {
    fprintf(stderr, "Can't open destination file %s\n", output_file_path);
    exit(1);
  }*/


  char *line;
  line = strtok(in_file_content, "\r\n");
  while (line != NULL) {
    printf("%s\n", line);
    line = strtok(NULL, "\r\n");
  }

}