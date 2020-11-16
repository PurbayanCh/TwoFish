CC=g++

run: final
	./final

final: byte.o bytestream.o twoFish.o
	$(CC) -o final byte.o bytestream.o twoFish.o

byte.o: byte.cpp
	$(CC) -c byte.cpp

bytestream.o: byte.o bytestream.cpp
	$(CC) -c bytestream.cpp

twoFish.o: twoFish.cpp
	$(CC) -c twoFish.cpp

clean: 
	rm *.o
	rm final
