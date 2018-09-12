num_elem([],0).
num_elem([X|Y],N):- num_elem(Y,NY),N is 1+NY.
