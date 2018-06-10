#!/bin/sh

aubiotrack -i ./sources/music/$1.wav > ./sources/music/$1-beat.txt
aubiotrack -i ./sources/music/$1.wav -f -o ./sources/music/$1-beat.wav
