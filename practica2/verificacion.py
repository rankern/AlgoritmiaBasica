f =open("resultado.txt")
f2 = open("resultadoFB.txt")
lines = [line.rstrip('\n') for line in f]
lines2 = [line2.rstrip('\n') for line2 in f2]
numProblema = 0
problemasMal = 0
while(numProblema < len(lines)):   
    problema = lines[numProblema].split(' ')
    problema2 = lines2[numProblema].split(' ')
    p1 = problema[0]
    p2 = problema2[2]
    if(int(p1) != int(p2)):
        problemasMal +=1
        print("------------------------------")
        print(lines2[numProblema] + " Pero se ha obtenido: " + p1)
        print("resultado: " + lines[numProblema])
        print("resultado FB: "  + lines2[numProblema])
    numProblema += 1
print("numProblemasMal : " + str(problemasMal))
f.close()
f2.close()