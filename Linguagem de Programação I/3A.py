class Numeros():
    __nums=[]
    def __init__(self,n):
        self.__nums=n
    def maior(self):
        return max(self.__nums)
    def menor(self):
        return min(self.__nums)
x=list(map(int,input("Digite a sequencia: ").split()))
numeros=Numeros(x)
print('Maior', numeros.maior())
print('Menor', numeros.menor())