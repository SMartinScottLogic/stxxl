FROM alpine:3.5

RUN apk add --no-cache git cmake make gcc g++
RUN git clone http://github.com/stxxl/stxxl.git /tmp/stxxl && \
    mkdir -p /tmp/stxxl/build && \
    cd /tmp/stxxl/build && \
    cmake -DCMAKE_BUILD_TYPE=Release .. && \
    make && \
    local/test1 && \
    make install && \
    cd / && \
    rm -rf /tmp/stxxl

COPY stxxl /root/.stxxl

WORKDIR /usr/local/app
COPY main.cpp /usr/local/app/
RUN g++ -o main main.cpp $( pkg-config stxxl --cflags --libs )
