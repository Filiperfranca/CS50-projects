quarters = 25
dimes = 10
nickels = 5
pennies = 1

while True:
    try:
        troco = int(input("digite o valor do troco: "))

        if troco > 0:
            break

    except ValueError:
        print("digite um valor acima de 0")

print(troco)
