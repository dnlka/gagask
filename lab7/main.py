import pandas as pd
import numpy as np
from sklearn import preprocessing
from sklearn.model_selection import train_test_split
from sklearn.naive_bayes import GaussianNB, MultinomialNB, ComplementNB, BernoulliNB
import matplotlib.pyplot as plt
from sklearn import tree



data = pd.read_csv('iris.data',header=None)
print(data)

X = data.iloc[:,:4].to_numpy()
labels = data.iloc[:,4].to_numpy()
le = preprocessing.LabelEncoder()
Y = le.fit_transform(labels)

X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=0.5)

gnb = GaussianNB()
y_pred = gnb.fit(X_train, y_train).predict(X_test)
print((y_test != y_pred).sum())
print(gnb.score(X_test, y_test))

def grafics(clf, title=""):
    test_sizes = np.arange(0.05, 0.95, 0.05)
    wrong_results = []
    accuracies = []

    for test_size in test_sizes:
        X_train, X_test, y_train, y_test = train_test_split(X, Y, test_size=test_size, random_state=830406)
        y_pred = clf.fit(X_train, y_train).predict(X_test)
        wrong_results.append((y_test != y_pred).sum())
        accuracies.append(clf.score(X_test, y_test))


    fig, axs = plt.subplots(1, 2, figsize=(8, 4))
    axs[0].plot(test_sizes, wrong_results)
    axs[1].plot(test_sizes, accuracies)
    axs[0].set_xlabel(title)
    axs[1].set_xlabel(title)
    plt.tight_layout()
    plt.show()
    #max_acc_index = accuracies.index(np.max(accuracies))
    #print(wrong_results[max_acc_index])
    #print(np.max(accuracies))


gnb = GaussianNB()
mnb = MultinomialNB()
cnb = ComplementNB()
bnb = BernoulliNB()
grafics(gnb, 'GaussianNB')
grafics(mnb, 'MultinomialNB')
grafics(cnb, 'ComplementNB')
grafics(bnb, 'BernoulliNB')

clf = tree.DecisionTreeClassifier()
y_pred = clf.fit(X_train, y_train).predict(X_test)
print((y_test != y_pred).sum())
print(clf.score(X_test, y_test))
print(clf.get_n_leaves())
print(clf.get_depth())
plt.subplots(1,1,figsize = (5,5))
tree.plot_tree(clf, filled = True)
plt.show()
grafics(clf)
