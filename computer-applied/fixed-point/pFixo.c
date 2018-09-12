#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 500
#define Xinicial 100


/*
Dado psedocódigo:

i = 0
repita até i < max
x_n = ?(x_0 )
Se | f(x_n  ) | < ? ou | x_n- x_0  | < ? então
	Fim
Senão
	x_0 = x_n
i = i + 1
*/

//para fi(x) = 10^6 / log_2(x)
int funcaoConverg(int x){
     int result;
     
     result = pow(10,6) / log2(x);
     return result;
}

//método do ponto fixo
void pontoFixo(){   
  int x0 = Xinicial;
  int xN; 
  int par = 1e-05;  
  int i = 1;
  
  while(i<=N){
     xN  = funcaoConverg(x0);
     if(abs(xN - x0)< par){
        break;
     }else{
        x0 = xN;
        i++;
     }   
  }
  printf("Raiz Aproximada: %d\n\n", xN);
}

int main(int argc, char *argv[]){
 
  pontoFixo();  
  
  system("PAUSE");	
  return 0;

}
