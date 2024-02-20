all: prog


prog: main.o temp_function.o
	gcc -o prog .\bin\main.o .\bin\temp_function.o

main.o: main.c temp_function.h 
	gcc -c -o .\bin\main.o main.c

temp_function.o: temp_function.c temp_function.h 
	gcc -c -o .\bin\temp_function.o temp_function.c

clean:
	del .\bin\*.o
	del prog.exe