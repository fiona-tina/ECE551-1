#include <ctype.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t = localtime(when);
  strftime(temp1, 512, "%Y-%m-%d %H:%M:%S", t);
  strftime(temp2, 32, "%z", t);
  snprintf(ans, 128, "%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

void step1(struct stat st, char * fileName) {
  printf("  File: ‘%s’\n", fileName);

  char * s;
  switch (st.st_mode & S_IFMT) {
    case S_IFBLK:
      s = "block special file\n";
      break;
    case S_IFCHR:
      s = "character special file";
      break;
    case S_IFDIR:
      s = "directory";
      break;
    case S_IFIFO:
      s = "fifo";
      break;
    case S_IFLNK:
      s = "symbolic link";
      break;
    case S_IFREG:
      s = "regular file";
      break;
    case S_IFSOCK:
      s = "socket\n";
      break;
    default:
      s = "unknow file";
      break;
  }
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
         st.st_size,
         st.st_blocks,
         st.st_blksize,
         s);

  printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
         st.st_dev,
         st.st_dev,
         st.st_ino,
         st.st_nlink);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "There should have two args");
    exit(EXIT_FAILURE);
  }
  struct stat st;

  if (lstat(argv[1], &st) == -1) {
    perror("stat");
    exit(EXIT_FAILURE);
  }
  step1(st, argv[1]);
}
