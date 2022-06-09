#!/bin/bash

###USER VARIABLES
#graphical terminal emulator that isn't xterm or konsole, preferably alacritty
userTerm=alacritty



# check if program exists
if ! command -v Xephyr &> /dev/null
then
    echo "This script requires Xephyr, try installing your distribution's X11 devel package";
	echo "Arch Pkg name: xorg-server-devel"
    exit
fi

# check if user terminal emulator exits
if ! command -v $userTerm &> /dev/null
then
    echo "This script requires $userTerm, try installing it or changing \$userTerm in this script";
    exit
fi

curWD=$(sed 's#.*/##' <<< $(pwd));
if [ $curWD != "XClient" ]; then
	echo "This script requires that the working directory must be the XClient directory";
	exit
fi

pkill Xephyr

Xephyr -br -ac -noreset -screen 800x600 :9 &

sleep 2;

../../../build/src/XServer/XClient/xClient &

sleep 1;

declare -a procs

DISPLAY=:9

for i in {0..4}
do
	echo "";
	$userTerm &
	sleep 0.2;
	procs[$i]=$!;
done

for i in "${!procs[@]}"
do
	kill -15 ${procs[$i]}
	sleep 0.75
done

for i in {0..1}
do
	$userTerm &
	sleep 0.2;
	procs[$i]=$!;
done

$userTerm &
procs[3]=$!

$userTerm &
procs[4]=$!

echo $procs;


