while True:
    try:
        alturas = int(input("digite a altura: "))

        if 1 <= alturas <= 8:
            break
    except ValueError:
        print("digite um valor entre 1 e 8")

for altura in range(alturas):
    for espaco in range((alturas - altura) - 1):
        print(" ", end="")

    for hashtags in range(altura):
        print("#", end="")

    print("#")
