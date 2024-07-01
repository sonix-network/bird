FROM docker.io/library/rockylinux:9

ARG BIRD_VERSION

RUN dnf -y update && \
    dnf -y upgrade && \
    dnf -y install epel-release && \
    dnf -y install bird-${BIRD_VERSION}.* && \
    dnf clean all

ENTRYPOINT ["/usr/sbin/bird"]
