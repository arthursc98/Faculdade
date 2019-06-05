from functools import reduce
num=list(map(int,input('Digite a sequencia: ').split()))
fatorial = lambda n : reduce(lambda x,y: x*y,range(1,n+1))
print(list(map(fatorial,num)))