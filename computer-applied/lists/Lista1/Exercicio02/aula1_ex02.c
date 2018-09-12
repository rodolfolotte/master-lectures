#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
 
  int i, j, n;  
  
  printf("Tamanho do vetor: ");
  scanf("%d",&n);
  printf("\n");
  //subtrai uma posi��o, pois inicia em 2
  n--;
  int vetor[n];
  
  //agrega um n�mero a cada posi��o do vetor, iniciando em 2 at� a
  //quantidade maxima solicitada
    for(i=1;i<=n;i++){
     vetor[i-1] = i+1;
     printf("%d ", vetor[i-1]);   
    }
    
  printf("\n\n");  
    
    for(i=0;i<n;i++){
         //testa se a posi��o ja foi excluida, sen�o testa os multiplos no conjunto
         if(vetor[i]==0){
             continue;
         }else{
         //f-1 pois este representa o ponto de onde � feita a verifica��o
         //se fosse 0 por exemplo, para o n�mero 3 ele vereficaria se 2 seria
         //multiplo (o que � incorreto e in�til), desta forma ele ira testar 
         //somente pontos acima do vetor (no exemplo, 4 em diante).
             for(j=vetor[i]-1;j<n;j++){
                 //se a posi��o a ser testado como multiplo ja estiver sido
                 //excluida, o break � acionado e ent�o � passado para o pr�ximo
                 //n�mero do vetor.    
                 if(vetor[j]==0){
                    break;
                 //se o vetor for multiplo (resto 0), e diferente deste
                 //ele � excluido do vetor.
                 }else if(vetor[j]%vetor[i]==0){
                    vetor[j]=0;               
                 }
             }
         }     
         //mostra resultado
         printf("%d ", vetor[i]);                     
    }
  printf("\n\n");     
  system("PAUSE");	
  return 0;
}
