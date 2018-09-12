#include <stdio.h>
#include <stdlib.h>

#define T 2
#define MAX_CHAVES 2*T-1
#define MAX_FILHOS 2*T
#define MIN_OCUP T-1

typedef struct arvoreB {
   int num_chaves; //Quantidades de chaves contida no nó
   int chaves[MAX_CHAVES]; //Chaves armazenadas no nó
   struct arvoreB *filhos[MAX_FILHOS]; //Ponteiro para os filhos
}arvoreB;

arvoreB *raiz;

//cria e inicia o novo nó
arvoreB* makeTree(arvoreB *p, int info, arvoreB *fDir){
     arvoreB *novo;
     
     novo = (arvoreB *)malloc(sizeof(arvoreB));
     novo->num_chaves = 1;
     novo->chaves[0] = info;
     novo->filhos[0] = p;
     novo->filhos[1] = fDir;
     
     return (novo);
}

//Insere uma chave e o ponteiro para o filho da direita em um nó
void insere_chave(arvoreB *raiz, int info, arvoreB *fDir){
  int k, pos;

  //busca para obter a posição ideal para inserir a nova chave
  pos = busca_binaria(raiz, info);
  k = raiz->num_chaves;

  //realiza o remanejamento para manter as chaves ordenadas
  while(k>pos && info<raiz->chaves[k-1]){
    raiz->chaves[k] = raiz->chaves[k-1];
    raiz->filhos[k+1] = raiz->filhos[k];
    k--;
  }
  //insere a chave na posição ideal
  raiz->chaves[pos] = info;
  raiz->filhos[pos+1] = fDir;
  raiz->num_chaves++;
}

//Realiza a busca do nó para inserir a chave e faz as subdivisões quando necessárias
//h = ponteiro do valor de altura da arvore
//info_retorno = 
arvoreB *insere(arvoreB *p, int info, int *h, int *info_retorno){
  int i, j, pos, infoMediano; 
  arvoreB *aux, *filho_dir; 

  if(p == NULL){
     *h = 1;
     *info_retorno = info;
     return(NULL);
  }else{
         pos = busca_binaria(p, info);
         if(p->num_chaves > pos && p->chaves[pos] == info){
             printf("---------------------------------------\n");
             printf("INFO %d: JA EXISTENTE!\n", info);
             printf("---------------------------------------\n\n");
             *h = 0;
         }else{
               //desce na árvore até encontrar o nó folha para inserir a chave.
               filho_dir = insere(p->filhos[pos],info,h,info_retorno);
               //Se true deve inserir a info_retorno no nó.
               if(*h!=0){
                  //Tem espaço na página
                   if(p->num_chaves < MAX_CHAVES){
                       insere_chave(p, *info_retorno, filho_dir);
                       *h = 0;
                   //subdivi chaves                   
                   }else{ 
                          aux = (arvoreB *)malloc(sizeof(arvoreB));
                          aux->num_chaves = 0;

                         //inicializa filhos com NULL
                         for(i=0;i<MAX_FILHOS;i++){
                           aux->filhos[i] = NULL;
                         }
                         //elemento mediano que vai subir para o pai
                         infoMediano = p->chaves[MIN_OCUP];

                         //insere metade do nó raiz no temp (efetua subdivisão)
                         aux->filhos[0] = p->filhos[MIN_OCUP+1];
                         
                         for (i=MIN_OCUP+1;i<MAX_CHAVES;i++){
                            insere_chave(aux, p->chaves[i], p->filhos[i+1]);
                         }

                         //atualiza nó raiz. 
                         for(i=MIN_OCUP;i<MAX_CHAVES;i++){
                           p->chaves[i] = 0;
                           p->filhos[i+1] = NULL;
                         }
                         p->num_chaves = MIN_OCUP;

                         //Verifica em qual nó será inserida a nova chave
                         if(pos <= MIN_OCUP){
                             insere_chave(p, *info_retorno, filho_dir);
                         }else{
                             insere_chave(aux, *info_retorno, filho_dir);
                         }

                         //retorna o mediano para inserí-lo no nó pai e o temp como filho direito do mediano.
                         *info_retorno = infoMediano;
                         return(aux);
                       }
                 }
              }
     }
}

//Insere um novo nó na arvoreB
arvoreB *insere_arvoreB(arvoreB *p, int info){
  int h = 0;
  int info_retorno, i;
  arvoreB *filho_dir, *novo;
  
  filho_dir = insere(p, info, &h, &info_retorno);
  //aumenta a altura da árvore
  if(h){
     novo = makeTree(p, info_retorno, filho_dir);  
     
     for(i=2;i<=MAX_CHAVES;i++){
       novo->filhos[i] = NULL;
     }     
     return(novo);
     
   }else{
     return(p);
   }
}

