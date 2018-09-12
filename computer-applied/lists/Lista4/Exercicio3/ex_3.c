#include <stdio.h>
#include <stdlib.h>

typedef struct arvore{
   int balde1, balde2;
   struct arvore *pai;
   struct arvore *filho;
   struct arvore *irmao;   
}arvore;

//------------------------------------------------------------------
//váriaveis globais
int cap1, cap2, estado;
arvore *raiz;
arvore *solucao;
//------------------------------------------------------------------

//cria uma arvore
void makeTree(){
    //aloca espaço na memória
    raiz = (arvore *)calloc(1,sizeof(arvore));  
    //inicia valores
    raiz->pai = NULL;
    raiz->filho = NULL;    
    raiz->irmao = NULL; 
    raiz->balde1 = 0;    
    raiz->balde2 = 0;        
}

//insere uma nova folha(possibilidade) na arvore
void insere(arvore *p, int bal1, int bal2){
    arvore *novo_no;
    novo_no = (arvore *)calloc(1,sizeof(arvore));
        
  if(pertence(p, cap1, cap2)){
    return;
  }else{    
    novo_no->balde1 = bal1;
    novo_no->balde2 = bal2;
    novo_no->pai = p;
    novo_no->filho = NULL;
    novo_no->irmao = NULL;
    
    if(p->filho == NULL){
       p->filho = novo_no;
    }else{
       p = p->filho;
    }
    
    while(p->irmao != NULL){
      p = p->irmao;
    }    
    p->irmao = novo_no;    
  }      
}

//verifica se ja houve ocorrencia da possibilidade
int pertence(arvore *p, int bal1, int bal2){
    //system("pause");
    arvore *h;
    if(p->balde1==bal1 && p->balde2==bal2){
       return 1;
    }else{
       for(h=p->filho;h!=NULL;h=h->irmao){
           if(pertence(h,bal1,bal2)){
              return 1;
           }
       }
       return 0;   
    }    
}

//transfere conteudo do balde2 para balde1
int transferir21(arvore *p){
    printf("T1 - %d,%d\n", p->balde1, p->balde2);
   int transf;
   //se o balde 2 não tiver conteudo e o balde 1 não tiver capacidade
   if(p->balde2==0 || p->balde1==cap1){
      return 0;
   }else{
      //transf = capacidade atual
      transf = cap1 - p->balde1;
      //se a capacidade for menor
      if(transf <= p->balde2){
         p->balde2 = p->balde2 - transf;  
         p->balde1 = p->balde1 + transf;
      }else{
         p->balde1 = p->balde1 + p->balde2;
         p->balde2 = 0;
      }     
   }
}

//transfere conteudo do balde1 para balde2
int transferir12(arvore *p){
   printf("T2 - %d,%d\n", p->balde1, p->balde2);
   int transf;
   
   //se o balde 2 tiver conteudo e o balde 1 capacidade
   if(p->balde1==0 || p->balde2==cap2){
      return 0;
   }else{
      //transf = capacidade atual
      transf = cap2 - p->balde2;
      //não tem capacidade
      if(transf==0){
         return 0;      
      }else if(transf > p->balde1){
         //balde2 recebe o que tinha no balde1
         p->balde2 = p->balde2 + p->balde1;         
         return 1;
      }else if(transf <= p->balde1){
         p->balde1 = (p->balde1-transf);  
         p->balde2 = p->balde2 + transf;
         return 1;
      }
   }
}

//enche balde1
int enche1(arvore *p){
    printf("E1 - %d,%d\n", p->balde1, p->balde2);
     if(p->balde1==cap1){
         printf("O BALDE JA ESTA CHEIO!\n");
         return 0;
     }else{         
         p->balde1 = cap1;
         return 1;
     }
}

//enche balde2
int enche2(arvore *p){
    printf("E2 - %d,%d\n", p->balde1, p->balde2);
     if(p->balde2==cap2){
         printf("O BALDE JA ESTA CHEIO!\n");
         return 0;
     }else{         
         p->balde2 = cap2;
         return 1;
     }
}


