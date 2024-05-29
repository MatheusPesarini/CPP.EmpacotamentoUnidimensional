import matplotlib.pyplot as plt
import sys

temperaturas = []
iteracoes = []
contadorMinRecipientes = []
melhoresSolucoesLocais = []

for arg in sys.argv[1:]:
    prefix, value = arg.split("_", 1)
    if prefix == "temp":
        temperaturas.append(float(value))
    elif prefix == "iter":
        iteracoes.append(int(value))
    elif prefix == "rec":
        contadorMinRecipientes.append(int(value))
    elif prefix == "ms":
        melhoresSolucoesLocais.append(int(value))
        

print("Temperaturas: ", temperaturas)
print("Iterações: ", iteracoes)
print("Contador de recipientes: ", contadorMinRecipientes)
print("Melhores soluções locais: ", melhoresSolucoesLocais)

def plot(x, y1, y2, y3):
    plt.figure("Gráfico das Soluções")
    plt.plot(x, y1, label="Temperatura")
    plt.plot(x, y2, label="Menor solução")
    plt.plot(x, y3, label="Melhor solução local")

    plt.xlabel("Quantidade de Iterações")
    plt.legend()
    plt.show()

# Faça qualquer grafico com base em qualquer dados
plot(iteracoes, temperaturas, contadorMinRecipientes, melhoresSolucoesLocais)