ARG base_image=ubuntu:20.04
FROM ${base_image}

ARG user=owner
ARG ssh_dir

ARG git_user
ARG git_pwd

RUN apt-get update
RUN apt-get install -y sudo git vim

# add sudo user
RUN groupadd -g 1000 developer && \
    useradd  -g      developer -G sudo -m -s /bin/bash ${user} && \
        echo "${user}:${user}" | chpasswd

	RUN echo "Defaults visiblepw"             >> /etc/sudoers
	RUN echo "${user} ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers

USER ${user}
WORKDIR /home/${user}
# RUN git clone https://${git_user}:${git_pwd}@github.com/TaishiUeda/JackOfAllTrades.git && \
#     cd JackOfAllTrades/DevEnv && \
#     ./install.sh
RUN git clone https://${git_user}:${git_pwd}@github.com/TaishiUeda/JackOfAllTrades.git

ENV TERM=xterm-256color 
ENV DISPLAY host.docker.internal:0.0

ENTRYPOINT ["/bin/bash"]



