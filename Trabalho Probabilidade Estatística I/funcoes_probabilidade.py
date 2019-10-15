from math import ceil, sqrt, log10
import os
from platform import system
import statistics


def tabela(conjunto):
    N = len(conjunto)  # Quantidade de dados existentes
    n = ceil(3.3 * log10(N))  # Número de faixas
    A = max(conjunto) - min(conjunto)  # Amplitude do conjunto de valores
    d = ceil((A / n) * 100) / 100  # Amplitude das faixas de valores
    acumulada = 0
    f_ra_val = 0
    p_faixa = []  # Inicio de uma faixa
    s_faixa = []  # Fim de uma faixa
    faixa_pm = []  # Faixa de ponto médio
    faixa_f = []  # Faixa de frequencia
    f_acumulada = []  # Faixa de frequencia acumulada
    f_relativa = []  # Faixa de frequencia relativa
    f_racumulada = [] # Faixa de frequencia relativa acumulada
    for i in range(n):
        count = 0
        # Definindo faixas de valores
        p_faixa.append(min(conjunto) + (i * d))
        s_faixa.append(min(conjunto) + ((i + 1) * d))
        # Definindo faixa do ponto médio
        faixa_pm.append(ceil(((p_faixa[i] + s_faixa[i]) / 2) * 100) / 100)
        # Verificando frequencia de cada faixa de valor do conjunto
        for j in range(N):
            if p_faixa[i] <= conjunto[j] < s_faixa[i]:
                count += 1
            elif conjunto[j] >= s_faixa[i - 1] and i == n - 1:
                count += 1
        faixa_f.append(count)
        acumulada += count
        # Adicionando a frequencia a frequencia acumulada
        f_acumulada.append(acumulada)
    for i in range(n):
        f_relativa.append(round((faixa_f[i] / acumulada) * 100) / 100)  # Definindo a frequencia relativa
        f_ra_val += round((faixa_f[i] / acumulada) * 100) / 100
        f_racumulada.append(f_ra_val)
    print('+'+150*'-'+'+')
    print('|     Faixa de Valores            Ponto Médio     Frequência    Frequência Acumulada      Frequência Relativa'
          '      Frequência Relativa Acumulada       |')
    print('+'+150*'-'+'+')
    for i in range(n):
        print('|{:10.2f} |---- {:-10.2f}{:15.2f}{:15.2f}{:20.2f}'
              '{:25.2f}{:30.2f}                  |'.format(p_faixa[i], s_faixa[i], faixa_pm[i], faixa_f[i], f_acumulada[i],
                                                    f_relativa[i],f_racumulada[i]))
    print('+'+150*'-'+'+')
    pause()
    clearscrn()
    media = media_desviopadrao_moda(conjunto, N, faixa_f, p_faixa, d, n, faixa_pm)
    boxplot(conjunto, N)
    return media


