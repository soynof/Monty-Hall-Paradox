# Monty-Hall-Paradox
Example of Monty Hall Paradox with odds of winning

# Functionality
Simulator of the game "Monty Hall" with a random generator.
This program simulates the execution of N moves to calculate the probabilities of winning, opting for the first choice of gate or the subsequent one.

# How to make & play

## Use

Syntaxis: ./monty_hall[.exe] runs

runs: number of game simulations

## Windows (using mingw64)
    g++.exe -g .\monty_hall.cpp -o .\monty_hall.exe
    ./montly_hall.exe 100
## Linux
    g++ monty_hall.cpp -o monty_hall
    ./monty_hall 100