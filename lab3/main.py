import pandas as pd
import numpy as np
from mlxtend.preprocessing import TransactionEncoder
from mlxtend.frequent_patterns import apriori
import matplotlib.pyplot as plt

all_data = pd.read_csv('dataset_group.csv', header=None)
unique_id = list(set(all_data[1]))
print(len(unique_id))
items = list(set(all_data[2]))
print(len(items))
dataset = [[elem for elem in all_data[all_data[1] == id][2] if elem in items] for id in unique_id]


te = TransactionEncoder()
te_ary = te.fit(dataset).transform(dataset)
df = pd.DataFrame(te_ary, columns=te.columns_)
print(df)

results = apriori(df, min_support=0.3, use_colnames=True)
results['length'] = results['itemsets'].apply(lambda x: len(x))
print(results)

results = apriori(df, min_support=0.3, use_colnames=True, max_len=1)
print(results)

results = apriori(df, min_support=0.3, use_colnames=True)
results['length'] = results['itemsets'].apply(lambda x: len(x))
results = results[results['length'] == 2]
print(results)
print('\nCount of result itemstes = ',len(results), '\n')
res = []
for minSup in range(5, 100):
    results = apriori(df, min_support=minSup/100, use_colnames=True)
    res.append(len(results))
plt.plot([i/100 for i in range(5, 100)], res)
results = apriori(df, min_support=0.05, use_colnames=True)
results['length'] = results['itemsets'].apply(lambda x: len(x))
for i in range(1, 5):
    res = results[results['length'] == i]
    print(max(res['support']))
    plt.vlines(max(res['support']), 0, 16000, color='r')
plt.show()

results = apriori(df, min_support=0.38, use_colnames=True, max_len=1)
new_items = [ list(elem)[0] for elem in results['itemsets']]
new_dataset = [[elem for elem in all_data[all_data[1] == id][2] if elem in new_items] for id in unique_id]
te = TransactionEncoder()
te_ary = te.fit(new_dataset).transform(new_dataset)
new_df = pd.DataFrame(te_ary, columns=te.columns_)
print(new_df)

results = apriori(new_df, min_support=0.3, use_colnames=True)
results['length'] = results['itemsets'].apply(lambda x: len(x))
print(results)

results = apriori(new_df, min_support=0.15, use_colnames=True)
results['length'] = results['itemsets'].apply(lambda x: len(x))
results = results[results['length'] > 1]
print(results[results['itemsets'].apply(lambda x: ('yogurt' in x) or ('waffles' in x))])

results = apriori(df, min_support=0.38, use_colnames=True, max_len=1)
new_items_ = [ list(elem)[0] for elem in results['itemsets']]
new_dataset_ = [[elem for elem in all_data[all_data[1] == id][2] if elem not in new_items_] for id in unique_id]
te = TransactionEncoder()
te_ary = te.fit(new_dataset_).transform(new_dataset_)
new_df_ = pd.DataFrame(te_ary, columns=te.columns_)
print(new_df_)


results = apriori(new_df_, min_support=0.08, use_colnames=True)
results['length'] = results['itemsets'].apply(lambda x: len(x))
print(results)

y = results['itemsets'].apply(lambda x: list(x))
for i in y:
    count = 0
    for j in i:
        if j[0] == 's':
            count += 1

    if count > 1:
        print(i)


results = results[results['support'] <= 0.25]
print(results[results['support'] >= 0.1])




