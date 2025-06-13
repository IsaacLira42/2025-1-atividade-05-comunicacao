FROM fedora:latest

RUN dnf -y update && \
    dnf -y install \
    gcc \
    findutils \
    fish \
    glibc-devel \
    make \
    util-linux \
    htop \
    ncurses \
    && dnf clean all && \
    rm -rf /var/cache/dnf

RUN mkdir -p /app
WORKDIR /app

CMD ["fish"]
