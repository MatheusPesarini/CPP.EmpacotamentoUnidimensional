import matplotlib.pyplot as plt
import sys

vetor1 = []
vetor2 = []
for arg in sys.argv[1:]:
    prefix, value = arg.split("_", 1)
    if prefix == "temp":
        vetor1.append(float(value))
    elif prefix == "iter":
        vetor2.append(int(value))
# Fazer algo com os vetores
print("Vetor 1:", vetor1)
print("Vetor 2:", vetor2)

def plot(x, y):
    plt.plot(x, y)
    plt.show()

# Faça qualquer grafico com base em qualquer dados
plot(vetor2, vetor1)