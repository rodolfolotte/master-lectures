#include <stdio.h>
#include <stdlib.h>

#define MAX_CLIENTES 100
#define MAX_CAIXAS 5

/*

A fila de clientes (valores) utilizada para N filas
não foi a mesma usada pela fila única, os valores de permanência
foram gerados aleatoriamente novamente para a fila única, 
considerando somente o mesmo número de clientes

Para a visualização dos valores de cada fila, basta retirar as
respectivas linhas comentadas nos métodos push() e pushFilaUnica()

De qualquer forma, mesmo com a mudança de permanencia entre as filas, 
conclui-se que o atendimento por uma unica fila é o ideal em relação 
ao menor tempo de espera

*/

typedef struct fila{
    int chegada, permanencia, saida;
    struct fila *prox;
    struct fila *anter;    
}fila;

float media_tempo_clientes, media_tempo_filas;
int qtd_clientes;

//empilha cliente
void push(fila *fi, fila *novo){    
       
    //se a fila estiver vazia
    if(fi->prox==NULL){
          fi->prox = novo;
          novo->anter = fi;
          novo->chegada = fi->saida;
          novo->permanencia = rand()%5+1;    
          //printf("Chegada: %d",novo->chegada);
          //printf(" Permanencia: %d",novo->permanencia);
          novo->saida = novo->permanencia + novo->chegada;
          //printf(" Saida: %d\n",novo->saida);
    }else{ 
       fila *aux = fi;              
       while(aux->prox != NULL){
           aux = aux->prox;                      
       }
       aux->prox = novo;         
       novo->chegada = aux->saida;
       novo->permanencia = rand()%5+1;  
       //printf("Chegada: %d",novo->chegada);
       //printf(" Permanencia: %d",novo->permanencia);
       novo->saida = novo->permanencia + novo->chegada;
       //printf(" Saida: %d\n",novo->saida);
       novo->anter = aux;       
       novo->prox = NULL;     
    }
}

//empilha cliente
void pushFilaUnica(fila *fi, fila *novo){    
       
    //se a fila estiver vazia
    if(fi->prox==NULL){
          fi->prox = novo;
          novo->anter = fi;
          novo->permanencia = rand()%5+1;
          //printf("Chegada: %d",novo->chegada);  
          //printf(" Permanencia: %d",novo->permanencia);  
          novo->saida = novo->permanencia + novo->chegada;
          //printf(" Saida: %d\n",novo->saida);
    }else{ 
       fila *aux = fi;              
       while(aux->prox != NULL){
           aux = aux->prox;                      
       }
       aux->prox = novo;         
       novo->permanencia = rand()%5+1;  
       //printf("Chegada: %d",novo->chegada);
       //printf(" Permanencia: %d",novo->permanencia);
       novo->saida = novo->permanencia + novo->chegada;
       //printf(" Saida: %d\n",novo->saida);
       novo->anter = aux;       
       novo->prox = NULL;     
    }
}

//retorna fila com menos cliente
int obterMenorFila(fila **fi, int filas){
   int i, cont, menor;
   int cont_fi[filas];
   cont=0;
   fila *aux;
          
   for(i=0;i<filas;i++){
       aux = fi[i];     
       while(aux->prox != NULL){
           cont++;
           aux = aux->prox;                                 
       }  
       cont_fi[i] = cont;
       cont = 0;      
   }   
   //Inicialmente recebe a primeira fila como a menor
   menor = 0;
      
   for(i=0;i<filas;i++){
     if(i!=filas-1){
     //se a fila i for maior que a fila i+1
        if(cont_fi[i] > cont_fi[i+1]){
           menor = i+1;
        }        
     }else{
        break;
     }
   }
   return menor;
}

//N FILAS-----------------------------------------------------------------------
//Simula o atendimento bancário com n filas
//a quantidade de caixas é a mesma para filas
void simulaNFilas(int caixas){
    int i, j, fila_menor;
    
    srand(time(NULL));    
    //declara a qtd de filas encadeadas
    fila *filas[caixas];
    //numero aleatorio de clientes por dia - 0 até 100
    qtd_clientes = rand()%MAX_CLIENTES;
    printf("QTD. CLIENTES: %d - %d Filas\n", qtd_clientes, caixas);
           
    //----INICIALIZA OS VALORES DA FILA (PRIMEIRA POSICAO - LISTHEAD)------
    for(i=0;i<caixas;i++){
        //aloca memoria para a primeira fila
        filas[i] = (fila *)calloc(1,sizeof(fila));
        filas[i]->chegada = 1;
        filas[i]->saida = 1;
    }
    //--------------------------------------------------------------------- 
    //-INSERE OS CLIENTES NA FILA CONFORME SEU TAMANHO---------------------     
        for(j=0;j<qtd_clientes;j++){
           //verifica a menor fila
           fila_menor = obterMenorFila(filas,caixas);
           //system("pause");
           //aloca memoria para o novo cliente da fila
           fila *novo = (fila *)calloc(1,sizeof(fila));           
           //insere na fila
           push(filas[fila_menor],novo);         
           //soma o valor de permanência do cliente
           media_tempo_clientes = media_tempo_clientes + novo->saida;
        }         
    media_tempo_clientes = media_tempo_clientes / qtd_clientes;
    media_tempo_filas = qtd_clientes / caixas;    
}



