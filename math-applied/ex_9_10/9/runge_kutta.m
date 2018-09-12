function [x y z] = runge_kutta(x0,y0,z0,H, Nx)
   x(1) = x0;
   y(1) = y0;
   z(1) = z0;
   h = H/Nx;
   for i=2:Nx+1
      % 1
      m1 = funcaoF(x(i-1), y(i-1), z(i-1));
      k1 = funcaoG(x(i-1), y(i-1), z(i-1));
      r1 = funcaoH(x(i-1), y(i-1), z(i-1));
      % 2
      m2 = funcaoF(x(i-1)+(h/2)*m1, y(i-1)+(h/2)*k1,z(i-1)+(h/2)*r1);
      k2 = funcaoG(x(i-1)+(h/2)*m1, y(i-1)+(h/2)*k1,z(i-1)+(h/2)*r1);
      r2 = funcaoH(x(i-1)+(h/2)*m1, y(i-1)+(h/2)*k1,z(i-1)+(h/2)*r1);
      % 3
      m3 = funcaoF(x(i-1)+(h/2)*m2, y(i-1)+(h/2)*k2,z(i-1)+(h/2)*r2);
      k3 = funcaoG(x(i-1)+(h/2)*m2, y(i-1)+(h/2)*k2,z(i-1)+(h/2)*r2);
      r3 = funcaoH(x(i-1)+(h/2)*m2, y(i-1)+(h/2)*k2,z(i-1)+(h/2)*r2);
      % 4
      m4 = funcaoF(x(i-1)+h*m3, y(i-1)+h*k3,z(i-1)+h*r3);
      k4 = funcaoG(x(i-1)+h*m3, y(i-1)+h*k3,z(i-1)+h*r3);
      r4 = funcaoH(x(i-1)+h*m3, y(i-1)+h*k3,z(i-1)+h*r3);
      
      x(i) = x(i-1) + (h/6)*(m1 + 2*(m2+m3) + m4);
      y(i) = y(i-1) + (h/6)*(k1 + 2*(k2+k3) + k4);
      z(i) = z(i-1) + (h/6)*(r1 + 2*(r2+r3) + r4);
   end
end
