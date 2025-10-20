while True:
    alturas = int(input("digite a altura: "))

    if 1 <= alturas <= 8:
        break
    print("digite um valor entre 1 e 8")

for altura in range(alturas):
    for espaco in range(altura - 1):
        print(" ", end="")

    for hashtags in range(altura - 1):
        print("#", end="")

    print("#")

