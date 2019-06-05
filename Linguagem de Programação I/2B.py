x=list(map(int,input("Digite a sequencia: ").split()))
y=list(filter(lambda a:a%2==0,x))
print(sum(y))