import math
import random
import copy

f = open("output.txt", "w")

# pop = int(input("Population: "))

# print ("Write the function domain:")

# a = float(input("lower bound: "))
# b = float(input("upper bound: "))

# print("Write the Polynomial coefficients: ")
# coef = [int(x) for x in input().split()]

# prec = int(input("Precision: "))
# cross = float(input("Crossover probability: "))
# mut = float(input("Mutation probability: "))
# nrstg = int(input("Number of stages: "))

pop = 20
a = -1
b = 2
coef = [-1, 1, 2]

prec = 6
cross = 0.25
mut = 0.25
nrstg = 50

# Chromosome length
# We're calculating the lenght of the chromosome based on the bounds interval
lenChrom = math.ceil(math.log2((b-a)*(10**prec)))

# Generate the Chromosome
# We will randomly generate a chromosome
# chromosomes[0] - first chromosome
# chromosomes[0][0] - first gene of the first chromosome
Chromosomes = [[random.randint(0, 1) for x in range(lenChrom)] for y in range(pop)]

# This is the fitness function also known as maximization function
# This is supposed to test the quality of the chromosome
def fx(x, v):
    return v[0] * (x ** 2) + v[1] * x + v[2]


def binarySearch(x, arr, l, r):
    global last
    while l <= r:
        mid = l + (r - l) // 2;
        if arr[mid] <= x:
            last = mid
            l = mid + 1
        elif arr[mid] > x:
            r = mid - 1
    return last


def intervals(intervals, selection, stage, pop):
    sumi = selection[0]
    intervals.append(sumi)
    if stage == 1:
        f.write("0 " + str(sumi) + " ")
    for i in range(1, pop):
        sumi += selection[i]
        intervals.append(sumi)      # the intervals are the sum of the probabilities
        if stage == 1:
            f.write(str(sumi) + " ")
    f.write("\n\n")
    return sumi

def interpolation(Xs, Chromosomes, stage, pop, coef, lenChrom):
    for i in range(pop):

        # Calculating the fitnees function for each chromosome and the biggest value of the fitness function

        BitString = ''.join(str(e) for e in Chromosomes[i])
        X = int(BitString, 2)   # convert the binary string to integer
        # Interpolate the value of X using the formula presented in the course 
        # for encoding a chromosome
        InterpolateX = ((b-a)/(2**lenChrom-1)) * X + a
        RoundInterpolateX = round(InterpolateX, prec)
        Xs[i]= InterpolateX # add the value of X to the list of Xs
        Fx = fx(RoundInterpolateX, coef) # calculate the fitness function

        if stage == 1:
            f.write(str(i+1) + ": " + BitString + " x= " + str(RoundInterpolateX) + " f= " + str(Fx) + "\n")


