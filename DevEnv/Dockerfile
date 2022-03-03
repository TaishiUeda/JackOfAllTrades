ARG BASE_IMG=ubuntu:20.04
FROM ${BASE_IMG}

ARG USER=owner
ARG ssh_dir

USER root
RUN apt-get update
RUN apt-get install -y sudo git vim openssh-client

USER ${USER}
WORKDIR /home/${USER}
RUN git clone https://github.com/TaishiUeda/JackOfAllTrades.git && \
    cd JackOfAllTrades/DevEnv && \
    ./install.sh

ENV TERM=xterm-256color 

ENTRYPOINT ["/bin/bash"]



