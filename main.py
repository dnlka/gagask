import numpy
import statistics
import matplotlib.pyplot as plt
import scipy.stats as stats

X = [69, 74, 68, 70, 72, 67, 66, 70, 76, 68, 72, 79, 74, 67, 66, 71, 74, 75, 75, 76]
Y = [153, 175, 155, 135, 172, 150, 115, 137, 200, 130, 140, 265, 185, 112, 140,  150, 165, 185, 210, 220]
print("Задание 1")
print ("A.\n  Среднее: "+str(numpy.mean(X)))
print("  Медиана: "+str(statistics.median(X)))
print("  Мода: "+str(statistics.mode(X)))
print("B.\n  Дисперсия: "+str(numpy.var(Y)))
plt.plot(sorted(X), stats.norm.pdf(sorted(X), numpy.mean(X), numpy.std(X)))
plt.title("C. График нормального распределения для X")
plt.show()
plt.plot(X, Y, 'o')
plt.title("D. Диаграмма рассеяния")
plt.show()
print("\nЗадание 3\nA.")
arr = [5, 6, 7]
first = stats.norm.pdf(arr, 4, 1)
second = stats.norm.pdf(arr, 8, 2)
for i in range(3):
    if (first[i] > second[i]):
        print("  Для значения "+str(arr[i])+" большая вероятность у Na")
    else:
        print("  Для значения "+str(arr[i])+" большая вероятность у Nb")
