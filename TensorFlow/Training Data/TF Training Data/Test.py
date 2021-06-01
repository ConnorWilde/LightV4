with open("linear.csv","w") as f:
    for x in range(4000):
        f.write(f'{x}, {x}\n')