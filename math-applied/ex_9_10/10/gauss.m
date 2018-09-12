function X = gauss (A,B)
   [Nx,Nx] = size(A);
   % Adiciona B na ultima coluna de A
   A(:, Nx+1) = B;
   % Resolve o sistema
   for i=1:(Nx-1)
      % procura maior elemento
      [valor, pos] = max(abs(A(i:Nx,i)));
      pos = pos + i - 1; 
      if(pos ~= i) %se necessario troca as linhas
         tmp = A(i,:);
         A(i,:) = A(pos,:);
         A(pos,:) = tmp;
      end   
      % Divide linha pelo primeiro elemento nao nulo
      A(i,:) =  A(i,:)/A(i,i);

      % Elimina os ultimos elementos
      for j=(i+1):Nx
        A(j,:) = A(j,:) - A(i,:)* A(j,i);
      end
   end
   B = A(:, Nx+1);
   A = A(:,1:Nx);

   X = zeros(Nx, 1);
   X(Nx) = B(Nx)/A(Nx, Nx);
   for i=Nx-1:-1:1
      X(i) = B(i) - dot(X(i+1:Nx),A(i,i+1:Nx));
      X(i) = X(i)/A(i,i);
   end
