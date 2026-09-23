import sys

import numpy as np
from matplotlib import pyplot as plt


def main():
    if len(sys.argv) < 2:
        print_usage()
        sys.exit(1)

    mode = sys.argv[1]

    if mode == "1":
        if len(sys.argv) != 7:
            print_usage()
            sys.exit(1)

        data_filename = sys.argv[2]
        x_label = sys.argv[3]
        y_label = sys.argv[4]
        title = sys.argv[5]
        result_filename = sys.argv[6]

        print(f"Data filename: {data_filename}")

        data = np.loadtxt(data_filename)
        x = data[:, 0]
        y = data[:, 1]

        plt.xlabel(x_label)
        plt.ylabel(y_label)
        plt.title(title)

        plt.plot(x, y, lw=1, color="black")
        plt.grid(True)

        ax = plt.subplot()
        ax.ticklabel_format(axis='y', style='plain', useOffset=False)
        ax.set_xlim(np.min(x), np.max(x))
        ax.set_ylim(np.min(y), np.max(y))

    elif mode == "2":
        if len(sys.argv) != 8:
            print_usage()
            sys.exit(1)

        x_filename = sys.argv[2]
        y_filename = sys.argv[3]
        x_label = sys.argv[4]
        y_label = sys.argv[5]
        title = sys.argv[6]
        result_filename = sys.argv[7]

        print(f"X filename: {x_filename}, Y filename: {y_filename}")

        x = np.fromfile(x_filename, sep='\n')
        y = np.fromfile(y_filename, sep='\n')

        plt.xlabel(x_label)
        plt.ylabel(y_label)
        plt.title(title)

        plt.plot(x, y, lw=1, color="black")
        plt.grid(True)

        ax = plt.subplot()
        ax.ticklabel_format(axis='y', style='plain', useOffset=False)
        ax.set_xlim(np.min(x), np.max(x))
        ax.set_ylim(np.min(y), np.max(y))

    elif mode == "3":
        remaining = sys.argv[2:]
        if len(remaining) < 4:
            print_usage()
            sys.exit(1)

        x_label = remaining[-4]
        y_label = remaining[-3]
        title = remaining[-2]
        result_filename = remaining[-1]

        pairs_args = remaining[:-4]

        if len(pairs_args) == 0 or len(pairs_args) % 2 != 0:
            print_usage()
            sys.exit(1)

        num_curves = len(pairs_args) // 2
        if num_curves > 4:
            print(f"Error: too many curves ({num_curves}), max is 4")
            sys.exit(1)

        line_styles = ['-', '--', '-.', ':']

        plt.xlabel(x_label)
        plt.ylabel(y_label)
        plt.title(title)

        all_x = []
        all_y = []

        for i in range(num_curves):
            data_filename = pairs_args[2 * i]
            curve_name = pairs_args[2 * i + 1]

            print(f"Curve {i + 1}: filename={data_filename}, name={curve_name}")

            data = np.loadtxt(data_filename)
            x = data[:, 0]
            y = data[:, 1]

            all_x.append(x)
            all_y.append(y)

            plt.plot(
                x, y,
                lw=1,
                color="black",
                linestyle=line_styles[i],
                label=curve_name,
            )

        plt.grid(True)
        plt.legend()

        ax = plt.subplot()
        ax.ticklabel_format(axis='y', style='plain', useOffset=False)
        ax.set_xlim(np.min([np.min(xx) for xx in all_x]),
                    np.max([np.max(xx) for xx in all_x]))
        ax.set_ylim(np.min([np.min(yy) for yy in all_y]),
                    np.max([np.max(yy) for yy in all_y]))

    else:
        print(f"Unknown mode: {mode}")
        print_usage()
        sys.exit(1)

    plt.savefig(result_filename + ".png", bbox_inches='tight', dpi=300)
    plt.show()


def print_usage():
    print("Usage:")
    print("  Mode 1 (single file):  python plot.py 1 data.txt x_label y_label title output")
    print("  Mode 2 (two files):    python plot.py 2 x.txt y.txt x_label y_label title output")
    print("  Mode 3 (multi curves): python plot.py 3 data1.txt name1 data2.txt name2 ... x_label y_label title output")
    print("                         (max 4 curves)")


if __name__ == "__main__":
    main()
