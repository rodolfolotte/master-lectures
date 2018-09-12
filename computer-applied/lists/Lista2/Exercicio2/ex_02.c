#include <stdio.h>
#include <stdlib.h>

int elemento, elemento2;
 
void mostraPolinomio(int elem, float pol[]){
    int i,j;
    int expoente = elem-1;
    for(i=0;i<elem;i++){
         if(i!=elem-1){
            if(expoente==1){
               printf("%0.2fx + ", pol[i]);
            }else{
                printf("%0.2fx^%d + ", pol[i], expoente);
                expoente--;
            }
         }else{
            printf("%0.2f\n", pol[i]);            
         }       
    }
    printf("\n");
    return;
}

//recebe os valores para cada polinomio
void lePolinomio(int elem, float pol[]){
   int i;
   for(i=0;i<elem;i++){
      printf("Digite os coeficiente do Polinomio: ");
      scanf("%f", &pol[i]);
   }
   return;   
}
   

//soma dois polinomios, e retorna resultado
void somarPolinomio(float pol1[], int elem1, float pol2[], int elem2){
    int i, maior_pol, menor_pol;
    float *aux, *aux_menor;
    int exp; 
    
    //le o segundo polinomio "q", a leitura de p é feita por padrão
    lePolinomio(elem2,pol2);
    printf("\nSoma dos polinomios 1 e 2:\n");
    printf("-----------------------------------\n");
    printf("Pol. 1: ");
    mostraPolinomio(elem1,pol1);    
    printf("Pol. 2: ");
    mostraPolinomio(elem2,pol2);
    printf("-----------------------------------\n");
    printf("Soma: ");
    
    if(elem1!=elem2){
        if(elem1<elem2){
            maior_pol = elem2;
            menor_pol = elem1;
            aux = pol2;
            aux_menor = pol1;
            exp = maior_pol-1;            
        }else{
            maior_pol = elem1;
            menor_pol = elem2;
            aux = pol1;
            aux_menor = pol2;
            exp = maior_pol-1;
        }
        int dif = maior_pol - menor_pol;
        float r[maior_pol];
          
        for(i=maior_pol-1;i>=dif-1;i--){
           r[i] = aux_menor[i-dif] + aux[i];
        }           
        for(i=dif-1;i>=0;i--){
           r[i] = aux[i];
        }        
        mostraPolinomio(maior_pol, r);
                       
    }else{
       exp = elem1-1; 
       maior_pol = elem1;
       float r[maior_pol];
                
       for(i=0;i<maior_pol;i++){
           r[i] = pol1[i] + pol2[i];           
       }       
       mostraPolinomio(maior_pol, r);
    }
    printf("\n\n");
    return;    
}

float calcularPolinomio(float pol1[], int a){
    int i;
    float total;

    for(i=0;i<elemento;i++){
       total = total + (pol1[i] * (pow(a,i)));
    }
    printf("%0.2f\n\n", total);
    return total;
}


void derivarPolinomio(int grau, float pol[]){
    int i, j;
    int expoe = elemento-1;
    int ordem = elemento;
    int qtd_elem = elemento-grau;
    
    if(grau>ordem){
        printf("\nERRO!\n\n");
        return;
    }
        
    for(i=0;i<grau;i++){
        for(j=0;j<ordem;j++){
           pol[j] = pol[j]*expoe;
           expoe--;
        }
        expoe = ordem-2; 
        ordem--;       
    }
    mostraPolinomio(qtd_elem, pol);
    return;
}


main(int argc, char *argv[]){   
  int i, opcao, ord, x;
  
  printf("Menu:\n1- Mostrar Polinomio\n2- Somar ");
  printf("Polinomio\n3- Derivar\n4- Calcular\n\n");
  printf("\n:> Digite o grau do polinomio: ");
  scanf("%d",&elemento);
  printf("\n");
  
  float *pol1;    
  pol1 = (float *)malloc((elemento+1)*sizeof(float));                              
  
  lePolinomio(elemento, pol1);
  printf("\n:> Sua opcao do menu: ");
  scanf("%d",&opcao);
  printf("\n\n");
  
  switch(opcao){
     case 1: mostraPolinomio(elemento, pol1);break;
     case 2: printf("Digite o grau do segundo polinomio: ");
             scanf("%d",&elemento2);
             printf("\n");
             //declara outra variavel para receber o segundo polinomio
             float *pol2;
             pol2 = (float *)malloc((elemento2+1)*sizeof(float));             
             somarPolinomio(pol1, elemento, pol2, elemento2);break;
     case 3: printf("Digite a ordem de derivacao: ");
             scanf("%d",&ord);             
             derivarPolinomio(ord, pol1);break;
     case 4: printf("Digite um valor para x: ");
             scanf("%d",&x);
             printf("\n");
             mostraPolinomio(elemento, pol1);
             printf("-----------------------------------\n = ");
             calcularPolinomio(pol1,x);break;
     default: break;  
  }        
  system("PAUSE");	  
}
