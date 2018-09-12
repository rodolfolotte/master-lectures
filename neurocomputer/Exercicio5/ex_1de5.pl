livro(M):- enciclopedia(M);dicionario(M).
livro(enciclopedia).
livro(dicionario).

tem(Y,X):-cor(X),livro(Y).
tem(enciclopedia,X):- cor(X).
tem(dicionario,vermelho).
tem(britanica,verde).

cor(verde).
cor(vermelho).
enciclopedia(britanica).
dicionario(aurelio).




