all: lcs prim kruskal

lcs: lcs.c lcs.h
	gcc -g lcs.c -o lcs.out

prim: prim.c prim.h
	gcc -g prim.c -o prim.out

kruskal: kruskal.c kruskal.h
	gcc -g kruskal.c -o kruskal.out

clean:
	rm -rf lcs.out
	rm -rf prim.out
	rm -rf kruskal.out

totalclean: clean
	rm -rf string.txt
	rm -rf graph.txt
	rm *.*~	

submit: totalclean
	tar -zvcf c_oniband1_proj3.tar.gz .
