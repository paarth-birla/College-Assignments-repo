'''
Write a Python program to add 'ing' at the end of a given string (length should be at least 3). 
If the given string already ends with 'ing' then add 'ly' instead. 
If the string length of the given string is less than 3, leave it unchanged. 
(hint: last 3 chars usinfg if string[-3:0]==”ing”:]
'''
s = input("Enter a string : ")

if len(s) == 3 :
    print(s)

elif s[-3:] == "ing" :
    l = list(s)
    l.pop(-1)
    l.pop(-1)
    l.pop(-1)
    l.append('l')
    l.append('y')

    s = ''
    for i in l:
        s += i

    print(s)

else :
    l = list(s)
    l.append('i')
    l.append('n')
    l.append('g')

    s = ''
    for i in l:
        s += i

    print(s)
