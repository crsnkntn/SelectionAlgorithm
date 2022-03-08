import random
import os

def main():
    writefile = open("random.txt", "w+")
    for _ in range(1, 100):
        for _ in range(1, 4):
            writefile.write(str(random.randint(1, 100)) + " ", end='')


if __name__ == "__main__":
    main()