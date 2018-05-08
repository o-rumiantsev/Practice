import sys
from heap import *

if len(sys.argv) < 2:
    print 'Please, enter input filename'
    exit(1)

filename = sys.argv[1]
input_file = open(filename)

input_array = [int(line.strip()) for line in input_file]
input_file.close()
del input_array[0]

max_heap = []
min_heap = []


for i in range(len(input_array)):
    if input_array[i] < get_max(max_heap):
        max_heap.append(input_array[i])
        build_heap(max_heap, max_heapify)

    else:
        min_heap.append(input_array[i])
        build_heap(min_heap, min_heapify)

    delta = compare(max_heap, min_heap)

    if delta == 2:
        min_heap.append(max_heap[0])
        build_heap(min_heap, min_heapify)
        del max_heap[0]

    elif delta == -2:
        max_heap.append(min_heap[0])
        build_heap(max_heap, max_heapify)
        del min_heap[0]

    diff = compare(max_heap, min_heap)

    if diff == 0:
        print get_max(max_heap), get_min(min_heap)
    elif diff == 1:
        print get_max(max_heap)
    else:
        print get_min(min_heap)
