import xml.etree.ElementTree as ET

p = int(input())
n = int(input())
r, c = map(int, list(input().split(',')))
o = input()
words = []
for i in range(p):
    words.append(input())

text = ""
for i in range(n):
    text += input()

tree = ET.fromstring(text)
notags = ET.tostring(tree, encoding='utf8', method='text')

mat = []
for i in range(r):
    row = []
    flag = True
    for j in range(c):
        pos = i * c + j
        if pos == len(notags):
            flag = False
            break
        row.append(chr(notags[i * c + j]))
    mat.append(row)
    if not flag:
        break

d = dict()
if(o == "S"):
    for i in range(len(mat)):
        for j in range(len(mat[i])):
            if mat[i][j] not in d:
                d[mat[i][j]] = (i, j)
if(o == "L"):
    for i in range(len(mat) - 1, -1, -1):
        for j in range(len(mat[i]) - 1, -1, -1):
            if mat[i][j] not in d:
                d[mat[i][j]] = (i, j)

possible = []
answer = []

for word in words:
    curr = []
    flag = True
    for i in range(len(word)):
        if(word[i] in d):
            curr.append(str(d[word[i]][0] + 1))
            curr.append(str(d[word[i]][1] + 1))
        else:
            flag = False
            break
    possible.append(flag)
    answer.append(curr)
    
for i in range(len(answer)):
    if(possible[i]):
        print(",".join(answer[i]))
    else:
        print(0)