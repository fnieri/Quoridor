# Includes et headers

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
le fichier cpp. Cela peut grandement améliorer les temps de compilation.

Et bien évidemment, aucune implémentation dans les headers. À la limite les getters et les setters.

# Initialisation

Préférez, si possible, l'initialisation uniforme. Sa syntaxe est la suivante :

```cpp
int var{ 9 };
```

Elle est meilleure car peut être utilisée partout et prévient contre la perte de données.
Et surtout, c'est la méthode recommandée pour le c++ moderne.
