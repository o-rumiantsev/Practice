import sys
from hashtable import Hash_table

if len(sys.argv) < 3:
    print 'Please, enter input filename'
    exit(1)

filename = sys.argv[2]
input_file = open(filename)

sizes = [int(size) for size in input_file.readline().split()]
input_array = [int(line.strip()) for line in input_file]
input_file.close()

task_type = sys.argv[1]
table_type = ""

if task_type == '1':
    table_type = 'chained'
    hash_type = 'devision'
elif task_type == '2':
    table_type = 'chained'
    hash_type = 'multiply'
elif task_type == '3':
    table_type = 'open address'
    hash_type = 'linear sampling'
elif task_type == '4':
    table_type = 'open address'
    hash_type = 'quadric sampling'
elif task_type == '5':
    table_type = 'open address'
    hash_type = 'double hashing'
else:
    print 'Unknown task type `' + str(task_type) + '`.'
    exit(1)

arr_length = sizes[0]
sums_length = sizes[1]

array = input_array[0:arr_length]
sums = input_array[arr_length:]


# Solution
#
table = Hash_table(arr_length, table_type)
table.hashing(hash_type)

for i in range(arr_length):
    table.insert(array[i])

print table.collisions()

for s in range(sums_length):
    summa = sums[s]
    res_exists = False

    for i in range(arr_length):
        diff = summa - array[i]
        res = table.search(diff)
        if res:
            res_exists = True
            print array[i], res
            break

    if not res_exists: print 0, 0
