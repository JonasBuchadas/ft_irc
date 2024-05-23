#!/usr/bin/bash

# USER a
xterm -geometry 80x24+100+300  -title "USER a" -e bash -c "nc localhost 10000 <<< 'PASS a
NICK a
USER a
'" &

# USER c
xterm -geometry 80x24+800+300 -title "USER c" -e bash -c "nc localhost 10000 <<< 'PASS a
NICK c
USER c
'" &

# USER b
xterm -geometry 80x24+400+300 -title "USER b" -e bash -c "nc localhost 10000 <<< 'PASS a
NICK b
USER b
'" &

#HexChat
xterm -geometry 80x14+400+400 -title "HexChat" -e bash -c "hexchat irc localhost 10000" &

terminate_children() {
    pkill -KILL -P $$
}

trap terminate_children EXIT
wait