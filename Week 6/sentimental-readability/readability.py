from cs50 import get_string

text = get_string("Text: ")

# Word count
word_count = len(text.split())
# Sentence count
sentence_count = text.count(".") + text.count("!") + text.count("?")
# Loop to count letters
letter_count = 0
for letters in text:
    if letters.isalpha():
        letter_count += 1

# Get index
L = (letter_count / word_count) * 100
S = (sentence_count / word_count) * 100
index = 0.0588 * L - 0.296 * S - 15.8

if index <= 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print(f"Grade {index: .0f}")