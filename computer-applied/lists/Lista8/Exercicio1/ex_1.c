#include <stdio.h>
#include <stdlib.h>

#define NUM_MAX 20

typedef struct fila{
    int inteiro;
    struct fila *prox;
    struct fila *anter;    
}Fila;

int num_vert, num_ares;
int matAdj1[NUM_MAX][NUM_MAX];
int num[NUM_MAX];
Fila *fi;

//Inicializa a matriz do grafo - adjacencia randomica         
void inicializa(int lin, int col){
   int i,j;
   
   for(i=0;i<lin;i++){
    for(j=0;j<col;j++){
       //somente para os valores da diagonal superior
       //pois estes são iguais para a diagonal inferior
       if(i!=j && i>j){
            matAdj1[i][j] = rand()%2;
            matAdj1[j][i] = matAdj1[i][j]; //atribui o valor para diag. inf.
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
      novo->anter = NULL;
      fi = novo;          
    }else{ 
       aux = fi;              
       while(aux->prox != NULL){
           aux = aux->prox;                      
       }
       aux->prox = novo;         
       novo->anter = aux;       
       novo->prox = NULL;            
    }
}

//exclui elemento da lista
int excluir(){
    Fila *aux;
    int inteir;
    
    if(fi!=NULL && fi->prox != NULL){
      aux = fi;
      fi = aux->prox;
      fi->anter = NULL;
      inteir = aux->inteiro;
      free(aux);
      return inteir;         
    }else if(fi!=NULL && fi->prox == NULL){
      inteir = fi->inteiro;
      fi = NULL;
      free(fi);
      return inteir;
    }else{
      return;
    }    
}

//Efetua a busca em largura
void BuscaEmLargura(){
    int i, v, u;
    i=0;
    //inicia valores de visita
    for(v=0;v<num_vert;v++){
        num[v] = 0;
    }
    v=0; //representação da letra A;   
    while(num[v] == 0){
     num[v] = i++;
     incluir(fi,v);
               
     while(fi != NULL){
        v = excluir();        
        for(u=1;u<num_vert;u++){
          if(matAdj1[v][u]==1){
           if(num[u] == 0){
               num[u] = i++;
               printf("(%d,%d) ",v,u);
               incluir(fi, u);
           }
          }
        }
     }
    }
}

//Busca em profundidade
void Profundidade(int v, int i){
     int u;
     num[v] = i++;
     for(u=1;u<num_vert;u++){
      if(matAdj1[v][u]==1){
         if(num[u] == 0){
            printf("(%d,%d) ",v,u);
            Profundidade(u, i);
         }
      }
     }
}

//inicia busca em profundidade
void BuscaEmProfundidade(){
    int i, v;
    for(v=0;v<num_vert;v++){
        num[v] = 0;
    }
    i=0;
    v=0;//partindo da aresta A
    Profundidade(v,i);        
    return;
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
  int op, i,v;
  srand(time(NULL));
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
  
  inicializa(num_vert, num_ares);
  system("cls");
  printf("---------------------------------------\n"); 
  printf("Menu: \n1-Matriz Adjacencia\n2-Busca Profundidade\n3-Busca Largura\n4-Sair\n");
  printf("---------------------------------------\n");
  while(op!=4){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("\n---------------------------------------\n");
               printf("   MATRIZ DE ADJACENCIA - %d ARESTAS\n\n",num_ares);                        
               imprimi();
               printf("\n---------------------------------------\n");
               break;
       case 2: printf("\n---------------------------------------\n");
               printf("   ADJACENCIA - BUSCA PROFUNDIDADE\n\n");        
               BuscaEmProfundidade();
               printf("\n---------------------------------------\n");
               break;
       case 3: printf("\n---------------------------------------\n");
               printf("     ADJACENCIA - BUSCA LARGURA\n\n");        
               BuscaEmLargura();               
               printf("\n---------------------------------------\n");
               break;
       default:break;    
     }
  }  
  printf("\nSaindo...\n\n\n");
  
  
  system("PAUSE");	
  return 0;
}
