# Quoridor, for real

> J'ai r à dire pour l'instant c juste un test

# Compilation

Pour compiler, exécutez ces commandes depuis la racine du repo git:

```bash
make setup
make
```

# Exécution

Les fichiers compilés se trouvent dans le folder ```build/bin```


```bash
# client
./build/bin/client
```


# Contributions

## Formatage

Le formatage est géré par `clang-format`, assurez-vous de l'avoir installé sur votre machine.

Pour être sûr de jamais l'oublier, exécutez ces commandes depuis la racine du repo :

```bash
chmod +x hooks/pre-commit
ln hooks/pre-commit .git/hooks
```

## Workflow

Lorsque vous finissez de travailler sur la fonctionnalité de votre branche, ouvrez **toujours** un PR. Ça va nous éviter
d'avoir trop de branches qui partent dans tous les sens et de devoir tout merge d'un coup.

## Database

Mongocxx is used to interact with mongoDB database. To use it you must install it. To do so, you will need to run this
script:

```bash
chmod +x setup_mongocxx
sudo ./setup_mongocxx
```

Now wait a bit. Go make yourself some coffee or something.

Run test db:
Right now we need to do this and idk if we can ask cmake to do it for us. Btw this doesn't work with fish.

```bash
export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH

g++ DbTest.cpp -o ok  -Iinclude -Ilib \
                      -I/usr/local/include/mongocxx/v_noabi \
                      -I/usr/local/include/bsoncxx/v_noabi \
                      -lmongocxx -lbsoncxx
```

At the moment the MongoDB server is NOT running locally. Rather, it is running on cloud.mongodb.com. It's a free service
so don't abuse it (don't run DbTest.cpp 700 times).

### Todo

- [ ] Include mongocxx in cmake
- [ ] Create Database Object
- [ ] Add env file (used for easily switching variables such as database ip)


## Includes et headers

En règle générale, nous pouvons répartir les includes en 4 groupes de différentes priorités.
Chaque groupe doit être séparé des autres par un retour à la ligne. Du plus prioritaire au
moins, nous avons :

1. header d'un fichier cpp;
2. headers locaux au projet;
3. headers d'une (ou plusieurs) librairie(s) extre(s);
4. headers de la librairie standard.

En suivant cet ordre, nous pouvons nous assurer d'une zone d'includes organisée et facilement
navigable.

```cpp
#include "header.h"

#include "board.h"
#include "players.h"

#include <cryptopp>

#include <string>
#include <vector>
```

Veillez aussi à ne mettre aucun `using namespace ...` dans les headers, seulement dans les cpp.

Veillez à ne mettre que les includes absolument nécessaires dans les headers. Si
une simple déclaration suffit, préférez cela et déplacez l'include en question dans
le fichier cpp. Cela peut grandement améliorer les temps de compilation en plus de réduire les
dépendances entre fichiers (moins de couplage!).

Par exemple :
```cpp
// w.h
class Widget {
    ...
};

//a.h
class Widget; // au lieu de #include "w.h"
auto f(Widget &) -> void;

//a.cpp
#include "w.h"
...

//b.h
#include "a.h" // w.h n'est pas copié ici
...

// Si w.h change, seul a.cpp va être recompilé et non tous les fichiers qui incluent a.h.

```

Et bien évidemment, aucune implémentation dans les headers. À la limite les getters et les setters.

## Initialisation

Préférez, si possible, l'initialisation uniforme. Sa syntaxe est la suivante :

```cpp
int var{ 9 };
```

Elle est meilleure car peut être utilisée partout et prévient contre la perte de données.
Et surtout, c'est la méthode recommandée pour le c++ moderne.
