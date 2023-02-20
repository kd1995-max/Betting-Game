#include "headers.h"



/*
*function Description : receive_event
*
*This function receives the "winners" event sent by the server via Ubus. 
*
*It extracts the winning ticket number from the message and checks if 
*the client has won the bet or not. 
*
*If the client has won the bet, 
*the function prints a message to the console and exits the process. 
*
*If the client has lost the bet, 
*the function generates a new random number and sends a new "bet" request 
*to the server via Ubus.
*
*The struct ubus_event_handler parameter is used to register this function 
*as a callback to be called by Ubus when a "winners" event is received. 
*
*The struct blob_attr parameter contains the message received from the 
*server, which is a binary large object (blob) that may contain 
*multiple attributes. 
*
*The blobmsg_parse() function is used to extract the ticket number from 
*the message.
*
*The rand() function is used to generate a new random number, which is 
*multiplied by 50 and stored in the random_number variable. 
*
*The memset() function is used to clear the b variable, which is used 
*to store the message to be sent to the server. 
*
*The blob_buf_init() function is used to initialize b as a binary large 
*object. 
*
*The blobmsg_add_u32() function is used to add the ticket_no attribute 
*to b with the new random number. 
*
*The ubus_invoke() function is used to send the "bet" request to the 
*server.
*
*/

static void receive_event(struct ubus_context *ctx, 
                            struct ubus_event_handler *ev,
			                const char *method,struct blob_attr *msg)
{
	if(!msg || !ev) {
		return;
	}
    
	int winning_ticket;
	struct blob_attr *tb[1];                                                
	static const struct blobmsg_policy recvd_msg[1] = {                     
		[0] = {.name = "ticket_no", .type=BLOBMSG_TYPE_INT32},};          


	blobmsg_parse(recvd_msg, 1, tb, blob_data(msg), blob_len(msg));             

	if(!tb[0]) {
		return;
	}

	if(blobmsg_type(tb[0]) == BLOBMSG_TYPE_INT32) {                   
		winning_ticket = blobmsg_get_u32(tb[0]);                          
	} else {                                                          
		printf("Ubus didnt returned any value!\n");
		return;                                                 
	}                                                             
	
	if(!winning_ticket) {
	    random_number = (rand() % 10 + 1) * 50;
        memset(&b, 0, sizeof(b));
        blob_buf_init(&b,0);
        blobmsg_add_u32(&b, "ticket_no", random_number);
        ubus_invoke( ctx, obj_id, "bet", b.head, NULL, NULL, 5000 );
	    printf("The Bet was Lost\n");
	}
	else {
	    int p_id = getpid();
		printf("Client Won. Exiting :)\n");
		syslog(LOG_INFO, "Process ID %d to universe, I just Won. See ya later!", p_id);
		exit(0);
	}
    
	return;
}

