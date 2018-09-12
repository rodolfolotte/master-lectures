#include <stdio.h>
#include <stdlib.h>

#define MAX_VETOR 100

/*
Não há validação de inputs, ou seja, se receber um int
onde é requerido char, possivelmente haverá erros

*/

typedef struct arvore{
   char chave;
   int prior;
   struct arvore *pai;
   struct arvore *esq;
   struct arvore *dir;
}arvore;

arvore *raiz;

//cria uma arvore
arvore *makeTree(char x){
    raiz = (arvore *)calloc(1,sizeof(arvore));    
    
    raiz->pai = NULL;
    raiz->esq = NULL;    
    raiz->dir = NULL; 
    raiz->chave = x; 
    raiz->prior = rand()%MAX_VETOR;
          
    return raiz;      
}

//insere folha lado esquerdo
int setLeft(arvore *p, char x){
    arvore *novo = (arvore *)calloc(1,sizeof(arvore));
    novo->chave = x;
    novo->dir = NULL;
    novo->esq = NULL;    
    novo->pai = p;
    novo->prior = rand()%MAX_VETOR;
    p->esq = novo;    
}

//insere folha lado direito
int setRight(arvore *p, char x){
    arvore *novo = (arvore *)calloc(1,sizeof(arvore));
    novo->chave = x;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = p;
    novo->prior = rand()%MAX_VETOR;
    p->dir = novo;
}

//retorna a posição para alocar
int buscaPosicao(arvore *p, char x){
    //se e o nó for null
    if(p==NULL){
       return 0;
    }
    
    if(x == p->chave){
        printf("CHAVE JA EXISTENTE!\n\n");  
        return 1; 
    //se x for maior que o nó atual, inicia a busca
    //pela direira    
    }else if(x > p->chave){
        if(buscaPosicao(p->dir,x) == 0){
           //aloca p
           setRight(p,x);
           return 1;
        }
    //se x for menor que o nó atual, inicia a busca
    //pela esquerda       
    }else if(x < p->chave){
        if(buscaPosicao(p->esq, x) == 0){
           //aloca p
           setLeft(p,x);
           return 1;
        }
    }   
    return 1;
}

//Mostra a arvore em Pré-Ordem
void imprimi(arvore *p){
   if(!raiz){
       printf("---------------------------------------\n");
       printf("** ARVORE VAZIA **\n");
       printf("---------------------------------------");
       return;
   }else{      
       //enquanto a lista não for "NULL" 
       if(p != NULL){           
         printf("%c,%.2d ", p->chave, p->prior); 
         imprimi(p->esq);                  
         imprimi(p->dir);                 
       }        
       return;
   }

}

//Ordena heapMinimo
arvore* HeapMin(arvore *q){
    arvore *e, *d, *menor;
    arvore *aux;

    if(q != NULL){ 
            
      q->esq = HeapMin(q->esq);
      q->dir = HeapMin(q->dir);
                     
        if(q->esq != NULL){
              if(q->esq->prior < q->prior){
                     if(q->dir == NULL){
                        aux  = q->esq;
                        q->esq = aux->dir;
                        aux->dir = q;
                        q = aux;          
                     }else if(q->dir->prior > q->esq->prior){
                        aux  = q->esq;
                        q->esq = aux->dir;
                        aux->dir = q;
                        q = aux;   
                     }else{
                        aux = q->dir;
                        q->dir = aux->esq;
                        aux->esq = q;
                        q = aux;
                     }
                  }          
        }
        if(q->dir != NULL){
                  if(q->dir->prior < q->prior){
                           aux = q->dir;
                           q->dir = aux->esq;
                           aux->esq = q;
                           q = aux;
                  }          
        }
    }
   return q;      
}
 


int main(int argc, char *argv[]){
  int op;
  int chave;
  
  srand(time(NULL));
    
  printf("Menu: \n1-Inserir\n2-Mostrar\n3-HeapMin\n4-Sair\n");
  printf("---------------------------------------\n");
  while(op!=4){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("Digite uma letra: ");
               scanf("%s",&chave);
               printf("\n");
                         
               //se ainda não houver arvore, cria uma               
               if(!raiz){
                  raiz = makeTree(chave);                               
               }else{
                  buscaPosicao(raiz,chave);                                       
               }                                          
               break;
       case 2: printf("\n---------------------------------------\n");
               imprimi(raiz);
               printf("\n---------------------------------------\n");
               break;
       case 3: raiz = HeapMin(raiz);
               printf("\n---------------------------------------\n");
               imprimi(raiz);
               printf("\n---------------------------------------\n");
       default:break;    
     }
  }
  printf("\nSaindo...\n\n\n");  
  
  system("PAUSE");	
  return 0;
}
