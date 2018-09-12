%---------------------------------------------------------------%
%-----------------------------QUEST�O 10------------------------%
%Resolu��o do problema de contorno pelo m�todo das diferen�as fi-
%nitas centradas.

clear all
Max = 1024;
N = 2;
contador = 1;
%constroi sistema de equa��es
while Max > N
   h = 1/N;
   A = diag((h^2-2)*ones(N,1),0) + diag(ones(N-1,1),1) + diag(ones(N-1,1),-1);
   B = zeros(N,1);
   B(N) = -1;
   %aplica m�todo de gauss como resolu��o de sistemas eq. alg. lineares
   X = gauss(A,B);   
   %solucao do problema
   %X2=valores exatos
   for i=1:N
      X2(i) = sin(i*h)/sin(1);
   end
   
   %Norma(1,contador) = N;
   %obtem a diferen�a dos valores obtidos com os valores dados
   %dando a possibilidade de gerar o gr�fico de erro
   %Norma(2,contador) = norm(X2'-X);
   Dif(contador,2)=N;
   Dif(contador,1)=norm(X2'-X);
   N = N*2
   contador = contador+1;
end
