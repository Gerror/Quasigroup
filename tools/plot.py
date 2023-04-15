import numpy as np
import sys
from matplotlib import pyplot as plt

def main():
    x_filename = sys.argv[1]
    y_filename = sys.argv[2]
    x_label = sys.argv[3]
    y_label = sys.argv[4]
    result_filename = sys.argv[5]

    print(f"X filename: { x_filename }, Y filename: { y_filename }")

    x = np.fromfile(x_filename, sep='\n')
    y = np.fromfile(y_filename, sep='\n')

    plt.xlabel(x_label)
    plt.ylabel(y_label)

    plt.plot(x, y, lw=1, color="black")
    plt.grid(True)

    ax = plt.subplot()
    ax.set_xlim(np.min(x), np.max(x))
    ax.set_ylim(np.min(y), np.max(y))
    plt.savefig(result_filename + ".png", bbox_inches='tight', dpi=300)

    plt.show()

if __name__ == "__main__":
    main()

