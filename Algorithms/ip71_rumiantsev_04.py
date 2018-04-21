def counting_sort(array):
    length = len(array)
    max_el = max(array)

    sorted_array = array[:]
    support = [0] * (max_el + 1)

    for i in range(0, length):
        support[array[i]] += 1

    for j in range(1, max_el + 1):
        support[j] += support[j - 1]

    for k in range(length - 1, -1, -1):
        element = array[k]
        support[element] -= 1
        sorted_array[support[element]] = array[k]

    return sorted_array


arr = [1, 6, 444, 23, 4533, 3, 0, 3, 0]
sorted_arr = counting_sort(arr)
print sorted_arr
