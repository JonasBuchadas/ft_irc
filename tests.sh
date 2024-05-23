#!/usr/bin/env bash

port=$1

# Create named pipes (FIFOs)
mkfifo /tmp/user_a_fifo
mkfifo /tmp/user_b_fifo
mkfifo /tmp/user_c_fifo

# Open a new terminal and initialize it with commands
open_terminal() {
    local user=$1
    local fifo=$2
    local pos=$3

    xterm -geometry 60x24+$pos -title "USER $user" -e bash -c "
        (cat $fifo; cat) | nc localhost $port
    " &
}

# Open terminals with named pipes for initial input
open_terminal "a" "/tmp/user_a_fifo" "100+300"
open_terminal "b" "/tmp/user_b_fifo" "470+300"
open_terminal "c" "/tmp/user_c_fifo" "840+300"

# Send initial commands to the IRC server through the named pipes
echo -e "PASS $2\nNICK a\nUSER a\n" > /tmp/user_a_fifo
echo -e "PASS $2\nNICK b\nUSER b\n" > /tmp/user_b_fifo
echo -e "PASS $2\nNICK c\nUSER c\n" > /tmp/user_c_fifo


# Cleanup function to remove FIFOs and kill child processes
terminate_children() {
    pkill -KILL -P $$
    rm /tmp/user_a_fifo /tmp/user_b_fifo /tmp/user_c_fifo
}

trap terminate_children EXIT
wait

