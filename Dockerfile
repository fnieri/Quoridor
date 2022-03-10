FROM ubuntu AS base

RUN apt-get update

RUN DEBIAN_FRONTEND=noninteractive TZ=Etc/UTC apt-get -y install tzdata
    
RUN apt-get install -y g++ python3 wget git libmongoc-1.0-0 libbson-1.0 cmake libssl-dev libsasl2-dev zlib1g-dev libcrypto++-dev libcrypto++-doc libcrypto++-utils

COPY . /usr/src/quoridor

FROM base AS builder
RUN cd /usr/src/quoridor;\
    make setup;\
    make

FROM base AS runtime

COPY --from=builder /usr/src/quoridor/build/_deps/* /usr/local/lib/
COPY --from=builder /usr/src/quoridor/build/bin/server /usr/local/bin

ENTRYPOINT ["server"]
