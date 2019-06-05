caps_strs = lambda lstr: list(map(lambda s:str.upper(s), lstr))
qnt=[]
strings=[]
x=input('Digite a string: ')
strings.append(x)
qnt.append(len(x))
y=input('Digite a string: ')
strings.append(y)
qnt.append(len(y))
z=input('Digite a string: ')
strings.append(z)
qnt.append(len(z))
strings=caps_strs(strings)
print('String: {} ... com {} caracteres'.format(max(strings),max(qnt)))