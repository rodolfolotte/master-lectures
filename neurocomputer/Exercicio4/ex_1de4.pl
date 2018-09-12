funcao(0,1).                     % Trata-se de um calculo fatorial
funcao(N,F) :-
	N>0,
	N1 is N-1,
	funcao(N1,F1),
	F is N*F1.
