main:
	gcc main.c -o build/main -Wall

reg:
	gcc registrasi.c -o build/registrasi -Wall

release:
	gcc main.c -o main -Wall
	gcc registrasi.c -o registrasi -Wall