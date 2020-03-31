build:
	gcc structures.h DataDefinition.h main.c -o ./tema1
run:
	./tema1
clean:
	rm tema1

check:
	valgrind  --leak-check=full  ./tema1 < in/test0.in
