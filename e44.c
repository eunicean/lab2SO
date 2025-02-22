#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

int main(){
  pid_t p = fork();
  clock_t inicio, fin;
  double tiempo;
  
  inicio = clock();
  if(p==0) for(int i=0;i<1600000; i++) printf("%d\n",i);
  else while(1);
  fin = clock();
  tiempo = (double)(fin-inicio);
  printf("Tiempo: %f segundos\n", tiempo/CLOCKS_PER_SEC);
  
  return(0);
}
