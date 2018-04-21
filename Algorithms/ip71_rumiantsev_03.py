import sys

if len(sys.argv) < 2:
    print 'Please, enter input filename'
    exit(1)

filename = sys.argv[1]
input_file = open(filename)

array_to_sort_1 = [int(line.strip()) for line in input_file]
input_file.close()

input_length = array_to_sort_1[0]
del array_to_sort_1[0]

array_to_sort_2 = array_to_sort_1[:]
array_to_sort_3 = array_to_sort_1[:]

compare_counter_1 = 0
compare_counter_2 = 0
compare_counter_3 = 0

# Default algorithm
#
#
def quick_sort(array, start, end):
    if start < end:
        q = partition(array, start, end)
        quick_sort(array, start, q - 1)
        quick_sort(array, q + 1, end)


def partition(array, start, end):
    global compare_counter_1

    base = array[end]
    i = start - 1

    compare_counter_1 += (end - start)

    for j in range(start, end):
        if array[j] <= base:
            i = i + 1
            array[i], array[j] = array[j], array[i]

    array[end], array[i + 1] = array[i + 1], array[end]
    return i + 1


# Using 3-median improvement
#
#
def quick_sort_3_med(array, start, end):
    if end - start <= 3 and end - start > 0:
       simple_sort_3_med(array, start, end)
    elif start < end:
        q = partition_3_med(array, start, end)
        quick_sort_3_med(array, start, q - 1)
        quick_sort_3_med(array, q + 1, end)


def partition_3_med(array, start, end):
    global compare_counter_2

    median = get_median(array, start, end)
    median_index = array.index(median)

    array[median_index], array[end] = array[end], array[median_index]

    base = median
    i = start - 1

    compare_counter_2 += (end - start)

    for j in range(start, end):
        if array[j] <= base:
            i = i + 1
            array[i], array[j] = array[j], array[i]

    array[end], array[i + 1] = array[i + 1], array[end]
    return i + 1


def simple_sort_3_med(array, start, end):
    global compare_counter_2
    for i in range(start + 1, end + 1):
        for j in range(i - 1, start - 1, -1):
            compare_counter_2 += 1
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]
            else:
                break




def get_median(array, start, end):
    i, j, k = array[start], array[(start + end)/2], array[end]
    if i <= j <= k or k <= j <= i:
      return j
    elif j <= i <= k or k <= i <= j:
      return i
    else:
      return k


# # 3-base-improvement
#
#
def quick_sort_3_base(array, start, end):
    if end - start <= 3 and end - start > 0:
        simple_sort_3_base(array, start, end)
    elif start < end:
        get_3_base(array, start, end)
        q1, q2, q3 = partition_3_base(array, start, end)
        quick_sort_3_base(array, start, q1 - 1)
        quick_sort_3_base(array, q1 + 1, q2 - 1)
        quick_sort_3_base(array, q2 + 1, q3 - 1)
        quick_sort_3_base(array, q3 + 1, end)

def partition_3_base(array, start, end):
    global compare_counter_3

    minb, medb, maxb = array[start], array[start + 1], array[end]

    # sort for last element
    #
    i = start + 1

    for j in range(start + 2, end):
        compare_counter_3 += 1
        if array[j] <= maxb:
            i += 1
            array[i], array[j] = array[j], array[i]

    array[end], array[i + 1] = array[i + 1], array[end]
    q3 = i + 1

    # sort for medium
    #
    i = q3

    for j in range(q3 - 1, start + 1, -1):
        compare_counter_3 += 1
        if array[j] >= medb:
            i -= 1
            array[i], array[j] = array[j], array[i]

    array[start + 1], array[i - 1] = array[i - 1], array[start + 1]
    q2 = i - 1

    # sort for first
    #
    i = q2

    for j in range(q2 - 1, start, -1):
        compare_counter_3 += 1
        if array[j] >= minb:
            i -= 1
            array[i], array[j] = array[j], array[i]

    array[start], array[i - 1] = array[i - 1], array[start]

    q1 = i - 1

    return q1, q2, q3

def simple_sort_3_base(array, start, end):
    global compare_counter_3
    for i in range(start + 1, end + 1):
        for j in range(i - 1, start - 1, -1):
            compare_counter_3 += 1
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]
            else:
                break


def get_3_base(array, start, end):
    min_el, med_el, max_el = array[start], array[start + 1], array[end]

    base = [min_el, med_el, max_el]

    for i in range(1, 3):
        for j in range(i - 1, -1, -1):
            if base[j] > base[j + 1]:
                base[j], base[j + 1] = base[j + 1], base[j]
            else:
                break

    array[start] = base[0]
    array[start + 1] = base[1]
    array[end] = base[2]

print array_to_sort_1
quick_sort(array_to_sort_1, 0, input_length - 1)
print array_to_sort_1
quick_sort_3_med(array_to_sort_2, 0, input_length - 1)
quick_sort_3_base(array_to_sort_3, 0, input_length - 1)

output = open('ip71_rumiantsev_03_output.txt', 'w')

output.write(str(compare_counter_1))
output.write(' ')

output.write(str(compare_counter_2))
output.write(' ')

output.write(str(compare_counter_3))
output.write(' ')

output.close()
