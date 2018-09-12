maior([X],X).               	
maior([X|Y],M):-            	
	maior(Y,N),          	
     	(X>N -> M=X; M=N).
