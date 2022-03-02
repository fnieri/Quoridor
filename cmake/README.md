# Les dependences de Quoridor

Le project a plusieurs dependences, lorsqu'une nouvelle librairie externe est utilisé, un cmake utilisant la compilant et l'incluant au projet doit etre écrit dans le dossier CMake (si possible en utilisant CPM) et inclu au CMakeLists.txt dans le root du projet.

## Liste des dependences

* CryptoPP
* Nlohmann/json
* MongoCxx
* BsonCxx
* Catch2
* SockPP
* ( Doxygen )

## Utilisation des dependences

* Cryptopp est utilisée pour l'encryption d'un mot de passe, nous utilisons notamment l'algorithme d'encryption SHA256 (Utilisèe par Francesco)
* Nlohmann/json est utilisée pour la communication client - server - database (Utilisée par Francesco - Boris - Louis)
* MongoCxx et BsonCxx sont utilisées pour la gestion de la base de donnés (Utilisées par Louis)
* Catch2 est utilisée pour les tests unitaires (Utilisée par tous)
* SockPP est utilisée pour la gestion des sockets (Utilisée par Boris)
* (Doxygen est utilisée pour la documentation du projet, il n'est pas nécessaire de le telecharger.)
