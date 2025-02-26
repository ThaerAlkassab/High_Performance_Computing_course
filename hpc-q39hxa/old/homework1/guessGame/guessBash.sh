#!/usr/bin/bash

function human_guess(){
    guess=0
    typeset -i num=0

    echo -e "Guess a number"
    (( answer = RANDOM % 100 + 1))

    while ((guess != answer)); do
        num=num+1
        read -p "Enter a guess $num: " guess
        if (( guess < answer)); then
            echo "Higher"
        elif (( guess > answer)); then
            echo "Lower"
        fi
    done
    echo -e "Correct! Number of guesses $num \n"
}

function cpu_guess(){
    guess=0
    lower=0
    maxi=101
    typeset -i num=0

    typeset -i answer=0
    read -p "Enter number: " answer

    while ((guess != answer)); do
        num=num+1
        a=maxi-lower
        (( guess= (RANDOM % (a+ 1)) + lower ))
        echo -e "CPU guess is $guess"
        if (( guess < answer)); then
            echo "Higher"
            (( lower=guess))
        elif (( guess > answer)); then
            echo "Lower"
            (( maxi=guess))
        fi
    done
    echo -e "Correct! Number of guesses $num \n"
}

function cpu_vs_cpu(){
    guess=0
    lower=0
    maxi=101
    typeset -i num=0

    typeset -i answer=0
    (( answer = RANDOM % 100 + 1))
    echo -e "CPU1 number is $answer"

    while ((guess != answer)); do
        num=num+1
        a=maxi-lower
        (( guess= (RANDOM % (a+ 1)) + lower ))
        echo -e "CPU guess is $guess"
        if (( guess < answer)); then
            echo "Higher"
            (( lower=guess))
        elif (( guess > answer)); then
            echo "Lower"
            (( maxi=guess))
        fi
    done
    echo -e "Correct! Number of guesses $num \n"
}


typeset -i mode=0
echo -e "1) Human guess"
echo -e "2) CPU guess"
echo -e "3) CPU vs CPU"
read -p "Enter a game mode: " mode
if (( mode == 1 )); then
    human_guess
elif (( mode == 2 )); then
    cpu_guess
elif (( mode == 3 )); then
    cpu_vs_cpu
fi