//esvazia balde1
int esvazia1(arvore *p){
    printf("V1 - %d,%d\n", p->balde1, p->balde2);
     if(p->balde1!=0){
         p->balde1 = 0;
         return 1;
     }else{
         printf("O BALDE JA ESTA VAZIO\n");
         return 0;
     }
}

//esvazia balde2
int esvazia2(arvore *p){
    printf("V2 - %d,%d\n", p->balde1, p->balde2);
     if(p->balde2!=0){
         p->balde2 = 0;
         return 1;
     }else{
         printf("O BALDE JA ESTA VAZIO\n");
         return 0;
     }
}

//testa se o valor do estado foi alcançado
void testaSolucao(arvore *p){
    if(p->balde2 == estado){
       //solucao = (arvore *)calloc(1,sizeof(arvore));
       solucao = p;
       printf("ENCONTROU A SOLUCAO!\n");             
    }
    return;
}

//---------BUSCA EM PROFUNDIDADE-----------------------------------------------
//efetua busca por profundidade
void buscaProfundidade(arvore *p){
    arvore *aux = (arvore *)calloc(1,sizeof(arvore));
    aux = p;
       
    //se encher balde1 for possivel, crie um novo nó
    if(enche1(aux)){
       insere(p, cap1, p->balde2);              
    } 
    //se encher balde2 for possivel, crie um novo nó
    if(enche2(aux)){
       insere(p, p->balde1, cap2);
    }
    //se esvaziar balde1 for possivel, crie um novo nó
    if(esvazia1(aux)){
       insere(p, 0, p->balde2);
    }
    //se esvaziar balde2 for possivel, crie um novo nó
    if(esvazia2(aux)){
       insere(p, p->balde1, 0);
    }
    //se for possivel transferir balde1 para balde2, crie um novo nó
    if(transferir12(aux)){
       insere(p, p->balde1, p->balde2);
    }
    //se for possivel transferir balde2 para balde1, crie um novo nó
    if(transferir21(aux)){
       insere(p, p->balde1, p->balde2);
    }   
}
//-----------------------------------------------------------------------------

//---------BUSCA EM LARGURA----------------------------------------------------
//efetua busca em largura
//void buscaLargura(arvore *p){}
//-----------------------------------------------------------------------------

//Mostra a arvore em Pré-Ordem
void imprimi(arvore *p){
   arvore *i;
   
   if(p!=NULL){
      printf("Solucao nao Encontrada!!\n");
   }else{
       printf("%.2d,%.2d ", p->balde1, p->balde2);
       //enquanto não tiver mais filhos, ou igual a "NULL" 
       for(i=p->filho;i!=NULL;i++){  
          imprimi(i);                 
       }                  
       return;
   }    
}

//inicia a busca
void iniciaBuscaProf(arvore *p){     
   if(p == NULL){
      return;
   }else{
     buscaProfundidade(p);
     //inia a busca para os irmãos
     iniciaBuscaProf(p->irmao);
     //inicia a busca para o filho dos irmaos
     iniciaBuscaProf(p->filho);     
   }
}

int main(int argc, char *argv[]){
     
  printf("---------------------------------------\n");  
     printf("Digite a capacidade do 1o. Balse: ");
     scanf("%d",&cap1);
     printf("\nDigite a capacidade do 2o. Balse: ");
     scanf("%d",&cap2);
     printf("\nDigite o estado desejavel: ");
     scanf("%d",&estado);
  printf("---------------------------------------\n");  
  //cria um nova arvore (raiz)
  makeTree();
  
  printf("-BUSCA-PROFUNDIDADE--------------------\n");
  //efetua a busca
  iniciaBuscaProf(raiz);  
  //imprimi o caminho da solução   
  imprimi(solucao);  
  printf("---------------------------------------\n");   
  printf("-BUSCA-LARGURA-------------------------\n");    
  //iniciaBuscaLargura(raiz);  
  //imprimi o caminho da solução   
  //imprimi(solucao);   
  printf("---------------------------------------\n");
         
  system("PAUSE");	
  return 0;
}
