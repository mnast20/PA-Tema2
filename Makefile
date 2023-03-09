# Nastase Maria 321CA

CC = g++
CFLAGS  = -g -Wall

TASK1 = task1/curatare
TASK2 = task2/fortificatii
TASK3 = task3/beamdrone
TASK4 = task4/curse

default: build

build: p1 p2 p3 p4

p1: task1/curatare.cpp
	g++ -o curatare task1/curatare.cpp -Wall

p2: task2/fortificatii.cpp
	g++ -o fortificatii task2/fortificatii.cpp -Wall

p3: task3/beamdrone.cpp
	g++ -o beamdrone task3/beamdrone.cpp -Wall

p4: task4/curse.cpp
	g++ -o curse task4/curse.cpp -Wall

run-p1:
	./curatare

run-p2:
	./fortificatii

run-p3:
	./beamdrone

run-p4:
	./curse

clean:
	$(RM) ./curatare ./fortificatii ./beamdrone ./curse