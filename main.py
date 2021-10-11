from apriori_python import apriori
from fpgrowth_py import fpgrowth

items = [['A', 'B', 'C', 'D'],
         ['A', 'C', 'D', 'F'],
         ['A', 'C', 'D', 'E', 'G'],
         ['A', 'B', 'D', 'F'],
         ['B', 'C', 'G'],
         ['D', 'F', 'G'],
         ['A', 'B', 'G'],
         ['C', 'D', 'F', 'G']]

freqItemSet, rules = apriori(items, minSup=3 / 8, minConf=0)
print('Задание 1\nApriori:')
print(freqItemSet)
freqItemSet, rules = fpgrowth(items, minSupRatio=2 / 8, minConf=0)
print('\nFPGRowth:')
print(freqItemSet)

items_ex2 = [['2', '3', '6', '7', '12', '14', '15'],
             ['1', '3', '4', '8', '11', '12', '14', '13', '15'],
             ['3', '9', '11', '12', '14', '13', '15'],
             ['1', '5', '6', '7', '14', '15'],
             ['1', '3', '8', '10', '11', '12', '14', '13', '15'],
             ['3', '5', '7', '9', '11', '12', '14', '15', '13'],
             ['4', '6', '8', '10', '11', '12', '14', '13', '15'],
             ['1', '3', '5', '8', '11', '12', '14', '13', '15']]

freqItemSet, rules = fpgrowth(items_ex2, minSupRatio=7 / 8, minConf=0)
simple = ['1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11']
print('\nЗадание 2')
print('A. Размер области поиска:', 2 ** len(simple))


def check(a, b):
    for i in a:
        if i in b:
            return True
    return False


result = []
for i in freqItemSet:
    if not check(i, simple):
        result.append(i)
print('B.', result)
