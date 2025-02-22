// copia del archivo e21.c

#include <stdio.h>
#include <time.h>

int main(){
  clock_t v1;
  clock_t v2;
  double total;
  
  v1 = clock();
  for(int i=0;i<1000000;i++){
    printf("Iteracion I: %d\n", i);
  }
  for(int j=0;j<1000000;j++){
    printf("Iteracion J: %d\n", j);
  }
  for(int k=0;k<1000000;k++){
    printf("Iteracion K: %d\n", k);
  }
  v2 = clock();
  
  total = (double)v2 - (double)v1;
  
  printf("Duracion %f segundos\n", total/CLOCKS_PER_SEC);
  
  return(0);
}
