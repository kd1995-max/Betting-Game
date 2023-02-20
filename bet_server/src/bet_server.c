#include "headers.h"



/*
*
*Function Description : insertStart
*
*The insertStart function is to insert a new node at the beginning of a 
*linked list. 
*The function takes two arguments: 
*
*1. a pointer to the head of the linked list, and 
*
*2. the data to be inserted. 
*
*The function creates a new node using dynamic memory allocation, initializes 
*its data field with the given data, and sets its next field to point to the 
*current head of the list. Finally, it  updates the head pointer to point to 
*the new node.
*
*The function also logs a message using the syslog function to indicate that the 
*insertion was successful. The message includes the value of the data field of 
*the new node.
*
*Note that the function does not perform any error checking to ensure that the 
*memory allocation was successful or that the head pointer is not NULL. It is up 
*to the caller to ensure that these conditions are satisfied.
*
*/
void insertStart (struct Winners_List **head, int data)
{
  struct Winners_List *newNode = 
  (struct Winners_List *) malloc (sizeof (struct Winners_List));

  newNode->data = data;
  newNode->next = *head;

  *head = newNode;
  syslog (LOG_ERR,"\n%d Inserted\n", newNode->data);
}



/*
*
*Function Description : display
*
*This Function Will display all the wining tickets contained in Linked list
*
*/
void display (struct Winners_List *node)
{  
  syslog (LOG_ERR,"Winners list starts");

  while (node != NULL)
    {
      syslog (LOG_ERR,"ticket number : %d ", node->data);
      node = node->next;
    }
  syslog (LOG_ERR,"Winners list ends");
}



/*
*
*Function Description : read_UCI_file
*
*This is a function that reads a UCI (Unified Configuration Interface) file in 
*OpenWrt and returns the value of the "winning_number" option in the "globals" 
*section of the file.
*
*The function first creates a new UCI context using uci_alloc_context(), which 
*initializes a new context for interacting with UCI data. Then it loads the UCI 
*data associated with the package "BetConf" using uci_load(), which loads the 
*contents of a UCI configuration file into memory and makes it accessible via 
*the uci_context object.
*
*Next, it looks up the "globals" section using uci_lookup_section(), and then it 
*retrieves the value of the "winning_number" option using 
*uci_lookup_option_string(), which returns the value of the option as a string.
*
*After retrieving the value of the option, the function assigns it to the ms 
*variable and then frees the UCI context using uci_free_context() before 
*returning the option value.
*
*/
static char *read_UCI_file(void)
{
   
    /*
    *
    *variable Description : context
    *
    *struct uci_context is a struct defined in the UCI (Unified Configuration 
    *Interface) library in OpenWrt. It represents a context for managing 
    *configuration data, which includes reading, modifying and saving 
    *configuration data.
    *
    */
    struct uci_context *context = NULL;
    
    /*
    *
    *variable Description : package
    *
    *struct uci_package represents a package which can contain multiple 
    *configuration sections.
    *
    */
	struct uci_package *package = NULL;
	
	/*
    *
    *variable Description : section
    *
    *sstruct uci_section represents a configuration section within a package. 
    *It contains configuration data for a specific component or application, 
    *for example the "wireless" section contains wireless configuration options.
    *
    */
	struct uci_section *section = NULL;
    
    /*
    *
    *Function Description : uci_alloc_context
    *
    *uci_alloc_context() is a function provided by the UCI library in OpenWrt 
    *to create a new UCI context. UCI context is the main structure that keeps 
    *track of configuration data read from UCI configuration files. It is used 
    *to load, query, and modify the UCI configuration data.
    *
    *The function uci_alloc_context() allocates memory for a new UCI context and 
    *initializes its data structures. The returned pointer to the UCI context is 
    *used in other UCI functions to perform operations on configuration data.
    *
    *It is important to note that any UCI context created with 
    *uci_alloc_context() must be properly freed using uci_free_context() when 
    *it is no longer needed.
    *
    */
    context = uci_alloc_context();
    
    /*
    *
    *Function Description : uci_load
    *
    *uci_load is a function from the UCI library in OpenWrt that is used to 
    *load a configuration package into memory. 
    *
    *The uci_load function takes three arguments:
    *
    *1. context: A pointer to a struct uci_context that is used to manage UCI 
    *configuration data.
    *
    *2. package: A pointer to a struct uci_package that will be assigned a 
    *pointer to the loaded configuration package.
    *
    *3. name: A string representing the name of the configuration package to 
    *load.
    *
    */
    uci_load(context, "BetConf", &package);
    
    /*
    *
    *Function Description : uci_lookup_section
    *
    *uci_lookup_section is a function provided by the libuci library, which is 
    *used to look up a specific section inside a package of UCI configuration. 
    *
    *The function takes the following parameters:
    *
    *1. ctx: a pointer to a struct uci_context object, which is the context in 
    *which to perform the lookup.
    *
    *2. package: a pointer to a struct uci_package object, which is the package 
    *in which to look up the section.
    *
    *3. name: a string that specifies the name of the section to look up.
    *
    The function returns a pointer to the struct uci_section object if the 
    *section is found, or NULL if the section is not found.
    *
    */
	section = uci_lookup_section(context, package, "globals");
	
	/*
    *
    *Function Description : uci_lookup_option_string
    *
    *uci_lookup_option_string() is a function provided by the UCI library that 
    *searches for an option in a specific section of a loaded configuration file 
    *and returns its value as a string.
    *
    *The function takes three arguments: a struct uci_context pointer that holds 
    *the context in which UCI operations are performed, a struct uci_section 
    *pointer that holds the section where the option is located, and a string 
    *that specifies the name of the option to search for.
    *
    *The function returns a pointer to a string containing the value of the 
    *option. If the option is not found or an error occurs, the function returns 
    *NULL.
    */
	const char *option = uci_lookup_option_string(context, section, 
	                    "winning_number");
	
	ms = option;
	
	/*
    *
    *Function Description : uci_lookup_option_string
    *
    *uci_free_context() is a function in OpenWRT's UCI (Unified Configuration 
    *Interface) library that is used to release the resources allocated for the 
    *UCI context.
    *
    *The UCI context is a data structure that holds the configuration data and 
    *provides an interface to read and modify configuration data. It is created 
    *using uci_alloc_context() and should be freed using uci_free_context() 
    *when the configuration data is no longer needed.
    *
    */
	uci_free_context(context);
		
	return option;
}



