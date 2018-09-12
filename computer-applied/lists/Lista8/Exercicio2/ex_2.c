#include <stdio.h>
#include <stdlib.h>

#define INFINITO 9999
#define NUM_MAX 20

typedef struct fila{
    int inteiro;
    struct fila *prox;   
}Fila;

int num_vert, num_ares;
int matAdj1[NUM_MAX][NUM_MAX];
int num[NUM_MAX];

Fila *faltaVerif;

//Inicializa a matriz do grafo - adjacencia randomica         
void inicializa(int lin, int col){
   int i,j;
   
   for(i=0;i<lin;i++){
    for(j=0;j<col;j++){
       //somente para os valores da diagonal superior
       //pois estes são iguais para a diagonal inferior
       if(i!=j){
            matAdj1[i][j] = rand()%10;            
       }else if(i==j){
           matAdj1[i][j] = 0; //diagonal
       }
    }  
   }
}

//inclui elemento na lista de visita
void incluir(Fila *f, int u){
    Fila *aux;
    Fila *novo = (Fila *)malloc(1*sizeof(Fila)); 
    novo->inteiro = u;

    if(!f){
      novo->prox = NULL;
      faltaVerif = novo;          
    }else{ 
       aux = faltaVerif;              
       while(aux->prox != NULL){
           aux = aux->prox;                      
       }
       aux->prox = novo;         
       novo->prox = NULL;            
    }
}

//exclui elemento da lista
int excluir(){
    Fila *aux;
    int inteir;
    
    if(faltaVerif!=NULL && faltaVerif->prox != NULL){
      aux = faltaVerif;
      faltaVerif = aux->prox;      
      inteir = aux->inteiro;
      free(aux);
      return inteir;         
    }else if(faltaVerif!=NULL && faltaVerif->prox == NULL){
      inteir = faltaVerif->inteiro;
      faltaVerif = NULL;
      free(faltaVerif);
      return inteir;
    }else{
      return;
    }    
}

int menor(){
    Fila *aux;
    int menor;
    
    aux = faltaVerif;
    menor = aux->inteiro;
    
    while(aux->prox != NULL){
       if(menor > aux->prox->inteiro){
          menor = aux->prox->inteiro;
       }       
       aux = aux->prox;                      
    }
    return menor;
}

void AlgoritmoDijkstra(int vert){
    int v,u;
    printf("       V  U\n");
    for(v=0;v<num_vert;v++){
       num[v] = INFINITO;    
    }
    
    num[vert]=0;
    
    for(v=0;v<num_vert;v++){
       incluir(faltaVerif,v);    
    }    
    
    while(faltaVerif!=NULL){
       //v = vertice de FaltaVerificar com menor valor[v];
       v = menor();
       //excluir v de FaltaVerifivar;
       excluir();             
       for(u=0;u<num_vert;u++){
          if(matAdj1[v][u]!=0){
             if(num[u] > (num[v] + matAdj1[v][u])){
                 num[u] = num[v] + matAdj1[v][u];
                 printf("      (%d->%d)-Peso:%d\n", v, u,matAdj1[v][u]);                 
             }
          }
       }
    }

}


//Exibi a matriz de adjacencia do grafo
void imprimi(){
   int i,j;
   
   //Apenas para teste e melhor vizualização
   //até 10 vertices...
   for(i=0;i<num_vert;i++){
      switch(i){
         case 0: printf(" A  ");break;
         case 1: printf(" B  ");break;
         case 2: printf(" C  ");break;
         case 3: printf(" D  ");break;
         case 4: printf(" E  ");break;
         case 5: printf(" F  ");break;
         case 6: printf(" G  ");break;
         case 7: printf(" H  ");break;
         case 8: printf(" I  ");break;
         case 9: printf(" J  ");break;
         default: break;
      }     
   }
   printf("\n");
   
   for(i=0;i<num_vert;i++){
    for(j=0;j<num_vert;j++){
        printf(" %d |", matAdj1[i][j]);
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
  printf("Menu: \n1-Mtz.Adj.\n2-Menor caminho\n3-Sair\n");
  printf("---------------------------------------\n");
  while(op!=3){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("\n---------------------------------------\n");
               printf("   MATRIZ DE ADJACENCIA - %d ARESTAS\n\n",num_ares);                        
               imprimi();
               printf("\n---------------------------------------\n");
               break;
       case 2: printf("\n---------------------------------------\n");
               printf("        CAMINHO PERCORRIDO\n\n");  
               AlgoritmoDijkstra(0);                           
               printf("\n---------------------------------------\n");
               break;       
       default:break;    
     }
  }   
  printf("\nSaindo...\n\n\n");
  
  
  system("PAUSE");	
  return 0;
}
