CC=g++

run: final
	./final

final: byte.o bytestream.o keyschedule.o twoFish.o
	$(CC) -o final byte.o bytestream.o keyschedule.o twoFish.o

byte.o: byte.cpp
	$(CC) -c byte.cpp

bytestream.o: bytestream.cpp
	$(CC) -c bytestream.cpp

keyschedule.o: keyschedule.cpp
	$(CC) -c keyschedule.cpp

twoFish.o: twoFish.cpp
	$(CC) -c twoFish.cpp

clean: 
	rm *.o
	rm final
