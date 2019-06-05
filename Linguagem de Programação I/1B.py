x=list(map(int,input("Digite a sequencia: ").split()))
soma=0
divisor=0
deno=[]
if len(x)<5:
    print('Minimo 5 valores')
else:
    for i in range(len(x)):
        if i<2:
            deno.append(x[i]*0.3)
            divisor+=0.3
        elif i>=2 and i<len(x)-2:
            deno.append(x[i]*0.1)
            divisor+=0.1
        else:
            deno.append(x[i]*0.3)
            divisor+=0.3
for i in deno:
    soma+=i
    print(soma)
print(soma/divisor)