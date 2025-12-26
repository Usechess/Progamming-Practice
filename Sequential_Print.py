import time
import sys

def sequential_print(text, delay=0.1, newline=True):
    for char in text:
        sys.stdout.write(char)
        sys.stdout.flush()
        time.sleep(delay)
    
    if newline:
        print()  # Ensures that a new line is printed at the end if 'newline' is True.


if __name__ == "__main__":
    text1 = "Hello, this is the first message!"
    sequential_print(text1, delay=0.2)

    text2 = "This is another message with a longer delay."
    sequential_print(text2, delay=0.01)

    text3 = "This will be printed continuously"
    sequential_print(text3, delay=0.1, newline=False)

    text4 = "Quick print!"
    sequential_print(text4, delay=0.05)