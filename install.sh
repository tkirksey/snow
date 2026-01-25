#!/usr/bin/bash

if [ -e /usr/include/ncurses.h ]; then
    sudo gcc -o /usr/local/bin/snow snow.c -lncurses
else
    echo "Couldn't find 'ncurses.h' in '/usr/include/'. Try Installing 'libncurses-dev' with your package manager."
fi;