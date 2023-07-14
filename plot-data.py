import os, re
import matplotlib.pyplot as plt
import numpy as np

machine = "deepbayou"
num = 100000000

data = {}
for f in os.listdir("data"):
    if not f.endswith(".csv"):
        continue
    g = re.match(r'^(\w+)_(\d+)_(\d+)_(\d+).csv$', f)
    if g:
        with open(f"data/{f}","r") as fd:
            for line in fd.readlines():
                row = line.strip().split(",")
                nprocs = int(row[0])
                tm = float(row[1])
                break
        assert int(g.group(2)) == num
        exe, procs, it = g.group(1), int(g.group(3)), int(g.group(4))
        assert procs == nprocs, f"{procs} != {nprocs}"
        if exe not in data:
            data[exe] = {}
        if procs not in data[exe]:
            data[exe][procs] = []
        data[exe][procs] += [tm]

for exe in data:
    procs_list = sorted(list(data[exe].keys()))
    data_list = [0 for n in procs_list]
    os.system(f"echo -n > data/WAMTA23/{machine}_{exe}.csv")
    for i in range(len(procs_list)):
        procs = procs_list[i]
        os.system(f"cat data/{exe}_{num}_{procs}_*.csv >> data/WAMTA23/{machine}_{exe}.csv")
        times = data[exe][procs]
        times = sorted(times)
        nn = len(times)//2
        data_list[i] = times[nn]
        print(exe, procs, data_list[i])
    plt.semilogy(np.array(procs_list), np.array(data_list), '-o', label=exe)
plt.legend()
plt.savefig("plt.png")
