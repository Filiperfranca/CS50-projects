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

L = letras / palavras * 100
S = frases / palavras * 100

resultado = 0.0588 * L - 0.296 * S - 15.8

if resultado >= 16:
    print("Grade 16+")

elif resultado < 1:
    print("Before Grade 1")

else:
    print(f"grade {int(round(resultado))}")