/*
*
*Function Description : substr
*
*The substr function takes a source string src and two integers m and n as 
*input. It returns a pointer to a new string that is a substring of the original 
*string, starting at index m and ending at index n.
*
*The function first calculates the length of the substring by subtracting m 
*from n, and then allocates memory for the new string using malloc. It then 
*iterates over the source string from index m to n, copying each character to 
*the new string. Finally, it adds a null terminator to the end of the new string 
*and returns a pointer to the beginning of the substring.
*
*One potential issue with this implementation is that it modifies the dest 
*pointer by incrementing it for each character that is copied. As a result, the 
*pointer that is returned may not be at the beginning of the new string. To fix 
*this, the function subtracts the length of the substring from dest before 
*returning it.
*
*/
char* substr(const char *src, int m, int n)
{
    int len = n - m;
    char *dest = (char*)malloc(sizeof(char) * (len + 1));
    
    for (int i = m; i < n && (*(src + i) != '\0'); i++) {
    
        *dest = *(src + i);
        dest++;
        
    }
 
    *dest = '\0';
    return dest - len;
}



/*
*
*Function Description : extractIntegers
*
*This function extractIntegers() extracts integers from a string ms and stores 
*them into an array winning_tickets. 
*
*It first determines the length of the string ms and initializes some variables 
*including k which is used to keep track of the starting position of the next 
*integer to be extracted. 
*
*Then, it loops through each character in the string, and if a space character 
*is found, it uses the substr() function to extract the integer between the 
*current position k and the position of the space character. 
*
*The integer is then converted to an integer type using atoi() and stored in the 
*winning_tickets array. The k variable is updated to the position after the 
*space character, and the loop continues. Once the loop has finished, it checks 
*if there are any remaining characters in the string and extracts the final 
*integer. Finally, the size of the array is stored in the variable 
*sizeOfUciRegisteredBets.
*
*/
void extractIntegers()
{
    int n = strlen(ms);
    int k = 0;
    int counter=0;
    char *temp = NULL;
    int i;
    
    for (i = 0; i < n; i++) {
        if (ms[i] == ' ') {
            temp = substr(ms,k,i);
            k = i + 1;
            winning_tickets[counter++] = atoi(temp);
        }
        else {
            temp = NULL;
        }
    }
    
    if (k != i) {
        temp = substr(ms,k,i);
        winning_tickets[counter++] = atoi(temp);
    }
    
    sizeOfUciRegisteredBets = counter;
}



