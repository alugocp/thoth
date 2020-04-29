
groups=[
    (2,["i","e"]),
    (2,["o","u"]),
    (3,["a","e","i","o","u"]),
    (1,["g","q","j","z","{","}","v","f","x"]),
    (2,["n","m"]),
    (2,["b","d"]),
    (1,["q","k"]),
    (2,["c","k"]),
    (1,["b","p"]),
    (1,["j","y","q"]),
    (1,["w","x","q"]),
    (1,["h"]),
]

# Group processing
def recurse(words,set,n):
    if n:
        next=[]
        for w in words:
            for s in set:
                next.append("%s%s"%(w,s))
        return recurse(next,set,n-1)
    return words

model={}
for l in groups:
    possible=recurse(l[1],l[1],l[0]-1)
    for s in l[1]:
        if not s in model: model[s]=[]
        model[s].extend(possible)

# C code generation
print("unordered_map<char,vector<string>> banned;")
print("void populate_banned(){")
for m in model:
    print("\tbanned['%s']={\"%s\"};"%(m,"\",\"".join(model[m])))
print("}")
