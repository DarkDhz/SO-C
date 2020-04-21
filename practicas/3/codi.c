#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

void alarma(){
}

void sisgur(int signo) {
  //printf("Hey he rebut un avis!\n");

}

void secondsCounter() {
	
}

int main(void)
{
  int fd[2];
  int id[2];
  int ret;
  pipe(fd);

  ret = fork();

  if (ret == 0) { // hours
    //waiting parent to start...
    signal(SIGUSR1, sisgur);
    pause();

    int h = 0;
    while (1) {
        signal(SIGUSR2, sisgur);
       
        int * xd = pause();
        printf("%d\n", *xd);
        printf("Ha pasat una hora ya bro\n");
        h = h+1;
      }
  } else { // 
    id[0] = ret;
    ret = fork();
    if (ret == 0) { // minutes 
      //waiting parent to start...
      signal(SIGUSR1, sisgur);
      pause(); 

      int m = 59;
      while (1) {
        signal(SIGUSR2, sisgur);
        pause(); 
        m = m+1;
        printf("%d\n", m);
        if ((m % 60) == 0) {
          m = 0;
          kill(id[0], SIGUSR2);
        }
      }
    } else {
      id[1] = ret;
      ret = fork();
      if (ret == 0) { // seconds
        //waiting parent to start...
        signal(SIGUSR1, sisgur);
        pause();

        int s = 55;
        
        while(1) {    
          alarm(1);     
          signal(SIGALRM, alarma);
          pause(); 
          s = s+1;
          if ((s % 60) == 0) {
            s = 0;
            kill(id[1], SIGUSR2);
          }
        }
      } else { //PARENT
        printf("Benvingut soc el pare y el meu id es: %d\n", getpid());
        //printf("%d:%d:%d\n", h, m, s);
        signal(SIGUSR1, sisgur);
        pause();
        kill(ret, SIGUSR1);
        kill(id[1], SIGUSR1);
        kill(id[0], SIGUSR1);
        while(1) {
          signal(SIGUSR1, sisgur);
          pause(); 
          kill(ret, SIGUSR1);
          printf("HEY 2\n");
        }
        
        
      }
    }
  }

  return 0;
}
