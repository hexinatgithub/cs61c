/**
 * This file contains functionality to parse command line arguments. Do not modify!
 */

#include <stdio.h>
#include <string.h>

#include <unistd.h>
#include <sys/stat.h>

#include "beargit.h"

int check_initialized(void) {
  struct stat s;
  int ret_code = stat(".beargit", &s);
  return !(ret_code == -1 || !(S_ISDIR(s.st_mode)));
}

int check_filename(const char* filename) {
  if (strlen(filename) > FILENAME_SIZE-1 || strlen(filename) == 0)
    return 0;

  if (filename[0] == '.')
    return 0;

  struct stat s;
  int ret_code = stat(filename, &s);
  return (ret_code != -1 && !(S_ISDIR(s.st_mode)));
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [<args>]\n", argv[0]);
        return 2;
    }

    // TODO: If students aren't going to write this themselves, replace by clean
    // implementation using function pointers.
    if (strcmp(argv[1], "init") == 0) {

      if (check_initialized()) {
        fprintf(stderr, "ERROR: Repository is already initialized\n");
        return 1;
      }

      return beargit_init();

    } else {

        if (!check_initialized()) {
            fprintf(stderr, "ERROR: Repository is not initialized\n");
            return 1;
        }

        if (strcmp(argv[1], "add") == 0 || strcmp(argv[1], "rm") == 0) {

          if (argc < 3 || !check_filename(argv[2])) {
            fprintf(stderr, "ERROR: No or invalid filname given\n");
            return 1;
          }

          if (strcmp(argv[1], "rm") == 0) {
            return beargit_rm(argv[2]);
          } else {
            return beargit_add(argv[2]);
          }

        } else if (strcmp(argv[1], "commit") == 0) {

          if (argc < 4 || strcmp(argv[2], "-m") != 0) {
            fprintf(stderr, "ERROR: Need a commit message (-m <msg>)\n");
            return 1;
          }

          if (strlen(argv[3]) > MSG_SIZE-1) {
            fprintf(stderr, "ERROR: Message is too long!\n");
            return 1;
          }

          return beargit_commit(argv[3]);

        } else if (strcmp(argv[1], "status") == 0) {
            return beargit_status();
        } else if (strcmp(argv[1], "log") == 0) {
            return beargit_log();
        } else {
            fprintf(stderr, "ERROR: Unknown command \"%s\"\n", argv[1]);
            return 1;
        }
    }
}