/*
*
*Function Description : checkForWin
*
*This function will check if the bet made by the client was correct and is 
*present in winning_tickets (previously filled by extractIntegers function)
*
*/
int checkForWin(int num)
{
    for(int i = 0; i < sizeOfUciRegisteredBets; i++) {
    
        if(winning_tickets[i] == num)
        return 1;
        
    }
    
    return 0;
}



/*
*
*Function Description : registerTicket
*
*This function stores all the correct bet in ticket winning_ticketsay
*/
void registerTicket(int n)
{
    ticket = n;
    insertStart(&list,n);
    display(list);
    
}



/*
*Function Description : bet_server
*
*The bet_server function is a UBUS method handler in OpenWrt. It is responsible 
*for processing incoming requests from UBUS clients and sending replies back 
*to the clients. The function takes a UBUS context, a UBUS object, UBus request 
*data, a method name, and a message as arguments.
*
*Here is a brief overview of what the function does:
*
*The function first initializes a blob_buf buffer and sets it to zero. 
*
*This buffer is used to store the reply that will be sent back to the client.
*
*The function then calls blobmsg_parse to parse the incoming message and store 
*the parsed attributes in a tb array. The bet_policy is a blobmsg policy that 
*is used to validate the incoming message.
*
*The function extracts the num field from the message using blobmsg_get_u32 and 
*checks whether it is a winning number by calling the checkForWin function. 
*
*If the number is a winning number, the registerTicket function is called to 
*register the ticket, and a reply containing the ticket number is sent back to 
*the client using ubus_send_reply. 
*
*If the number is not a winning number, 
*the ticket number is set to zero and a reply containing the ticket number is 
*sent back to the client.
*
*The betCycleCount is then incremented, and the blob_buf buffer is freed.
*
*
*It is important to note that the bet_server function is registered as a UBus 
*method handler using ubus_add_object and can be called by UBUS clients using 
*the method name specified in the registration. 
*
*The function should return UBUS_STATUS_OK if the request was handled 
*successfully. 
*If the function  encounters an error, it should return an 
*appropriate error status.
*
*/
static int bet_server(struct ubus_context *ctx, struct ubus_object *obj,
		      struct ubus_request_data *req, const char *method,
		      struct blob_attr *msg)
{	
    /*
    *
    *variable Description : blob_attr
    *
    *blob_attr is a struct used in OpenWrt's UBus subsystem to represent a single 
    *attribute in a message. A UBus message is a binary blob that consists of one 
    *or more attributes. Each attribute has a type and a value.
    *
    *The blob_attr struct has the following members:
    *
    *1. id: A 16-bit identifier that uniquely identifies the attribute within the 
    *message.
    *2. type: An 8-bit type identifier that specifies the type of the attribute's 
    *value.
    *3. len: A 16-bit length field that specifies the length of the attribute's 
    *value in bytes.
    *4. data: A pointer to the start of the attribute's value.
    *
    *The type field of a blob_attr struct specifies the type of the attribute's 
    *value. 
    *
    *The following are some of the most commonly used types:
    *
    *1. BLOBMSG_TYPE_INT32: A 32-bit signed integer.
    *2. BLOBMSG_TYPE_STRING: A null-terminated string.
    *3. BLOBMSG_TYPE_ARRAY: An array of attributes.
    *4. BLOBMSG_TYPE_TABLE: A table of attributes.
    *
    *The blob_attr struct is used extensively in OpenWrt's UBus subsystem for 
    *parsing and generating messages. The blobmsg_parse function is used to 
    *parse a message and extract its attributes, while the blobmsg_add_* 
    *functions are used to add attributes to a message.
    *
    */
	struct blob_attr *tb[__BET_MAX];
	
