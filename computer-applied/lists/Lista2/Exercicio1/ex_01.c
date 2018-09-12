#include <stdio.h>
#include <stdlib.h>

struct produto{
  int cod_prod, contador;
  float preco;
};

struct cliente{
  int cod_cliente, qtd_compra;
  float total;
};

//int produto_mais_comprado;
float media = 0.0f;
float media_clientes_por_dia = 0.0f;
float fat_total = 0.0f;
float fat_medio = 0.0f;  

//----------------------------------------------------------------------------------
//inicia cada produto do vetor repassado, com 
//valores randomicos, para o preço valores randomicos
//entre 20 e 40 reais.
void geraProduto(struct produto pr[], int qtd){   
  int i;
  srand(time(NULL));
  
  for(i=0;i<qtd;i++){
      pr[i].cod_prod = i;
      pr[i].contador = 0;
      pr[i].preco = rand()%25+2;      
  }
}
//-----------------------------------------------------------------------------------

int obterMaiorQtd(struct produto prod[], int qtd){
    int i, maior, pos_prod;
    maior = prod[0].contador;
    for(i=0;i<qtd;i++){       
       if(i!=qtd-1){
          if(maior<=prod[i+1].contador){
             maior = prod[i+1].contador;
             pos_prod = i+1;
          }
       }else{
          if(maior<=prod[i].contador){
             pos_prod = i;
          }
       }
    }
    return pos_prod;   
}

//-----------------------------------------------------------------------------------

//inicia cada cliente do vetor repassado, com 
//valores randomicos, para o codigo do cliente é feito
//a multiplicaçao por 100, para melhor identificação do cod do cliente
//e tbm para difenciar do cod. do produto
void geraCliente(struct cliente cl[], int qtd){ 
  int i; 
  
  for(i=1;i<=qtd;i++){
      cl[i].cod_cliente = i;
      cl[i].qtd_compra = 0;
      cl[i].total = 0.0f;      
  }
}

//------------------------------------------------------------------------------------

//inicia a simulação
void iniciaPeriodo(struct cliente cl[], 
                   struct produto pr[], 
                   int qtd_produto, 
                   int qtd_cliente){
   
   srand(time(NULL));
   //qtd de visita por dia do periodo (valor na posição)   
   int i, j, k, u_rand, p_rand;// qtd_compradores;
     
   int *qtd_cliente_dia[500];   
   for(i=0;i<500;i++){
      qtd_cliente_dia[i] = (int *)malloc((500+1)*sizeof(int));
   }

   for(i=0;i<500;i++){
     //quantos clientes visitaram a loja aquele dia (randomico)
     *qtd_cliente_dia[i] = rand()%qtd_cliente;                    
          
     for(j=0;j<*qtd_cliente_dia[i];j++){                                    
        //Pega um cliente aleatório, e contabiliza
        //uma qtd aleatoria de produtos comprados.. até no 
        //máximo 3 produtos.                 
        u_rand = rand()%qtd_cliente;
        cl[u_rand].qtd_compra = (rand()%20)+1;        
        
        for(k=0;k<cl[u_rand].qtd_compra;k++){                                                        
           //p_rand é um produto aleatório da lista de produtos
           p_rand = rand()%qtd_produto;
           //incrementa quando o produto for vendido
           pr[p_rand].contador++;
           //soma o valor do produto a somatória do cliente
           cl[u_rand].total = cl[u_rand].total + pr[p_rand].preco;
           fat_total = fat_total + pr[p_rand].preco;                              
        }  
               
     }
     //soma dos clientes por dia
     media_clientes_por_dia = media_clientes_por_dia + *qtd_cliente_dia[i];       
     //cada dia, são até 3 clientes. Primeiro é feito a média de gastos
     //do cliente depois a média do dia.
     media = fat_total/500;  
     
   }    
   //media da qtd de clientes ao dia
   media_clientes_por_dia = media_clientes_por_dia / 500;   
   //faturamento medio por dia
   fat_medio = fat_total / 500;        
  
}

//--------------------------------------------------------------------------------

//mostra os dados estatisticos
void mostraEstatisticas(struct cliente cli[], 
                        struct produto pr[], 
                        int prod_mais_vendido, 
                        int qtd_clientes){
     int i, j, k;
      printf("===============================================================\n");
      printf(" %d clientes - media ao dia: %0.2f                                \n",qtd_clientes, media_clientes_por_dia); 
      printf(" Media Compras/Periodo: R$ %0.2f                            \n",media); 
      printf(" Produto mais vendido: %d = %d Und(s).                      \n",pr[prod_mais_vendido].cod_prod, pr[prod_mais_vendido].contador); 
      printf("---------------------------------------------------------------\n");
      printf(" Fat.Diario.: R$ %0.2f  \n Fat.Tot. R$ %0.2f                   \n", fat_medio, fat_total); 
      printf("===============================================================\n\n\n");      

}

//--------------------------------------------------------------------------------

main(int argc, char *argv[]){
  int i, produto_mais_vendido;
    
  srand(time(NULL));  
  
  //gera qtd de 10 a 29 produtos aleatoriamente
  int qtd_prod_alea = rand()%30+1;
  struct produto *prod[qtd_prod_alea];
  //aloca espaco para produto
  for(i=0;i<qtd_prod_alea;i++){
      prod[i] = (struct produto *)malloc((qtd_prod_alea+1)*sizeof(struct produto));
  }  
  //gera produtos
  geraProduto(*prod, qtd_prod_alea);
  
  //gera qtd de 10 a 29 clientes aleatoriamente
  int qtd_cli_alea = rand()%40+1;
  struct cliente *cli[qtd_cli_alea];
  //aloca espaco para cliente
  for(i=0;i<qtd_cli_alea;i++){
      cli[i] = (struct cliente *)malloc((qtd_cli_alea+1)*sizeof(struct cliente));
  }  
  //gera clientes
  geraCliente(*cli, qtd_cli_alea);
  
  //inicia o periodo
  iniciaPeriodo(*cli, *prod, qtd_prod_alea, qtd_cli_alea);
  //obtem o produto mais vendido
  produto_mais_vendido = obterMaiorQtd(*prod,qtd_prod_alea);
  //Exibe as estatisticas do Periodo
  mostraEstatisticas(*cli, *prod, produto_mais_vendido, qtd_cli_alea);
      
  system("PAUSE");	

}
