#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//particiona o vetor de modo que as partes se 
//ordenem
void quickSort(int vec[], int inicio, int fim) {
  int i = inicio;
  int j = fim;
  int aux, pivo;
  
  //obtem pivo aleatorio
  pivo = vec[(int)((rand()%(j-i))+i)];  

  //faz ate que os indices se encontrem
  while(i<j){
      while(vec[i] < pivo){
         i++;      
      }
      while(vec[j] > pivo){
         j--;      
      }
      //se os indices não se cruzam, troca os valores
      if(i<=j){
          aux = vec[i];
          vec[i] = vec[j];
          vec[j] = aux;
          i++;
          j--;
      }
  }
  if(j>inicio){
      //vetor da esquerda 
      quickSort(vec, inicio, j);
  }
  if(i < fim){
      //vetor da direita
      quickSort(vec, i, fim);
  }  
}


int main(int argc, char *argv[]){
  int i;
  int vetor_desord[5000];
  int vetor_parcial_ord[5000];
  clock_t clock1, clock2, clock3, clock4;
  clock_t tempodecorrido1, tempodecorrido2;
  
  srand(time(NULL));
  
  //-------------------INICIA VETORES--------------------------------------
  //inicia vetor com números aleatórios de 0 a 49.999
  for(i=0;i<5000;i++){
     vetor_desord[i] = rand()%50000;                     
  }
  //vetor parcialmente ordenado
  for(i=1;i<=5000;i++){
     vetor_parcial_ord[i] = i;                     
  }
  //preenche algumas posições com valores aleatórios
  for(i=1;i<=5000/3;i++){
     vetor_parcial_ord[i] = rand()%5000;                     
  }
  //------------------------------------------------------------------------
  
  clock1 = clock();
  //ordenamento do vetor por quicksort
  quickSort(vetor_desord, 0, 5000);   
  clock2 = clock();
  
  clock3 = clock();
  //ordenamento do vetor por quicksort
  quickSort(vetor_parcial_ord, 0, 5000);   
  clock4 = clock();
  
  tempodecorrido1 = ((clock2-clock1)/(CLOCKS_PER_SEC/1000));
  tempodecorrido2 = ((clock4-clock3)/(CLOCKS_PER_SEC/1000));
  
  //mostra o ordenamento
  for(i=0;i<5000;i++){
     printf("Pos %d: %d\t", i, vetor_desord[i]);                 
  } 
  
  //mostra o ordenamento
  for(i=0;i<5000;i++){
     printf("Pos %d: %d\t", i, vetor_parcial_ord[i]);                 
  } 
  
  printf("\n---------------------------------------------\n");
  printf("\n----------COMPARATIVO DE EFICIENCIA----------\n");
  printf("\nVetor desordenado, classificou em %d mls.\n", tempodecorrido1);
  printf("Vetor parciamente ordenado, classificou em %d mls.\n", tempodecorrido2);
  printf("\n---------------------------------------------\n"); 
  printf("\n---------------------------------------------\n"); 
  
  //comparativo mostra que mesmo parciamente ordenado o algoritmo
  //tem mesma complexidade, e na MAIORIA das vezes tem a mesma taxa
  //de processamento no ordenamento de vetores totalmente desordenados
  
  system("PAUSE");	
  return 0;
}