	/*
    *
    *variable Description : blob_buf
    *
    *The blob_buf struct represents a buffer that holds a binary message 
    *being constructed. The struct contains the following members:
    *
    *1. buf: A pointer to the start of the buffer.
    *2. len: The length of the buffer.
    *3. head: A pointer to the start of the message.
    *
    */
	struct blob_buf bb;
	memset(&bb,0,sizeof(bb));
	
	/*
    *
    *function Description : blob_buf_init
    *
    *blob_buf_init is a function used in OpenWrt's UBus subsystem to initialize 
    *a blob_buf struct, which is used for building binary messages to be sent 
    *over UBus.
    *
    *The blob_buf_init function initializes a blob_buf struct by setting the 
    *length of the buffer to the specified size and allocating memory for it 
    *using malloc. 
    *
    *If the size argument is 0, blob_buf_init will allocate an initial buffer 
    *of size BLOBMSG_DEFAULT_SIZE (which is defined as 256 bytes) and will 
    *automatically resize the buffer as needed when more data is added to it.
    *
    *After calling blob_buf_init, you can use the blobmsg_add_* functions to 
    *add attributes to the message by specifying the attribute type and value. 
    *
    *Once you have added all the attributes to the message, you can send the 
    *message using the ubus_send_reply or ubus_send_event function, passing in 
    *the head member of the blob_buf struct as the message data. Finally, you 
    *should free the memory used by the blob_buf struct using the blob_buf_free 
    *function.
    *
    */
	blob_buf_init(&bb,0);
	
    /*
    *
    *function Description : blobmsg_parse
    *
    *blobmsg_parse is a function in OpenWrt's UBus subsystem that is used to 
    *parse a binary message into a set of blob_attr structures. A blob_attr is 
    *a structure that represents a single attribute in a UBus message.
    *
    *The blobmsg_parse function takes the following arguments:
    *
    *1. policy: A policy table that specifies the allowed attribute types and 
    *their names. The policy table is an array of blobmsg_policy structures, 
    *which specify the name, type, and minimum and maximum values (for numeric 
    *types) of each attribute.
    *
    *2. policy_len: The length of the policy table.
    *
    *3. tb: An array of blob_attr structures that will be filled in with the 
    *parsed attributes.
    *
    *4. data: A pointer to the binary message data.
    *
    *5. len: The length of the binary message data.
    *
    *When blobmsg_parse is called, it parses the binary message data into 
    *blob_attr structures according to the policy table, and fills in the tb 
    *array with pointers to the parsed attributes. 
    *
    *If any attribute is found that is not allowed by the policy table, or if
    * an attribute has an invalid value, blobmsg_parse returns an error code. 
    *Otherwise, it returns the number of attributes that were successfully parsed.
    *
    *Once the message has been parsed, the blob_attr structures can be accessed 
    *to retrieve the values of the message attributes using the blobmsg_get_* 
    *functions, which take a pointer to the blob_attr structure and return the 
    *attribute value as the appropriate type (string, integer, boolean, etc.).
    *
    */
	blobmsg_parse(bet_policy,__BET_MAX,tb,blob_data(msg),blob_len(msg));
	
	/*
    *
    *function Description : blobmsg_get_u32
    *
    *blobmsg_get_u32 is a function in OpenWrt's UBus subsystem that is used to 
    *retrieve an integer value from a blob_attr structure. It takes a pointer 
    *to a blob_attr structure as its argument and returns the integer value of 
    *the attribute if it is of the correct type (i.e., BLOBMSG_TYPE_INT32), or 
    *zero if the attribute is not of the correct type.
    *
    *The blobmsg_get_u32 function is used in UBus handlers to retrieve integer 
    *values from UBus messages that have been parsed into blob_attr structures 
    *using the blobmsg_parse function. 
    *
    */
    num = blobmsg_get_u32(tb[BET_MSG]);
	
