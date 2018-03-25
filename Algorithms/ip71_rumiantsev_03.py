input_file = open('input.txt', 'r')
array_to_sort = [int(line.strip()) for line in input_file]

input_length = array_to_sort[0]
del array_to_sort[0];

def quick_sort(array, p, r):
    if p < r:
        q = partition(array, p, r)
        quick_sort(array, p, q - 1)
        quick_sort(array, q + 1, r)

def partition(array, p, r):
    support_element = array[r]
    i = p - 1

    for j in range(p, r):
        if array[j] <= support_element:
            i = i + 1
            array[i], array[j] = array[j], array[i]

    array[r], array[i + 1] = array[i + 1], array[r]
    return i + 1

quick_sort(array_to_sort, 0, input_length - 1)
