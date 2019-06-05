from math import sqrt

class Quadrilatero():
	__base=0
	__altura=0
	def __init__(self,base,altura):
		self.__base=float(base)
		self.__altura=float(altura)
	def calcular_area(self):
		return float(self.__base*self.__altura)
	def calcular_perimetro(self):
		return float(self.__base*2+self.__altura*2)

class Quadrado(Quadrilatero):
	def __init__(self,lado):
		Quadrilatero.__init__(self,lado,lado)

class Trapezio(Quadrilatero):
	__base_menor=0
	__lado=0
	def __init__(self,base_maior,base_menor,altura):
		self.__base_menor=float(base_menor)
		self.__base_maior=float(base_maior)
		self.__altura=float(altura)
		self.__lado=float(sqrt(self.__altura**2+(self.__base_maior-self.__base_menor)**2))
	def calcular_area(self):
		return float(((self.__base_menor+self.__base_maior)*self.__altura)/2)
	def calcular_perimetro(self):
		return float(self.__base_menor+self.__base_maior+self.__lado*2)

perimetro_total=0
area_total=0
base,altura=input('Digite a base e altura do quadrilatero: ').split()
quadrilatero=Quadrilatero(base,altura)
lado=input('Digite o lado do quadrado: ')
quadrado=Quadrado(lado)
base_maior,base_menor,altura_trapezio=input('Digite a base maior, menor e a altura: ').split()
trapezio=Trapezio(base_maior,base_menor,altura_trapezio)
area_total+=quadrilatero.calcular_area()
area_total+=quadrado.calcular_area()
area_total+=trapezio.calcular_area()
perimetro_total+=quadrilatero.calcular_perimetro()
perimetro_total+=quadrado.calcular_perimetro()
perimetro_total+=trapezio.calcular_perimetro()
print('Area: {}\tPerimetro: {:.1f}'.format(area_total,perimetro_total))