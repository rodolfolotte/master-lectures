aprovado(cliente) :- 
	          regular(cliente), 
		  possui(cliente, bens), 
		  casado(cliente), 
		  possui(cliente, filhos), 
		  nao_possui(cliente, dividas),
		  possui(cliente, renda).
      
possui(cliente, renda):- 
	          possui(cliente, trabalho), 
		  trabalho(servidor_publico),
		  (recebe(cliente,Dinheiro)->Dinheiro>=2000).

possui(cliente, cpf).
possui(cliente, trabalho).
possui(cliente, bens).
possui(cliente, filhos).
regular(cliente).
bens(casa).
bens(carro).
bens(estab_coml).
recebe(cliente, 2000).
trabalho(servidor_publico).
casado(cliente).
nao_possui(cliente, dividas).
