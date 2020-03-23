#!/bin/bash

g++ -c LexAnalyzer.cpp

g++ -c Regex.cpp

g++ -o Regex LexAnalyzer.o Regex.o
