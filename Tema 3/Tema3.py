st = ['Z0']
graf = {}

f = open("tema3.in")

n = int(f.readline())
initial = f.readline().strip()
for i in range(n):
    text = f.readline().split('/')
    text[0] = text[0].split(', ')
    text[0][2] = text[0][2].strip()
    text[1] = text[1].split(',')
    for i in range(2):
        text[1][i] = text[1][i].strip()
    t1 = text[0][0] + ' ' + text[0][1] + ' ' + text[0][2]
    t2 = text[1][0] + ' ' + text[1][1]
    graf.update([(t1, t2)])

# print(graf)
finale = f.readline().strip()
finale = finale.split(' ,')
cuv = f.readline().strip()
stare = initial

while st:
    p = st.pop(-1)
    while p == '~':
        p = st.pop(-1)
    if cuv == '' or graf.get(stare + ' ~ ' + p):
        l = '~'
    else:
        l = cuv[0]
        cuv = cuv[1:]
    if graf.get(stare + ' ' + l + ' ' + p):
        t = graf[(stare + ' ' + l + ' ' + p)]
        t = t.split()
        stare = t[0]
        t = t[1:]
        while t:
            st.append(t.pop(-1))
    else:
        break

if (stare in finale) and (cuv == '' and st == []):
    print(True)
else:
    print(False)
