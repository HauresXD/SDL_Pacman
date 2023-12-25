# SDL_Pacman

Hra Pacman v jazyku C se SDL2.

### Příkazy:<br>
vytvoření složky build/:
```bash
mkdir build
cd build
```

kompilujte v: build/:
```bash
make
```
rozjeďte v: build/:
```bash
./main
```
---
### Mapa ze souboru:

formát: 

- 12x16
- ohraničení je vždy doplněno samo
- tečky nahraďte sami
  - pokud neurčíte spawn duchů, nebo pacmana vybere se náhodně
- body se doplní automaticky
- speciální body se doplní automaticky a náhodně

<pre>
################
#..............# 
#..............# 
#..............#  
#..............#
#..............#
#..............#
#..............#
#..............#
#..............# 
#..............#
################
</pre>

---
### Možné znaky:
- '#' - zeď
- 'G' - spawn duchů
- 'P' - spawn pacmana