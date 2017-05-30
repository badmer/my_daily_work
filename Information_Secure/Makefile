main:main.o des.o aes.o des_frame.o
	gcc -o main main.o des.o aes.o des_frame.o `pkg-config --cflags --libs gtk+-2.0` -export-dynamic

main.o:main.c
	gcc -c -o main.o main.c `pkg-config --cflags --libs gtk+-2.0` -export-dynamic

des.o:des.c des.h
	gcc -c -o des.o des.c
	
aes.o:aes.c aes.h
	gcc -c -o aes.o aes.c
	
des_frame.o:des_frame.c
	gcc -c -o des_frame.o des_frame.c

clean:
	rm main *.o
