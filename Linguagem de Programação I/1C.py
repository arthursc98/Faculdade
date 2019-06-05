caixa_alta=[]
qnt=[]
for i in range(3):
    string=str(input('Digite a string: '.format(i+1)))
    caixa_alta.append(string.upper())
    qnt.append(len(string))
for i in caixa_alta:
    print(i)
print('String: {} ... com {}'.format(max(caixa_alta),max(qnt)))