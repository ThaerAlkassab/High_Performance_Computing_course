#!/usr/bin/python3
import random

g = random.randint(1,100)

inp = 0
cont = 1
while g != inp:
    inp = int(input("Make a guess "))
    if inp < g:
        print("Is bigger ")
        cont +=1
    elif inp > g:
        print("Is smaller ")
        cont +=1
    else:
        print(cont)