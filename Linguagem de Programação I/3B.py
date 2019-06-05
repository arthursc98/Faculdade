class Numeros():
    __n=[]
    __soma=0
    __divisor=0
    __deno=[]
    def __init__(self,n):
       self.__n=n
       self.soma=0
       self.__divisor=0
       self.__deno=[]
    def Pondera(self):
        for i in range(len(self.__n)):
            if i < 2:
                self.__deno.append(x[i] * 0.3)
                self.__divisor += 0.3
            elif i >= 2 and i < len(x) - 2:
                self.__deno.append(x[i] * 0.1)
                self.__divisor += 0.1
            else:
                self.__deno.append(x[i] * 0.3)
                self.__divisor += 0.3
    def Imprime(self):
        for i in self.__deno:
            self.__soma += i
            print(self.__soma)
        print(self.__soma / self.__divisor)
x=list(map(int,input("Digite a sequencia: ").split()))
lista=Numeros(x)
if len(x)<5:
    print('Minimo 5 valores')
else:
    lista.Pondera()
    lista.Imprime()