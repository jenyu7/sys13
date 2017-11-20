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

  if (f == 0)
    {
      close(p1[WRITE]);
      int num;
      read(p1[READ], num, sizeof(num));
      printf("Reading the number 2 from parent...\n");
      close(p2[READ]);
      num = num + 2 - 1;
      printf("Did quick maths on number, sending back to parent...\n");
      write(p2[WRITE], num, sizeof(num));
    }
  else
    {
      close(p1[READ]);
      int in = 2;
      write(p1[WRITE], in, sizeof(in));
      printf("Sending the number 2 to my child...\n");
      wait(null);
      close(p2[WRITE]);
      int out;
      read(p2[READ], out, sizeof(out));
      printf("Received back the number: %d...", out);
    }
  return 0;
}
