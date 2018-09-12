#include <stdio.h>
#include <stdlib.h>

typedef struct lista{
   int num;
   struct lista *prox;
   struct lista *ante;
}lista;

lista *listHead;
lista *listTail;

//insere um elemento na lista
void incluir(int vlr){
    lista *novo = (lista *)calloc(1,sizeof(lista));
    lista *aux;
    novo->num = vlr;
        
    //caso o lista esteja vazia: inicia valores
    if(!listHead){
      novo->ante = NULL;
      novo->prox = NULL;    
      listHead = novo;
      listTail = novo;
      return;
    }else{        
        //insere no inicio
        if(listHead->num > novo->num){
            aux = listHead;
            novo->prox = aux;
            novo->ante = NULL;            
            aux->ante = novo;
            listHead = novo;    
            return;
        //insere no fim
        }else if(listTail->num < novo->num){
            listTail->prox = novo;
            novo->prox = NULL;
            novo->ante = listTail;
            listTail = novo;
            return;
        //percoree a lista para inclusão intermediária
        }else{
            aux = listHead;              
            while(aux->num < novo->num && aux->prox->num < novo->num){
               aux = aux->prox;
            }
               novo->prox = aux->prox;
               novo->ante = aux;
               aux->prox = novo; 
               return;
        }            
    }    
}

//exclui um elemento na lista
void excluir(int vlr){
    lista *aux;
    lista *dado;
    
    //se for o ultimo elemento
    if(listHead == listTail){       
     listHead = NULL;
     listTail = NULL;
     free(listHead); 
     free(listTail);
    //se for igual ao listHead
    }else if(vlr == listHead->num){
      aux = listHead;
      listHead = aux->prox;
      listHead->ante = NULL;
      //desaloca memória
      free(aux);
      return;
    //se for igual ao listTail
    }else if(vlr == listTail->num){
      aux = listTail;
      listTail = aux->ante;
      listTail->prox = NULL;
      //desaloca memória          
      free(aux);
      return;
    //caso não seja igual ao listTail ou listHead
    //percorre a lista em busca.
    }else{
        lista *anterior;
        lista *posterior;
        aux = listHead->prox;
            //enqto o proximo existir
            while(aux->prox != NULL){
               if(aux->num == vlr){
                  break;
               }else{
                  aux = aux->prox;
               }           
            }
               //variaveis auxiliares para armazenar
               //os valores anterior e posteiror ao 
               //elemento excluido
               anterior = aux->ante;
               posterior = aux->prox;
               //desaloca memoria
               free(aux);
               anterior->prox = posterior;               
               posterior->ante = anterior;                                   
               return;
        }    
}
    
//imprimi a lista
void mostraLista(){
   lista *aux = listHead;
   
   if(!listHead){
       printf("---------------------------------------\n");
       printf("** LISTA VAZIA **\n");
       printf("---------------------------------------\n");
       return;
   }else{
       printf("---------------------------------------\n");
       //enquanto a lista não for "NULL" 
       while(aux){
          printf("%.2d ", aux->num);
          aux = aux->prox;
       }
       printf("\n---------------------------------------\n");  
       return;
   }
}

int main(int argc, char *argv[]){
  int op, vlr;
  
  printf("Menu: \n1-Inserir\n2-Excluir\n3-Mostrar\n4-Sair\n");
  printf("---------------------------------------\n");
  while(op!=4){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("Digite um valor: ");
               scanf("%d",&vlr);
               printf("\n");
               incluir(vlr); 
               mostraLista(); 
               printf("\n");             
               break;
       case 2: printf("Digite um dos valores acima: ");
               scanf("%d",&vlr);
               excluir(vlr);   
               mostraLista(); 
               printf("\n");           
               break;
       case 3: mostraLista();
               break;
       default:break;    
     }
  } 
  
  system("PAUSE");	
  return 0;
}
