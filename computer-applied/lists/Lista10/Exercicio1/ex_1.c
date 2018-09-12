#include <stdio.h>
#include <stdlib.h>

#define NUM_MAX 20
#define INFINITO 1000000
#define WHITE 0
#define GRAY 1
#define BLACK 2

typedef struct arvore{
    int nome;
    struct arvore *adj;
    struct arvore *prox;   
}Arvore;

int num_vert;
int num_ares;
int capacidade[NUM_MAX][NUM_MAX];
int fluxo[NUM_MAX][NUM_MAX];
int num[NUM_MAX];
int cor[NUM_MAX]; 
int pred[NUM_MAX];  // vetor q armazena o caminho

int min(int x, int y){
    return x<y ? x : y;  //retorna minimo de x e y
}

int head,tail;
int q[NUM_MAX+2];

void push(int x){
    q[tail] = x;
    tail++;
    cor[x] = GRAY;
}

int pop(){
    int x = q[head];
    head++;
    cor[x] = BLACK;
    return x;
}

//Inicializa a matriz do grafo - adjacencia randomica         
void inicializa(){
   int i,j;
   
   srand(time(NULL));

   //o valor do vert é dividido por dois pela 
   for(i=0;i<num_vert;i++){
    for(j=0;j<num_vert;j++){
       if(i!=j){
            capacidade[i][j] = rand()%10; 
            fluxo[i][j] = capacidade[i][j];             
       }else{
           capacidade[i][j] = 0; //diagonal principal
           fluxo[i][j] = 0;
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
        printf(" %02d |", capacidade[i][j]);
    }
    printf("\n");
   }
}

int rotula(int start, int target){
    int u,v;
    
    for(u=0;u<num_vert;u++){
       cor[u] = WHITE;
    }
       
    head = tail = 0;
    push(start);
    pred[start] = -1;
    
    while(head!=tail){
	u = pop();
        
    	for(v=0;v<num_vert;v++){
    	    if(cor[v]==WHITE && capacidade[u][v]-fluxo[u][v]>0) {
    		push(v);
    		pred[v] = u;
    	    }
        }
    }
    
    return cor[target]==BLACK;
}


int AlgoritmoFordFulkerson(int fonte, int destino){
     int fluxo_max = 0;
     int i, j, u;
     
    //ajustar o fluxo de todas as arestas e vert para 0
    for(i=0;i<num_vert;i++){
  	   for(j=0;j<num_vert;j++){
           fluxo[i][j] = 0;
       }
    }
    
    while(rotula(fonte,destino)){
        
    	int incrementa = INFINITO;
    	
    	for(u=num_vert-1;pred[u]>=0;u=pred[u]){
    	    incrementa = min(incrementa,capacidade[pred[u]][u]-fluxo[pred[u]][u]);
    	}
    
    	for(u=num_vert-1;pred[u]>=0;u=pred[u]){
    	    fluxo[pred[u]][u] += incrementa;
    	    fluxo[u][pred[u]] -= incrementa;
    	}
    	    fluxo_max += incrementa;
    }
 
    return fluxo_max;
     /*rotulo(f) = (vazio,infinito);
     rotulados = f;
     
     while(rotulados!=0){
         retire um vertice v de rotulados;
         for(todos os vert u não rotulados adjac a v){
            if(direto(vu) && folga(vu) > 0){
               rotulo(u) = (v+, min(qf(v), folga(vu));
            }else if(contrario(vu) && fluxo(vu)>0){
               rotulo(u) = (v-, min(qf(v), fluxo(vu));               
            }
            
            if(u recebe um rótulo){
                 if(qf(d)>0){
                    AumentarFluxo(caminho de f ate d);
                 }
              rotulados = (f);
            }else{
              rotulados = rotulados + u;
            }
         }
     }*/
}

/*void AumentarFluxo(caminho C){
       for(cada aresta a pertencente a C){
          if(direto(a)){
             f(a) = f(a) + qt(d);
          }else{
             f(a) = f(a) - qt(d);
          }
       }
}*/

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
      printf("\n Digite a qtd. de vertices: ");
      scanf("%d",&num_vert);
      if(num_vert<=0){
          printf("\n---------------------------------------\n");
          printf("QTD.DE ARESTAS DEVE SER SUPERIOR A 0\n");                    
          printf("---------------------------------------\n");
      }
  }while(num_vert<=0);
  system("cls");
  //caso seja 0, o grafo é completamente desconexo.
  
  inicializa(num_vert);
  
  printf("---------------------------------------\n"); 
  printf("Menu: \n1-Mtz.Adjacencia\n2-Fluxo Maximo\n3-Sair\n");
  printf("---------------------------------------\n");
  while(op!=3){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("\n---------------------------------------\n");
               printf("          MATRIZ DE ADJACENCIA \n\n");                        
               imprimi();
               printf("\n---------------------------------------\n");
               break;
       case 2: printf("\n---------------------------------------\n");
               printf("           FORD-FULKERSON\n\n");  
               AlgoritmoFordFulkerson(0,num_vert-1);                       
               printf("\n---------------------------------------\n");
               break;            
       default:break;    
     }
  }   
  printf("\nSaindo...\n\n\n");
  
  system("PAUSE");	
  return 0;
}
