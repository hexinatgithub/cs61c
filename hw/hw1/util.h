/**
 * This file contains utility functions to use in the homework. Do not modify!
 */
#include <stdlib.h>

#define ASSERT_ERROR_MESSAGE(fn, msg) \
  if (!(fn)) { \
    fprintf(stderr, "\n        *** AN ERROR OCCURRED IN %s ***\n\n", __func__); \
    fprintf(stderr, "  This should not happen. Most likely, you tried to access\n"); \
    fprintf(stderr, "  or manipulate a file that doesn't exist, or create one\n"); \
    fprintf(stderr, "  that already does. You should first try to delete the\n"); \
    fprintf(stderr, "  .beargit directory and start over; maybe a previous run\n"); \
    fprintf(stderr, "  corrupted it. If not, you need to fix the problem in\n"); \
    fprintf(stderr, "  your program -- the following error message might give\n"); \
    fprintf(stderr, "  more information about what went wrong:\n\n"); \
    fprintf(stderr, "  Error in %s: %s\n\n", __func__, msg); \
    exit(1); \
  }

int is_sane_path(const char* path) {
  if (strlen(path) > 512)
    return 0;

  // Only allow modifying files in .beargit directory
  const char* prefix = ".beargit";
  if (strncmp(prefix, path, strlen(prefix)) != 0)
    return 0;

  return 1;
}

static void fs_mkdir(const char* dirname) {
  ASSERT_ERROR_MESSAGE(dirname != NULL, "dirname is not a valid string");
  ASSERT_ERROR_MESSAGE(is_sane_path(dirname), "dirname is not a valid path within .beargit");
  int ret = mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  ASSERT_ERROR_MESSAGE(ret == 0, "creating directory failed");
}

static void fs_rm(const char* filename) {
  ASSERT_ERROR_MESSAGE(filename != NULL, "filename is not a valid string");
  ASSERT_ERROR_MESSAGE(is_sane_path(filename), "filename is not a valid path within .beargit");
  int ret = unlink(filename);
  ASSERT_ERROR_MESSAGE(ret == 0, "deleting/unlinking file failed");
}

static void fs_mv(const char* src, const char* dst) {
  ASSERT_ERROR_MESSAGE(src != NULL, "src is not a valid string");
  ASSERT_ERROR_MESSAGE(dst != NULL, "dst is not a valid string");
  ASSERT_ERROR_MESSAGE(is_sane_path(src), "src is not a valid path within .beargit");
  ASSERT_ERROR_MESSAGE(is_sane_path(dst), "dst is not a valid path within .beargit");
  int ret = rename(src, dst);
  ASSERT_ERROR_MESSAGE(ret == 0, "renaming file failed");
}

static void fs_cp(const char* src, const char* dst) {
  ASSERT_ERROR_MESSAGE(src != NULL, "src is not a valid string");
  ASSERT_ERROR_MESSAGE(dst != NULL, "dst is not a valid string");
  ASSERT_ERROR_MESSAGE(is_sane_path(dst), "dst is not a valid path within .beargit");

  FILE* fin = fopen(src, "r");
  ASSERT_ERROR_MESSAGE(fin != NULL, "couldn't open source file");
  FILE* fout = fopen(dst, "w");
  ASSERT_ERROR_MESSAGE(fout != NULL, "couldn't open destination file");

  char buffer[4096];
  int size;

  while ((size = fread(buffer, 1, 4096, fin)) > 0) {
    fwrite(buffer, 1, size, fout);
  }

  fclose(fin);
  fclose(fout);
}

static void write_string_to_file(const char* filename, const char* str) {
  FILE* fout = fopen(filename, "w");
  ASSERT_ERROR_MESSAGE(fout != NULL, "couldn't open file");
  fwrite(str, 1, strlen(str)+1, fout);
  fclose(fout);
}

static void read_string_from_file(const char* filename, char* str, int size) {
  FILE* fin = fopen(filename, "r");
  ASSERT_ERROR_MESSAGE(fin != NULL, "couldn't open file");
  int real_size = fread(str, 1, size, fin);
  fclose(fin);
}

