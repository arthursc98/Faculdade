maximo=[]
minimo=[]
for i in range(2):
    x=list(map(int,input("Digite a sequencia: ").split()))
    maximo.append(max(x))
    minimo.append(min(x))
print(maximo)
print(minimo)