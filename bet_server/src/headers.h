#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <uci.h>
#include <libubus.h>
#include <libubox/blobmsg.h>
#include <libubox/blobmsg_json.h>
#include <libubox/uloop.h>
#include <libubox/ustream.h>
#include <libubox/utils.h>
#include <libubus.h>
#include <uci_blob.h>
#include <time.h>
#include <syslog.h>
#include "enums_and_structs.h"

/*
*
*variable Description : ms
*
*stores the list of Bets extracted from UCI conf file
*
*/
static char *ms = NULL;

/*
*
*variable Description : ticket
*
*will store the current winning ticket
*
*/
int ticket;

/*
*
*variable Description : k
*
*used by extractIntegers functions to identify the space character which will be 
*later passed to the substr function
*
*/
int k = 0;

/*
*
*variable Description : sizeOfUciRegisteredBets
*
*will store the number of valid Bets extracted from UCI conf file
*
*/
int sizeOfUciRegisteredBets = 0;

/*
*
*variable Description : num
*
*will store the ticket number received from the client
*
*/
int num=11;

/*
*
*variable Description : betCycleCount
*
*will store the count of winning cycles
*
*/
int betCycleCount = 0;

/*
*
*variable Description : winning_tickets
*
*It is an array to store all the valid winning tickets received from UCI conf
*and is processed by extract integer function
*
*/
int *winning_tickets;