int main() {
	
	/*
    *
    *variable Description : ctx
    *
    *In the OpenWrt operating system, ubus_context is a data structure that 
    *represents the UBus system context. It is used to manage the communication 
    *between UBus clients and servers.
    *
    The ubus_context structure is defined in the ubus.h header file, and it contains 
    *information such as the UBus socket file descriptor, a list of registered UBus 
    *objects, and a UBus message buffer.
    *
    */
	struct ubus_context *ctx;

	/*
    *
    *variable Description : ctx
    *
    *This function seeds the random number generator with the current time, 
    *which is used in generating random numbers using rand() function. Since 
    *time() returns the current time in seconds since January 1, 1970, this 
    *ensures that each time the program is run, a different seed value is 
    *generated for the random number generator.
    *
    */
	srand(time(NULL));

	/* 1. 
    *
    *Function Description : create an epoll instatnce descriptor poll_fd 
    *
    *uloop_init is a function provided by the Uloop API in OpenWrt that is 
    *used to initialize the Uloop event loop. 
    *
    *The Uloop event loop is a software loop that waits for events to occur and 
    *then dispatches the corresponding callbacks. The event loop is the central 
    *component of the Ubus system in OpenWrt, and is responsible for handling 
    *all Ubus-related events.
    *
    *The uloop_init function initializes the Uloop event loop and sets up the 
    *necessary data structures. It must be called before any other Uloop 
    *functions can be used.
    *
    */   
	uloop_init();

	/* 2.  
    *
    *Function Description : ubus_connect 
    *
    *ubus_connect is a function provided by the Ubus API in OpenWrt that is 
    *used to connect to the Ubus system. 
    *
    *The ubus_connect function creates a new Ubus context and connects to the 
    *Ubus system. If the connection is successful, the function returns a 
    *pointer to the new Ubus context. If the connection fails, the function 
    *returns NULL.
    *
    *the ubus_connect function is called with NULL as the path argument to 
    *connect to the default Ubus socket file. If the connection is successful, 
    *a pointer to the new Ubus context is returned and stored in the ctx 
    *variable. If the connection fails, an error message is printed to the 
    *standard error stream and the program exits.
    *
    *After the Ubus context has been obtained, it can be used to perform 
    *various Ubus-related operations, such as sending and receiving Ubus 
    *messages. Finally, the ubus_free function is called to disconnect from the 
    *Ubus system and free the resources associated with the Ubus context.
    *
    *about Ubus context
    *the Ubus context is a data structure used to represent a connection to 
    *the Ubus system.
    *The Ubus context is a handle that is used to interact with the Ubus system 
    *and send/receive Ubus messages.
    *The Ubus context is created by calling the ubus_connect function, which 
    *establishes a connection to the Ubus system and returns a pointer to a 
    *newly created Ubus context. The Ubus context is then used to perform 
    *various Ubus-related operations, such as sending and receiving Ubus 
    *messages, subscribing to Ubus events, and managing Ubus objects and methods.
    *
    */
	ctx = ubus_connect(NULL);

	if (!ctx) {
		printf("\nFailed to connect to ubus\n");
		syslog(LOG_INFO,"Failed to connect to UBUS\n");
		return -1;
	}

	/* 3.   
    *
    *Function Description : ubus_add_uloop
    *
    *ubus_add_uloop is a function that is used to integrate Ubus into the main 
    *event loop of the system. The main event loop is managed by the Uloop 
    *system, which provides a platform-independent interface for managing 
    *various event sources and timers in a single loop. By adding Ubus to 
    *the Uloop event loop, it is possible to receive Ubus messages and events 
    *as they arrive, without the need for a separate thread or polling loop.
    *
    *The ubus_add_uloop function takes a Ubus context as its argument, and 
    *registers it with the Uloop system. Once registered, the Ubus context can 
    *receive Ubus messages and events as they occur. The function returns 0 on 
    *success, or a negative error code if an error occurs.
    *
    */   
	ubus_add_uloop(ctx);
    
    /* 4.   
    *
    *Function Description : ubus_lookup_id
    *
    *ubus_lookup_id is a function in the ubus library of OpenWRT that searches 
    *for a registered ubus object with the given name and returns its ID. 
    *The ID can be used to call the ubus object's methods. The function has the 
    *following signature:
    *
    *int ubus_lookup_id(struct ubus_context *ctx, 
    *                   const char *path, 
    *                   uint32_t *id);
    *
    *where:
    *
    *1. ctx: pointer to the ubus context
    *
    *2. path: the name of the ubus object to search for
    *
    *3. id: pointer to a variable that will hold the ID of the ubus object if 
    *found
    *
    *The function returns 0 on success and a negative error code on failure.
    *
    */  
    int status = ubus_lookup_id(ctx, "bet_server", &obj_id);
    
	if(status){	
		syslog(LOG_INFO,stderr);
		syslog(LOG_INFO,"Problem in connection\n");
	}
	
    //Updating Random Number
	random_number = (rand() % 10 + 1) * 50;
	
	/*  
    *
    *Function Description : refer betserver
    *
    */
    memset(&b, 0, sizeof(b));
    
    /*  
    *
    *Function Description : blob_buf_init
    *
    *refer betserver
    *
    */
    blob_buf_init(&b,0);
    
    /*  
    *
    *Function Description : blobmsg_add_u32
    *
    *refer betserver
    *
    */
    blobmsg_add_u32(&b, "ticket_no", random_number);
    
	/*  5.
    *
    *Function Description : ubus_invoke
    *
    *ubus_invoke is a function used in the UBus framework, which is a message 
    *bus system used in OpenWrt and other similar embedded systems. The purpose 
    *of ubus_invoke is to send a request to an object in the UBus system and 
    *wait for a response.
    *
    *The function takes several parameters:
    *
    *1. ctx: a pointer to the UBus context structure.
    *
    *2.obj: a pointer to the UBus object structure that the request should be 
    *sent to.
    *
    *3. method: the name of the UBus method to call.
    *
    *4. msg: a pointer to a blob structure that contains the message to send.
    *
    *5. cb: a pointer to a function that will be called when a response is 
    *received.
    *
    *6. priv: a pointer to user data that will be passed to the callback 
    *function.
    *
    *7. timeout: by what time a callback will be called it is specified in 
    *miliseconds
    *
    *The ubus_invoke function is non-blocking, which means that it returns 
    *immediately after sending the request. When a response is received, the 
    *callback function specified in the cb parameter is called with the response 
    *message as a parameter.
    *
    */
    ubus_invoke( ctx, obj_id, "bet", b.head, NULL, NULL, 5000 );
	
	
	/*  6.
    *
    *variable Description : event and ev
    *
    *This code sets up an event handler for the "winners" event in the UBUS 
    *system. The event handler function receive_event will be called when an 
    *event with the name "winners" is received.
    *
    *The ubus_event_handler structure is used to specify the event handler 
    *function and additional options for the event handler, such as a context 
    *pointer that can be used to pass additional data to the event handler.
    *
    *The cb field of the ubus_event_handler structure is a function pointer that 
    *points to the event handler function. In this case, the event handler 
    *function is
    *
    */
	const char *event = "winners";
	struct ubus_event_handler ev = {
		.cb = receive_event,
	};
	
	/*  6.
    *
    *function Description : ubus_register_event_handler
    *
    *ubus_register_event_handler is a function provided by the UBUS 
    *(OpenWrt's Unified Bus System) API, which is used to register a callback 
    *function that is called when a particular UBUS event occurs. The function 
    *takes the following parameters:
    *
    *1. ctx: A pointer to the ubus_context object that represents the UBUS 
    *connection.
    *
    *2. ev: A pointer to a ubus_event_handler object that describes the event 
    *and the callback function that will handle it.
    *
    *3. path: A string that specifies the UBUS object path for which to register 
    *the event handler.
    *
    *The callback function specified in the ubus_event_handler object takes the following parameters:
    *
    *1. ctx: A pointer to the ubus_context object that represents the UBUS connection.
    *2. obj: A pointer to the UBUS object that triggered the event.
    *3. event: A string that specifies the name of the event that occurred.
    *4. data: A pointer to the event data.
    *
    */
	ubus_register_event_handler(ctx,&ev,event);
    
    
	//Uloop routine : event monitoring.
	uloop_run();

	return 0;
}
