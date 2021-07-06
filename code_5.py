'''
Ask the user for a string and print out whether this string is a palindrome or not.
'''
s = input("Enter string : ")

if (s == s[::-1]): #slicing of string in reverse order
    print("\nPalindrome")
else :
    print("\nNot Palindrome")
