#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
  int READ = 0;
  int WRITE = 1;
  int p1[2];
  int p2[2];
  int f;

  pipe(p1);
  pipe(p2);
  f = fork();

  if (!f)
    {
      close(p1[READ]);
      int in = 2;
      printf("[parent] Sending the number %d to my child...\n", in);
      sleep(1);
      write(p1[WRITE], &in, sizeof(in));
      //wait(null);
      close(p2[WRITE]);
      int out;
      read(p2[READ], &out, sizeof(out));
      printf("[parent] Received back the number: %d...\n", out);
      exit(0);
    }
  close(p1[WRITE]);
  int num;
  read(p1[READ], &num, sizeof(num));
  printf("[child] Reading the number %d from parent...\n", num);
  sleep(1);
  close(p2[READ]);
  num = num + 2 - 1;
  printf("[child] Doing quick maths: %d + 2 - 1 = ...\n", num);
  sleep(4);
  printf("[child] Did quick maths on number, sending back to parent...\n");
  sleep(1);
  write(p2[WRITE], &num, sizeof(num));
  return 0;
}
