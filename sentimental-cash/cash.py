quarters = 25
dimes = 10
nickels = 5
pennies = 1

moedas_usadas = 0

while True:
    try:
        troco = float(input("digite o valor do troco: "))

        if troco > 0:
            break

        else:
            print("digite um valor acima de 0")

    except ValueError:
        print("digite um valor válido")

troco = round(troco * 100)


moedas_usadas = troco // quarters
troco = troco % quarters

moedas_usadas += troco // dimes
troco = troco % dimes

moedas_usadas += troco // nickels
troco = troco % nickels

moedas_usadas += troco // pennies
troco = troco % pennies

print(f"foram usados {moedas_usadas} moedas para o troco")
