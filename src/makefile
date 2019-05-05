CC = clang++
FLAG = -O2
STD = --std=c++17

all: main

main: main.cc compare.h experience.h file-io.h generator.h time-point.h
	$(CC) main.cc -o timeline-gen ${FLAG} ${STD}

clean:
	rm ./timeline-gen