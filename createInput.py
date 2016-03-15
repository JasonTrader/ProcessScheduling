import random
f = open('data.txt', 'w')
for pid in range (0, 10000):
    arrival_time = random.randint(0, 100000)
    cpu_to_io_count = random.randint(0, 5)
    cpu_to_io_count *= 2
    cpu_to_io_count += 1
    f.write(str(pid) + ', Arrival ' + str(arrival_time))
    for i in range (0, cpu_to_io_count):
        time = random.randint(1, 100)
        f.write(', IO ') if i%2 else f.write(', CPU ')
        f.write(str(time))
    f.write('\n')
