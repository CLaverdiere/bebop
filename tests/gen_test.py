# Generates random mathematical expressions for testing.
# Not perfect. You'll probably have to run it a few times before it doesn't
# crash from div / mod by 0 error. I'm not sure how to avoid evaluated
# expressions becoming 0 without a lot more code. Also there's some negative
# modulos, not sure if that's ok or not.

from random import choice, randrange, randint, random
import re
import sys

def gen():
    # Maximum generations to reduce
    max_gens = 12 

    # Expression symbol
    s = 'e'

    # All production rules
    prods = ["e + e", "e - e", "e * e", "e / e", "e % e", "e ** x", "(e)", "-e"]

    # Randomly choose productions up to max_gens generations.
    for i in range(max_gens):
        cbuf = ""
        for char in s:
            if char == 'e':
                cbuf += choice(prods)
            else:
                cbuf += char
        s = cbuf

    # Remove all redundant (e) productions
    s = s.replace("(e)", "e")
    s = s.replace("(-e)", "-e")

    # Remove all repeated unary (-)
    s = re.sub(r'-+', '-', s)

    # Replace each remaining e with a random number.
    while 'e' in s:
        s = s.replace('e', str(randrange(1, 9)), 1)

    # Replace exponents separately.
    # I'm limiting exponents to prevent overflow.
    while 'x' in s:
        s = s.replace('x', str(randrange(2, 3)), 1)

    return s

def main():
    s = gen()
    while not (-sys.maxint < eval(s) < sys.maxint):
        s = gen()

    print(s)
    print("Answer: ", eval(s))

main()
