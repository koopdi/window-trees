#!/bin/bash

pkill Xephyr

Xephyr -br -ac -noreset -screen 800x600 :9 &

sleep 2;

../../../build/src/XServer/XClient/xClient &

sleep 1;

procs=();

DISPLAY=:9

for i in {0..4}
do
	$(alacritty) &
	sleep 0.5;
	procs+=($!);
done

for id in procs
do
	pkill id;
	echo id;
done

for i in {0..2}
do
	$(alacritty) &
	sleep 0.5;
	procs+=($!);
done

echo procs;
