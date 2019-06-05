x=list(map(int,input("Digite a sequencia: ").split()))
print(min(x))
print(max(x))
soma=0
for i in x:
    soma+=i
print(soma/len(x))