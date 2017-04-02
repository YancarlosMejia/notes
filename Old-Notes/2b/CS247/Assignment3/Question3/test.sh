#!/bin/bash
blue='\e[0;34m'
none='\e[0m'


echo -e "${blue}WrongWord${none}"
./GuessWrongWord

echo -e "${blue}CapitalLetters${none}"
./GuessCapitalLetters

echo -e "${blue}CorrectWord${none}"
./GuessCorrectWord

echo -e "${blue}WrongWord${none}"
./GuessWrongWord

echo -e "${blue}Letters${none}"
./GuessLetters

echo -e "${blue}NewRound${none}"
./NewRound

echo -e "${blue}Seed${none}"
./Seed

echo -e "${blue}NoFile${none}"
./NoFile

echo -e "${blue}BadFile${none}"
./BadFile
