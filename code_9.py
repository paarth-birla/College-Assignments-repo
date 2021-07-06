'''
Write a Python program to get a string from a given string where all occurrences of its first char have been changed to '$', 
except the first char itself. 
(use replace() eg.restart will be resta$t)
'''
s = input("Enter a String : ")
c = s[0]
l = list(s)
s1 = ''
for i in range(1,len(s)):
    s1 += l[i]
x = s1.replace(c,'$')
print(c,x,sep = '')
