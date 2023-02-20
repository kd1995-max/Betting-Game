# build helloworld executable when user executes "make"
betclient: betclient.o
	$(CC) $(LDFLAGS) -lubus -lubox betclient.o -o betclient
betclient.o: betclient.c
	$(CC) $(CFLAGS) -c betclient.c

# remove object files and executable when user executes "make clean"
clean:
	rm *.o betclient
