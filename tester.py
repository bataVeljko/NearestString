import json
from subprocess import call
import time

def main():
    data = {}
    try:
        with open('params.json') as f:
            data = json.load(f)
    except Exception as e:
        raise e

    # max_iterations, pop_size, mutation_rate, tournament_k, crossover_prob
    params_iters = data['iters']
    params_popSize = data['popSize']
    params_mutationRate = data['mutationRate']
    params_crossoverProb = data['crossoverProb']
    params_tournamentK = [(i//5) for i in params_popSize] # one fifth of the population

    print("NumberOfIterations", "PopulationSize", "MutationRate", "TournamentSize", "CrossoverProbability", " BestFit", "Elapsed time(ms)")

    # all combinations
    for i1 in params_iters:
        for i2 in params_popSize:
            for i3 in params_mutationRate:
                for i4 in params_tournamentK:
                    if i2 <= i4:
                        break

                    for i5 in params_crossoverProb:
                        # run nearestString exec with arguments
                        start = time.time()
                        call(['./nearestString', str(i1), str(i2), str(i3), str(i4), str(i5)])
                        # time program needed to finish with passed arguments
                        print("     %12.6f" % ((time.time()-start) * 1000))


if __name__ == '__main__':
    main()
