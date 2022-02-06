# Quoridor, for real

>J'ai r à dire pour l'instant c juste un test

# Compilation

Pour compiler, exécutez ces commandes depuis la racine du repo git:

```bash
mkdir build
cd build
cmake ../src
cmake --build .
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
