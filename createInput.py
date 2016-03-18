import random
import sys
f = open('data.txt', 'w')
process_num = sys.argv[1]
max_burst_time = sys.argv[2]
total_run_time = sys.argv[3]
for pid in range (0, int(process_num)):
    arrival_time = random.randint(0, int(total_run_time))
    cpu_to_io_count = random.randint(0, 5)
    cpu_to_io_count *= 2
    cpu_to_io_count += 1
    f.write(str(pid) + ' Arrival ' + str(arrival_time))
    for i in range (0, cpu_to_io_count):
        time = random.randint(1, int(max_burst_time))
        f.write(' IO ') if i%2 else f.write(' CPU ')
        f.write(str(time))
    f.write('\n')
