import json
import matplotlib.pyplot as plt
import numpy as np

def main():
    with open("data.json") as input_file:
        # read json file
        data = json.load(input_file)
        caches = data["context"]["caches"]
        benchmarks = data["benchmarks"]
        family_indices = np.array([ int(bm["family_index"]) for bm in benchmarks ])
        array_sizes = np.array([ int(bm["name"].split('/')[-1]) for bm in benchmarks ])
        items_per_second = np.array([ float(bm["items_per_second"]) for bm in benchmarks ])
        seconds_per_item = 1.0 / items_per_second

        # parse data
        no_sort_indices = np.where(family_indices == 0)
        std_sort_indices = np.where(family_indices == 1)
        quick_sort_indices = np.where(family_indices == 2)
        insertion_sort_indices = np.where(family_indices == 3)
        bubble_sort_indices = np.where(family_indices == 4)

        # plot data
        plt.loglog(array_sizes[no_sort_indices], seconds_per_item[no_sort_indices], "k", label="No Sort")
        plt.loglog(array_sizes[std_sort_indices], seconds_per_item[std_sort_indices], "b", label="std::sort")
        plt.loglog(array_sizes[quick_sort_indices], seconds_per_item[quick_sort_indices], "m", label="Quick Sort")
        plt.loglog(array_sizes[insertion_sort_indices], seconds_per_item[insertion_sort_indices], "r", label="Insertion Sort")
        #plt.loglog(array_sizes[bubble_sort_indices], seconds_per_item[bubble_sort_indices], "y", label="Bubble Sort")
        plt.xlim(1, 1024)
        plt.xlabel("Items in Array")
        plt.ylabel("Time per Item (s)")
        plt.title("Performance of Sorting Algorithms for Small Array Sizes")
        plt.legend()
        plt.grid()
        plt.show()

if __name__ == "__main__":
    main()