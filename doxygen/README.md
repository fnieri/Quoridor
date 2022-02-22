# Documenter Quoridor

Wow nous avons une documentation très jolie uWu.

# Preface

La documentation de ce projet s'effectue avec doxygen, qui utilise
les commentaires mis dans les headers, les commentaires doivent etre claires et en anglais.
La compilation de la documentation s'effectuera lors de la remise ou avant une reunion. Seulement une personne compilera la documentation et mettra à jour les fichiers dans la branch main.

## Setup

Si vous voulez compiler Doxygen dans une distro Linux, vous devez telecharger Doxygen sur votre machine.
Le telechargement change de gestionnaire de package en gestionnaire.
```bash
# Avec apt
$ sudo apt-get install doxygen
# Avec pacman
% pacman -S doxygen
```

## Compilation

Un fichier bash executable *main.sh* est fourni, ce fichier permet de compiler le fichier Doxyfile et ouvrir dans **Firefox** le fichier index.html.

```bash
chmod +x main.sh # Seulement la première fois
./main.sh
```

## Comment écrire les commentaires dans les headers  

Voici un site qui nous peut aider à suivre un style de documentation clair, concis et cohérent, il contient aussi des tips & tricks pour la documentation des headers avec des mots-clés utilisées par Doxygen

https://developer.lsst.io/cpp/api-docs.html

## A quoi ressemble un header

Les crochets indiquent quelque chose de facultatif

```cpp
AHeader.h

/**
* @file AHeader.h
* @brief This is a test header
* @author Francesco Nieri, [other authors]
* @date 21/02/2022
* [@details Here i detail the implementation, boring :P]
*/

#pragma once 

#include <whatnot>

class MyHeader 
{
    public:

        /**
        * @brief a Test method
        * [@param aTestParameter If parameter, specify what is is/should be]
        * [@warning Note an eventual warning]
        * [@note Author's note]
        * [@throw If the method throws an error]
        * [@tparam If the parameter is templated]
        * [@return If non-void, specify return type + what it is]
        */
        void myHeaderMethod(testP aTestParameter);
}
```

## Remerciements
Thank you for coming to my Ted Talk🄯.
