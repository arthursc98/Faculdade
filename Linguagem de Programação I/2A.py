impar=[]
par=[]
x=list(map(int,input("Digite a sequencia: ").split()))
print(list(filter(lambda y:y%2!=0,x)))
print(list(filter(lambda y:y%2==0,x)))