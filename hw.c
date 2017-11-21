#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

/*
 * Jen Yu
 * Systems Pd 10
 * HW #13: Check your pipes for leaks.
 * 2017-11-20
 */

int main()
{
  int READ = 0;
  int WRITE = 1;
  int p1[2];
  int p2[2];
  int f;

  //pipe it up
  pipe(p1);
  pipe(p2);
  f = fork();

  //da parent
  if (!f)
    {
      //no ready
      close(p1[READ]);
      int in = 2;
      printf("[parent] Sending the number %d to my child...\n", in);
      sleep(1);
      //send da numba
      write(p1[WRITE], &in, sizeof(in));
      //no writey
      close(p2[WRITE]);
      int out;
      //read da numba
      read(p2[READ], &out, sizeof(out));
      printf("[parent] Received back the number: %d...\n", out);
      exit(0);
    }
  //james didn't let me write an else statement >:(((((
  //close da write
  close(p1[WRITE]);
  int num;
  //readin is fun
  read(p1[READ], &num, sizeof(num));
  printf("[child] Reading the number %d from parent...\n", num);
  sleep(1);
  close(p2[READ]);
  printf("[child] Doing quick maths: %d + 2 - 1 = ...\n", num);
   num = num + 2 - 1;
  //lol the child kinda dum
  sleep(4);
  printf("[child] Did quick maths on number, sending back to parent...\n");
  sleep(1);
  //send da maths back to mum
  write(p2[WRITE], &num, sizeof(num));
  return 0;
}
