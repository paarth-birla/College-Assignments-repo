'''
Write a Python program to get a single string from two given strings, 
separated by a space and swap the first two characters of each string.
'''
s1 = input("Enter a string : ")
s2 = input("\nEnter a string : ")

l1 = list(s1)
l2 = list(s2)

c = l1[0]
l1[0]=l2[0]
l2[0] = c

s1 = ''
s2 = ''

for i in l1:
    s1 += i

for j in l2:
    s2 += j

print(s1,s2,sep=' ')
