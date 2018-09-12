#include <stdio.h>
#include <stdlib.h>

/*
A cada inser��o de um elemento, a arvore � "vistoriada", analisando-se
o fator de balanceamento de cada n�, caso este n�o esteja no padr�o dese-
jado, parte da �rvore em que encontra este n� tem seus fatores de balan. 
reajustados, possibilitando a cada inser��o um ajuste, e a cada ajuste
a arvore balanceada.
*/

typedef struct arvore{
   int inteiro;
   int fb; //fator de balanceamento he - hd
   struct arvore *esq;
   struct arvore *dir;
}arvore;

arvore *raiz;

//cria uma arvore
arvore *makeTree(int x, int *atualiza){
    raiz = (arvore *)malloc(sizeof(arvore));    
    
    raiz->esq = NULL;    
    raiz->dir = NULL; 
    raiz->inteiro = x;  
    //novo n�, fator de balanceamento � 0.
    raiz->fb = 0;
    *atualiza = 1; 
       
    return raiz;      
}

//Rota��es s�o feitas � direita quando fator de balanceamento � negativo
arvore* RotacoesADireita(arvore *p, int *atualiza){
     arvore *aux1, *aux2;
     
     switch(p->fb){
                 case -1:p->fb = 0;
                         *atualiza = 0; 
                         break; 
                 case 0: p->fb = 1; 
                         break;
                 case 1: aux1 = p->dir;
                          if(aux1->fb == 1){
                              p->dir = aux1->esq;
                              aux1->esq = p;
                              p->fb = 0;
                              p = aux1;
                          }else{
                              aux2 = aux1->esq;
                              aux1->esq = aux2->dir;
                              aux2->dir = aux1;
                              p->dir = aux2->esq;
                              aux2->esq = p;
                                                    
                              if(aux2->fb == 1){
                                  p->fb = -1;
                              }else{
                                  p->fb = 0;
                              }
                              
                              if(aux2->fb == -1){
                                  aux1->fb = 1;
                              }else{
                                  aux1->fb = 0;
                              }
                              
                              p = aux2;
                          }
                          p->fb = 0;
                          *atualiza = 0;  
                          break;
            }
     return(p);
}


//Rota��es s�o feitas � esquerda quando o fator de balanceamento � positivo
arvore* RotacoesAEsquerda(arvore *p, int *atualiza){
     arvore *aux1, *aux2;
     
     switch(p->fb){                 
                 case 1: p->fb = 0;
                         *atualiza = 0; 
                         break;
                 case 0: p->fb = -1; 
                         break;
                 case -1: aux1 = p->esq;
                          if(aux1->fb == -1){
                              p->esq = aux1->dir;
                              aux1->dir = p;
                              p->fb = 0;
                              p = aux1;
                          }else{
                              aux2 = aux1->dir;
                              aux1->dir = aux2->esq;
                              aux2->esq = aux1;
                              p->esq = aux2->dir;
                              aux2->dir = p;
                                                    
                              if(aux2->fb == -1){
                                  p->fb = 1;
                              }else{
                                  p->fb = 0;
                              }
                              
                              if(aux2->fb ==1){
                                  aux1->fb = -1;
                              }else{
                                  aux1->fb = 0;
                              }
                              
                              p = aux2;
                          }
                          p->fb = 0;
                          *atualiza = 0;  
                          break;
            }     
     return(p);
}

//Mostra a arvore AVL
void imprimi(arvore *p){
   if(!raiz){
       printf("** ARVORE VAZIA **\n");
       return;
   }else{      
       //enquanto a lista n�o for "NULL" 
       if(p != NULL){  
         printf("%.2d ", p->inteiro);
         imprimi(p->esq);
         imprimi(p->dir);
       }        
       return;
   }
}

//insere um elemento, e atualiza os fatores de balanceamento.
//caso estes valores estejam fora de padr�o de balanceamento,
//efetua as rota��es para a direita ou esquerda.
arvore* insere(arvore *p, int x, int *atualiza){
    arvore *aux1, *aux2;
    
    if(!p){
        p = makeTree(x, atualiza);
    }else if(x == p->inteiro){
        printf("VALOR JA EXISTENTE!\n\n");        
    //se x for maior que o n� atual, inicia a busca
    //pela direira    
    }else if(x < p->inteiro){
        p->esq = insere(p->esq, x, atualiza);
        if(*atualiza){
            RotacoesAEsquerda(p,atualiza);            
        }
    }else if(x > p->inteiro){
        p->dir = insere(p->dir, x, atualiza);
        if(*atualiza){
            RotacoesADireita(p,atualiza);            
        }
    }       
    return(p);
}

int main(int argc, char *argv[]){
  int vlr, op;
  int atualiza;
    
  printf("Menu: \n1-Inserir\n2-Mostrar\n3-Sair\n");
  printf("---------------------------------------\n");
  while(op!=3){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("Digite um valor: ");
               scanf("%d",&vlr);
               printf("\n");                         
               //cria novo ponto na arvore
               raiz = insere(raiz, vlr, &atualiza);                      
               break;               
       case 2: printf("\n-ARVORE-AVL-----------------pre-ordem--\n");
               imprimi(raiz);
               printf("\n---------------------------------------\n");
               break;               
       default:break;
     }
  } 
  printf("Saindo...\n\n\n");
  
  system("PAUSE");	
  return 0;
}
