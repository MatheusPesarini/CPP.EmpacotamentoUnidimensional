import matplotlib.pyplot as plt
import sys

temperaturas = []
iteracoes = []
contadorMinRecipientes = []

for arg in sys.argv[1:]:
    prefix, value = arg.split("_", 1)
    if prefix == "temp":
        temperaturas.append(float(value))
    elif prefix == "iter":
        iteracoes.append(int(value))
    elif prefix == "rec":
        contadorMinRecipientes.append(int(value))

print("Temperaturas: ", temperaturas)
print("Iterações: ", iteracoes)
print("Contador de recipientes: ", contadorMinRecipientes)

def plot(x, y1, y2):
    plt.plot(x, y1, label="Temperaturas")
    plt.plot(x, y2, label="Recipientes menor solucao")
    plt.xlabel("Quantidade de Iterações")
    plt.legend()
    plt.show()

# Faça qualquer grafico com base em qualquer dados
plot(iteracoes, temperaturas, contadorMinRecipientes)