import sys

import numpy as np
from matplotlib import pyplot as plt


def main():
    if len(sys.argv) == 6:
        data_filename = sys.argv[1]
        x_label = sys.argv[2]
        y_label = sys.argv[3]
        title = sys.argv[4]
        result_filename = sys.argv[5]

        print(f"Data filename: {data_filename}")

        data = np.loadtxt(data_filename)

        x = data[:, 0]
        y = data[:, 1]

    elif len(sys.argv) == 7:
        x_filename = sys.argv[1]
        y_filename = sys.argv[2]
        x_label = sys.argv[3]
        y_label = sys.argv[4]
        title = sys.argv[5]
        result_filename = sys.argv[6]

        print(f"X filename: {x_filename}, Y filename: {y_filename}")

        x = np.fromfile(x_filename, sep='\n')
        y = np.fromfile(y_filename, sep='\n')
    else:
        print("Usage:")
        print("  Mode 1 (single file): python plot.py data.txt x_label y_label title output")
        print("  Mode 2 (two files):   python plot.py x.txt y.txt x_label y_label title output")
        sys.exit(1)

    plt.xlabel(x_label)
    plt.ylabel(y_label)
    plt.title(title)

    plt.plot(x, y, lw=1, color="black")
    plt.grid(True)

    ax = plt.subplot()
    ax.set_xlim(np.min(x), np.max(x))
    ax.set_ylim(np.min(y), np.max(y))
    plt.savefig(result_filename + ".png", bbox_inches='tight', dpi=300)

    plt.show()


if __name__ == "__main__":
    main()
