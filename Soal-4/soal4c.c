#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int fd1[2];
int fd2[2];

int main()
{
  if (pipe(fd1) == -1){
    exit(1);
  }

  pid_t child = fork();
  if (child == 0) 
  {
    dup2(fd1[1], STDOUT_FILENO);

    close(fd1[0]);
    close(fd1[1]);

    char *argv[] = {"ls", NULL};
        execv("/bin/ls", argv);
  } else {
    dup2(fd1[0], STDIN_FILENO);

    close(fd1[0]);
    close(fd1[1]);

    char *argv[] = {"wc", "-l", NULL};
        execv("/usr/bin/wc", argv);
  }
}