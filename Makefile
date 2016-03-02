GHOST: GHOST.o
	gcc GHOST.o -o GHOST
GHOST.o: GHOST.o
	gcc -c GHOST.c -D_FILE_OFFSET_BITS=64
CLEAN:
	rm *.o GHOST
INSTALL: GHOST
	cp $< /usr/local/bin/GHOST
UNINSTALL: GHOST
	rm -f $< /usr/local/bin/GHOST
