'''
Write a Python program which accepts the radius of a circle from the user and compute the area. 
(Hint: import math and use math.pi)
'''

import math

rad = float(input("Enter radius of circle : "))

area = (rad**2)*(math.pi)

print("\nArea of circle is : " , area)
