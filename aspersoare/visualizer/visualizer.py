import matplotlib.pyplot as plt
import numpy as np

def visualize_circles(N, L, W, circle_data):
    fig, ax = plt.subplots()
    
    rectangle = plt.Rectangle((0, 0), L, W, linewidth=1, edgecolor='black', facecolor='none')
    ax.add_patch(rectangle)

    for circle in circle_data:
        c, r = circle
        circle_obj = plt.Circle((c, W/2), r, edgecolor='blue', facecolor='none')
        help = np.sqrt(r**2 - (W/2)**2)
        obj_rect = plt.Rectangle((c-help,0), help * 2, W, linewidth=1, edgecolor='red', facecolor = 'none')
        ax.add_patch(obj_rect)
        ax.add_patch(circle_obj)

    ax.set_xlim(0, L)  
    ax.set_ylim(0, W)  
    ax.set_aspect('equal', adjustable='datalim')  
    plt.xlabel('Lungime (L)')
    plt.ylabel('Lățime (W)')
    plt.title('Grădina lui Andrei')

    plt.show()

input = open("input.txt","r")

circle_data = []
N = 8
L = 20
W = 2

for line in input:
    numbers = [ int(x) for x in line.strip().split() ]
    if len(numbers) == 3:
        N = numbers[0]
        L = numbers[1]
        W = numbers[2]
    else:
        circle_data.append((numbers[0],numbers[1]))

visualize_circles(N, L, W, circle_data)