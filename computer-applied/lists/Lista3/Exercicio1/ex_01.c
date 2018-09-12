#include <stdio.h>
#include <stdlib.h>


typedef struct ponto{
   float x;
   float y;
   int envConv;
}ponto;

//define os pontos que fazem parte da envoltoria
//Se para a reta nos pontos A e B 
void getEC(ponto pt[], int qtd_pontos){
    int i, j; 
    int cont_p = 0;
    //contador de pontos à direita da reta
    int dir_reta = 0;
    //contador de pontos à esquerda da reta
    int esq_reta = 0;
    float coef_angular, coef_linear, x;
           
    //cada iteração do while é traçado um reta
    //sendo o primeiro for a escolha dos 2 pontos em que esta reta passa 
    //o segundo for é a análise dos pontos restantes em relaçao a esta reta
    //se não tiver nenhum ponto, no lado esquedo da reta ou direito
    //os pontos que passam a reta é considerados extremos.
    while(cont_p<qtd_pontos){
        for(i=cont_p+1;i<qtd_pontos;i++){
               //calculo do coeficiente angular da reta 
               coef_angular = (pt[i].y - pt[cont_p].y)/(pt[i].x - pt[cont_p].x);
               //calculo do coeficiente linear da reta
               coef_linear = -(coef_angular * pt[i].x) + pt[i].y;  
           //for para analise dos pontos em relação a reta                                                 
           for(j=0;j<qtd_pontos;j++){
             //testa se j for igual a i, então j é o mesmo ponto onde a 
             //resta esta passando, assim como o cont_p
             if(j==i || j==cont_p){continue;}
             
             //se a reta passar pela origem seu coef. linear é = 0
             if(coef_linear==0){
                x = pt[j].y / coef_angular;
             }else{
                x = (pt[j].y - coef_linear)/ coef_angular;
             }
               //analisa em que lado esta o ponto j
               if(x < pt[j].x){
                  dir_reta++;
               }else if(x > pt[j].x){
                  esq_reta++;
               }                            
           }     
           //se a contagem dos pontos em um dos lados for 
           //igual a zero, os pontos em que passa a reta 
           //são extremos.                           
           if(dir_reta==0 || esq_reta==0){
              pt[i].envConv = 1;
              pt[cont_p].envConv = 1;                        
           } 
           //zera os contadores       
           dir_reta = 0;
           esq_reta = 0;       
        }
        //proxima reta
        cont_p++;        
    }    
    
    
    int contador = 1;
    //mostra os pontos que constituem a envoltoria  
    for(i=0;i<qtd_pontos;i++){      
      if(pt[i].envConv==1){
         printf("%d. Ponto: %0.0f,%0.0f \n", contador, pt[i].x, pt[i].y);  
         contador++;    
      }      
    }
}

int main(int argc, char *argv[]){
  int i, j, qtd_pontos, tamanho_eixoX, tamanho_eixoY;
  
  srand(time(NULL));
  
  printf("--------------------------------------------\n");
  printf("Defina a quantidade de pontos no plano: ");
  scanf("%d", &qtd_pontos);
  printf("Defina o tamanho do eixo de X: ");
  scanf("%d", &tamanho_eixoX);
  printf("Defina o tamanho do eixo Y: ");
  scanf("%d", &tamanho_eixoY);
  printf("--------------------------------------------\n");
  printf("--------------------------------------------\n\n");
  
  ponto pontos[qtd_pontos];  
    
  for(i=0;i<qtd_pontos;i++){
     pontos[i].x = rand()%tamanho_eixoX+1;
     pontos[i].y = rand()%tamanho_eixoY+1;
     pontos[i].envConv = 0;
     printf("%do. ponto: %0.0f,%0.0f\n", i+1, pontos[i].x, pontos[i].y);
  }
  
  printf("\n--------------------------------------------\n");
  printf("--------------------------------------------\n");
  printf("Pontos corresp. a envoltoria convexa:\n\n");
  getEC(pontos, qtd_pontos);
  printf("\n--------------------------------------------\n\n");  
    
  system("PAUSE");	
  return 0;
}