def media_desviopadrao_moda(conjunto, N, faixa_f, p_faixa, d, n, faixa_pm):
    print('Para conjunto não agrupado')
    # Calculando a média para não agrupado
    media = statistics.mean(conjunto)
    # Calculando a moda para não agrupado
    repetir = 0
    for k in conjunto:
        aparece = conjunto.count(k)
        if aparece > repetir:
            repetir = aparece
    moda = []
    for k in conjunto:
        aparece = conjunto.count(k)
        if aparece == repetir and k not in moda:
            moda.append(k)
    if len(moda) != 1:
        moda = 'Não existe moda para tal conjunto de valores'
    # Definindo qual será o valor do desvio padrão para não agrupado
    desviopadrao = statistics.stdev(conjunto)
    for v in range(2):
        if type(moda) != str and type(moda)!=float:
            print('Média: {}\nDesvio Padrão: {}\nModa: {}'.format(round(media, 3), round(desviopadrao, 3), round(moda[0], 3)))
        else:
            print('Média: {}\nDesvio Padrão: {}\nModa: {}'.format(round(media, 3), round(desviopadrao, 3), moda))
        pause()
        clearscrn()
        # Irá repetir o laço porém agora para conjunto agrupado
        if v==0:
            print('Para conjunto agrupado')
        # Determina a média para agrupada
        somatoria_media = 0
        for p in range(n):
            somatoria_media += (faixa_pm[p] * faixa_f[p])
        media = (somatoria_media / N)
        # Definindo a faixa inferior da classe modal
        linf_classe_modal = p_faixa[faixa_f.index(max(faixa_f))]
        # Verificando se as frequencias posteriores e anteriores não ultrapassam o tamanho da faixa de valores
        if faixa_f.index(max(faixa_f)) - 1 < 0 or faixa_f.index(max(faixa_f)) + 1 >= n:
            moda = 'Não existe moda para tal conjunto de valores'
        else:
            # Calculando a moda para agrupada
            f_pos = faixa_f[faixa_f.index(max(faixa_f)) + 1]
            f_ant = faixa_f[faixa_f.index(max(faixa_f)) - 1]
            moda = linf_classe_modal + d * (f_pos / (f_ant + f_pos))
        desviopadrao = 0
        # Definindo qual será o valor do desvio padrão para agrupada
        for i in range(n):
            desviopadrao += (faixa_pm[i] - media) ** 2
        desviopadrao = sqrt(desviopadrao / N)
    media = sum(conjunto) / N
    return media


def boxplot(conjunto, N):
    conjunto_organizado = sorted(conjunto)
    # Definindo o valor da mediana, primeiro quartil e terceiro quartil
    m = 0.5 * (N + 1)
    if m % 2 != 0:
        m = (conjunto_organizado[int(m - 1)] + conjunto_organizado[int(m)]) / 2
    else:
        m = conjunto_organizado[int(m - 1)]
    q3 = 0.75 * (N + 1)
    if q3 % 2 != 0:
        q3 = (conjunto_organizado[int(q3 - 1)] + conjunto_organizado[int(q3)]) / 2
    else:
        q3 = conjunto_organizado[int(q3 - 1)]
    q1 = 0.25 * (N + 1)
    if q1 % 2 != 0:
        q1 = (conjunto_organizado[int(q1 - 1)] + conjunto_organizado[int(q1)]) / 2
    else:
        q1 = conjunto_organizado[int(q1 - 1)]
    # Definindo limite superior e inferior
    I = q3 - q1
    linf = q1 - (1.5 * I)
    lsup = q3 + (1.5 * I)
    outlier_sup = []
    outlier_inf = []
    # Verificando outliers
    for out in conjunto:
        if out > lsup:
            outlier_sup.append(out)
        if out < linf:
            outlier_inf.append(out)
    print('Q1: {:.2f}\nMediana: {:.2f}\nQ3: {:.2f}\nLimite superior: {:.2f}\nLimite Inferior: {:.2f}'
          .format(q1, m, q3, lsup, linf))
    pause()
    clearscrn()
    imprime_boxplot(lsup, q3, m, q1, linf, outlier_sup, outlier_inf)


def imprime_boxplot(lsup, q3, m, q1, linf, outlier_sup, outlier_inf):
    if len(outlier_sup) != 0:
        print('  Outliers superiores ao limite superior')
        print(outlier_sup)
    else:
        print('Não há Outliers superiores ao limite superior')
    print('        ------------  Lsup: {:.2f} '.format(lsup))
    print('              |                ')
    print('              |                ')
    print('              |                ')
    print('     ------------------- Q3: {:.2f}'.format(q3))
    print('     ||               ||       ')
    print('     ||               ||       ')
    print('     ||               ||       ')
    print('     ------------------- M: {:.2f}'.format(m))
    print('     ||               ||       ')
    print('     ||               ||       ')
    print('     ||               ||       ')
    print('     ------------------- Q1: {:.2f}'.format(q1))
    print('              |                ')
    print('              |                ')
    print('              |                ')
    print('        ------------  Linf: {:.2f} '.format(linf))
    if len(outlier_inf) != 0:
        print('  Outliers inferiores ao limite inferior')
        print(outlier_inf)
    else:
        print('Não há Outliers inferiores ao limite inferior')
    pause()
    clearscrn()


