'''
Write a Python program to change a given string to a new string where the first and last chars have been exchanged.
'''
s = input("Enter a string : ")
l = list(s)

x = l[0]
l[0] = l[len(s)-1]
l[len(s)-1] = x

s = ''

for i in l:
    s += i

print(s)
