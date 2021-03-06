import numpy as np
import matplotlib.pyplot as plt
from math import sqrt


def get_probability(delta_energy, beta):
    return np.exp(-delta_energy*beta)

def get_energy():
    return -np.sum(
    interaction * spins * np.roll(spins, 1, axis=0) +
    interaction * spins * np.roll(spins, -1, axis=0) +
    interaction * spins * np.roll(spins, 1, axis=1) +
    interaction * spins * np.roll(spins, -1, axis=1)
  )/2 - moment * np.sum(field * spins)


def update(beta):
    global spins
    # global current_energy
    global spins_sum
    i = np.random.randint(spins.shape[0])
    j = np.random.randint(spins.shape[1])
    delta_energy=2*spins[i,j]*(spins[(i+1)%L,j]+spins[(i-1)%L,j]+spins[i,(j+1)%L]+spins[i,(j-1)%L])
    if get_probability(delta_energy, beta) > np.random.random():
        spins[i,j] *= -1
        # current_energy += delta_energy
        # spins_sum += spins[i,j]*2


def isweep(N,beta):
    for i in range(N):
        update(beta)
        # print("isweep",i)

if __name__ == '__main__':
    L = 16
    shape = (L, L)
    N = L*L
    moment = 1
    delta=0.05
    # External magnetic field
    field = np.full(shape, 0)

    # Temperature (in units of energy)
    temperature = 4.0                   
    beta=1/temperature
    # Interaction (ferromagnetic if positive, antiferromagnetic if negative)
    interaction = 1
    global spins
    spins = np.full(shape,1)
    N_total=1000000
    isweep(N_total,beta)
    plt.matshow(spins)
    plt.show()
