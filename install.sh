#!/usr/bin/bash

if [ ! -e /usr/include/ncurses.h ]; then
    echo "Couldn't locate 'ncurses.h' in '/usr/include/'. Failed to install."
    exit 1
fi;

if [ ! -e /usr/bin/cc ]; then 
    echo "Couldn't locate 'cc' in '/usr/bin/'. Failed to install."
    exit 1
fi;

sudo cc -o /usr/local/bin/snow snow.c -lncurses
echo "Installation successful! Program is located at '/usr/local/bin/snow'"
echo "Run 'snow --help' for information on options available"