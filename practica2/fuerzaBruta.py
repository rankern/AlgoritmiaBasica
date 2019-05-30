def subResolver(pedidos, cap, tramosIn):
	maxbeneficio = maxbeneficio = sum(tramosIn);
	i = 0
	for pedido in pedidos:
		tramos = tramosIn.copy()
		i+=1
		m = max(tramos[pedido.get('salida'):pedido.get('llegada')])
		if m+pedido.get('numPasajeros') <= cap:
			for tramo in range(pedido.get('salida'), pedido.get('llegada')):
				tramos[tramo] += pedido.get('numPasajeros')
			maxbeneficio = max(maxbeneficio, sum(tramos))
		#print("\t" + str(i)+ " " + str(len(pedidos)))
		if i <= len(pedidos):
			maxbeneficio =max(maxbeneficio,  subResolver(pedidos[i:], cap, tramos[:]))
	return maxbeneficio
			
		
def resolver(pedidos, cap, final):
	maxbeneficio = 0
	i = -1
	for pedido in pedidos:
		i += 1
		#print(str(i) + " " +  str(pedido))
		if i < len(pedidos):
			resul = subResolver(pedidos[i:], cap, [0]*final)
			if resul > maxbeneficio:
				maxbeneficio = resul
	return maxbeneficio

w = open("resultadoFB.txt", "w+")
lines = [line.rstrip('\n') for line in open("pruebas.txt")]
i = 0
numProblema = 0
while(i < len(lines)-1):
	problema = lines[i].split(' ')
	i += 1
	numProblema += 1
	capMax = int(problema[0])
	estacionFinal = int(problema[1])
	numPedidos = int(problema[2])
	pedidos = []
	print(str(numProblema) + " " + str(capMax) + " " + str(estacionFinal) + " " + str(numPedidos))
	for line in lines[i:i+numPedidos]:
		pedido = line.split(' ')
		pedidos = pedidos + [{'salida': int(pedido[0]), 'llegada': int(pedido[1]), 'numPasajeros': int(pedido[2])}]
		i+=1
	beneficio = resolver(pedidos, capMax, estacionFinal)
	print("\t" + str(beneficio))
	w.write("problema " + str(numProblema) + " " + str(beneficio) + "\n")
w.close()
	
	

	