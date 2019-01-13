#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <unistd.h>
#include <sys/stat.h>

#include "beargit.h"
#include "util.h"

/* Implementation Notes:
 *
 * - Functions return 0 if successful, 1 if there is an error.
 * - All error conditions in the function description need to be implemented
 *   and written to stderr. We catch some additional errors for you in main.c.
 * - Output to stdout needs to be exactly as specified in the function description.
 * - Only edit this file (beargit.c)
 * - You are given the following helper functions:
 *   * fs_mkdir(dirname): create directory <dirname>
 *   * fs_rm(filename): delete file <filename>
 *   * fs_mv(src,dst): move file <src> to <dst>, overwriting <dst> if it exists
 *   * fs_cp(src,dst): copy file <src> to <dst>, overwriting <dst> if it exists
 *   * write_string_to_file(filename,str): write <str> to filename (overwriting contents)
 *   * read_string_from_file(filename,str,size): read a string of at most <size> (incl.
 *     NULL character) from file <filename> and store it into <str>. Note that <str>
 *     needs to be large enough to hold that string.
 *  - You NEED to test your code. The autograder we provide does not contain the
 *    full set of tests that we will run on your code. See "Step 5" in the homework spec.
 */

/* beargit init
 *
 * - Create .beargit directory
 * - Create empty .beargit/.index file
 * - Create .beargit/.prev file containing 0..0 commit id
 *
 * Output (to stdout):
 * - None if successful
 */

int beargit_init(void) {
  fs_mkdir(".beargit");

  FILE* findex = fopen(".beargit/.index", "w");
  fclose(findex);
  
  write_string_to_file(".beargit/.prev", "0000000000000000000000000000000000000000");

  return 0;
}


/* beargit add <filename>
 * 
 * - Append filename to list in .beargit/.index if it isn't in there yet
 *
 * Possible errors (to stderr):
 * >> ERROR: File <filename> already added
 *
 * Output (to stdout):
 * - None if successful
 */

int beargit_add(const char* filename) {
  FILE* findex = fopen(".beargit/.index", "r");
  FILE *fnewindex = fopen(".beargit/.newindex", "w");

  char line[FILENAME_SIZE];
  while(fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    if (strcmp(line, filename) == 0) {
      fprintf(stderr, "ERROR: File %s already added\n", filename);
      fclose(findex);
      fclose(fnewindex);
      fs_rm(".beargit/.newindex");
      return 3;
    }

    fprintf(fnewindex, "%s\n", line);
  }

  fprintf(fnewindex, "%s\n", filename);
  fclose(findex);
  fclose(fnewindex);

  fs_mv(".beargit/.newindex", ".beargit/.index");

  return 0;
}


/* beargit rm <filename>
 * 
 * See "Step 2" in the homework 1 spec.
 *
 */

int beargit_rm(const char* filename) {
  /* COMPLETE THE REST */
  FILE* findex = fopen(".beargit/.index", "r");
  FILE *fnewindex = fopen(".beargit/.newindex", "w");

  char line[FILENAME_SIZE];
  bool isExist = false;
  while(fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    if (strcmp(line, filename) == 0) {
      isExist = true;
      continue;
    }

    fprintf(fnewindex, "%s\n", line);
  }

  fclose(findex);
  fclose(fnewindex);
  
  if (!isExist) {
    fprintf(stderr, "ERROR: File %s not tracked\n", filename);
    fs_rm(".beargit/.newindex");
    return 1;
  }

  fs_mv(".beargit/.newindex", ".beargit/.index");

  return 0;
}

/* beargit commit -m <msg>
 *
 * See "Step 3" in the homework 1 spec.
 *
 */

const char* go_bears = "GO BEARS!";

int is_commit_msg_ok(const char* msg) {
  /* COMPLETE THE REST */
  u_int32_t i = 0, j = 0;
  
  while(msg[i] != '\0'){
    if (msg[i] == go_bears[j]) {
      j++;
      i++;
      
      if (go_bears[j] == '\0') {
        return 1;
      }
      continue;
    }
    j = 0;
    i++;
  }
  
  return 0;
}

