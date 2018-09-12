#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cont;
int tam_pequeno;

//algoritmo de ordenação por seleção
void ordenacaoSelec(int v[], int inicio, int fim){
     int k, aux;
     int menor, posicao, marcador;
     clock_t t_inic, t_final;
     cont=0;
     
     t_inic = clock();    
     
     marcador = inicio;
     while (marcador < fim-1){
        menor = v[marcador];
        posicao = marcador;
        for(k=marcador+1;k<fim;k++){
            if(v[k]<menor){
               menor = v[k];
               posicao = k;
            }
        }
        aux = v[marcador];
        v[marcador] = v[posicao];
        v[posicao] = aux;        
        marcador++;     
     }
     t_final = clock();
     //sel[cont] = ((t_final-t_inic)/(CLOCKS_PER_SEC/1000));
     
         
}

//define o tamanho do subvetor, de modo que sua ordenação
//seja mais eficiente como método seleção do que pelo método quicksort
int obtemTamanhoSubVec(clock_t t1[], clock_t t2[]){
    int i = 1;
    int pos;
    /*do{
       if(t2[i]<t1[i]){
         pos = i;
         i++;
       }
    }while(t1[i]!=null || t2[i]!=null);*/
   return 50;//pos;
}


//particiona o vetor de modo que as partes se ordenem
//o terceiro argumento diz respeito ao tipo de ordenação
//1-somente quicksort
//2-hibrida
void quickSort(int vec[], int inicio, int fim, int tipo_ord){
  int i = inicio;
  int j = fim;
  int aux, pivo;
  clock_t t_inic, t_final;  
  
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
  
  switch(tipo_ord){
     case 1:  if(j>inicio){
                  t_inic = clock();
                  //vetor da esquerda 
                  quickSort(vec, inicio, j, 1); 
                  t_final = clock();
                  //mp[cont] = ((t_final-t_inic)/(CLOCKS_PER_SEC/1000));    
                  cont++;
              }
              if(i<fim){
                  t_inic = clock();
                  //vetor da direita
                  quickSort(vec, i, fim, 1);                  
                  t_final = clock();
                  //mp[cont] = ((t_final-t_inic)/(CLOCKS_PER_SEC/1000));    
                  cont++;
              }break;
              //Definido o menor número de um subvetor, tal que este seja mais
              //eficientemente classificado pelo método de seleção,
              //classifica:  
     case 2: if(j>inicio && inicio<=tam_pequeno){
                  //vetor da esquerda com método de ordenação
                  ordenacaoSelec(vec, inicio, j); 
              }else if(j>inicio){     
                  //vetor da esquerda 
                  quickSort(vec, inicio, j, 2);     
              }
              if(i<fim && (fim-i)<=tam_pequeno){
                  //vetor da esquerda com método de ordenação
                  ordenacaoSelec(vec, i, fim); 
              }else if(i<fim){     
                  //vetor da esquerda 
                  quickSort(vec, i, fim, 2);     
              }       
              break; 
     default: break;   
  }
  
}


int main(int argc, char *argv[]){
  int i;
  int vetor_desord[5000];
  int vetor_desord2[5000];
  int vetor_desord3[5000];
  
  //clock_t t_quicksort[10000];
  //clock_t t_selecao[10000];
   
  srand(time(NULL));
  
  //-------------------INICIA VETORES--------------------------------------
  //inicia vetor com números aleatórios de 0 a 49.999
  for(i=0;i<5000;i++){
     vetor_desord[i] = rand()%5000;   
     //mesmos valores para os tres vetores
     vetor_desord2[i] = vetor_desord[i];
     vetor_desord3[i] = vetor_desord[i];                    
  }
  
  //------------------------------------------------------------------------
  
  //ordenamento do vetor por quicksort
  quickSort(vetor_desord, 0, 5000, 1);  
  //ordenamento do vetor por quicksort
  ordenacaoSelec(vetor_desord2, 0, 5000);   
  
  int pos = obtemTamanhoSubVec(t_quicksort, t_selecao);
  tam_pequeno = pos;
  
  //ordenamento do vetor por quicksort
  quickSort(vetor_desord3, 0, 5000, 2);
  
  //mostra o ordenamento
  for(i=0;i<5000;i++){
     printf("Pos %d: %d\t", i, vetor_desord[i]); 
  } 
    
  printf("\n---------------------------------------------------------------------\n");
  printf("\n----------------------COMPARATIVO DE EFICIENCIA----------------------\n");
  printf("A estrategia hibrida e mais eficiente para subvetores com tamanho: %d", pos);
  printf("\n---------------------------------------------------------------------\n");
  printf("\n---------------------------------------------------------------------\n");  
  system("PAUSE");	
  return 0;
}
