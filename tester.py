import json
from subprocess import call
        # call(["g++", "animacija.cpp", "-lglut", "-lGLU", "-lGL"])
        # call(["./a.out"])

def main():
    data = {}
    try:
        with open('params.json') as f:
            data = json.load(f)
    except Exception as e:
        raise e

    # max_iterations, pop_size, mutation_rate, tournament_k. crossover_prob
    params_iters = data['iters']
    params_popSize = data['popSize']
    params_mutationRate = data['mutationRate']
    params_crossoverProb = data['crossoverProb']
    params_tournamentK = [(i//5) for i in params_popSize] # one fifth of the population

    print(params_tournamentK)

    # all combinations
    for i1 in params_iters:
        for i2 in params_popSize:
            for i3 in params_mutationRate:
                for i4 in params_tournamentK:
                    for i5 in params_crossoverProb:
                        print('iters: ' + str(i1) + ' popSize: ' + str(i2), ' mutationRate: ' + str(i3), end='')
                        print(' tournamentK: ' + str(i4) + " crossoverProb: " + str(i5))
                        # run nearestString exec with arguments
                        call(['./nearestString', str(i1), str(i2), str(i3), str(i4), str(i5)])


if __name__ == '__main__':
    main()