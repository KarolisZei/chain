# Chain
Darbo tikslas buvo parašyti paprasta blokų grandinę.

## Naudojimas

Programą reikia sukompiliuoti ir ją paleidus bus automatiškai sukurti vartotojai, transakcijos, pirmas blokas su viena transakcija ir 10 blokų ilgio blokų grandinė, kurioje yra po 100 transakcijų. Genesis bloko informacija bus išspausdinta į terminalą, kartu su transakcija.

Toliau programa kuria naujus blokus ir iš karto bando surasti naują bloką, suradus bloką priskiria jam transakcijas ir išspausdina jo informaciją. Toliau paklausia vartotojo ar jis nori pamatyti visas blokui priklausančias transakcijas.

## libbitcoin merkle tree implementacija

Libbitcoin suinstaliuoti nebuvo sunku. Implementacija pasidarė labai paprasta kai paskaičiau [dokumentaciją](https://libbitcoin.dyne.org/doc/overview.html?highlight=hash_digest#hash_digest) ir kai žinojau, kokius  tipus gauti merkelkintamųjų hash kiekvienam blokui nebuvo problemų.
Pirma problema buvo tai, kad "bitcoin/blockchain.hpp" buvo pakeistas į "bitcoin/system.hpp" ir toliau reikėjo, kad kompiliatorius matytų man naujai reikiamą "bitcoin/system.hpp". Po pakankamai daug ieškojimo suradau, kaip pasikeisti pkg-config kelią į direktoriją, kurios reikėjo. Tačiau sunkiausia buvo išsiaiškinti, kaip viską sukompiliuoti. Iš pradžių viską bandžiau sukompiliuoti naudojant clang, kaip buvo pateikta pavyzdyje.
```rb
clang++ -g -std=c++11 -o BlockChain BlockChain.cpp genBlock.cpp hashFunc.cpp merkle.cpp mine.cpp $(pkg-config --cflags --libs libbitcoin-system)

```
Tačiau nors ir gavau rezultatą jis man duodavo "segmentation fault". Po kelių bandymo pabandžiau sukompiliuoti naudojant g++ kompiliatorių, nes jį naudojau pradinei blockchain versijai ir viskas suveikė.
