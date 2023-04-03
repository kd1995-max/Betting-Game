# Betting Game
 
Create 2 openwrt packages
1. betclient
2. betserver

and include them in your build.

Find requirements for each as follows

requirement for betserver
-------------------------

the betting server should init on boot if its is enabled in the uci file and  continue to run forever.

plus your betting server should also read the winning numbers from a list of numbers shared in the uci file. The format of the uci file is as follows

config globals 'globals'
    option enabled '1' // 1 to enable 0 to disable
    option winning_number '100 200 300 400 500 600 700'


your bet server should expose a ubus method bet which accepts a ticket number as a mandatory argument. so a cli call to this method would look like this

ubus call bet_server bet '{"ticket_no":100}'

when a call to this method is made you bet server should place a bet with this number.

The bet server runs in a betting cycle of 1 minute so all bets places within a betting cycle are considered for that round. At the end of a round the betting server
should send an event declaring the winning ticket number and the number of bets placed in the last cycle and start next betting cycle.


the winner even should be

winner {"ticket_no":<winning ticket number>}

Requirement for betclient
--------------------------
Your betclient should be launched at will, once launched it should place a bet by making a call to the bet server's bet method and also continue to listen on the bet
server's event declaring the winner.

the ticket number that the betclient palces a bet with should be generated randomly using the time as seed.

if the betclient wins then it should exit having printed a message in the syslog saying ("process id <process id of the betclient> to universe, I just won, see you later")
and exit.

if the betclient has not won it should place another bet on receiving the winner event from the betserver for the next cycle. 
  
  
  
  Output:
![output 1.png]([https://github.com/kd1995-max/Interprocess-communication/blob/main/screenshots/acces_points.png](https://github.com/kd1995-max/Betting-Game/blob/main/Screenshots/output%201.png))
![output 2.png]([https://github.com/kd1995-max/Interprocess-communication/blob/main/screenshots/output.png](https://github.com/kd1995-max/Betting-Game/blob/main/Screenshots/output%202.jpg))