def pearson_reta(conjunto1, conjunto2, media1, media2):
    somatoria = 0
    somatoria2 = 0
    somatoria3 = 0
    # Fazendo as devidas somatórias para calcular o coeficiente de correlação de Pearson
    for i in range(len(conjunto1)):
        somatoria += ((conjunto1[i] - media1) * (conjunto2[i] - media2))
        somatoria2 += (conjunto1[i] - media1) ** 2
        somatoria3 += (conjunto2[i] - media2) ** 2
    print('Coeficiente de correlação de Pearson: {}'.format(round(somatoria / sqrt(somatoria2 * somatoria3), 3)))
    somatoria = 0
    somatoria2 = 0
    # Calcula os coeficientes da reta de mínimos quadrados
    for i in range(len(conjunto1)):
        somatoria += (conjunto1[i] * conjunto2[i] - media1 * media2)
        somatoria2 += (conjunto1[i] ** 2 - media1 ** 2)
    a = round((somatoria / len(conjunto1)) / (somatoria2 / len(conjunto1)), 3)
    b = round(media2 - a * media1, 3)
    print('a: {}\nb: {}'.format(a, b))
    if b > 0:
        print('y = {}x + {}'.format(a, b))
    else:
        print('y = {}x {}'.format(a, b))
    pause()
    clearscrn()


def ler_arquivo(nome_arquivo, separador):
    # Lendo o arquivo e separando os dados com seus respectivos conjuntos
    arquivo = open(nome_arquivo, 'r')
    conjunto1 = []
    conjunto2 = []
    for linha in arquivo:
        linhas = linha.replace('\n', '').split(separador)
        linhas = list(map(float, linhas))
        conjunto1.append(linhas[0])
        conjunto2.append(linhas[1])
    arquivo.close()
    clearscrn()
    return conjunto1, conjunto2


def saida():
    clearscrn()
    print('-' * 20)
    print('|' + ' ' * 18 + '|')
    print('|' + '  Até a próxima!  ' + '|')
    print('|' + ' ' * 18 + '|')
    print('-' * 20)
    pause()
    clearscrn()


def error():
    print('-' * 20)
    print('|' + ' ' * 8 + '|')
    print('|' + '  Opção inválida  ' + '|')
    print('|' + ' ' * 18 + '|')
    print('-' * 20)


def escreve_arquivo(nome_arquivo, separador):
    # Escrevendo os dados no arquivo com o separador
    arquivo = open(nome_arquivo, 'w')
    conjunto1 = input('Digite os valores do primeiro conjunto: ').split()
    conjunto2 = input('Digite os valores do segundo conjunto: ').split()
    if len(conjunto2) != len(conjunto1):
        print('Error: Tamanho dos conjuntos desiguais')
        exit(1)
    for i in range(len(conjunto1)):
        arquivo.write(conjunto1[i] + separador + conjunto2[i] + '\n')
    diretorio = os.getcwd()
    print('Arquivo criado com sucesso!')
    print('Para acessar o arquivo estará no diretório: {}'.format(diretorio))
    print('Caso não se lembre é o mesmo diretório o qual o arquivo .py está')
    arquivo.close()


def bemvindo():
    bemv = '|               Bem-Vindo                   |'
    trab = '| Trabalho de Probabilidade e Estatística I |'
    print('-' * len(trab))
    print('|' + ' ' * (len(trab) - 2) + '|')
    print(bemv)
    print(trab)
    print('|' + ' ' * (len(trab) - 2) + '|')
    print(len(trab) * '-')


def clearscrn():
    if system()=='Windows':
        os.system('cls')
    else:
        os.system('clear')


def pause():
    input('Pressione ENTER para continuar...')
