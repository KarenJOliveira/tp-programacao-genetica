import sympy as sp
import csv
import pandas as pd

def reorganizar_elementos_rpn(expressao_rpn):
    elementos = expressao_rpn.split(" ")
    elementos_invertido = elementos[::-1]
    pilha = []

    for elemento in elementos_invertido:
        if elemento.isalpha(): 
            # Se o elemento é uma variável, adiciona à pilha
            pilha.append(elemento)
        elif elemento in ['+', '-', '*', '/']:
            # Se o elemento é um operador, desempilha dois valores e reorganiza
            operand2 = pilha.pop()
            operand1 = pilha.pop()
            nova_expressao = f"({operand1} {elemento} {operand2})"
            #nova_expressao_simplificada = simplificar_expressao(nova_expressao)
            pilha.append(nova_expressao)

    # O resultado final estará no topo da pilha
    return pilha[0]

def simplificar_expressao(expressao):
    sp.symbols('x y')
    expressao_simplificada = sp.simplify(expressao)

    return expressao_simplificada

# Ler o CSV com linhas de diferentes tamanhos
df = pd.read_csv('pop_melhores/funcao9.csv', delimiter=',')

# Visualizar o DataFrame 
# print(df)

expressoes_rpn = df['expressao']
expressoes_rpn_lista = expressoes_rpn.tolist()

expressoes_reorganizadas = []
for expressao in expressoes_rpn_lista:
    resultado = reorganizar_elementos_rpn(expressao)
    expressoes_reorganizadas.append(resultado)

expressoes_reorganizadas_simplificadas = []
for expressao in expressoes_reorganizadas:
    simplificada = simplificar_expressao(expressao)
    expressoes_reorganizadas_simplificadas.append(simplificada)

# for original, reorganizada in zip(expressoes_rpn_lista, expressoes_reorganizadas):
#    print(f"Original: {original}, Reorganizada: {reorganizada}")

for reorganizada in expressoes_reorganizadas_simplificadas:
    print(f"{reorganizada}\n")

