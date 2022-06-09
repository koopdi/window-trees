#!/bin/bash

# check if program exists


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
	alacritty &
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
	$(alacritty) &
	sleep 0.2;
	procs[$i]=$!;
done
alacritty --command=top &
procs[3]=$!

alacritty --command=$EDITOR &
procs[4]=$!

echo $procs;
