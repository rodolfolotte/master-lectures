#include <stdio.h>
#include <stdlib.h>

/*

Se encontrar algum parentese aberto: empilha, caso
encontre um fechado: desempilha um parentese aberto. 
De modo que um anule o outro. Caso ocarra de haver mais
parenteses fechados do que aberto, não havendo mais elementos
para desempilhar, a expressao ja é considerada incorreta.

*/

typedef struct pilha{
   char info;
   struct pilha *prox;   
}pilha;

pilha *pil; 

//empilha parentese aberto
void push(pilha *p, char in){
    pilha *aux; 
    pilha *novo = (pilha *)calloc(1,sizeof(pilha));
    novo->info = in;
    
    if(!pil){
        novo->prox = NULL;
        pil = novo;       
    }else{
        aux = pil;
        novo->prox = aux;
        pil = novo;                        
    }
}

//desempilha parentese aberto
void pop(pilha *p){   
   pilha *aux;
   
   if(!pil){
      push(p,')');
      return;
   }else{
      aux = pil;
      pil = aux->prox;
      //desaloca memória
      free(aux);
   }  
}

//verifica se a expressão tem o mesmo número de parentese (aberto e fechado)
//se tiver, a expressão é considerada bem formada!
int verificaExpressao(char expr[]){
   int i;
   
   for(i=0;i<strlen(expr);i++){
      if(expr[i]=='('){
         push(pil,'(');      
      }else if(expr[i]==')'){
         pop(pil);         
      }     
   }   
  
   if(!pil){
      return 0;
   }else{
      return 1;
   }   
}


int main(int argc, char *argv[]){
  char expr[10];
  char op;

      printf("Entre com a expressao: ");
      scanf("%s", &expr);
             
      printf("\n-----------------------------------------\n");
      if(verificaExpressao(expr)){
          printf("PARENTESE EM EXCESSO!");
          printf("\nEXPRESSAO MAL FORMADA");
      }else{
          printf("EXPRESSAO BEM FORMADA");
      }
      printf("\n-----------------------------------------");
      printf("\n\n");
  
  
  system("PAUSE");	
  return 0;
}
