from cs50 import get_int

# Takes user's input
height = 0
while height > 8 or height < 1:
    height = get_int("Choose a height: ")

for i in range(1, height + 1):
    print(" " * (height - i) + "#" * i + "  " + "#" * i)