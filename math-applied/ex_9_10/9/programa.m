
x0 = 5;
y0 = 5;
z0 = 0;
tmax = 0.008;
N=8;

[xe ye ze] = euler(x0,y0,z0,tmax,N);
[xr yr zr] = runge_kutta(x0,y0,z0,tmax,N);
[xa ya za] = adams_bashforth(x0,y0,z0,tmax,N);

h = tmax/(N);
for t=0:(N)
   xl(t+1) = 110/21 - (23/5)*exp(-500*(t*h)) + (458/105)*exp(-10500*(t*h));
   tt = t*h;
   zl(t+1) = 10/21 - (10/21)*exp(-10500*tt);
end
