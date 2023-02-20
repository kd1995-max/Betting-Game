# build bet_server executable when user executes "make"
bet_server: bet_server.o
	$(CC) $(LDFLAGS) -lubus -lubox -luci -w bet_server.o -o bet_server
bet_server.o: bet_server.c
	$(CC) $(CFLAGS) -c bet_server.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o bet_server
