import operator
class Pedido:
	billetes = 0
	estacionIni = 0
	estacionFin = 1
	numEstacion = 1
	beneficio = 0

	def __init__(self, _billetes, _estacionIni, _estacionFin):
		self.billetes = _billetes
		self.estacionIni = _estacionIni
		self.estacionFin = _estacionFin
		self.numEstacion = _estacionFin - _estacionIni
		self.beneficio = self.numEstacion*self.billetes

	def __gt__(self, value):
		
		if self.numEstacion == value.numEstacion:
			return self.billetes <= value.billetes
		return self.numEstacion <= value.numEstacion
	
	
	def __lt__(self, value):
		if self.numEstacion == value.numEstacion:
			return self.billetes >= value.billetes
		return self.numEstacion >= value.numEstacion
	
	def __ge__(self, value):
		if self.numEstacion == value.numEstacion:
			return self.billetes < value.billetes
		return self.numEstacion < value.numEstacion
	
	def __le__(self, value):
		if self.numEstacion == value.numEstacion:
			return self.billetes > value.billetes
		return self.numEstacion > value.numEstacion


	def __str__(self):
		return  "\testaciones = " + str(self.numEstacion) + "; \tnum Pasajeros: " + str(self.billetes)  + "; \tEstacion inicial: " + str(self.estacionIni)+ "; \tEstacion final: " + str(self.estacionFin) 




def calcualrCostes(listaPedidos, capMax, tramos):
	for pedido in listaPedidos:
		p = pedido[1]
		if p.billetes >= capMax - max(tramos[p.estacionIni:p.estacionFin]):
			for i in range(p.estacionIni, p.estacionFin):
				tramos[i] += p.billetes
		else:
			b = capMax - max(tramos[p.estacionIni:p.estacionFin])
			for i in range(p.estacionIni, p.estacionFin):
				tramos[i] += b
				return sum(tramos)

	return sum(tramos)


def calcualrCotas(listaPedidos, capMax, tramos):
	for pedido in listaPedidos:
		p = pedido[1]
		if p.billetes >= capMax - max(tramos[p.estacionIni:p.estacionFin]):
			for i in range(p.estacionIni, p.estacionFin):
				tramos[i] += p.billetes
		else:
			b = capMax - max(tramos[p.estacionIni:p.estacionFin])
			for i in range(p.estacionIni, p.estacionFin):
				tramos[i] += b
				return sum(tramos)

	return sum(tramos)


def beneficiosCogidos(listaPedidos, capMax, tramos, cogidos):
	for c in cogidos:
		p = listaPedidos[c][1]
		for i in range(p.estacionFin, p.estacionFin):
			tramos[i] += p.billetes
	return [calcualrCostes(listaPedidos[cogidos[-1]:], capMax, tramos), calcualrCotas(listaPedidos[cogidos[-1]:], capMax, tramos)]

def buscarProblema(numP):
	f = open("pruebas.txt")
	
	lines = [line.rstrip('\n') for line in f]
	i = 0
	pedidos = 1
	while(i < len(lines) and pedidos <= numP ):
		problema = lines[i].split(' ')
		print (str(pedidos) + " - " + lines[i])
		i += int(problema[2])
		i += 1
		pedidos += 1

	print("lin " + str(i))
	print (str(pedidos) + " - " + lines[i])
	cap = int(lines[i].split(' ')[0])
	estaciones = int(lines[i].split(' ')[1])
	pedM = int(lines[i].split(' ')[2])
	ped = {}
	i += 1
	for h in range(i, i+pedM):
		p = lines[h].split(' ')
		ped[(h-i)] = Pedido(int(p[2]),int(p[0]),int(p[1]))
	return [ped, cap, estaciones]

print("Inserte numero de problema")
prob = 0
prob = int(input())
i = 1
[pedidos,cap, estaciones] = buscarProblema(prob)
for pedido in pedidos.values():
	print(str(i) + " " + str(pedido))
	i += 1

print('\n\n\n')
pedidos_r = sorted(pedidos.items(), key=operator.itemgetter(1))
for pedido in pedidos_r:
	print(str(i) + " " + str(pedido[1]))
	i += 1

lista = input("Inserte lista de cogidos").split()
cogidos = []
for l in lista:
	cogidos += [int(l)]

print (str(beneficiosCogidos(pedidos_r, cap, [0]*estaciones, cogidos)))