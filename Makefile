#!/bin/bash

CC=g++
FLAGS=-Wall -g
LIBS=-lcgraph
SRC=$(wildcard *.cpp)
OBJS=$(subst .cpp,.o,$(SRC))
RM=rm -f
OUTPUT=toposort

all: $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(OUTPUT) $(LIBS)

%.o: %.cpp
	$(CC) $(FLAGS) -c $< $(LIBS)

run:
	./$(OUTPUT)

clean:
	@$(RM) $(OBJS)

purge: clean
	@$(RM) $(OUTPUT)