import pandas as pd
import numpy as np
from sklearn import preprocessing
import matplotlib.pyplot as plt
from sklearn.decomposition import PCA, KernelPCA, SparsePCA, FactorAnalysis

df = pd.read_csv('glass.csv')
var_names = list(df.columns) #получение имен признаков
labels = df.to_numpy('int')[:, -1] #метки классов
data = df.to_numpy('float')[:, :-1] #описательные признаки

data = preprocessing.minmax_scale(data)

fig, axs = plt.subplots(2, 4)
for i in range(data.shape[1]-1):
    axs[i // 4, i % 4].scatter(data[:, i], data[:, (i+1)], c=labels, cmap='hsv')
    axs[i // 4, i % 4].set_xlabel(var_names[i])
    axs[i // 4, i % 4].set_ylabel(var_names[i+1])

plt.show()

svd_solver = ["auto", "full", "arpack", "randomized"]
fig, axs = plt.subplots(1, 4)
for i in range(len(svd_solver)):
    pca = PCA(n_components=4, svd_solver=svd_solver[i])
    pca_data = pca.fit(data).transform(data)
    axs[i].scatter(pca_data[:, 0], pca_data[:, 1], c=labels, cmap='hsv')
    axs[i].set_title(svd_solver[i])


print(pca.explained_variance_ratio_)
print(pca.singular_values_)
print(sum(pca.explained_variance_ratio_))
plt.show()

inv_data = pca.inverse_transform(pca_data)

fig, axs = plt.subplots(2, 4)
for i in range(inv_data.shape[1]-1):
    axs[i // 4, i % 4].scatter(inv_data[:, i], inv_data[:, (i+1)], c=labels, cmap='hsv')
    axs[i // 4, i % 4].set_xlabel(var_names[i])
    axs[i // 4, i % 4].set_ylabel(var_names[i+1])

plt.show()

pars = ["linear", "poly", "rbf", "sigmoid", "cosine"]
fig, axs = plt.subplots(1, 5)
for i in range(len(pars)):
    data_kernel = KernelPCA(n_components=4, kernel=pars[i]).fit_transform(data)
    axs[i].scatter(data_kernel[:, 0], data_kernel[:, 1], c=labels, cmap='hsv')
    axs[i].set_title(pars[i])

plt.show()

fig, axs = plt.subplots(2, 3)
for i in range(0, 11, 2):
    data_sparse = SparsePCA(n_components=4, alpha=i/10).fit_transform(data)
    axs[i // 6, (i % 6)//2].scatter(data_sparse[:, 0], data_sparse[:, 1], c=labels, cmap='hsv')
    axs[i // 6, (i % 6)//2].set_title(f"alpha = {i/10}")

plt.show()

pca = FactorAnalysis(n_components=4)
data_factor = pca.fit_transform(data)

plt.scatter(data_factor[:, 0], data_factor[:, 1], c=labels, cmap='hsv')
plt.show()
