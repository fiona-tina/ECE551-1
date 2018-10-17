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

char step1(struct stat st, char * fileName) {
  printf("  File: ‘%s’\n", fileName);
  char res;
  char * s;
  switch (st.st_mode & S_IFMT) {
    case S_IFBLK:
      s = "block special file\n";
      res = 'b';
      break;
    case S_IFCHR:
      s = "character special file";
      res = 'c';
      break;
    case S_IFDIR:
      res = 'd';
      s = "directory";
      break;
    case S_IFIFO:
      res = 'p';
      s = "fifo";
      break;
    case S_IFLNK:
      res = 'l';
      s = "symbolic link";
      break;
    case S_IFREG:
      res = '-';
      s = "regular file";
      break;
    case S_IFSOCK:
      res = 's';
      s = "socket\n";
      break;
    default:
      res = '?';
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

  return res;
}
void step2_3(char des, struct stat st) {
  char permissions[] = "----------";
  permissions[0] = des;

  permissions[1] = (st.st_mode & S_IRUSR) != 0 ? 'r' : '-';
  permissions[2] = (st.st_mode & S_IWUSR) != 0 ? 'w' : '-';
  permissions[3] = (st.st_mode & S_IXUSR) != 0 ? 'x' : '-';
  permissions[4] = (st.st_mode & S_IRGRP) != 0 ? 'r' : '-';
  permissions[5] = (st.st_mode & S_IWGRP) != 0 ? 'w' : '-';
  permissions[6] = (st.st_mode & S_IXGRP) != 0 ? 'x' : '-';
  permissions[7] = (st.st_mode & S_IROTH) != 0 ? 'r' : '-';
  permissions[8] = (st.st_mode & S_IWOTH) != 0 ? 'w' : '-';
  permissions[9] = (st.st_mode & S_IXOTH) != 0 ? 'x' : '-';
  uid_t uid = st.st_uid;
  gid_t gid = st.st_gid;
  struct passwd * pw;
  struct group * gp;

  pw = getpwuid(uid);
  gp = getgrgid(gid);
  printf("Access: (%04o/%s)  ", st.st_mode & ~S_IFMT, permissions);
  printf("Uid: (%5d/%8s)   Gid: (%5d/%8s)\n", st.st_uid, pw->pw_name, gid, gp->gr_name);
}

void step4(struct stat st) {
  char * timestr = time2str(&st.st_atime, st.st_atim.tv_nsec);
  printf("Access: %s\n", timestr);
  free(timestr);

  timestr = time2str(&st.st_mtime, st.st_mtim.tv_nsec);
  printf("Modify: %s\n", timestr);
  free(timestr);

  timestr = time2str(&st.st_ctime, st.st_ctim.tv_nsec);
  printf("Change: %s\n", timestr);
  free(timestr);

  printf(" Birth: -\n");
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
  char des = step1(st, argv[1]);
  step2_3(des, st);
  step4(st);
}
