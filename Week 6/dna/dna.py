import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        return 1

    # TODO: Read database file into a list of dicts
    databases = []
    count = 0
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        # Save names in STRs variable
        STRs = next(reader)
        STRs.remove("name")
        for row in reader:
            # Saves databases names in dict
            databases.append({"name": row[0]})
            # Saves databases STRs names and STRs count in dict
            for i in range(1, len(row)):
                databases[count].update({STRs[i - 1]: row[i]})
            count += 1

    # TODO: Read DNA sequence file into a string
    with open(sys.argv[2], "r") as file:
        reader = csv.reader(file)
        for row in reader:
            sequence = row[0]

    # TODO: Find longest match of each STR in DNA sequence
    subsequence_count = []
    for i in range(len(STRs)):
        if STRs[i] in sequence:
            subsequence_count.append(longest_match(sequence, STRs[i]))

    # TODO: Check database for matching profiles
    # Count to check if all STRs match
    match_count = 0
    for i in range(len(databases)):
        for j in range(len(subsequence_count)):
            # If database's count of repeated STRs match, count += 1
            if int(databases[i][STRs[j]]) == subsequence_count[j]:
                match_count += 1
        # If all counts match, we have a a matching DNA
        if match_count == len(STRs):
            valid = True
            break
        valid = False
        match_count = 0

    # Print result
    if (valid):
        print(databases[i]["name"])
    else:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
