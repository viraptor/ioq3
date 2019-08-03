FROM ubuntu:bionic-20190612
MAINTAINER megamindbrian@gmail.com

RUN apt-get update && apt-get install -y \
    ioquake3 \
    wget \
    xvfb \
    x11vnc \
    xinit \
    x11-xserver-utils

COPY ./baseq3/* /usr/lib/ioquake3/baseq3/
COPY ./missionpack/* /usr/lib/ioquake3/missionpack/
COPY ./virtual_client.sh /
RUN chmod a+x /virtual_client.sh
