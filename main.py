import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn import preprocessing


df = pd.read_csv('heart_failure_clinical_records_dataset.csv')
df = df.drop(columns=['anaemia', 'diabetes', 'high_blood_pressure', 'sex', 'smoking', 'time', 'DEATH_EVENT'])
print(df)

n_bins = 20
fig, axs = plt.subplots(2, 3)
axs[0, 0].hist(df['age'].values, bins=n_bins)
axs[0, 0].set_title('age')
axs[0, 1].hist(df['creatinine_phosphokinase'].values, bins=n_bins)
axs[0, 1].set_title('creatinine_phosphokinase')
axs[0, 2].hist(df['ejection_fraction'].values, bins=n_bins)
axs[0, 2].set_title('ejection_fraction')
axs[1, 0].hist(df['platelets'].values, bins=n_bins)
axs[1, 0].set_title('platelets')
axs[1, 1].hist(df['serum_creatinine'].values, bins=n_bins)
axs[1, 1].set_title('serum_creatinine')
axs[1, 2].hist(df['serum_sodium'].values, bins=n_bins)
axs[1, 2].set_title('serum_sodium')
plt.show()


def draw(data_scaled):
    fig, axs = plt.subplots(2, 3)
    axs[0, 0].hist(data_scaled[:, 0], bins=n_bins)
    axs[0, 0].set_title('age')
    axs[0, 1].hist(data_scaled[:, 1], bins=n_bins)
    axs[0, 1].set_title('creatinine_phosphokinase')
    axs[0, 2].hist(data_scaled[:, 2], bins=n_bins)
    axs[0, 2].set_title('ejection_fraction')
    axs[1, 0].hist(data_scaled[:, 3], bins=n_bins)
    axs[1, 0].set_title('platelets')
    axs[1, 1].hist(data_scaled[:, 4], bins=n_bins)
    axs[1, 1].set_title('serum_creatinine')
    axs[1, 2].hist(data_scaled[:, 5], bins=n_bins)
    axs[1, 2].set_title('serum_sodium')
    plt.show()


data = df.to_numpy(dtype='float')

print("Мат. ожидание до стандартизации:", [np.mean(i) for i in data.T])
print("СКО до стандартизации:", [np.std(i) for i in data.T], "\n")

scaler = preprocessing.StandardScaler().fit(data[:, :])

print("Мат. ожидание поля mean_:", scaler.mean_)
print("СКО поля var_:", scaler.var_, "\n")

data_scaled = scaler.transform(data)

print("Мат. ожидание после стандартизации:", [np.mean(i) for i in data_scaled.T])
print("СКО после стандартизации:", [np.std(i) for i in data_scaled.T], "\n")

draw(data_scaled)


min_max_scaler = preprocessing.MinMaxScaler().fit(data)
data_min_max_scaled = min_max_scaler.transform(data)

draw(data_min_max_scaled)


attributes = ['age', 'creatinine_phosphokinase', 'ejection_fraction', 'platelets', 'serum_creatinine', 'serum_sodium']
for i in range(6):
    print(attributes[i], "min:", min_max_scaler.data_min_[i], "max:", min_max_scaler.data_max_[i])

max_abs_scaler = preprocessing.MaxAbsScaler().fit(data)
max_abs_scaled = max_abs_scaler.transform(data)

draw(max_abs_scaled)

robust_scaler = preprocessing.RobustScaler().fit(data)
robust_scaled = robust_scaler.transform(data)

draw(robust_scaled)

range_scaler = preprocessing.MinMaxScaler(feature_range=(-5, 10)).fit(data)
range_scaled = range_scaler.transform(data)

draw(range_scaled)

quantile_transformer = preprocessing.QuantileTransformer(n_quantiles=100, random_state=0).fit(data)
data_quantile_scaled = quantile_transformer.transform(data)

draw(data_quantile_scaled)

quantile_transformer = preprocessing.QuantileTransformer(n_quantiles=100, random_state=0, output_distribution='normal').fit(data)
data_quantile_scaled = quantile_transformer.transform(data)

draw(data_quantile_scaled)

power_transformer = preprocessing.PowerTransformer().fit(data)
power_scaled = power_transformer.transform(data)

draw(power_scaled)

disc_transformer = preprocessing.KBinsDiscretizer(n_bins=[3, 4, 3, 10, 2, 4], encode='ordinal').fit(data)
disc_scaled = disc_transformer.transform(data)

draw(disc_scaled)
print("\n", disc_transformer.bin_edges_)
