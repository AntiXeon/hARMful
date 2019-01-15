FROM debian:sid

RUN apt-get --no-install-recommends update \
&& apt-get install -y git build-essential cmake \
freeglut3 freeglut3-dev xorg-dev libglu1-mesa-dev \
libglfw3-dev libglew-dev libassimp-dev libpng-dev

ADD files/libjpeg-turbo-official_2.0.1_amd64.deb /root
RUN apt-get install /root/libjpeg-turbo-official_2.0.1_amd64.deb