void next_commit_id(char* commit_id) {
  /* COMPLETE THE REST */
  uint32_t i = 0;

  while(commit_id[i] != '\0'){

    switch (commit_id[i]) {
      case '0':
      case 'c':
        commit_id[i] = '6';
        break;
      case '6':
        commit_id[i] = '1';
        goto End;
        break;
      case '1':
        commit_id[i] = 'c';
        goto End;
        break;
      default:
        fprintf(stderr, "ERROR: commit id only contain charactors in ['6', '1', 'c'], origin commit id \"%s\"\n", commit_id);
        break;
    }
    
    i++;
  }

End: return;
}

int beargit_commit(const char* msg) {
  if (!is_commit_msg_ok(msg)) {
    fprintf(stderr, "ERROR: Message must contain \"%s\"\n", go_bears);
    return 1;
  }

  FILE* findex = fopen(".beargit/.index", "r");
  char commit_id[COMMIT_ID_SIZE];
  char commit_dir[FILENAME_SIZE];
  char commit_file[FILENAME_SIZE];
  char tmp1[FILENAME_SIZE];
  char tmp2[FILENAME_SIZE];
  read_string_from_file(".beargit/.prev", commit_id, COMMIT_ID_SIZE);
  next_commit_id(commit_id);

  /* COMPLETE THE REST */
  sprintf(commit_dir, ".beargit/%s", commit_id);
  fs_mkdir(commit_dir);

  sprintf(commit_file, "%s/.index", commit_dir);
  fs_cp(".beargit/.index", commit_file);

  sprintf(commit_file, "%s/.prev", commit_dir);
  fs_cp(".beargit/.prev", commit_file);

  while(fgets(tmp2, sizeof(tmp2), findex)) {
    strtok(tmp2, "\n");
    sprintf(tmp1, "./%s", tmp2);
    sprintf(commit_file, "%s/%s", commit_dir, tmp2);
    fs_cp(tmp1, commit_file);
  }
  fclose(findex);

  sprintf(commit_file, "%s/.msg", commit_dir);
  write_string_to_file(commit_file, msg);

  write_string_to_file(".beargit/.prev", commit_id);

  return 0;
}

/* beargit status
 *
 * See "Step 1" in the homework 1 spec.
 *
 */

int beargit_status() {
  /* COMPLETE THE REST */
  FILE* findex = fopen(".beargit/.index", "r");
  char line[FILENAME_SIZE];
  uint32_t size = 0;

  fprintf(stdout, "Tracked files:\n\n");
  while(fgets(line, sizeof(line), findex)) {
    strtok(line, "\n");
    fprintf(stdout, "  %s\n", line);
    size++;
  }
  fprintf(stdout, "\n%d files total\n", size);

  fclose(findex);

  return 0;
}

/* beargit log
 *
 * See "Step 4" in the homework 1 spec.
 *
 */

void print_beargit_log(char* id) {
  if (strcmp(id, "0000000000000000000000000000000000000000") == 0) {
    return;
  }

  char tmp1[MSG_SIZE];
  char tmp2[FILENAME_SIZE];

  sprintf(tmp2, ".beargit/%s/.msg", id);
  read_string_from_file(tmp2, tmp1, MSG_SIZE);
  fprintf(stdout, "commit %s\n", id);
  fprintf(stdout, "    %s\n\n", tmp1);

  sprintf(tmp2, ".beargit/%s/.prev", id);
  read_string_from_file(tmp2, id, COMMIT_ID_SIZE);
  print_beargit_log(id);
}

int beargit_log() {
  /* COMPLETE THE REST */
  char commit_id[COMMIT_ID_SIZE];

  read_string_from_file(".beargit/.prev", commit_id, COMMIT_ID_SIZE);
  if (strcmp(commit_id, "0000000000000000000000000000000000000000") == 0) {
    fprintf(stderr, "ERROR: There are no commits!\n");
    return 1;
  }
  
  fprintf(stdout, "\n");
  print_beargit_log(commit_id);
  return 0;
}
