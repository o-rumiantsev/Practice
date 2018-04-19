def quick_sort(array, start, end):
    if start < end:
        q = partition(array, start, end)
        quick_sort(array, start, q - 1)
        quick_sort(array, q + 1, end)
        return array


def partition(array, start, end):
    base = array[end]
    i = start - 1

    for j in range(start, end):
        if array[j] <= base:
            i = i + 1
            array[i], array[j] = array[j], array[i]

    array[end], array[i + 1] = array[i + 1], array[end]
    return i + 1


def quick_sort_obj(array, start, end):
    if start < end:
        q = partition_obj(array, start, end)
        quick_sort_obj(array, start, q - 1)
        quick_sort_obj(array, q + 1, end)

def partition_obj(array, start, end):
    base = array[end].number
    i = start - 1

    for j in range(start, end):
        if array[j].number <= base:
            i = i + 1
            array[i], array[j] = array[j], array[i]

    array[end], array[i + 1] = array[i + 1], array[end]
    return i + 1
