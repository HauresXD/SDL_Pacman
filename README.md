# SDL_Pacman

Hra Pacman v jazyku C se SDL2.

### Příkazy:<br>
vytvoření složky build/:
```bash
mkdir build
cd build
```

cmake v: build/:
```bash
cmake ..
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
- v souboru [map](map.txt)
- 12x16
- tečky nahraďte sami (nebo nenahrazujte)
  - pokud neurčíte spawn duchů, nebo pacmana vybere se automaticky (viz [Možné znaky](#možné-znaky))
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
  - Default pozice - 1x1
- 'P' - spawn pacmana
  - Default pozice - 10x10

---
### Důležité poznámky:
- Doporučuji manuelně vyplnit 'G' i 'P' jinak může dojít k chybě
- Pokud bude více 'P' nebo 'G' v gracím poly bude se brát znak nejvíce dole v pravo