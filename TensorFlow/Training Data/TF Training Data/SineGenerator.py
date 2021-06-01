import math
pi = 3.14

print(pi)

f= open("Sine.csv","w+")


for x in range(1):
    i = x    
    i = i * 0.0001
    x = i - (pi/2)
    y = math.sin(x)
    z = math.sin(y)
    
    
    
    print(i)
    
    
    f.write(f'{x}{y}{z}\r\n')

