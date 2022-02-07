# Quoridor, for real

> J'ai r à dire pour l'instant c juste un test

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
./setup_mongocxx
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






