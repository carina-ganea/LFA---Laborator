chart = {}
f = open("test.in")
m = int(f.readline())

start = -1

for i in range(m):
    p = f.readline().split()
    if i == 0:
        start = p[0]

    if chart.get(p[0]):
        chart[p[0]].append((p[1], p[2]))
    else:
        chart.update([(p[0], [(p[1], p[2])])])

stop = f.readline().split()

p = f.readline()
curent = start

j = 0
while j < len(p):
    for x in chart[curent]:
        if x[1] == p[j]:
            j += 1
            curent = x[0]
            break
    else:
        break
if j == len(p) and curent in stop:
    print('Mesaj acceptat')
else:
    print('Mesaj eronat')

f.close()