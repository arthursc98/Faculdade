import funcoes_po as fpo

continuar='S'
while True:
    fpo.clearscrn()
    existe=input('Já possui um arquivo? (S/N)\n>>>')
    if existe.upper()=='N':
        var = int(input('Quantas variaveis (maximo 20)? '))
        rest = int(input('Quantas restricoes (maximo 20)? '))
        tipo_problema = input('Tipo de problema (Max/Min): ')
        # Cria o quadro principal com seu devido tipo de problema e passando o novo número de quantas restricoes tem
        quadro , rest, quadro_inicial= fpo.cria_quadro(var, rest, tipo_problema)
        salvar = input('Deseja salvar o arquivo? (S/N)\n>>>')
        if salvar.upper()=='S':
            if tipo_problema.upper()=='MAX':
                fpo.escreve_arquivo(quadro,var,rest,'z')
            elif tipo_problema.upper()=='MIN':
                fpo.escreve_arquivo(quadro, var, rest, '-z')
        print('Quadro inicial')
        coluna_x = fpo.colunas(quadro, var)
        fpo.imprime(quadro,tipo_problema,coluna_x)
        interacao = 1
        while fpo.verifica_otimizacao(quadro) == False or fpo.verifica_viabilizacao(quadro) == False:
            while fpo.verifica_viabilizacao(quadro) == False:
                print('Interacao {}'.format(interacao))
                interacao+=1
                quadro = fpo.viabilizacao(quadro,tipo_problema,coluna_x)
            while fpo.verifica_otimizacao(quadro) == False:
                print('Interacao {}'.format(interacao))
                interacao += 1
                quadro = fpo.otimizacao(quadro,tipo_problema,coluna_x)
        fpo.imprime_solucao(quadro, var, coluna_x)
        fpo.pause()
        fpo.clearscrn()
        continuar = input('Deseja continuar?: (S/N)\n>>>')
        if continuar.upper() == 'N':
            break
    elif existe.upper()=='S':
        quadro, tipo_problema , quadro_inicial= fpo.ler_arquivo()
        print('Quadro inicial')
        var=fpo.identifica_var(quadro)
        coluna_x = fpo.colunas(quadro,var)
        fpo.imprime(quadro,tipo_problema,coluna_x)
        interacao = 1
        while fpo.verifica_otimizacao(quadro) == False or fpo.verifica_viabilizacao(quadro) == False:
            while fpo.verifica_viabilizacao(quadro) == False:
                print('Interacao {}'.format(interacao))
                interacao += 1
                quadro = fpo.viabilizacao(quadro,tipo_problema,coluna_x)
            while fpo.verifica_otimizacao(quadro) == False:
                print('Interacao {}'.format(interacao))
                interacao += 1
                quadro = fpo.otimizacao(quadro,tipo_problema,coluna_x)
        fpo.imprime_solucao(quadro, var, coluna_x)
        fpo.pause()
        fpo.clearscrn()
        continuar = input('Deseja continuar?: (S/N)\n>>>')
        if continuar.upper() == 'N':
            break
    else:
        fpo.error()
        continuar = input('Deseja continuar?: (S/N)\n>>>')
        if continuar.upper() == 'N':
            break
fpo.saida()