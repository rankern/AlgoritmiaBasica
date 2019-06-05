f =open("resultado.txt")
f2 = open("resultado1.txt")
lines = [line.rstrip('\n') for line in f]
lines2 = [line2.rstrip('\n') for line2 in f2]
numProblema = 0
problemasMal = 0
mejor1 = 0
while(numProblema < len(lines)):   
    problema = lines[numProblema].split(' ')
    problema2 = lines2[numProblema].split(' ')
    p1 = problema[1]
    p2 = problema2[1]
    if(int(p1) <= int(p2)):
        mejor1 +=1
    numProblema += 1
print("Mejor 1 = " + str(mejor1) +  " es el " + str(100*(mejor1/8000)) +"%")
f.close()
f2.close()