FROM ubuntu AS base

RUN set -ex;\
    apt-get update

RUN DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC apt-get -y install tzdata
    
RUN OP_DIR=$(pwd);\
    apt-get install -y g++ python3 wget git libmongoc-1.0-0 libbson-1.0 cmake libssl-dev libsasl2-dev zlib1g-dev libcrypto++-dev libcrypto++-doc libcrypto++-utils;\

    wget https://github.com/mongodb/mongo-c-driver/releases/download/1.17.0/mongo-c-driver-1.17.0.tar.gz;\
    tar xzf mongo-c-driver-1.17.0.tar.gz;\
    cd mongo-c-driver-1.17.0;\
    mkdir cmake-build;\
    cd cmake-build;\
    cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF ..;\
    make install;\

  git clone https://github.com/mongodb/mongo-cxx-driver.git \
      --branch releases/stable --depth 1;\
  cd mongo-cxx-driver/build;\

  cmake .. \
      -DCMAKE_BUILD_TYPE=Release \
      -DBSONCXX_POLY_USE_MNMLSTC=1 \
      -DCMAKE_INSTALL_PREFIX=/usr/local;\

  make;\
  make install;\
  cd $TOP_DIR;\
  rm -rf mongo-c-driver-1.17.0*

COPY . /usr/src/quoridor

FROM base AS builder
RUN set -ex;\
    cd /usr/src/quoridor;\
    make setup;\
    make

FROM base AS runtime

COPY --from=builder /usr/src/quoridor/build/_deps/* /usr/local/lib/
COPY --from=builder /usr/src/quoridor/build/bin/server /usr/local/bin

ENTRYPOINT ["server"]