//FILA UNICA--------------------------------------------------------------------
//Simula o atendimento bancário com fila única
void simulaFilaUnica(int caixas){
    int i, j, k, contad, menor;
    
    contad = 0;
    //declara fila encadeada única
    fila *fil;    
    //declara a qtd de caixas
    fila *caixa[caixas];
    //----INICIALIZA OS VALORES ------------------------------------------------
    media_tempo_clientes = 0.0f;
    media_tempo_filas = 0.0f;
    //aloca memoria para a primeira fila
    fil = (fila *)calloc(1,sizeof(fila));
    //aloca memoria para os caixas
    for(i=0;i<caixas;i++){
        caixa[i] = (fila *)calloc(1,sizeof(fila));                
    }                  
    printf("QTD. CLIENTES: %d\n", qtd_clientes);
    
    //--------------------------------------------------------------------- 
    //-INSERE OS CLIENTES NA FILA CONFORME SEU TAMANHO---------------------     
    //Laço que insere cada cliente no CAIXA, considerando que cada cliente
        for(i=0;i<qtd_clientes;i++){
           //aloca memoria para o novo cliente da fila
           fila *novo = (fila *)calloc(1,sizeof(fila)); 
           //Laço para identificar os caixas disponíveis,
           //determinando assim o valor de chegada de cada 
           //novo elemento inserido na fila
           for(j=0;j<caixas;j++){
              if(caixa[j]->chegada==0){
                 novo->chegada = 1;
                 caixa[j]=novo; 
                 contad = 0;
                 break;                
              }else{
                 contad++;               
                 continue;
              } 
           }      
                       
             //se todos estao ocupados, escolhe aquele 
             //com saida menor  
             if(contad==caixas){
                contad=0;
                menor = 0;
                  for(k=0;k<caixas;k++){
                     if(k!=caixas-1){
                         //obtem o cliente com a saida mais proxima
                         if(caixa[menor]->saida > caixa[k+1]->saida){
                            menor = k+1;
                         }                               
                     }                     
                  }
                  //chegada do novo = saida do ultimo
                  novo->chegada = caixa[menor]->saida;
                  //substitui outro no caixa
                  caixa[menor] = novo;                  
               }      
                   
                           
           //insere na fila
           pushFilaUnica(fil,novo);         
           //soma o valor de permanência do cliente
           media_tempo_clientes = media_tempo_clientes + novo->saida;                    
           
        }          
    media_tempo_clientes = media_tempo_clientes / qtd_clientes;
    media_tempo_filas = qtd_clientes;
}


int main(int argc, char *argv[]){
  int qtd_caixas, qtd_clientes, i;
  
  media_tempo_clientes = 0.0f;
  media_tempo_filas = 0.0f;
  qtd_clientes = 0;
  
  srand(time(NULL));
  
  while(qtd_caixas>MAX_CAIXAS){
      //A quantidade de caixas no banco,
      //é a mesma quatidade de filas.
      printf("\nDigite a quantidade de caixas: ");
      scanf("%d",&qtd_caixas);
  }
  
  printf("\n--SIMULACAO: %d FILA(S)------------------------------------\n", qtd_caixas);
  simulaNFilas(qtd_caixas);
  printf("Media de permanencia na fila/por cliente: %0.2fmin.\n", media_tempo_clientes);
  printf("Tamanho medio das filas: %0.2f", media_tempo_filas);
  printf("\n----------------------------------------------------------");
  printf("\n--SIMULACAO: FILA UNICA-----------------------------------\n");
  simulaFilaUnica(qtd_caixas);
  printf("Media de permanencia na fila/por cliente: %0.2fmin.\n", media_tempo_clientes);
  printf("Tamanho medio das filas: %0.2f", media_tempo_filas);
  printf("\n----------------------------------------------------------\n\n");
  system("PAUSE");	
  return 0;
}
