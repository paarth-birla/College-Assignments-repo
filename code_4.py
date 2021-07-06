'''
Ask the user for a number. Depending on whether the number is even or odd, print out an appropriate message to the user.
'''
no = int(input("Enter a no : "))

if (no % 2) == 0 :
    print("\nNumber entered is even")
else:
    print("\nNumber entered is odd")
