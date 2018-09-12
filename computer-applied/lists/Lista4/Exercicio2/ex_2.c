#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{
   int inteiro;
   struct arvore *pai;
   struct arvore *esq;
   struct arvore *dir;
}arvore;

arvore *raiz;

//cria uma arvore
arvore *makeTree(int x){
    raiz = (arvore *)calloc(1,sizeof(arvore));    
    
    raiz->pai = NULL;
    raiz->esq = NULL;    
    raiz->dir = NULL; 
    raiz->inteiro = x;    
       
    return raiz;      
}


//insere folha lado esquerdo
int setLeft(arvore *p, int x){
    arvore *novo = (arvore *)calloc(1,sizeof(arvore));
    novo->inteiro = x;
    novo->dir = NULL;
    novo->esq = NULL;    
    novo->pai = p;
    p->esq = novo;    
}

//insere folha lado direito
int setRight(arvore *p, int x){
    arvore *novo = (arvore *)calloc(1,sizeof(arvore));
    novo->inteiro = x;
    novo->dir = NULL;
    novo->esq = NULL;
    novo->pai = p;
    p->dir = novo;
}

//retorna a posição para alocar
int buscaPosicao(arvore *p, int x){
    //se e o nó for null
    if(p==NULL){
       return NULL;
    }
    
    if(x == p->inteiro){
        printf("VALOR JA EXISTENTE!\n\n");  
        return 1; 
    //se x for maior que o nó atual, inicia a busca
    //pela direira    
    }else if(x > p->inteiro){
        if(buscaPosicao(p->dir,x) == NULL){
           //aloca p
           setRight(p,x);
           return 1;
        }
    //se x for menor que o nó atual, inicia a busca
    //pela esquerda       
    }else if(x < p->inteiro){
        if(buscaPosicao(p->esq, x) == NULL){
           //aloca p
           setLeft(p,x);
           return 1;
        }
    }   
    return 1;
}

//Mostra a arvore em Pré-Ordem
void mostraPreOrdem(arvore *p){
   if(!raiz){
       printf("---------------------------------------\n");
       printf("** ARVORE VAZIA **\n");
       printf("---------------------------------------\n");
       return;
   }else{      
       //enquanto a lista não for "NULL" 
       if(p != NULL){  
         printf("%.2d ", p->inteiro);
         mostraPreOrdem(p->esq);
         mostraPreOrdem(p->dir);
       }        
       return;
   }

}

//Mostra a arvore em ordem
void mostraOrdem(arvore *p){   
   if(!raiz){
       printf("---------------------------------------\n");
       printf("** ARVORE VAZIA **\n");
       printf("---------------------------------------\n");
       return;
   }else{
     if(p != NULL){
         mostraOrdem(p->esq);
         printf("%.2d ", p->inteiro);
         mostraOrdem(p->dir);
     }
     return;
   }   
}

//Mostra a arvore em PosOrdem
void mostraPosOrdem(arvore *p){
     if(!raiz){
       printf("---------------------------------------\n");
       printf("** ARVORE VAZIA **\n");
       printf("---------------------------------------\n");
       return;
   }else{
     if(p != NULL){
         mostraPosOrdem(p->esq);
         mostraPosOrdem(p->dir);
         printf("%.2d ", p->inteiro);
     }
     return;
   }            
}
     


int main(int argc, char *argv[]){
  int op, vlr;
    
  printf("Menu: \n1-Inserir\n2-Mostrar\n3-Sair\n");
  printf("---------------------------------------\n");
  while(op!=3){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("Digite um valor: ");
               scanf("%d",&vlr);
               printf("\n");
                         
               //se ainda não houver arvore, cria uma               
               if(!raiz){
                  raiz = makeTree(vlr);                                
               }else{
                  buscaPosicao(raiz,vlr);                      
               }
               break;
       case 2: printf("\n  .4-Pre-Ordem\n  .5-Ordem\n  .6-Pos-Ordem\n\n>: ");
               scanf("%d",&op);
               printf("\n");
                   if(op==4){
                     printf("-PRE-ORDEM-----------------------------\n");
                     mostraPreOrdem(raiz);
                     printf("\n---------------------------------------\n");
                   }else if(op==5){
                     printf("-ORDEM---------------------------------\n");
                     mostraOrdem(raiz);
                     printf("\n---------------------------------------\n");
                   }else{
                     printf("-POS-ORDEM-----------------------------\n");
                     mostraPosOrdem(raiz);
                     printf("\n---------------------------------------\n");
                   }               
               break;
       default:break;    
     }
  }
  system("PAUSE");	
  return 0;
}












