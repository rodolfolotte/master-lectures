mult([],0).
mult([X|Y],N):- mult(Y,_),N is X*2.
