while true:
    altura = int(input("digite a altura: "))

    if 1 <= altura <= 8:
        break
    print("digite um valor entre 1 e 8")

print(f"log: o valor escolhido foi {altura}")
