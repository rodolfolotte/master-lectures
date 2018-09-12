#include <stdio.h>
#include <stdlib.h>

#define NUM_MAX 20

typedef struct arvore{
    int nome;
    struct arvore *adj;
    struct arvore *prox;   
}Arvore;

int num_vert, num_ares;
int matAdj1[NUM_MAX][NUM_MAX];
int matAdj2[NUM_MAX][NUM_MAX];
int num[NUM_MAX];


//Inicializa a matriz do grafo - adjacencia randomica         
void inicializa(int lin, int col){
   int i,j;
      
   for(i=0;i<lin;i++){
    for(j=0;j<col;j++){
       //somente para os valores da diagonal superior
       //pois estes são iguais para a diagonal inferior
       if(i!=j && i>j){
            matAdj1[i][j] = rand()%15; 
            matAdj2[i][j] = matAdj1[i][j]; 
            matAdj1[j][i] = matAdj1[i][j]; 
            matAdj2[j][i] = matAdj1[i][j];          
       }else if(i==j){
           matAdj1[i][j] = 0; //diagonal principal
       }
    }  
   }
}

//atualiza a linha de uma matriz, atribuindo 0 para os
//valores diferente do menor
void atualizaMatriz(int menor[]){
     int i, j;
     for(i=0;i<num_vert;i++){
         for(j=0;j<num_vert;j++){
            if(matAdj2[i][j]!= menor[i]){
                matAdj2[i][j]= 0;             
            }else{                
                matAdj2[j][i]= 0; 
                menor[i]=0;                                
            }
         }
     }
}

void AlgoritmoBoruvka(){
     int i, j;
     int menor[num_vert];
     
     //obtem o menor valor de cada linha da matriz
     for(i=0;i<num_vert;i++){
        menor[i] = 100; 
        for(j=0;j<num_vert;j++){                               
           if(matAdj2[i][j]!=0){                            
               if(menor[i] > matAdj2[i][j]){               
                  menor[i] = matAdj2[i][j];                                                         
               }
           }
        }                        
     }
     
     atualizaMatriz(menor);
     
     //exibi a arvore de espalhamento  
     for(i=0;i<num_vert;i++){
        for(j=0;j<num_vert;j++){
            if(matAdj2[i][j]!=0){
                 printf("(%d,%d) Peso: %d\n", i,j,matAdj2[i][j]);
            //}else if(){
            //     printf("(%d,%d) Peso: %d\n", i,j,matAdj2[i][j]);
            }
        }     
     }       
}

//http://perkinsg.tripod.com/c_source_code/kruskal.c
/*void AlgoritmoKruskal(){
  int i;
   
  while (num_edges < N - 1){
      a = E[next_edge][0];
      b = E[next_edge][1];
      
      i = find(a);
      j = find(b);
      
      if(!equal(i, j)){  merge (i, j);
         F[num_edges][0] = E[next_edge][0];
         F[num_edges][1] = E[next_edge][1];
         F[num_edges][2] = E[next_edge][2];
         num_edges++;
         
         test_univ();
      }      
      next_edge++;
   }
   
   printf("F = (");
   for(i=0;i<N-1;i++){
      printf("(V%d,V%d)", F[i][0], F[i][1]);
      if(i<N-2){
         printf(", ");
      }      
   }
   printf(")\n");  
}

//http://www.cs.sunysb.edu/~skiena/392/programs/prim.c
void AlgoritmoPrim(){
     arvore *p;
     p = makeTree();
     aresta = sequencia de arestas de A ordenadas pelo peso;
     
     for(i=0;i<|V|-1;i++){
           for(j=0;j<|A|;j++){
               if((aresta[j] nao forma um ciclo em arvore) && (aresta[j] e incidente a um vertice de arvore)){
                  arvore = arvore ¾ aresta[j];
                  break;
               }
           }     
     }
}

http://w3.ualg.pt/~hshah/algoritmos/aula2mstdijkstra.html
void AlgoritmoDijkstra(){}
*/

//Exibi a matriz de adjacencia do grafo
void imprimi(){
   int i,j;
   
   //Apenas para teste e melhor vizualização
   //até 10 vertices...
   for(i=0;i<num_vert;i++){
      switch(i){
         case 0: printf("  A  ");break;
         case 1: printf("  B  ");break;
         case 2: printf("  C  ");break;
         case 3: printf("  D  ");break;
         case 4: printf("  E  ");break;
         case 5: printf("  F  ");break;
         case 6: printf("  G  ");break;
         case 7: printf("  H  ");break;
         case 8: printf("  I  ");break;
         case 9: printf("  J  ");break;
         default: break;
      }     
   }
   printf("\n");
   
   for(i=0;i<num_vert;i++){
    for(j=0;j<num_vert;j++){
        printf(" %02d |", matAdj1[i][j]);
    }
    printf("\n");
   }
}


int main(int argc, char *argv[]){
  int op, i;
  
  do{
      printf("\n Digite a qtd. de vertices: ");
      scanf("%d",&num_vert);
      if(num_vert<=0){
          printf("\n---------------------------------------\n");
          printf("QTD.DE ARESTAS DEVE SER SUPERIOR A 0\n");                    
          printf("---------------------------------------\n");
      }
  }while(num_vert<=0);
  system("cls");
  do{
      printf("\n Digite a qtd. de arestas: ");
      scanf("%d",&num_ares);
      if(num_ares<0){
          printf("\n---------------------------------------\n");
          printf("QTD.DE ARESTAS DEVE SER SUPERIOR ");          
          printf("OU IGUAL A 0");
          printf("---------------------------------------\n");
      }
  }while(num_ares<0); //caso seja 0, o grafo é completamente desconexo.
  
  inicializa(num_vert,num_ares);
  system("cls");
  printf("---------------------------------------\n"); 
  printf("Menu: \n1-Mtz.Adj.\n---ARVORE DE ESPALHAMENTO MINIMO---\n");
  printf("2-Algoritmo Boruvka\n4-Algoritmo Kruskal\n5-Algoritmo Prim\n5-Algoritmo Dijkstra\n6-Sair\n");
  printf("---------------------------------------\n");
  while(op!=6){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("\n---------------------------------------\n");
               printf("          MATRIZ DE ADJACENCIA \n\n");                        
               imprimi();
               printf("\n---------------------------------------\n");
               break;
       case 2: printf("\n---------------------------------------\n");
               printf("           AEM - BORUVKA\n\n");  
               AlgoritmoBoruvka();                           
               printf("\n---------------------------------------\n");
               break; 
       case 3: printf("\n---------------------------------------\n");
               printf("           AEM - KRUSKAL\n\n");  
               //AlgoritmoKruskal();                           
               printf("\n---------------------------------------\n");
               break;
       case 4: printf("\n---------------------------------------\n");
               printf("           AEM - PRIM\n\n");  
               //AlgoritmoPrim();                           
               printf("\n---------------------------------------\n");
               break;  
       case 5: printf("\n---------------------------------------\n");
               printf("           AEM - DIJKSTRA\n\n");  
               //AlgoritmoDijkstra();                           
               printf("\n---------------------------------------\n");    
       default:break;    
     }
  }   
  printf("\nSaindo...\n\n\n");
  
  
  system("PAUSE");	
  return 0;
}
