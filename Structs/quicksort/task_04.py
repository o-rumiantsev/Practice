from quicksort import quick_sort_obj

class Abonent:
    def __init__(self, name, number):
        self.name = name
        self.number = number

    def __str__(self):
        return "{ name: " + self.name + ", number: " + self.number + " }"

oleksii = Abonent("Oleksii", "0956956967")
diana = Abonent("Diana", "0993089930")
olia = Abonent("Olia", "0679960862")
machendos = Abonent("Machendos", "0977637913")

abonents = [oleksii, diana, olia, machendos]
length = len(abonents)

for abonent in abonents:
    print abonent


quick_sort_obj(abonents, 0, length - 1)
print

for abonent in abonents:
    print abonent
