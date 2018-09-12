#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//efetua a busca binária
int buscaBinaria(int v[], int x, int meio, int fim){
   
   if(meio > fim){
      return -1;
   }else{
      int m;
      m = (meio + fim)/2;
        
      if(v[m]==x){return m;}
      if(v[m]<x){return buscaBinaria(v,x,m+1,fim);}
      if(v[m]>x){return buscaBinaria(v,x,meio,m-1);}      
   }  
}

//faz a troca de posições
void Troca(int *v, int *k){
  //variavel auxiliar
  int t;  
  //aponta para o valor de troca
  t = *v;
  //recebe o valor menor
  *v = *k;
  //posicao do valor menor recebe valor maior
  *k = t;
}

//ordena o vetor
void ordenarVetor(int v[], int n){
    int i,k;
    int limite = n-1;
    int ultima_troca;
    
    while(limite > 0){
       ultima_troca = 0;
       for(k=0;k<limite;k++){
          if(v[k]>v[k+1]){
             Troca(&v[k],&v[k+1]);
             ultima_troca = k;
          }
       }
       limite = ultima_troca;
    }
    
    printf("\n----------------------------------\n");
    for(i=0;i<n;i++){
      printf("%d ", v[i]);
    }
    printf("\n----------------------------------\n\n");    
    
}   

int main(int argc, char *argv[]){
  int n, i, x;
    
  srand(time(NULL));
  
  printf("Digite a quantidade de elementos: ");
  scanf("%d",&n);
  
  int vetor[n];
  
  printf("\n----------------------------------\n");
  for(i=0;i<n;i++){
     vetor[i] = rand()%300;
     printf("%d ", vetor[i]);
  }
  printf("\n----------------------------------\n"); 
  
  ordenarVetor(vetor, n);
  
  printf("Digite o valor de busca: ");
  scanf("%d",&x);
  
  printf("\nEsta na %da posicao no vetor", buscaBinaria(vetor, x, 0, n-1)+1);
  printf("\n\n");
  
  system("PAUSE");
  return 0;  
}
