
/*
*
*enum Description : enum
*
*Enum created to have policy ordered with names
*
*/
enum {
	BET_MSG,
	__BET_MAX
};

/*
*
*variable Description : bet_policy
*
*blobmsg_policy is a mechanism in OpenWrt's UBus subsystem for defining a 
*policy for parsing the contents of a message received by a UBus server.
*
*When a UBus server receives a message, it needs to extract the data from the 
*message and use it to perform some operation. 
*
*The blobmsg_policy mechanism is used to specify what data is expected to be 
*present in the message, what types the data should be, and how the data should 
*be extracted from the message.
*
*The blobmsg_policy mechanism is implemented using an array of struct 
*blobmsg_policy structures. Each structure in the array specifies a single 
*expected data element in the message. 
*
*The fields in each structure specify the name of the data element, the type of 
*the data element, and any additional constraints or requirements on the data 
*element.
*
*Example
*static const struct blobmsg_policy my_msg_policy[] = {
*    { "id",  BLOBMSG_TYPE_INT32 },
*    { "name", BLOBMSG_TYPE_STRING },
*    { "data", BLOBMSG_TYPE_UNSPEC },
*    { "flag", BLOBMSG_TYPE_BOOL },
*};
*
*/
static const struct blobmsg_policy bet_policy[] = {
	[BET_MSG] = { .name = "ticket_no", .type = BLOBMSG_TYPE_INT32 }
};

/*
*
*variable Description : Winners_List
*
*This defines a linked list which will be storing all the winning tickets
*as the data element
*/
struct Winners_List {
    int data;
    struct Node* next;
};

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
static struct ubus_context *ctx;

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
static struct blob_buf b;

/*
*
*variable Description : list
*
*created a Winners_List pointer
*/
static struct Winners_List *list = NULL; 
