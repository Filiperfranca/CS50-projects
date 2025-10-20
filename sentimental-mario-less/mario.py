while True:
    alturas = int(input("digite a altura: "))

    if 1 <= alturas <= 8:
        break
    print("digite um valor entre 1 e 8")

for altura in alturas:
    for espaco in altura - 1:

