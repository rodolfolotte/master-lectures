#include <stdio.h>
#include <stdlib.h>

#define MAX_VETOR 100

/*
O métore Insere() foi implementado como diz o enunciado,
no entanto, o programa possibilita a mesma funcionalidade
conforme o menu que lhe é mostrado, bastando somente 
inserir elementos, mesmo que o heapMin ja tenha se processado.
*/


typedef struct filaPr{
    int prior;
    char info;
}filaPr;

filaPr v[MAX_VETOR];

filaPr Minimo(filaPr v[], int n){
    return v[0];    
}

//Modifica o valor da prioridade de um determinado
//indice
void DiminuirChave(filaPr v[], int n, int k, int x){
    filaPr aux;
    
    //não modifica se a nova priorid for menor
    if(x < v[k].prior){
         printf("\nPRIORID. MENOR QUE ATUAL\n");
         return;
    }
    
    v[k].prior = x;
    
    while((k > 0) && (v[pai(k)].prior < v[k].prior)){
       aux = v[k];
       v[k] = v[pai(k)];
       v[pai(k)] = aux;
       k = pai(k);
    }    
}

//Imprimi vetor
void imprimi(filaPr vetor[], int n){
   int i;      
   for(i=0;i<n;i++){
      printf("%c,%d ", vetor[i].info, vetor[i].prior);   
   }
   printf("\n--------------------------------------\n");
}

//retorna indice da folha
int pai(int indice){
   return ((indice+1)/2)-1;
}

//retorna indice da folha
int filhoEsquerdo(int indice){
   return 2*indice+1;
}

//retorna indice da folha
int filhoDireito(int indice){
   return 2*indice+2;
}

//Ordena heapMinimo
void HeapMin(filaPr v[], int n, int i){
    int e, d, menor;
    filaPr aux;

    e = filhoEsquerdo(i);
    d = filhoDireito(i);
    
    if((e < n) && (v[e].prior < v[i].prior)){
       menor = e;
    }else{
       menor = i;
    }
    if((d < n) && (v[d].prior < v[menor].prior)){
       menor = d;
    }
    
    if(menor != i){
       aux = v[i];
       v[i] = v[menor];
       v[menor] = aux;
       HeapMin(v,n,menor);
    }
}

//Extrai um elemento do Heap, e reoganiza a arvore
filaPr ExtrairMinimo(filaPr v[], int n){
    filaPr min;
    
    if(n < 1){
         printf("\nHEAP VAZIO\n");
    }
    
    min = v[0];
    printf("\nExtraindo... %c,%d\n\n",min.info, min.prior);
    v[0] = v[n-1];
    HeapMin(v,n-1,0);
    
    return min;
}

//Controi o HeapMínimo
void construirHeapMinimo(filaPr v[], int n){
     int i;
     
     for(i=(n/2)-1;i>=0;i--){
        HeapMin(v,n,i);
     }     
}

int main(int argc, char *argv[]){
  int op, cont;
  int ind, prior;
  char letra;
  //conta a quantidade de elementos inseridos no vetor   
  cont=0;
  srand(time(NULL));
  
  printf("Menu: \n1-Inserir dados no vetor\n");
  printf("2-Realizar Heap Minimo\n3-Minimo\n4-Extrair Minimo\n");
  printf("5-Diminuir Chave\n6-Sair\n");
  printf("--------------------------------------\n");
  while(op!=6){
     printf("Digite sua opcao: ");
     scanf("%d",&op);
     switch(op){
       case 1: printf("Digite uma letra: ");
               scanf("%s",&letra);
               printf("\n");  
               if(cont==MAX_VETOR){
                  printf("NAO E POSSIVEL INSERIR. LIMITE DO VETOR\n\n");
               }else{
                  v[cont].info = letra;
                  v[cont].prior = rand()%100;
                  cont++;
               }               
               break;               
       case 2: printf("\n--------------------------------------\n");
               printf("Vetor: "); 
               imprimi(v,cont); 
               printf("Heap Minimo: ");  
               construirHeapMinimo(v,cont);            
               imprimi(v,cont);
               break;
       case 3: printf("\n--------------------------------------\n");
               construirHeapMinimo(v,cont);
               printf("Prior. Min: Letra %c,%d", Minimo(v,cont).info, Minimo(v,cont).prior);
               printf("\n--------------------------------------\n");
               break;
       case 4: ExtrairMinimo(v,cont);
               cont--;
               break;
       case 5: printf("Entre com o indice: ");
               scanf("%d",&ind);
               printf("Entre com nova prioridade: ");
               scanf("%d",&prior);
               DiminuirChave(v, cont, ind, prior);
               printf("\n--------------------------------------\n");
               HeapMin(v,cont,ind);
               imprimi(v,cont);
               break;
       default:break;
     }
  } 
  printf("Saindo...\n\n\n");  
  
  system("PAUSE");	
  return 0;
}