	if(checkForWin(num) == 1) {
	    
	    /*
        *
        *function Description : registerTicket
        *
        *register the winning ticket
        */    
        registerTicket(num);
        
        /*
        *
        *function Description : blobmsg_add_u32
        *
        *blobmsg_add_u32 is a function in OpenWrt's UBus subsystem that is used 
        *to add an integer value to a blob_buf structure as a BLOBMSG_TYPE_INT32 
        *attribute. It takes a pointer to a blob_buf structure and a name-value 
        *pair as its arguments and adds a new attribute with the given name and 
        *integer value to the buffer.
        *
        *The blobmsg_add_u32 function is used in UBus handlers to add integer 
        *values to the response messages that are sent back to UBus clients. 
        *
        */
	    blobmsg_add_u32(&bb,"ticket",num);
	    
	    /*
        *
        *function Description : ubus_send_reply
        *
        *ubus_send_reply is a function in OpenWrt's UBus subsystem that is used 
        *to send a reply message to a UBus client. It takes a pointer to a 
        *ubus_context structure, a pointer to a ubus_request_data structure, 
        *and a pointer to a blob_attr structure as its arguments.
        *
        *The ubus_send_reply function is typically used in UBus handlers to 
        *send response messages to UBus clients.  
        *
        *bb is a blob_buf structure that is initialized using the blob_buf_init 
        *function, num is an integer value that represents a ticket number, and 
        *ctx and req are UBus context and request data structures, respectively. 
        *The blobmsg_add_u32 function adds a new attribute to the bb buffer with 
        *the name "ticket" and the value of num. The ubus_send_reply function 
        *sends the response message back to the UBus client with the attributes 
        *added to the bb buffer.
        *
        */
	    ubus_send_reply(ctx,req,bb.head);
    }
    else {
    
        /*
        *
        *variable Description : ticket
        *
        *setting ticket value to 0 which will represent losed bet
        */
        ticket = 0;
        blobmsg_add_u32(&bb,"ticket",ticket);
	    ubus_send_reply(ctx,req,bb.head);
    }
	
	/*
    *
    *variable Description : betCycleCount
    *
    *Count the previous bets made
    */
	betCycleCount++;
	
	/*
    *
    *function Description : blob_buf_free
    *
    *blob_buf_free is a function in OpenWrt's UBus subsystem that is used to 
    *free the memory allocated for a blob_buf structure.
    *
    *The blob_buf_free function takes a pointer to a blob_buf structure as its 
    *argument and frees the memory used by the buffer in the structure.
    *
    *In this code, bb is a blob_buf structure that is initialized using the 
    *blob_buf_init function, and num is an integer value that represents a 
    *ticket number. The blobmsg_add_u32 function adds a new attribute to the bb 
    *buffer with the name "ticket" and the value of num. The ubus_send_reply 
    *function sends the response message back to the UBus client with the 
    *attributes added to the bb buffer. Finally, the blob_buf_free function is 
    *used to free the memory used by the bb buffer.
    *
    */
	blob_buf_free(&bb);
	
	/*
    *
    *variable Description : UBUS_STATUS_OK
    *
    *UBUS_STATUS_OK is a status code in OpenWrt's UBus subsystem that indicates 
    *that a UBus request or operation was successful.
    *
    *In UBus, most functions and procedures return a status code to indicate 
    *whether the operation was successful or not. UBUS_STATUS_OK is a common 
    *status code that indicates that the operation completed successfully, 
    *without errors.
    *
    */
	return UBUS_STATUS_OK;
}



/*
*
*variable Description : bet_methods
*
*ubus_method is typically used in conjunction with other Ubus API functions 
*to define the methods that can be called on a Ubus object, so that other 
*processes in the system can communicate with it.
*
*bet_method will be passed in ubus_object_type
*
*/
static const struct ubus_method bet_methods[] = {
	UBUS_METHOD("bet", bet_server, bet_policy)
};



/*
*
*variable Description : bet_object_type
*
*ubus_object_type is typically used in conjunction with other Ubus API 
*functions to register objects and their methods with the Ubus system, 
*so that they can be accessed by other processes in the system.
*
*bet_object_type will be passed in bet_server_object's .method parameter
*/
static struct ubus_object_type bet_object_type =
	UBUS_OBJECT_TYPE("bet_server", bet_methods);



