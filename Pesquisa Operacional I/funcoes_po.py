import os
from platform import system

def cria_quadro(var, rest, tipo_problema):
    print('Função Objetivo')
    z = []
    quadro_provisorio = []
    for i in range(var):
        val = float(input('Coeficiente da variavel x' + str(i) + ': '))
        z.append(val)
    if tipo_problema.upper() == 'MAX':  # Caso seja maximização a linha do Z é multiplicada por -1
        for i in range(len(z)):
            if z[i] != 0:
                z[i] *= -1
    for i in range(rest):
        linha = []
        print('Restrição ' + str(i + 1))
        for j in range(var):
            val = float(input('Coeficiente da variavel x' + str(j) + ': '))
            linha.append(val)
        tipo_rest = input('Tipo de restrição: ')
        termo_independente = float(input('Termo independente: '))
        linha.append(termo_independente)
        if tipo_rest == '==':  # Invertendo os valores e jogando uma copia da linha caso o tipo seja ==
            quadro_provisorio.append(linha)
            linha_aux = []
            for j in range(len(linha)):
                if float(linha[j]) != 0:
                    linha_aux.append(float(linha[j]) * -1)
                else:
                    linha_aux.append(float(linha[j]))
            quadro_provisorio.append(linha_aux)
        elif tipo_rest == '>=':  # Invertendo os valores da linha caso o tipo seja >=
            linha_aux = []
            for j in range(len(linha)):
                if float(linha[j]) != 0:
                    linha_aux.append(float(linha[j]) * -1)
                else:
                    linha_aux.append(float(linha[j]))
            quadro_provisorio.append(linha_aux)
        else:
            quadro_provisorio.append(linha)
    if tipo_problema.upper() == 'MIN':  # Caso o tipo do problema seja minimizar ele irá inverter todas as restriçoes
        for i in range(1, len(quadro_provisorio)):
            for j in range(var + 1):
                quadro_provisorio[i][j] *= -1
    quadro = []
    rest = len(quadro_provisorio)
    for i in range(rest + 1):
        linha = []  # Colocando 1 nas variaveis de folga de cada linha
        for j in range(var + rest + 1):
            if j - 1 == i:
                linha.append(1)
            else:
                linha.append(0)
        quadro.append(linha)
    for i in range(var):  # Passando a linha do z para o quadro
        quadro[0][i] = z[i]
    for i in range(rest):  # Passando todos os valores para o quadro
        for j in range(var):
            quadro[i + 1][j] = quadro_provisorio[i][j]
        quadro[i + 1][var + rest] = quadro_provisorio[i][var]
    return quadro, rest, quadro


def escreve_arquivo(quadro, var, rest, tipo_problema):
    nome_arquivo = input('Digite o nome do arquivo que será salvo (com a extensão): ')
    arquivo = open(nome_arquivo, 'w')
    for linha in quadro:
        for elemento in linha:
            arquivo.write(str(elemento) + ' ')
        arquivo.write('\n')
    arquivo.write(str(var) + ' ' + str(rest)+'\n')
    arquivo.write(tipo_problema)
    diretorio = os.getcwd()
    print('Arquivo criado com sucesso!')
    print('Para acessar o arquivo estará no diretório: {}'.format(diretorio))
    print('Caso não se lembre é o mesmo diretório o qual o arquivo .py está')


def ler_arquivo():
    # Lendo o arquivo e separando os dados com seus respectivos conjuntos
    nome_arquivo = input('Digite o nome do arquivo (com extensão): ')
    arquivo = open(nome_arquivo, 'r')
    quadro = []
    tipo_problema=''
    flag = True
    parar_ler_quadro = 0
    for linha in arquivo:
        linhas = linha.split(' ')
        if linhas[len(linhas) - 1] == '\n':
            linhas.pop()
        if linhas[0]=='z' or linhas[0]=='-z':
            tipo_problema = linhas.pop()
        else:
            linhas = list(map(float, linhas))
            if flag is True:
                parar_ler_quadro = len(linhas)
            flag = False
            if parar_ler_quadro == len(linhas):
                quadro.append(linhas)
    return quadro, tipo_problema, quadro


# Verifica se o quadro esta viabilizado
def verifica_viabilizacao(quadro):
    for i in range(1, len(quadro)):
        if quadro[i][len(quadro[0]) - 1] < 0:
            return False
    return True


# Verifica se o quadro esta otimizado
def verifica_otimizacao(quadro):
    for i in range(len(quadro[0]) - 1):
        if quadro[0][i] < 0:
            return False
    return True


def menor_col(quadro):
    menor = 0
    index_coluna = 0
    for i in range(len(quadro[0]) - 1):
        if quadro[0][i] < menor:
            menor = quadro[0][i]
            index_coluna = i
    return index_coluna


# Pega a linha a qual a solução divida pela coluna do possivel pivo é o menor positivo
def menor_lin(quadro, index_coluna):
    solucao = []
    solucao_index = []
    for i in range(1, len(quadro)):
        if divisao(quadro[i][len(quadro[0]) - 1], quadro[i][index_coluna]) > 0:
            solucao.append(quadro[i][len(quadro[0]) - 1] / quadro[i][index_coluna])
            solucao_index.append(i)
    return solucao_index[solucao.index(min(solucao))]


