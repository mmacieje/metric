FROM ubuntu:20.04


COPY cpp /usr/src/cpp
COPY nodejs /usr/src/nodejs
WORKDIR /usr/src/

ENV TZ=Europe/Warsaw
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get -y install build-essential

RUN apt-get -y install cmake

RUN apt-get -y install libcpprest-dev

RUN apt-get -y install curl
RUN curl -sL https://deb.nodesource.com/setup_12.x | bash -
RUN apt-get install -y nodejs

EXPOSE 9000

CMD cd nodejs && npm install && node index.js & cd cpp && mkdir build && cd build && cmake ../ && make && ./metric