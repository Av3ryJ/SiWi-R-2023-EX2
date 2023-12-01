import subprocess
import os.path as p
import json
import matplotlib.pyplot as plt
import numpy as np

binary = "./rbgs.exe"
thread_numbers = [1, 2, 5, 10, 15, 20]
number_of_iterations = 500
sizes_to_time = [32, 33, 1024, 1025, 2048, 2049]

json_path = "times.json"
time_json = {size: {thread: 0.0 for thread in thread_numbers} for size in sizes_to_time}


def run_bin(bin, size1, size2, iterations, option):
    result = subprocess.run([bin, size1, size2, iterations, option], capture_output=True, text=True)
    return result.stdout


def time_all():
    # iterate over sizes and threads
    for thread_num in thread_numbers:
        for size in sizes_to_time:
            print(f"running: {size} {thread_num}")
            returned = run_bin(binary, str(size), str(size), str(number_of_iterations), str(thread_num))
            time = float(returned)
            print(f"time was: {time}")
            time_json[size][thread_num] = time
    with open(json_path, 'w') as f:
        json.dump(time_json, f)


if __name__ == '__main__':
    if p.exists(json_path):
        with open(json_path, 'r') as file:
            time_json = json.load(file)
    else:
        time_all()