# Pega o index do menor elemento da solucao
def menor_solucao(quadro):
    menor_index = 0
    menor = 0
    for i in range(1, len(quadro)):
        if quadro[i][len(quadro[0]) - 1] < menor:
            menor_index = i
    return menor_index


# Pega o index onde a razao mais proxima de zero e negativa está
def razao(quadro, index_linha):
    razao = []
    razao_index = []
    for i in range(len(quadro[0]) - 1):
        if divisao(quadro[0][i], quadro[index_linha][i]) < 0 or divisao(quadro[0][i], quadro[index_linha][i]) > 0:
            razao.append(divisao(quadro[0][i], quadro[index_linha][i]))
            razao_index.append(i)
    for i in range(len(razao)):
        if razao[i] < 0:
            razao[i] *= -1
    return razao_index[razao.index(min(razao))]


# Viabiliza o quadro
def viabilizacao(quadro,tipo_problema,coluna_x):
    index_linha = menor_solucao(quadro)
    index_coluna = razao(quadro, index_linha)
    pivo = quadro[index_linha][index_coluna]
    nova_lin_pivo = []
    # Divide a linha pelo pivo e cria a nova linha pivo
    for i in range(len(quadro[0])):
        quadro[index_linha][i] = round(divisao(quadro[index_linha][i], pivo), 3)
        nova_lin_pivo.append(quadro[index_linha][i])
    quadro = escalonamento(quadro, nova_lin_pivo, index_linha, index_coluna)
    coluna_x[index_linha] = index_coluna
    imprime(quadro,tipo_problema,coluna_x)
    return quadro


# Otimiza o quadro
def otimizacao(quadro,tipo_problema,coluna_x):
    index_coluna = menor_col(quadro)
    index_linha = menor_lin(quadro, index_coluna)
    pivo = quadro[index_linha][index_coluna]
    nova_lin_pivo = []
    # Divide a linha pelo pivo e cria a nova linha pivo
    for i in range(len(quadro[0])):
        quadro[index_linha][i] = round(divisao(quadro[index_linha][i], pivo), 3)
        nova_lin_pivo.append(quadro[index_linha][i])
    quadro = escalonamento(quadro, nova_lin_pivo, index_linha, index_coluna)
    coluna_x[index_linha]=index_coluna
    imprime(quadro,tipo_problema,coluna_x)
    return quadro


# Faz os escalonamento das linhas
def escalonamento(quadro, nova_lin_pivo, index_linha, index_coluna):
    # Escalonando a matriz
    for i in range(len(quadro)):
        if i != index_linha:
            elemento = quadro[i][index_coluna]
            elemento *= -1
            for j in range(len(quadro[0])):
                nova_lin = nova_lin_pivo[j]
                quadro[i][j] = round(quadro[i][j] + (nova_lin * elemento), 3)
    return quadro


# Cria a coluna das variaveis de folga na base
def colunas(quadro,var):
    coluna=[]
    for i in range(var,len(quadro[0])-1):
        coluna.append(i)
    return coluna


# Identifica quantas variaveis tem o quadro quando o arquivo é lido
def identifica_var(quadro):
    for i in range(len(quadro[0])-1,-1,-1):
        if quadro[0][i]!=0:
            return i

# Imprime o quadro
def imprime (quadro,tipo_problema,coluna_x):
    print('Base\t ',end="")
    for i in range(len(quadro[0])-1):
        print('x'+str(i)+'\t',end="")
    print('Solução')
    for i in range(len(quadro)):
        if i==0:
            print(tipo_problema+'\t',end="")
        else:
            print('x'+str(coluna_x[i])+'\t',end="")
        for j in range(len(quadro[0])):
            print(str(quadro[i][j])+'\t',end="")
        print()


# Imprime solução
def imprime_solucao(quadro,var,colunas_x):
    print('Solução: {}'.format(quadro[0][len(quadro[0])-1]))
    for i in range(var+1):
        for j in range(1,len(quadro)):
            if colunas_x[j]==i:
                print('x'+str(i)+': '+str(quadro[j][len(quadro[0])-1]))



# Verifica divisibilidade por 0
def divisao(a, b):
    if b == 0:
        return 0
    if a == 0:
        return 0
    return a / b


# Limpa a tela
def clearscrn():
    if system=='Windows':
        os.system('cls')
    else:
        os.system('clear')


# Quadro de bem vindo
def bemvindo():
    bemv = '|               Bem-Vindo                   |'
    trab = '|     Trabalho de Pesquisa Operacional I    |'
    print('-' * len(trab))
    print('|' + ' ' * (len(trab) - 2) + '|')
    print(bemv)
    print(trab)
    print('|' + ' ' * (len(trab) - 2) + '|')
    print(len(trab) * '-')


# Saída do programa
def saida():
    clearscrn()
    print('-' * 20)
    print('|' + ' ' * 18 + '|')
    print('|' + '  Até a próxima!  ' + '|')
    print('|' + ' ' * 18 + '|')
    print('-' * 20)
    pause()
    clearscrn()


# Error caso o usuário escolha uma opção inválida
def error():
    print('-' * 20)
    print('|' + ' ' * 8 + '|')
    print('|' + '  Opção inválida  ' + '|')
    print('|' + ' ' * 18 + '|')
    print('-' * 20)


# Pausa
def pause():
    input('Pressione ENTER para continuar...')


