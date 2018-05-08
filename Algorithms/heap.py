def parent(i):
    return (i + 1) / 2 - 1

def left(i):
    return 2 * i + 1

def right(i):
    return 2 * i + 2


def max_heapify(heap, heap_size, i):
    l = left(i)
    r = right(i)

    largest = 0

    if l <= heap_size - 1 and heap[l] > heap[i]:
        largest = l
    else:
        largest = i

    if r <= heap_size - 1 and heap[r] > heap[largest]:
        largest = r

    if not largest == i:
        heap[i], heap[largest] = heap[largest], heap[i]
        max_heapify(heap, heap_size, largest)


def min_heapify(heap, heap_size, i):
    l = left(i)
    r = right(i)

    smallest = 0

    if l <= heap_size - 1 and heap[l] < heap[i]:
        smallest = l
    else:
        smallest = i

    if r <= heap_size - 1 and heap[r] < heap[smallest]:
        smallest = r

    if not smallest == i:
        heap[i], heap[smallest] = heap[smallest], heap[i]
        min_heapify(heap, heap_size, smallest)


def build_heap(heap, heapify):
    heap_size = len(heap)
    last = len(heap) - 1

    for k in range(parent(last), -1, -1):
        heapify(heap, heap_size, k)


def heap_sort(heap, heapify):
    build_heap(heap, heapify)

    heap_size = len(heap)

    for i in range(heap_size - 1, 0, -1):
        heap[i], heap[0] = heap[0], heap[i]
        heap_size -= 1
        heapify(heap, heap_size, 0)


def get_min(min_heap):
    heap_size = len(min_heap)
    if heap_size > 0: return min_heap[0]
    else: return -1

def get_max(max_heap):
    heap_size = len(max_heap)
    if heap_size > 0: return max_heap[0]
    else: return -1

def compare(max_heap, min_heap):
    return len(max_heap) - len(min_heap)
