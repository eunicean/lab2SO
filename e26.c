#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  pid_t pt1,pt2,pt3;
  clock_t inicio, fin;
  double tiempo;
  
  inicio = clock();
  pt1 = fork(); // proceso hijo
  
  if(pt1 == 0){ // si es 0 estoy dentro del hijo
    pt2 = fork(); // proceso nieto creado desde el hijo
    if(pt2 == 0){ // dentro del nieto
      pt3 = fork(); // proceso bisnieto
      if(pt3 == 0){ // dentro del bisnieto
        for(int i=0; i<1000000; i++){}
      }
      else{
        for(int i=0; i<1000000; i++){}
        wait(NULL);
      }
    }
    else{
      for(int j=0; j<1000000; j++){}
      wait(NULL);
    }
  }
  else{
    wait(NULL);
    fin = clock();
    tiempo = (double)(fin-inicio);
    printf("Tiempo: %f\n", tiempo);
  }
  
  return(0);
}
