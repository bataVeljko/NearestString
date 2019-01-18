import sys
import random

def main():
    if len(sys.argv) != 3:
        sys.exit('3 arguments needed... program | numOfWords | lenOfWords')

    path = "words.txt"
    numOfWords = int(sys.argv[1])
    length = int(sys.argv[2])

    allowedSymbols = ['A', 'C', 'T', 'G']
    # allowedSymbols = ['0', '1']

    try:
        with open(path, 'w') as f:
            for i in range(numOfWords):
                word = ['A' for k in range(length)]
                for j in range(length):
                    index = random.randrange(0, len(allowedSymbols))
                    word[j] = allowedSymbols[index]
                f.write(''.join(word) + '\n')

    except Exception as e:
        raise e


if __name__ == '__main__':
    main()