for stage in range(1,nrstg):
    if stage == 1:
        f.write("Populatia initiala\n")

    SumF = 0
    Xs = []
    MaxFittest = float('-inf')
    IdFittest = 0

    for i in range(pop):

        # Calculating the fitnees function for each chromosome and the biggest value of the fitness function

        BitString = ''.join(str(e) for e in Chromosomes[i])
        X = int(BitString, 2)   # convert the binary string to integer
        # Interpolate the value of X using the formula presented in the course 
        # for encoding a chromosome
        InterpolateX = ((b-a)/(2**lenChrom-1)) * X + a
        RoundInterpolateX = round(InterpolateX, prec)
        Xs.append(InterpolateX) # add the value of X to the list of Xs
        Fx = fx(RoundInterpolateX, coef) # calculate the fitness function
        SumF += fx(InterpolateX, coef) # calculate the sum of the fitness functions

        if Fx > MaxFittest:
            MaxFittest = Fx
            IdFittest = i

        if stage == 1:
            f.write(str(i+1) + ": " + BitString + " x= " + str(RoundInterpolateX) + " f= " + str(Fx) + "\n")
        
    
    Fittest = Chromosomes[IdFittest].copy()

    # Calculate the selection probability for each chromosome
    if stage == 1:
        f.write("\nProbabilitati selectie\n")
    
    SelectionProb = []

    for i in range(pop):
        prob = fx(Xs[i], coef) / SumF
        SelectionProb.append(prob)
        if stage == 1:
            f.write("Cromozom " + str(i+1) + " probability: " + str(prob) + "\n")

    # Calculate the intervals
    if stage == 1:
        f.write("\nIntervale probabilitati selectie\n")
    
    # The intervals are the sum of the probabilities
    SelectionProbIntervals = [0]
    SumI = intervals(SelectionProbIntervals, SelectionProb, stage, pop)

    # Selecting the Chromosomes Randomly
    
    Selected = [0 for x in range(pop)]

    for i in range(pop):
        rand = random.random()
        index = binarySearch(rand, SelectionProbIntervals, 0, pop-1)
        Selected[i] = index

        if stage == 1:
            f.write("u =  " + str(rand) + " cromozom selectat: " + str(index) + "\n")

    if stage == 1:
        f.write("\nDupa Selectie\n")
    
    SelectedChromosomes = []
    for i in range(pop):
        SelectedChromosomes.append(Chromosomes[Selected[i]].copy())
        if stage == 1:
            Bit = ''.join([str(e) for e in Chromosomes[Selected[i]]])
            Fx = fx(Xs[Selected[i]], coef)
            f.write(str(i+1) + ": " + Bit + " x= " + str(round(Xs[Selected[i]], prec)) + " f= " + str(Fx) + "\n")

    Chromosomes = copy.deepcopy(SelectedChromosomes)

    # Crossover

    Crossovers = []

    if stage == 1:
        f.write("\nProbabilitati crossover: " + str(cross) + "\n")

    for i in range(pop):
        Bit = ''.join([str(e) for e in Chromosomes[Selected[i]]])
        rand = random.random()

        if stage == 1:
            f.write(str(i+1) + ": " + Bit + " u = " + str(rand) + " ")
            if rand <= cross:
                Crossovers.append(i)
                f.write(" < " + str(cross) + " participa\n")
            else:
                f.write("\n")

    
    if stage == 1:
        f.write("\n")

    
    while len(Crossovers) > 1:

        # Choose the last two chromosomes that will be crossed
        i = len(Crossovers) - 1
        j = i - 1

        # Point of crossover. Where the chromosomes will be cut and the genes will be swapped
        slice = random.randrange(lenChrom)

        if stage == 1:
            f.write("Recombinare dintre cromozomul: " + str(Crossovers[i]+1) + " si cromozomul: " + str(Crossovers[j]+1) + "\n")
            Bit1 = ''.join([str(e) for e in Chromosomes[Crossovers[i]]])
            Bit2 = ''.join([str(e) for e in Chromosomes[Crossovers[j]]])
            f.write("\n" + Bit1 + " si " + Bit2 + " punct " + str(slice) + "\n")

        # Swap the genes

        First = Chromosomes[Crossovers[i]][:slice + 1].copy()
        Chromosomes[Crossovers[i]][:slice + 1] = Chromosomes[Crossovers[j]][:slice + 1].copy()
        Chromosomes[Crossovers[j]][:slice + 1] = First.copy()

        Bit1 = ''.join([str(e) for e in Chromosomes[Crossovers[i]]])
        Bit2 = ''.join([str(e) for e in Chromosomes[Crossovers[j]]])

        if stage == 1:
            f.write("\nRezultat: " + Bit1 + " si " + Bit2 + "\n")


        # Remove the chromosomes that have been crossed
        Aux = Crossovers[:len(Crossovers) - 1]
        Crossovers = Aux.copy()

    if stage == 1:
        f.write("\nDupa recombinare\n")

    interpolation(Xs, Chromosomes, stage, pop, coef, lenChrom)


    # Mutation

    if stage == 1:
        f.write("\nProbabilitate de mutatie pentru fiecare gena: " + str(mut) + "\n")
        f.write("Au fost modificati cromozomii: \n")
    
    for i in range(pop):
        rand = random.random()

        if rand <= mut:
            Gene = random.randrange(lenChrom)

            # Mutation happens when a bit switches from 0 to 1 or from 1 to 0

            Chromosomes[i][Gene] = 1 - Chromosomes[i][Gene]

            if stage == 1:
                f.write(str(i+1) + "\n")

    if stage == 1:
        f.write("\nDupa mutatie\n")

    interpolation(Xs, Chromosomes, stage, pop, coef, lenChrom)

    Max = float('-inf')
    WorstValue = float('inf')
    Worst = 0
    MediumValSum = 0

    for i in range(pop):

        # Calculating the fitnees function for each chromosome and the biggest value of the fitness function

        BitString = ''.join(str(e) for e in Chromosomes[i])
        X = int(BitString, 2)   # convert the binary string to integer
        # Interpolate the value of X using the formula presented in the course 
        # for encoding a chromosome
        InterpolateX = ((b-a)/(2**lenChrom-1)) * X + a
        RoundInterpolateX = round(InterpolateX, prec)
        Xs[i]= InterpolateX # add the value of X to the list of Xs
        Fx = fx(RoundInterpolateX, coef) # calculate the fitness function

        Max = max(Max, Fx) # calculate the maximum value of the fitness function
        MediumValSum += Fx # calculate the sum of the fitness functions

        if Fx < WorstValue:

            # If the fitness function is smaller than the worst value then we save the index of the chromosome
            # and the value of the fitness function
            WorstValue = Fx
            Worst = i
        
    # Replace the worst chromosome with the fittest chromosome
    Chromosomes[Worst] = Fittest.copy()
    Max = max(Max, MaxFittest)
    MediumValSum = MediumValSum - WorstValue + MaxFittest

    if stage == 1:
        f.write("\nEvolutia maximului\n")

    f.write(str(Max) + "\n")

f.close()
