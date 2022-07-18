from cs50 import get_int


def main():

    while True:
        cardnumber = get_int("Write credit card number: ")
        if cardnumber <= 10 ** 16 and cardnumber > 0:
            break

    if validationluhn(cardnumber):
        structcheck(cardnumber)
    else:
        print("INVALID")


def structcheck(card):

    # VISA 13 digits
    if card >= 10 ** 12 * 4 and card <= 10 ** 12 * 5:
        print("VISA")
    # American Express 15 digits
    elif (card >= 10 ** 13 * 34 and card < 10 ** 13 * 35) or card >= 10 ** 13 * 37 and card < 10 ** 13 * 38:
        print("AMEX")
    # MasterCard 16 digits
    elif card >= 10 ** 14 * 51 and card < 10 ** 14 * 56:
        print("MASTERCARD")
    # Visa 16 digits
    elif card >= 10 ** 15 * 4 and card < 10 ** 15 * 5:
        print("VISA")


# Luhn's algorithm to check if it is valid
def validationluhn(card):

    oddsum = 0
    sum = 0

    while card > 0:
        # Oddsum adds all the odd numbers together
        oddsum += card % 10
        card //= 10
        temp = card % 10
        temp *= 2
        # Sum add products digits together
        while (temp > 0):
            sum += temp % 10
            temp //= 10
        card //= 10

    if (oddsum + sum) % 10 == 0:
        return True
    else:
        return False


if __name__ == '__main__':
    main()