/*
*
*variable Description : bet_server_object
*
*ubus_object struct is used to represent a Ubus object, which is a logical unit 
*of functionality that can be accessed and controlled using Ubus messages.
*
*The ubus_object struct contains the following members:
*
*1. name: A string that specifies the name of the Ubus object.
*
*2. methods: An array of ubus_method structures that define the methods that 
*can be called on the object.
*
*3. n_methods: An integer that specifies the number of methods in the methods 
*array.
*
*4. type: used to register a type of object which is already defined.
*
*The ubus_object struct is typically used in conjunction with other Ubus 
*API functions to register the object and its methods with the Ubus system, 
*so that they can be accessed by other processes in the system.
*
*/
static struct ubus_object bet_server_object = {
	.name = "bet_server",
	.type = &bet_object_type,
	.methods = bet_methods,
	.n_methods = ARRAY_SIZE(bet_methods),
};



/*
*Function Description : event_handler_bet
*
*The event_handler_bet function is the event handler that sends an event to 
*the Ubus system using the ubus_send_event function. The event contains two 
*key-value pairs: 
*
*1. "ticket_no" with the value of the ticket variable, and 
*
*2. "previous bets" with the value of the betCycleCount variable. 
*
*ubus_send_event is a function provided by the Ubus API in OpenWrt that is 
*used to send an event to the Ubus system. An event is a message that can be 
*sent from one process to another to indicate that some state or condition has 
*changed or that some action has occurred.
*
*The function has the following prototype:
*
*int ubus_send_event(struct ubus_context *ctx, const char *path, 
*                   struct blob_attr *msg);
*
*1. The ctx argument is a pointer to the Ubus context, which is used to 
*identify the Ubus connection to which the event should be sent. 
*
*2. The path argument is a string that identifies the event path, which is a 
*hierarchical string that describes the namespace of the event.
*
*3. The msg argument is a pointer to a blob_attr structure that contains 
*the actual event data. 
*
*The blob_attr structure is a binary format used by Ubus to serialize data in 
*a compact and efficient way. It is constructed using a set of 
*blobmsg_add_* functions, which are used to add different types of data to 
*the blob_buf buffer.
*
*The return value of the ubus_send_event function is 0 if the event was 
*successfully sent, or a negative error code if an error occurred.
*
*In this code, blobmsg and blob_buf are used to create and manage Ubus messages 
*in a convenient way. blob_buf_init initializes a blob_buf structure, 
*which is then used to create a Ubus message using blobmsg_add_u32. 
*The resulting message is then sent to the Ubus system using ubus_send_event.
*
*/
static void event_handler_bet(struct uloop_timeout *timeout)
{
    
    struct blob_buf bb;
    memset(&bb, 0, sizeof(bb));
    blob_buf_init(&bb,0);

    blobmsg_add_u32(&bb, "ticket_no", ticket);
    blobmsg_add_u32(&bb, "previous bets", betCycleCount);
    
    ubus_send_event(ctx, "winners", bb.head);
        
    set_event_bet();
}



/*
*
*Function Description : set_event_bet
*
*The set_event_bet function is used to set a timer that will trigger 
*the event_handler_bet function every 60 seconds. It uses the 
*uloop_timeout_set function to set a timer with a callback to the 
*event_handler_bet function, which will be executed every time the timer 
*expires.
*
*uloop_timeout_set is a function provided by the Uloop API in OpenWrt that 
*is used to set a timer. A timer is a mechanism that allows a function to be 
*executed after a certain period of time has elapsed. The Uloop timer is a 
*software timer that is implemented using the event loop mechanism in OpenWrt.
*
*The function has the following prototype:
*void uloop_timeout_set(struct uloop_timeout *timeout, unsigned int msecs);
*
*The timeout argument is a pointer to a uloop_timeout structure, 
*which contains a callback function that will be executed when the timer 
*expires. The msecs argument is the duration of the timer in milliseconds.
*
*The uloop_timeout structure has the following fields:
*
*struct uloop_timeout {
*    struct list_head list;
*    struct uloop_timeout *pending;
*    void (*cb)(struct uloop_timeout *timeout);
*    unsigned int expires;
*};
*
*The list and pending fields are used internally by the Uloop system to 
*manage the timer. The cb field is a pointer to the callback function that 
*will be executed when the timer expires. The expires field is the time when 
*the timer will expire, represented as the number of milliseconds since the 
*system was started.
*
*/
void set_event_bet(void)
{

    static struct uloop_timeout bet_event_timer;
    bet_event_timer.cb = event_handler_bet;
    uloop_timeout_set(&bet_event_timer, 5*1000);
}


