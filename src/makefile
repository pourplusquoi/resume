CC = clang++
FLAG = -O2
STD = --std=c++17

all: main

main: main.cc eq.h experience.h generator.h time-point.h
	$(CC) main.cc -o timeline-gen ${FLAG} ${STD}

clean:
	rm ./timeline-gen