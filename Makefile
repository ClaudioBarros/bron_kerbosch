
output: main.o bron_kerbosch.o graph_list.o io.o graph_mat.o 
	gcc main.o bron_kerbosch.o graph_list.o io.o graph_mat.o -g -o output

main.o: main.c
	gcc -c -g main.c

bron_kerbosch.o: bron_kerbosch.c
	gcc -c -g bron_kerbosch.c

graph_list.o: graph_list.c
	gcc -c -g graph_list.c

graph_mat.o: graph_mat.c
	gcc -c -g graph_mat.c

io.o: io.c
	gcc -c -g io.c

clean:
	rm *.o output


