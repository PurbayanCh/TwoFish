CC=g++

run: final
	./final

final: byte.o bytestream.o hfunction.o keyschedule.o twoFish.o
	$(CC) -o final byte.o bytestream.o hfunction.o keyschedule.o twoFish.o

byte.o: byte.cpp
	$(CC) -c byte.cpp

bytestream.o: bytestream.cpp
	$(CC) -c bytestream.cpp

hfunction.o: hfunction.cpp
	$(CC) -c hfunction.cpp

keyschedule.o: keyschedule.cpp
	$(CC) -c keyschedule.cpp

twoFish.o: twoFish.cpp
	$(CC) -c twoFish.cpp

clean: 
	rm -f *.o
	rm -f final
