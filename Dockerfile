FROM ubuntu:20.04


COPY cpp /usr/src/cpp
WORKDIR /usr/src/

ENV TZ=Europe/Warsaw
ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update -y
RUN apt-get upgrade -y

RUN apt-get -y install build-essential

RUN apt-get -y install cmake

RUN apt-get -y install libcpprest-dev

EXPOSE 9000

CMD cd cpp && mkdir build && cd build && cmake ../ && make && ./metric