int main(int argc, char **argv)
{   
    
	/*
    *
    *Function Description : read_UCI_file
    *
	*calling the read_UCI_file to read the UCI file named BetConf which 
	*contains information of all the win bets 
	*/
    read_UCI_file();
    
    /*
    *
    *Function Description : winning_tickets
    *
    *allocating the size of array winning_tickets which will store the win hits
    */
    winning_tickets = (int *)malloc(sizeof(int)*strlen(ms));
    
    /*
    *
    *Function Description : extractIntegers
    *
    *This function will convert all the numbers contained in the string from 
    *UCI file into an integer
    */
    extractIntegers();
    
    /* 1. 
    *
    *Function Description : uloop_init
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
		fprintf(stderr, "Failed to connect to ubus\n");
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
    *Function Description : ubus_add_object
    *
    *ubus_add_object is a function that is used to register a new Ubus object 
    *with a Ubus context. A Ubus object is a collection of Ubus methods that 
    *can be invoked by remote clients over the Ubus protocol. By registering a 
    *Ubus object, you can expose a set of methods that can be used by other 
    *programs to interact with your application.
    *
    *The ubus_add_object function takes several arguments, including the Ubus 
    *context to which the object should be added, a Ubus object structure that 
    *defines the object's methods and handlers, and an optional path that can 
    *be used to specify the location of the object within the Ubus namespace. 
    *The function returns 0 on success, or a negative error code if an error 
    *occurs.
    *
    */ 
	int ret = ubus_add_object(ctx, &bet_server_object);
	if (ret)
		fprintf(stderr, "Failed to add object: %s\n", ubus_strerror(ret));

    /*
     *
    *Function Description : set_event_bet
    *
    *setting up event handler function is used to register a Ubus event handler 
    *that will be called whenever an event of type "event_handler_bet" 
    *is received
    *
    */
    set_event_bet();
    
    /* 5.     
    *
    *Function Description : uloop_run
    *
    *uloop_run is a function in OpenWrt that starts the main event loop and 
    *waits for events to occur. The function is part of the Uloop library.
    *
    *The uloop_run function takes no arguments and returns when the event loop 
    *has been stopped. While the event loop is running, the Uloop library will 
    *monitor file descriptors, timers, and other events for activity, and 
    *invoke registered callback functions when events occur.
    *
    */ 
	uloop_run();
	
    /* 6.     
    *
    *Function Description : uubus_free
    *
    *ubus_free is a function in OpenWrt that is used to free resources 
    *allocated by the UBus library. The function takes a pointer to a UBus 
    *context as an argument and frees all memory associated with that context.
    *
    *It is important to note that once a context is freed, it cannot be used 
    *again without first creating a new context. Additionally, any objects or 
    *subscribers that were registered with the context will be automatically 
    *unregistered and their resources freed.
    *
    */ 
	ubus_free(ctx);
	
	/* 7.     
    *
    *Function Description : uloop_done
    *
    *uloop_done is a function in OpenWrt that is used to clean up and 
    *release resources used by the Uloop library. The function takes no 
    *arguments and should be called when the event loop is no longer needed 
    *and the program is about to exit.
    *
    *It is important to always call uloop_done to avoid memory leaks and other 
    *resource issues. If uloop_done is not called, the Uloop library may not 
    *be able to release its resources and may continue running in the 
    *background, which can cause unexpected behavior and resource issues 
    *in the system.
    *
    */ 
	uloop_done();

	return 0;
}
