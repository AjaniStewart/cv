import sys
import os

a = os.listdir(".")
a.remove(sys.argv[0])

print(a)
