def verifica(jogo,letra):
    if ((jogo[0][0] == jogo[1][1] == jogo[2][2] == letra) or
        (jogo[0][2] == jogo[1][1] == jogo[2][0] == letra)):
        return True
    for i in range(3):
        if ((jogo[i][0] == jogo[i][1] == jogo[i][2] == letra) or
            (jogo[0][i] == jogo[1][i] == jogo[2][i] == letra)):
            return True
print('Digite o jogo abaixo')
jogo=[]
letras=[]
for i in range(3):
    x=list(input().split())
    jogo.append(x)
for i in range(3):
    for j in range(3):
        if jogo[i][j] not in letras:
            letras.append(jogo[i][j])
if len(letras)>2:
    print('Digite apenas duas letras')
    exit(1)
else:
    for i in range(2):
        if verifica(jogo,letras[i]):
            print('Letra {} Ganhou'.format(letras[i]))
            exit(0)
    print('Impate')