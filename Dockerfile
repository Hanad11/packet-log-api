FROM ubuntu:22.04

WORKDIR /app

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    libboost-system-dev \
    libboost-filesystem-dev \
    libasio-dev \
    git \
    && rm -rf /var/lib/apt/lists/*

COPY . .

RUN mkdir build && cd build && cmake .. && make

EXPOSE 23500

CMD ["./build/packet-log-api"]