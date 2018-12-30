import sys
import random

def main():
    if len(sys.argv) != 4:
        sys.exit('4 arguments needed... program | output_file | numOfWords | lenOfWords')

    path = sys.argv[1]
    numOfWords = int(sys.argv[2])
    length = int(sys.argv[3])

    allowedSymbols = ['A', 'C', 'T', 'G']

    try:
        with open(path, 'a') as f:
            for i in range(numOfWords):
                word = ['A' for k in range(length)]
                for j in range(length):
                    index = random.randrange(0, len(allowedSymbols))
                    word[j] = allowedSymbols[index]
                f.write(''.join(word) + ' ')

    except Exception as e:
        raise e


if __name__ == '__main__':
    main()