#!/bin/zsh

# Nazwa wyjściowego programu
OUT="main"

# Wyczyść ekran
clear

# Kompilacja wszystkich plików .cpp w bieżącym katalogu
g++ -Wall -Wextra -std=c++17 *.cpp -o $OUT

# Sprawdź kod wyjścia
if [ $? -eq 0 ]; then
    ./$OUT
else
    echo "${NC}"
fi
