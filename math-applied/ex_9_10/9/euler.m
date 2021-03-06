function [x y z] = euler(x0,y0,z0,H, N)
   x(1) = x0;
   y(1) = y0;
   z(1) = z0;
   h = H/(N);
   for i=2:N+1
      x(i) = x(i-1) + h*funcaoF( x(i-1), y(i-1), z(i-1));
      y(i) = y(i-1) + h*funcaoG( x(i-1), y(i-1), z(i-1));
      z(i) = z(i-1) + h*funcaoH( x(i-1), y(i-1), z(i-1));
   end
end

