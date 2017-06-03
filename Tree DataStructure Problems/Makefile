all: display

stra: nibandhe_pa2_stra.c nibandhe_pa2_stra.h
	gcc -g nibandhe_pa2_stra.c -o stra
	./stra 2

tro: nibandhe_pa2_tro.c 
	gcc nibandhe_pa2_tro.c -lm -o tro 
	

floyd: nibandhe_pa2_floyd.c nibandhe_pa2_floyd.h
	gcc nibandhe_pa2.floyd -o floyd -lm
	
clean:
	rm -rf stra
	rm -rf floyd
	rm -rf tro

display: nibandhe_pa2_stra.c nibandhe_pa2_stra.h nibandhe_pa2_tro.c nibandhe_pa2_tro.h nibandhe_pa2_floyd.c nibandhe_pa2_floyd.h
	gcc nibandhe_pa2_stra.c -o stra
	gcc nibandhe_pa2_tro.c -o tro
	gcc nibandhe_pa2_floyd.c -o floyd
	@echo "\n\t./stra N"
	@echo "\n\t./tro"
	@echo "\n\t./floyd inputfloyd.txt\n"
