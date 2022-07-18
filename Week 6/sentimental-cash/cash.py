from cs50 import get_float

# Ask how many change the customer is owed
while True:
    cents = get_float("Change owed: ")
    if cents > 0:
        break
cents = round(cents * 100)

# Initialize coins variable
coins = 0

# Calculate the number of quarters to give the customer
while cents >= 25:
    cents -= 25
    coins += 1
# Calculate the number of dimes to give the customer
while cents >= 10:
    cents -= 10
    coins += 1
# Calculate the number of nickels to give the customer
while cents >= 5:
    cents -= 5
    coins += 1
# Calculate the number of pennies to give the customer
while cents >= 1:
    cents -= 1
    coins += 1
# Sum coins
print(coins)