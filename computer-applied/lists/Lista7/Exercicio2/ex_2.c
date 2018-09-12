#include <stdio.h>
#include <stdlib.h>

#define NIL -1
#define DEL -2
#define M 100 //número de elementos

/*
Com 100 elementos e valores aleatórios para chaves de 0 a 500
a probabilidade de colisao varia entre 35 a 40%.

Em Porcentagem:
Probabilidade = (Qd Colisões / Qtdade de elementos)*100;

*/

typedef struct No{
    int chave;
    char nome[10];
}No;

No h[M]; //hashing
float probab;

//Cria e inicializa valores da tabela hash
No* makeHash(){
   int i;
   for(i=0;i<M;i++){
      h[i].chave = NIL;
   }
   return h;
}

//cria um novo elemento no conjunto
No *makeNo(int chave, char nome[]){
   No *no;
   no = (No *)malloc(sizeof(No));
   no->chave = chave;
   strcpy(no->nome ,nome);
   return no;
}

//chave hash duplo para tratamento de colisões
int hashing(int k, int i){
    int h1, h2;
    h1 = k%M;
    h2 = 1 + (k%(M-1));
    h2 = h2 * i;
    
    return (h1+h2)%M;
}

//inclui um elemento na tabela hash
int Incluir(No h[], No *elem, int indice){
    int i, j, pos;
            
   for(i=0;i<M;i++){ 
     pos = hashing(elem->chave, indice);
       if(h[pos].chave == NIL){
           printf("Dado: %d,%s -> Pos: %d\n\n",elem->chave, elem->nome,pos);
           h[pos] = *elem;
           return pos;           
       }else{
           printf("\n-------------------------------------\n");
           printf("COLISAO DE CHAVES!");
           printf("\n-------------------------------------\n");
           probab++;
           return;
       }
   }
       
   //procura de pos até o fim do vetor
   //pois as posições anteriores de pos a chave logicamente
   //não exite
   for(i=pos;i<M && h[i].chave!=0;i++){
      if(h[i].chave == elem->chave){
         printf("-------------------------------------\n");
         printf("CHAVE %d JA EXISTENTE!", elem->chave);
         printf("\n-------------------------------------\n\n");
         return;
      }
   }
   //se i é igual a ultima posição
   //e a posição de inserção for igual a 0
   //percorre vetor desde o inicio
   if(i==M && pos>0){
      for(i=0;i<pos && h[i].chave!=0;i++){
         if(h[i].chave == elem->chave){
            printf("-------------------------------------\n");
            printf("CHAVE %d JA EXISTENTE!", elem->chave);
            printf("\n-------------------------------------\n\n");
            return;
         }
      }
      //quando i cruzar com a posição, 
      //Não encontrou o valor
      if(i==pos){
         printf("-------------------------------------\n");
         printf("VALOR NAO ENCONTRADO!");
         printf("\n-------------------------------------\n\n");
         return;
      }      
   }
   printf("-------------------------------------\n");
   printf("TABELA CHEIA!");
   printf("-------------------------------------\n");
   return;  
}

//imprimi chaves e seus respectivos nomes.
void imprimi(){
   int i;
   printf("\n-------------------------------------\n");
   for(i=0;i<M;i++){
      if(h[i].chave!=0){
         printf("%d- %d,%s\n", i+1, h[i].chave, h[i].nome);
      }
   }
   printf("\n-------------------------------------\n\n");
}


int main(int argc, char *argv[]){ 
  int i, chave, op, remov;
  char nome[10]; 
  No *elem;
  probab = 0.0f;
      
  srand(time(NULL)); 
  
  makeHash();
      
  printf("Menu: \n1-Iniciar Simulacao\n2-Mostrar\n3-Prob.Colidir\n4-Sair\n");
  printf("---------------------------------------\n");
  while(op!=5){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: for(i=0;i<M;i++){
                  chave = rand()%500;
                  //nome = 'Rodolfo';
                  elem = makeNo(chave,nome);                  
                  Incluir(h, elem, i);
               }                                                  
               
               break;
       case 2: imprimi();
               break;
       case 3: printf("-------------------------------------\n");
               printf("Prob. de Colidir: %.0f%%", (probab/M)*100);
               printf("\n-------------------------------------\n\n");
               break;           
       default:break;    
     }
  }  
  printf("\nSaindo...\n\n\n");
  
  system("PAUSE");	
  return 0;
}
