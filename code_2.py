'''
Create a program that asks the user to enter their name and their age.
Print out a message addressed to them that tells them the year that they will turn 100 years old.
'''

name = input("\nEnter your name : ")
age = int(input("\nEnter your age : "))
yrs_left = (100 - age) + 2020
print(name," will turn 100 yrs in " , yrs_left , "year" , end = '\n')