//Realiza a busca na arvore B, de forma binaria em relacao ao vetor chaves
int busca_binaria(arvoreB *p,  int info){ 
  int meio, i, f; 

  i = 0;
  f = p->num_chaves-1;

  while(i <= f){
    meio = (i+f)/2;
    if(p->chaves[meio] == info){
       //retorna a posíção em que a chave está.
       return(meio); 
    }else{
       if(p->chaves[meio] > info){
           f = meio - 1;
       }else{
           i = meio + 1;
       }
    }
  }
  //retorna a posição do ponteiro para o filho.
  return(i); 
}

//Realiza busca na arvoreB
int busca(arvoreB *p, int info){
  arvoreB *no;
  int pos; 

  no = p;
  
  while(no != NULL){
     pos = busca_binaria(no, info);
     if(pos < no->num_chaves && no->chaves[pos] == info){
         return(1);
     }else{
         no = no->filhos[pos];
     }
   }
  return(0);
}

//imprimi valores em ordem crescente
void imprimi(arvoreB *p){
  int i;
  if(p!=NULL){
      for(i=0;i<p->num_chaves;i++){ 
        imprimi(p->filhos[i]);        
        printf("%d ", p->chaves[i]);                   
      }     
      imprimi(p->filhos[i]);          
  }
}

//remove um elemento e reorganiza arvore
arvoreB* remover(arvoreB *p, int info, int h){
  int pos, temp, i;
  arvoreB *aux; 
  
  if(p == NULL){
     h = 1;
     return NULL;
  }else{
         pos = busca_binaria(p, info); //busca o valor na arvore
         if(p->num_chaves > pos && p->chaves[pos] == info){
             for(i=pos;i<MAX_CHAVES;i++){
                  if(p->chaves[i+1]!=0){
                      p->chaves[i] = p->chaves[i+1]; //enfilera os elementos daquela chave
                      p->chaves[i+1]=0;
                  }else{
                      p->chaves[i]=0; //caso seja o ultimo elemento ou se próximo 
                  }                   //não possuir valor.
             }
             p->num_chaves--;         //diminui o número de chaves de p.
             
             
             
             //exibe chave removida e sua posição
             printf("---------------------------------------\n");
             printf("CHAVE %d: EXCLUIDA!\n", info);         
             printf("---------------------------------------\n\n");
             h=0;                          
         }else{
             aux = remover(p->filhos[pos], info, h);                 
         }
  }    
}

//Exibe o elemento e a posição na chave caso esteja estiver na arvore
arvoreB* recuperar(arvoreB *p, int info, int h){
     int pos;
     arvoreB *aux;
     
     if(p == NULL){
         h = 1;         
         return(NULL);
     }else{
         pos = busca_binaria(p, info);
         if(p->num_chaves > pos && p->chaves[pos] == info){
            printf("---------------------------------------\n");
            printf("ENCONTROU %d -> POS: %d\n", info, pos+1);             
            printf("---------------------------------------\n\n"); 
            h = 0;       
         }else{
            aux = recuperar(p->filhos[pos], info, h);        
         }    
     }       
}


int main(int argc, char *argv[]){
  int op;
  int chave;
  
  srand(time(NULL));
    
  printf("Menu: \n1-Inserir\n2-Remover\n3-Recuperar\n4-Mostrar Arvore B\n5-Sair\n");
  printf("---------------------------------------\n");
  while(op!=5){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("Digite um valor: ");
               scanf("%d", &chave);
               printf("\n");   
               raiz = insere_arvoreB(raiz, chave);               
               break;
       case 2: printf("Valor a ser removido: ");
               scanf("%d", &chave);
               printf("\n");
               remover(raiz, chave, 1);   
               break;
       case 3: printf("Valor a ser recuperado: ");
               scanf("%d", &chave);
               printf("\n");
               recuperar(raiz, chave, 1);               
               break;
       case 4: printf("\n-ARVORE-B---------------------ordem----\n");
               if(!raiz){
                   printf("\n** ARVORE VAZIA **\n");       
               }else{
                   imprimi(raiz);
               }
               printf("\n---------------------------------------\n");
               break;       
       default:break;    
     }
  }
  printf("\nSaindo...\n\n\n");  
  
  system("PAUSE");	
  return 0;
}
