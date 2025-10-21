texto = input("digite o texto aqui: ")

letras = 0
palavras = 1
frases = 0

for char in texto:
    if char.isalpha():
        letras += 1

    if char.isspace():
        palavras += 1

    if char == '.' or char == '!' or char == '?':
        frases += 1
