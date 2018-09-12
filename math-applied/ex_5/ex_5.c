#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <conio.h> 

void gradMin(float* x, float* v){
    float  gx, hx, fx;
    
    gx = -(pow(x[0]-8,2)+pow(x[1]-8,2))/8;
    hx = -(pow(x[0]-12,2)+pow(x[1]-12,2))/8;
       
    v[0] = ((-(x[0]-8)/4)*exp(gx) + (-(x[0]-12)/4)*exp(hx))*(-1);
    v[1] = ((-(x[1]-8)/4)*exp(gx) + (-(x[0]-12)/4)*exp(hx))*(-1);
}

void gradMax(float* x, float* v){
    float  gx, hx, fx;
    
    gx = -(pow(x[0]-8,2)+pow(x[1]-8,2))/8;
    hx = -(pow(x[0]-12,2)+pow(x[1]-12,2))/8;
       
    v[0] = (-(x[0]-8)/4)*exp(gx) + (-(x[0]-12)/4)*exp(hx);
    v[1] = (-(x[1]-8)/4)*exp(gx) + (-(x[0]-12)/4)*exp(hx);
}

void CalculoX(float alpha, float* x, float* v){
    x[0]=x[0]-alpha*v[0];
    x[1]=x[1]-alpha*v[1];
}

float CalculoAlpha(float* x){

float alpha, alpha2;

		   if((((-(pow(-2*x[0]*x[1] + pow(x[1],3) + pow(x[0],2)*(1 + x[1]),2)))*
                  (pow(x[0],4) + 4*x[0]*x[1] + pow(x[1],2)*(-4 + pow(x[1],2)) + 
                   pow(x[0],2)*(-1 + 2*pow(x[1],2)))))<0){
				
				   alpha2 =0.1;
				   
		   }else if((pow(x[0],6) - 12*pow(x[0],3)*x[1] - 12*x[0]*pow(x[1],3) + 
                     3*pow(x[0],4)*(1 + pow(x[1],2)) + 3*pow(x[0],2)*
                     pow(x[1],2)*(5 + pow(x[1],2)) + pow(x[1],4)*
                     (12 + pow(x[1],2)))==0){
				   
				   alpha2 =0.1;		  
				   
		   }else{ 
			       alpha2 = (pow(x[0],3) + pow(x[0],5) - 4*pow(x[0],2)*x[1] - 
                   2*pow(x[0],3)*x[1] + 4*x[0]*pow(x[1],2) + 4*pow(x[0],2)*
                   pow(x[1],2) + 2*pow(x[0],3)*pow(x[1],2) - 
				   2*x[0]*pow(x[1],3) + 4*pow(x[1],4) + x[0]*pow(x[1],4) + 
				   sqrt((-(pow(-2*x[0]*x[1] + pow(x[1],3) + pow(x[0],2)*
                   (1 + x[1]),2)))*(pow(x[0],4) + 4*x[0]*x[1] + 
				   pow(x[1],2)*(-4 + pow(x[1],2)) + pow(x[0],2) *
                   (-1 + 2*pow(x[1],2)))))/(pow(x[0],6) - 12*pow(x[0],3)*x[1] - 
                   12*x[0]*pow(x[1],3) + 3*pow(x[0],4)*(1 + pow(x[1],2)) + 
				   3*pow(x[0],2)*pow(x[1],2)*(5 + pow(x[1],2)) + 
                   pow(x[1],4)*(12 + pow(x[1],2)));
			}
	return alpha2;
}

float fObjMax(float* x){
	return (exp(-(pow(x[0]-8,2)+pow(x[1]-8,2))/8) - exp(-(pow(x[0]-12,2)+pow(x[1]-12,2))/8));
}

float fObjMin(float* x){
	return (exp(-(pow(x[0]-8,2)+pow(x[1]-8,2))/8) - exp(-(pow(x[0]-12,2)+pow(x[1]-12,2))/8))*(-1);
}


int main (){

	float x[2];
	float v[2];
	float alpha, obj=0;
	int k=0;

	printf("\ndigite os valores iniciais de x: ");
	scanf("%f",&x[0]);
	system("cls");
	printf("\ndigite os valores iniciais de y: ");
	scanf("%f",&x[1]);
	system("cls");
	
    printf("---------------------------------------------------------------------------\n");
    printf("| IT.|   F(x1,x2) |    GRADIENTE   |   ALPHA    |      x      |     y     |\n");
    printf("---------------------------------------------------------------------------\n");
	for(k=1;k<=10;k++){
		
		printf("|%2d. | %10.6f | v1= %10.6f | %10.6f | %10.6f  | %9.6f |\n",k,obj,v[0],alpha,x[0],x[1]);	
		printf("|    |            | v2= %10.6f |            |             |           |\n",v[1]);
		
        obj = fObjMax(x);
		gradMax(x,v);
		alpha = CalculoAlpha(x);		
		CalculoX(alpha, x, v);        
        	
	}
	
	printf("---------------------------------------------------------------------------\n\n\n");
	
	printf("---------------------------------------------------------------------------\n");
    printf("| IT.|   F(x1,x2) |    GRADIENTE   |   ALPHA    |      x      |     y     |\n");
    printf("---------------------------------------------------------------------------\n");
	for(k=1;k<=10;k++){
		
		printf("|%2d. | %10.6f | v1= %10.6f | %10.6f | %10.6f  | %9.6f |\n",k,obj,v[0],alpha,x[0],x[1]);	
		printf("|    |            | v2= %10.6f |            |             |           |\n",v[1]);
		
        obj = fObjMin(x);
		gradMin(x,v);
		alpha = CalculoAlpha(x);		
		CalculoX(alpha, x, v);        
        	
	}
	
	printf("---------------------------------------------------------------------------\n");
    
	system("pause");
	return(0);
}

