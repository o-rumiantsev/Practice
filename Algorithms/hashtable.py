import math

hashing = {}

def hash_dev(key, size):
    return key % size

def hash_mul(key, size):
    A = 0.618034
    return int(math.floor((key * A) % 1 * size))

def linear(key, i, size):
    return (hash_mul(key, size) + i) % size

def quadric(key, i, size):
    return (hash_dev(key, size) + i + i * i) % size

def double_hashing(key, i, size):
    h1 = hash_dev(key, size)
    h2 = 1 + (key % (size - 1))
    return (h1 + i * h2) % size


hashing['devision'] = hash_dev
hashing['multiply'] = hash_mul
hashing['linear sampling'] = linear
hashing['quadric sampling'] = quadric
hashing['double hashing'] = double_hashing


class Hash_table():
    def __init__(self, size, table_type):
        self.size = size * 3
        self.type = table_type

        if table_type == 'chained':
            self.table = []
            for i in range(self.size): self.table.append([])
        elif table_type == 'open address':
            self.table = [None] * self.size
            self._collisions = 0

    def hashing(self, hash_type):
        self.hash = hashing[hash_type]

    def insert(self, value):
        if self.type == 'chained':
            if not self.search(value):
                key = self.hash(value, self.size)
                self.table[key].append(value)
        elif self.type == 'open address':
            i = 0
            while i != self.size - 1:
                key = self.hash(value, i, self.size)
                if not self.table[key]:
                    self.table[key] = value
                    return
                i += 1
                self._collisions += 1

    def search(self, value):
        if self.type == 'chained':
            key = self.hash(value, self.size)
            chain = self.table[key]

            for i in range(len(chain)):
                if chain[i] == value: return chain[i]

            return None
        elif self.type == 'open address':
            i = 0
            while i != self.size - 1:
                key = self.hash(value, i, self.size)
                if self.table[key] == value:
                    return value
                i += 1
            return None

    def collisions(self):
        if self.type == 'chained':
            count = 0

            for i in range(self.size):
                chain_length = len(self.table[i])
                if chain_length > 1:
                    count += chain_length - 1

            return count
        elif self.type == 'open address':
            return self._collisions
