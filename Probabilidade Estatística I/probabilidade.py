'''
 probabilidade.py

 Sistema o qual recebe ou lê um arquivo de dados e faz uma tabela contendo: sua faixa de valor,
 frequencia, frequencia acumulada e frequencia relativa. Estima a média, moda e desvio padrão.
 Faz um Box-Plot estimado indicando os outliers e calcula o coeficiente de correlação de Pearson e
 os coeficientes da reta de mínimos quadrados

 Arthur Silveira Chaves (Sistema da Informação)
 Beatriz Jonas Justino (Sistema da Informação)
 Rodrigo Suarez Moreira (Ciência da Computação)

 Disciplina: Probabilidade e Estatística I

 29/05/2019
'''
# -*- coding: utf-8 -*-
import funcoes_probabilidade as fc

continuar='S'
while True:
    fc.clearscrn()
    fc.bemvindo()
    choose = input('Já possui um arquivo? (S/N): ')
    if choose.upper()=='S':
        nome_arquivo=input('Digite o nome do arquivo (com extensão): ')
        print('Obs: Evite usar separador como ponto, pode afetar os dados')
        separador=input('Digite o separador usado no arquivo: ')
        conjunto1,conjunto2=fc.ler_arquivo(nome_arquivo,separador)
        media1=fc.tabela(conjunto1)
        media2=fc.tabela(conjunto2)
        fc.pearson_reta(conjunto1,conjunto2,media1,media2)
        continuar=input('Deseja continuar?: (S/N)\n>>>')
        if continuar.upper()=='N':
            break
    elif choose.upper()=='N':
        nome_arquivo=input('Digite o nome do arquivo que será criado (com extensão): ')
        separador=input('Digite o separador que usará no arquivo: ')
        fc.escreve_arquivo(nome_arquivo,separador)
        continuar = input('Deseja continuar?: (S/N)\n>>>')
        if continuar.upper()=='N':
            break
    else:
        fc.error()
        continuar = input('Deseja continuar?: (S/N)\n>>>')
        if continuar.upper()=='N':
            break
fc.saida()