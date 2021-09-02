-include config.mk

ge:             ge.o menu.o console.o getileset.o gensprite.o debug.o inifiles.o gelua.o globals.o inputs.o playsound.o
	$(CC) -o ge ge.o menu.o console.o getileset.o gensprite.o debug.o inifiles.o gelua.o globals.o inputs.o playsound.o $(LIBS)

console.o: console.c console.h config.h
	$(CC) -c console.c $(CFLAGS)

menu.o: menu.c menu.h config.h
	$(CC) -c menu.c $(CFLAGS)

gensprite.o: gensprite.c gensprite.h config.h
	$(CC) -c gensprite.c $(CFLAGS)

getileset.o: getileset.c getileset.h config.h
	$(CC) -c getileset.c $(CFLAGS)

debug.o: debug.c debug.h config.h
	$(CC) -c debug.c $(CFLAGS)

inputs.o: inputs.c inputs.h config.h globals.h ge.h
	$(CC) -c inputs.c $(CFLAGS)

playsound.o: playsound.c playsound.h config.h globals.h ge.h
	$(CC) -c playsound.c $(CFLAGS)

inifiles.o: inifiles.c inifiles.h config.h
	$(CC) -c inifiles.c $(CFLAGS)

gelua.o: gelua.c gelua.h config.h
	$(CC) -c gelua.c $(CFLAGS)

globals.o: globals.c globals.h config.h
	$(CC) -c globals.c $(CFLAGS)

ge.o: ge.c ge.h globals.h config.h
	$(CC) -c ge.c $(CFLAGS)

clean:
	rm -f ge *.o ./log/*.log 

test: ge
	./ge

