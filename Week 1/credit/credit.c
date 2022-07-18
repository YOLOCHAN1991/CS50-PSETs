#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // Declaring functions
    void Structcheck(long creditnumber);
    bool ValidationLuhn(long creditnumber);
    long creditnumber;

    do
    {
        creditnumber = get_long("Write credit card number: ");
    }
    while (creditnumber > pow(10, 16) || creditnumber < 0);

    bool validation = ValidationLuhn(creditnumber);
    if (validation == true)
    {
        Structcheck(creditnumber);
    }
    else
    {
        printf("INVALID\n");
    }
}

// Check for card structure
void Structcheck(long creditnumber)
{
    // Visa 13 digits
    if (creditnumber >= pow(10, 12) * 4 && creditnumber < pow(10, 12) * 5)
    {
        printf("VISA\n");
    }
    // American Express 15 digits
    else if ((creditnumber >= pow(10, 13) * 34 &&  creditnumber < pow(10, 13) * 35) || (creditnumber >= pow(10, 13) * 37
             && creditnumber < pow(10, 13) * 38))
    {
        printf("AMEX\n");
    }
    // MasterCard 16 digits
    else if (creditnumber >= pow(10, 14) * 51 && creditnumber < pow(10, 14) * 56)
    {
        printf("MASTERCARD\n");
    }
    // Visa 16 digits
    else if (creditnumber >= pow(10, 15) * 4 && creditnumber < pow(10, 15) * 5)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}

// Luhn's algorithm to check if it is valid
bool ValidationLuhn(long creditnumber)
{
    int temp;
    int oddsum = 0;
    int sum = 0;

    while (creditnumber > 0)
    {
        // Oddsum adds all the odd numbers together
        oddsum += creditnumber % 10;
        creditnumber = creditnumber / 10;
        temp = creditnumber % 10;
        temp = temp * 2;
        // Sum add products digits together
        while (temp > 0)
        {
            sum += temp % 10;
            temp /= 10;
        }
        creditnumber = creditnumber / 10;
    }
    if ((oddsum + sum) % 10 == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

