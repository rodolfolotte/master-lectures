#include <stdio.h>
#include <stdlib.h>

#define MAX_VETOR 100

int v[MAX_VETOR];

//Imprimi vetor
void imprimi(int vetor[], int n){
   int i;      
   for(i=0;i<n;i++){
      printf("%d ", vetor[i]);   
   }
   printf("\n--------------------------------------\n\n");
}

//obtem o filho esquerdo no vetor
int filhoEsquerdo(int indice){
   return 2*indice+1;
}
//obtem o filho direito no vetor
int filhoDireito(int indice){
   return 2*indice+2;
}

//Realiza o HeapMin
void HeapMin(int v[], int n, int i){
    int e, d, menor, aux;

    e = filhoEsquerdo(i);
    d = filhoDireito(i);
    
    if((e < n)&&(v[e] < v[i])){
       menor = e;
    }else{
       menor = i;
    }
    if((d < n) && (v[d] < v[menor])){
       menor = d;
    }
    
    if(menor != i){
       aux = v[i];
       v[i] = v[menor];
       v[menor] = aux;
       HeapMin(v,n,menor);
    }
}

//inicia o heap
void construirHeapMinimo(int vetor[], int n){
     int i;
     
     for(i=(n/2)-1;i>=0;i--){
        HeapMin(v,n,i);
     }
     for(i=0;i<n;i++){
        printf("%d ",v[i]);
     }
     printf("\n--------------------------------------\n\n");
}

//verifica se o valor x ja existe no vetor.
int existente(int v[], int cont, int x){
    int i;
    
    for(i=0;i<cont;i++){
       if(x==v[i]){
          return 1;          
       }                    
    }
    return 0;
}

int main(int argc, char *argv[]){
  int vlr, op, cont;
     
  cont=0;
  
  printf("Menu: \n1-Inserir dados no vetor\n2-Mostrar vetor\n3-Realizar Heap Minimo\n4-Sair\n");
  printf("---------------------------------------\n");
  while(op!=4){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("Digite um valor: ");
               scanf("%d",&vlr);
               printf("\n");  
               if(cont==MAX_VETOR){
                  printf("NAO E POSSIVEL INSERIR. LIMITE DO VETOR\n\n");
               }else if(existente(v,cont,vlr)){
                  printf("CHAVE JA EXISTENTE!\n\n");  
               }else{
                  v[cont] = vlr;
                  cont++;
               }               
               break;
               
       case 2: printf("\n-VETOR--------------------------------\n");
               imprimi(v,cont);               
               break;
       case 3: printf("\n-HEAP MIN------------------------------\n");
               construirHeapMinimo(v,cont);
               break;
       default:break;
     }
  } 
  printf("\nSaindo...\n\n\n");
  
  
  system("PAUSE");	
  return 0;
}
