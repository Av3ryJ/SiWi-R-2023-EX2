import matplotlib.pyplot as plt
import numpy as np
import os.path as p
import json

binary = "./rbgs.exe"
thread_numbers = [1, 2, 5, 10, 15, 20]
number_of_iterations = 500
sizes_to_time = [32, 33, 1024, 1025, 2048, 2049]

json_path = "times.json"
time_json = {size: {thread: 0.0 for thread in thread_numbers} for size in sizes_to_time}


def get_array_for_size(size: int):
    out = []
    for thread in thread_numbers:
        out.append(time_json[str(size)][str(thread)])
    return out


def plot_all():
    for size in sizes_to_time:
        times = get_array_for_size(size)
        plt.plot(thread_numbers, times, label=f"{size}")

    plt.xlabel("Number of threads")
    plt.ylabel("Runtime in seconds")
    plt.legend(loc="upper left")
    plt.show()


if __name__ == '__main__':
    if p.exists(json_path):
        with open(json_path, 'r') as file:
            time_json = json.load(file)
    else:
        print("no json you idiot run timing.py first")

    plot_all()
