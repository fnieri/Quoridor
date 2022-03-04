# Quoridor, for real

# Documentation

[View documentation](https://quoridor-doc.herokuapp.com/docs/html/index.html)


# Compilation

Pour compiler, exécutez ces commandes depuis la racine du repo git:

```bash
make setup
make
```

### IMPORTANT! 
Avant d'exécuter le client il est nécessaire de mettre la taille du texte du terminal à 11 ou moins.

# Compilation avec Docker (plus facile)

Installation [Docker](https://docs.docker.com/get-docker/)

Docker permet en gros de compiler et faire tourner le code dans un environment identique sur toutes les machines. 
Le fichier compilé tourne dans un container avec l'argument run. Ce container redirige son port 1234 vers le port 1234.
Si les commandes ne fonctionnent pas, il faut les exécuter avec sudo en prefix.
```bash
docker build -t quoridor .
docker run --name quoridor_server -it -d --rm -p 1234:1234 quoridor
```
Pour voir les logs du container:
```bash
docker logs quoridor_server
```
Pour s'accrocher au container:
```bash
docker attach quoridor_server
```
Pour voir les containers en cours:
```bash
docker ps
```
Pour voir les images (ce que ```docker build``` crée):
```bash
docker images
```
Pour supprimer une image:
```bash
docker rmi image_name
```
Pour arrêter le container:
```bash
docker stop quoridor_server
```

# Contributions

## Formatage

Le formatage est géré par `clang-format`, assurez-vous de
l'avoir installé sur votre machine.

Pour être sûr de jamais l'oublier, exécutez ces commandes
depuis la racine du repo :

```bash
chmod +x hooks/pre-commit
ln hooks/pre-commit .git/hooks
```

## Workflow

Lorsque vous finissez de travailler sur la fonctionnalité de votre branche, ouvrez **toujours** un PR. Ça va nous éviter d'avoir trop de branches qui partent dans tous les sens et de devoir tout merge d'un coup.

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
