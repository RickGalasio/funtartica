-include config.mk

$(GE):             ge.o menu.o console.o getileset.o rnd.o gensprite.o debug.o inifiles.o gelua.o globals.o inputs.o playsound.o
	$(CC) -o $(GE) ge.o menu.o console.o getileset.o rnd.o gensprite.o debug.o inifiles.o gelua.o globals.o inputs.o playsound.o $(LIBS)

console.o: src/console.c src/console.h src/config.h
	$(CC) -c src/console.c $(CFLAGS)

menu.o: src/menu.c src/menu.h src/config.h
	$(CC) -c src/menu.c $(CFLAGS)

rnd.o: src/rnd.c src/rnd.h
	$(CC) -c src/rnd.c $(CFLAGS)

gensprite.o: src/gensprite.c src/gensprite.h src/config.h
	$(CC) -c src/gensprite.c $(CFLAGS)

getileset.o: src/getileset.c src/getileset.h src/config.h
	$(CC) -c src/getileset.c $(CFLAGS)

debug.o: src/debug.c src/debug.h src/config.h
	$(CC) -c src/debug.c $(CFLAGS)

inputs.o: src/inputs.c src/inputs.h src/config.h src/globals.h src/ge.h
	$(CC) -c src/inputs.c $(CFLAGS)

playsound.o: src/playsound.c src/playsound.h src/config.h src/globals.h src/ge.h
	$(CC) -c src/playsound.c $(CFLAGS)

inifiles.o: src/inifiles.c src/inifiles.h src/config.h
	$(CC) -c src/inifiles.c $(CFLAGS)

gelua.o: src/gelua.c src/gelua.h src/config.h
	$(CC) -c src/gelua.c $(CFLAGS)

globals.o: src/globals.c src/globals.h src/config.h
	$(CC) -c src/globals.c $(CFLAGS)

ge.o: src/ge.c src/ge.h src/globals.h src/config.h
	$(CC) -c src/ge.c $(CFLAGS)

clean:
	rm -f ge ge.exe ge.html ge.wasm ge.js *.o ./log/*.log 

