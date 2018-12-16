CC=g++
DLIBS=-lwiringPi
epd:main.o epd7in5.o imagedata.o epdif.o icons.o font8.o font12.o font16.o font20.o font24.o font32.o font48.o epdpaint.o
	$(CC) -Wall -o epd main.o epd7in5.o icons.o imagedata.o epdif.o font8.o font12.o font16.o font20.o font24.o font32.o font48.o epdpaint.o $(DLIBS)
imagedata.o:imagedata.cpp imagedata.h 
	$(CC) -Wall -c imagedata.cpp $(DLIBS)
epd7in5.o:epd7in5.cpp epd7in5.h
	$(CC) -Wall -c epd7in5.cpp $(DLIBS)
epdif.o:epdif.cpp epdif.h
	$(CC) -Wall -c epdif.cpp $(DLIBS)
icons.o:icons.cpp icons.h
	$(CC) -Wall -c icons.cpp
font8.o:fonts.h font8.c
	$(CC) -Wall -c font8.c
font12.o:fonts.h font12.c
	$(CC) -Wall -c font12.c
font16.o:fonts.h font16.c
	$(CC) -Wall -c font16.c
font20.o:fonts.h font20.c
	$(CC) -Wall -c font20.c
font24.o:fonts.h font24.c
	$(CC) -Wall -c font24.c
font32.o:fonts.h font32.c
	$(CC) -Wall -c font32.c
font48.o:fonts.h font48.c
	$(CC) -Wall -c font48.c
epdpaint.o:epdpaint.cpp epdpaint.h
	$(CC) -Wall -c epdpaint.cpp $(DLIBS)
main.o:main.cpp epd7in5.h imagedata.h epdpaint.h
	$(CC) -Wall -c main.cpp $(DLIBS)
clean:
	rm imagedata.o main.o epd7in5.o epdif.o font8.o font12.o font16.o font20.o font24.o font32.o font48.o epdpaint.o epd icons.o

