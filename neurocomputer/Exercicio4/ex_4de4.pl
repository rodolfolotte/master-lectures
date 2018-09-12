imc(P,A,M):- P>0, A>0, 
	     M is (P/(A*A)), message(M).
message(M):- (M > 20, M =< 24.9 -> write(' Normal'));
	     (M >= 25, M =< 29.9 -> write(' Obesidade 1'));
             (M >= 30, M =< 39.9 -> write(' Obesidade 2')); 
             (M >= 40 -> write(' Obesidade 3')). 



