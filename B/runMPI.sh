#!/bin/bash

# mpicc main.c -o main

mpic++ ./solucaoMPI.cpp -o main.run

mpirun -np 4 ./main.run < inputExample.txt

