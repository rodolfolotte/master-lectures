Pessoa(cliente).
pessoa(dono).

possui(Q,Dinheiro):- pessoa(Q), Dinheiro>0.
possui(cliente,200).	
possui(dono,3000).

tem(restaurante,mesa).
tem(restaurante,menu).
tem(restaurante,comida).
tem(restaurante,conta).
tem(restaurante,cliente).
tem(restaurante,garcom).
tem(restaurante,cozinheiro).
tem(restaurante,caixa).
tem(restaurante,dono).
tem(cliente,fome).

entra(C,restaurante):- pessoa(C), tem(C,fome).%, possui(C,dinheiro).





