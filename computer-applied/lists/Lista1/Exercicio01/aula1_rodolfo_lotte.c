#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
 
  int m, n, linha10, linha11, r, mult, s, t, result;
  
  printf("Digite um valor para m: ");
  scanf("%d",&m);
  printf("Digite um valor para n: ");
  scanf("%d",&n);
  //linha nas cordenadas 1,0
  linha10 = 10 - m;
  //linha nas cordenadas 1,1
  linha11 = 10 -n;
  //mostra matriz
  printf("\n%d %d\n%d %d\n\n", m, n, linha10, linha11);
  //r corresponde ao valor da subtração de uma diagonal
  r = m - linha11;
  
  mult = linha10 * linha11;
  //Atribui a t o resto da divisão por 10, desta forma
  //todo e qualquer valor "mult" dividido por 10 seja ele um número
  //inteiro grande ou pequeno atribuirá a t valores entre 0 e 9
  t = mult%10;
  printf("\nO valor de t: %d", t);
  //Atribui a s o algarismo da esquerda do valor de "mult". Este
  //valor possui um intervalo indefinido, pois a multiplicação 
  //dos valores (10-m)(10-n) é impreciso para dezenas, centenas e 
  //assim por diante...
  s = (mult - t)/10;
  printf("\nO valor de s: %d\n\n", s);
  //Se todo r+s corresponde ao valor exato da centena, dezena ou até mesmo 
  //milhar de um número, tal que a multiplicação deste por 10 resultara no valor 
  //sem resto, tal que t seja o resto. A soma destes será o resultado final
  //da (m.n) para qualquer número inteiro positivo/negativo
  result = ((r+s)*10)+t;
  printf("O resultado e: %d\n\n\n", result);
  system("PAUSE");	
  return 0;
  
  //
}
