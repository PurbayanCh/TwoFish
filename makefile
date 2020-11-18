CC=g++

run: final
	./final

final: byte.o bytestream.o twofish.o driver.o
	$(CC) -o final byte.o bytestream.o twofish.o driver.o

byte.o: byte.cpp
	$(CC) -c byte.cpp

bytestream.o: bytestream.cpp
	$(CC) -c bytestream.cpp

twofish.o: twofish.cpp
	$(CC) -c twofish.cpp

driver.o: driver.cpp
	$(CC) -c driver.cpp	

clean: 
	rm -f *.o
	rm -f final
