import time
import sys
from Sequential_Print import sequential_print


print("This is a bit calculator, it can be used to know how many numbers (from 0) can be represented with a given number of bits\n")
time.sleep(0.6)

while True:
    try:
        n = int (input("Number of bits? (It has to be a positive number): "))
        if n <= 0:
            print ("The number has to be more than 0")
            continue
        
        nf = (2 ** n) - 1
        print(f"With {n} of bits you can count from 0 to {nf}")
        break
    except ValueError:
        print ("Numbers and letters are not allowed, please enter a positive number")
        continue

text = "Hello world, this is a new project!"
sequential_print(text, delay=0.3)
