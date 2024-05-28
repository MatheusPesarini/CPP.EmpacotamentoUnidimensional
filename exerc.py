import random
import math
import time

itemRecipiente = []  # list of tuples (item, recipiente)
temperatura = 0

def trocarVizinhanca(solucaoInicial, capacidadeRecipiente, custo, recipientes):
    global temperatura
    solucaoFinal = solucaoInicial[:]
    deltaEInicial = 0
    for i in solucaoInicial:
        if i != 15 and i != 0:
            deltaEInicial += 1

    gerar = True
    index1 = random.randint(0, len(itemRecipiente) - 1)
    index2 = random.randint(0, len(itemRecipiente) - 1)
    rec1 = itemRecipiente[index1][1]
    rec2 = itemRecipiente[index2][1]
    capacidadeRec1 = solucaoInicial[rec1]
    capacidadeRec2 = solucaoInicial[rec2]

    while gerar:
        index1 = random.randint(0, len(itemRecipiente) - 1)
        index2 = random.randint(0, len(itemRecipiente) - 1)
        rec1 = itemRecipiente[index1][1]
        rec2 = itemRecipiente[index2][1]
        capacidadeRec1 = solucaoInicial[rec1]
        capacidadeRec2 = solucaoInicial[rec2]

        if rec1 != rec2 and (capacidadeRec1 - itemRecipiente[index2][0]) >= 0:
            print(f"capacidade do primeiro para a troca: {capacidadeRec1 - itemRecipiente[index2][0]}")
            gerar = False

    deltaE = 0

    itemRecipiente[index2] = (itemRecipiente[index2][0], rec1)
    solucaoFinal[rec1] -= itemRecipiente[index2][0]
    solucaoFinal[rec2] += itemRecipiente[index2][0]

    print("S: ", end="")
    for i in solucaoFinal:
        recipientes += 1
        if i != 15 and i != 0:
            deltaE += 1
        custo += i
        print(i, end=" ")
    print()

    print(f"DeltaE: {deltaE - deltaEInicial}")
    if (deltaE - deltaEInicial) > 0:
        divisao = -(deltaE - deltaEInicial) / temperatura
        pE = math.exp(divisao)
        print(f"pE: {pE}")

        p = random.random()
        print(f"p: {p}")
        if pE > p:
            print("Aceitou")
            print(f"Recipiente {rec1} vai receber o item {itemRecipiente[index2][0]}")
            print(f"Recipiente {rec2} vai perder o item {itemRecipiente[index2][0]}")
            return solucaoFinal
        else:
            print("Rejeitou")
            itemRecipiente[index2] = (itemRecipiente[index2][0], rec2)
            return solucaoInicial
    else:
        print(f"Recipiente {rec1} vai receber o item {itemRecipiente[index2][0]}")
        print(f"Recipiente {rec2} vai perder o item {itemRecipiente[index2][0]}")
        return solucaoFinal

def buscaGulosa(capacidade, numItens, itens):
    global temperatura
    random.seed(time.time())

    solucaoInicial = []
    recipienteAtual = 0

    while numItens != 0:
        if itens:
            if not solucaoInicial:
                solucaoInicial.append(capacidade)

            index = random.randint(0, len(itens) - 1)
            itemSorteado = itens.pop(index)
            numItens -= 1
            if itemSorteado <= solucaoInicial[recipienteAtual]:
                itemRecipiente.append((itemSorteado, recipienteAtual))
                solucaoInicial[recipienteAtual] -= itemSorteado
            else:
                solucaoInicial.append(capacidade)
                recipienteAtual += 1
                itemRecipiente.append((itemSorteado, recipienteAtual))
                solucaoInicial[recipienteAtual] -= itemSorteado

    print("solucaoInicial: ", end="")
    for i in solucaoInicial:
        print(i, end=" ")
    print()

    saMax = 3
    deltaE = 0
    recipientesTotais = 0
    alfa = 0.95

    # Initialize temperatura to a starting value, e.g., 1
    temperatura = 1

    while temperatura > 0.005:
        if temperatura != 0:
            temperatura *= alfa
        for _ in range(saMax):
            custoIndividual = 0
            recipienteIndividual = 0
            solucaoInicial = trocarVizinhanca(solucaoInicial, capacidade, custoIndividual, recipienteIndividual)

            deltaE += custoIndividual
            recipientesTotais += recipienteIndividual
        if temperatura == 0:
            temperatura = recipientesTotais / saMax
        print(f"Temperatura final: {temperatura}")

def main():
    random.seed(time.time())
    try:
        with open("./entradasParaTeste/PEU2.txt") as file:
            capacidadesolucaoInicial = int(file.readline().strip())
            numItens = int(file.readline().strip())
            tamanhoItens = list(map(int, file.readline().strip().split()))
    except FileNotFoundError:
        print("Não foi possível abrir o arquivo")
        return

    buscaGulosa(capacidadesolucaoInicial, numItens, tamanhoItens)

if __name__ == "__main__":
    main()
