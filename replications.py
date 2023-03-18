import os

p1 = "p1.txt"
p2 = "p2.txt"

# Clear les fichiers
open("resultat.txt", "w").close()
open("output.txt", "w").close()


# 100 réplications
for i in range(1, 101):
    os.system(f"./build/TP5 {i} ./data/{p1} ./data/{p2} >> resultat.txt")

# On génére la solution combinée
os.system(f"./build/TP5 -1 resultat.txt >> output.txt")