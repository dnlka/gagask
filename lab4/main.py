import pandas as pd
from mlxtend.preprocessing import TransactionEncoder
from mlxtend.frequent_patterns import fpgrowth, fpmax, association_rules
import matplotlib.pyplot as plt
import numpy as np
import networkx as nx

all_data = pd.read_csv('groceries - groceries.csv')
print(all_data) #Видно, что датафрейм содержит NaN значения

np_data = all_data.to_numpy()
np_data = [[elem for elem in row[1:] if isinstance(elem,str)] for row in np_data]

unique_items = set()
for row in np_data:
    for elem in row:
        unique_items.add(elem)

print(unique_items)
print(len(unique_items))

te = TransactionEncoder()
te_ary = te.fit(np_data).transform(np_data)
data = pd.DataFrame(te_ary, columns=te.columns_)
print(data)

result = fpgrowth(data, min_support=0.03, use_colnames = True)
print(result)
result['length'] = result['itemsets'].apply(lambda x: len(x))
result_1 = result[result['length'] == 1]
print("len 1 min:", min(result_1['support']))
print("len 1 max:", max(result_1['support']))
result_2 = result[result['length'] == 2]
print("len 2 min:", min(result_2['support']))
print("len 2 max:", max(result_2['support']))

result = fpmax(data, min_support=0.03, use_colnames=True)
print(result)
result['length'] = result['itemsets'].apply(lambda x: len(x))
result_1 = result[result['length'] == 1]
print("len 1 min:", min(result_1['support']))
print("len 1 max:", max(result_1['support']))
result_2 = result[result['length'] == 2]
print("len 2 min:", min(result_2['support']))
print("len 2 max:", max(result_2['support']))

count_of_items = data.sum()
count_of_items.nlargest(10).plot.bar()
plt.tight_layout()
plt.show()

items = ['whole milk', 'yogurt', 'soda', 'tropical fruit', 'shopping bags', 'sausage',
         'whipped/sour cream', 'rolls/buns', 'other vegetables', 'root vegetables',
         'pork', 'bottled water', 'pastry', 'citrus fruit', 'canned beer', 'bottled beer']
np_data = all_data.to_numpy()
np_data = [[elem for elem in row[1:] if isinstance(elem,str) and elem in items] for row in np_data]
te = TransactionEncoder()
te_ary = te.fit(np_data).transform(np_data)
data_ = pd.DataFrame(te_ary, columns=te.columns_)
print(data_)
result = fpgrowth(data_, min_support=0.03, use_colnames = True)
print(result)
result['length'] = result['itemsets'].apply(lambda x: len(x))
result_1 = result[result['length'] == 1]
print("len 1 min:", min(result_1['support']))
print("len 1 max:", max(result_1['support']))
result_2 = result[result['length'] == 2]
print("len 2 min:", min(result_2['support']))
print("len 2 max:", max(result_2['support']))

result = fpmax(data_, min_support=0.03, use_colnames=True)
print(result)
result['length'] = result['itemsets'].apply(lambda x: len(x))
result_1 = result[result['length'] == 1]
print("len 1 min:", min(result_1['support']))
print("len 1 max:", max(result_1['support']))
result_2 = result[result['length'] == 2]
print("len 2 min:", min(result_2['support']))
print("len 2 max:", max(result_2['support']))

colors = ['r', 'g', 'b', 'black', 'orange']
for i in range(1, 6):
    arr = []
    for minSup in np.linspace(0.005, 1.0, 50):
        results = fpgrowth(data, min_support=minSup, use_colnames=True, max_len=i)
        results['length'] = results['itemsets'].apply(lambda x: len(x))
        results = results[results['length'] == i]
        arr.append(len(results))
    plt.plot(np.linspace(0.005, 1, 50), arr, colors[i - 1])
plt.show()

np_data = all_data.to_numpy()
np_data = [[elem for elem in row[1:] if isinstance(elem,str) and elem in items] for row in np_data]
np_data = [row for row in np_data if len(row) > 1]
te = TransactionEncoder()
te_ary = te.fit(np_data).transform(np_data)
data = pd.DataFrame(te_ary, columns=te.columns_)
result = fpgrowth(data, min_support=0.05, use_colnames = True)
print(result)
rules = association_rules(result, min_threshold = 0.3)
print(rules)
metrics = ["support", "confidence", "lift", "leverage", "conviction"]
for i in metrics:
    print(i)
    rules = association_rules(result, min_threshold=0.01, metric=i)
    print("Mean:", rules[i].mean())
    print("Median:", rules[i].median())
    print("Std:", rules[i].std())
rules = association_rules(result, min_threshold = 0.4, metric='confidence')
G = nx.DiGraph()

for index, row in rules.iterrows():
    l = list(row['antecedents'])[0]
    r = list(row['consequents'])[0]
    w = row['support'] * 25
    label = round(row['confidence'], 4)
    G.add_edge(l, r, label=label, weight=w)
pos = nx.spring_layout(G)
plt.figure()
nx.draw_networkx(G, pos, with_labels=True)
nx.draw_networkx_edges(G, pos, width=list([G[n1][n2]['weight'] for n1, n2 in G.edges]))
nx.draw_networkx_edge_labels(G, pos,edge_labels=dict([((n1, n2), f'{G[n1][n2]["label"]}') for n1, n2 in G.edges]), font_color='black')
plt.show()
