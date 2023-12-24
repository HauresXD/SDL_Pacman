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

!!! Soubor musí být typu .txt !!!

formát: 12x16

<pre>
[   
    [. . . . . . . . . . . . . . . .],
    [-||-], 
    [-||-], 
    [-||-],  
    [-||-],
    [-||-],
    [-||-],
    [-||-],
    [-||-],
    [-||-], 
    [-||-],
    [-||-],
]
</pre>

---
### Možné znaky:
- '#' - zeď
- 'G' - spawn duchů
- 'P' - spawn pacmana