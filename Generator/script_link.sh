#!/bin/bash

g++ -c GenDefault.cpp

g++ -c GenErr.cpp

g++ -c Generator.cpp

g++ -o Generator GenDefault.o GenErr.o Generator.o