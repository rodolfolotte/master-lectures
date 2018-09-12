#include <stdio.h>
#include <stdlib.h>

#define NUM_MAX 20

typedef struct arvore{
    int nome;
    struct arvore *adj;
    struct arvore *prox;   
}Arvore;

int num_vert;
int matAdj1[NUM_MAX][NUM_MAX];
int matAdj2[NUM_MAX][NUM_MAX];
int num[NUM_MAX];

//Inicializa a matriz do grafo - adjacencia randomica         
void inicializa(){
   int i,j;
   
   srand(time(NULL));

   //o valor do vert é dividido por dois pela 
   for(i=0;i<num_vert;i++){
    for(j=0;j<num_vert;j++){
       //somente para os valores da diagonal superior
       //pois estes são iguais para a diagonal inferior
       //pois não é grafo orientado
       if(i!=j && i>=num_vert/2 && j<num_vert/2){
            matAdj1[i][j] = rand()%2; 
            matAdj2[i][j] = matAdj1[i][j]; 
            matAdj1[j][i] = matAdj1[i][j]; 
            matAdj2[j][i] = matAdj1[i][j];          
       }else{
           matAdj1[i][j] = 0; //diagonal principal
       }
    }  
   } 
}

/*void CasamentoMaximo(){
     int i,j;
     for(i=0;i<num_vert;i++){
        for(j=0;j<num_vert;j++){
           if(matAjd1[i][j]==0){
                 ajustar o nivel de todos os vertices em 0;
                 ajustar o pai de todos os vertices em nulo;
                 //fila=0;
                 ultimo= nulo;
                 v = vertice nao-casado;
                 nivel(v) = 1;
                 incluirNaFila(v);
                 while(fila != 0 $$ ultimo == nulo){
                 v = removerDaFila();
                   if(nivel(v)%2==1){
                              for(todo vertice u ajacente a v tal que nivel(u) == 0){
                                 if(u é nao-casado){
                                      pai(u) = v;
                                      ultimo = u;
                                      break;
                                 }else if(u é casado mas nao com v){
                                       pai(u) = v;
                                       nivel(u) = nivel(v) +1;
                                       incluirNaFila(u);                                   
                                 }
                              }
                          }else{
                              incluirNaFila(vertice u casado com v);
                              pai(u) = v;
                              nivel(u) = nivel(v) + 1;
                          }
                      }
                      if(ultimo != NULL){
                          for(u=ultimo; u!= NULL;u=pai(pai(u)){
                             casadoCom(u) = pai(u);
                             casadoCom(pai(u)) = u;                         
                          }
                      }            
     }
}*/

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

void imprimiGrafo(){
   int i,j;
   
   printf("\n---------------------------------------\n");
   printf("          GRAFO BIPARTIDO \n\n");
                           
   for(i=0;i<num_vert;i++){
    for(j=0;j<num_vert;j++){
        if(matAdj1[i][j]!=0 && i>j){
           printf("(%d,%d)", j+1,i+1);
        }
    }    
   }
   printf("\n");   
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
  //caso seja 0, o grafo é completamente desconexo.
  
  inicializa(num_vert);
  imprimiGrafo();
  printf("---------------------------------------\n"); 
  printf("Menu: \n1-Mtz.Adjacencia\n2-Casamento Maximo\n3-Sair\n");
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
               printf("           CASAMENTO MAXIMO\n\n");  
               //CasamentoMaximo();                           
               printf("\n---------------------------------------\n");
               break;            
       default:break;    
     }
  }   
  printf("\nSaindo...\n\n\n");  
  
  system("PAUSE");	
  return 0;
}
