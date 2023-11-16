FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    gcc \
    g++ \
    cmake \
    python3 \
    python3-pip \
    git

RUN pip3 install conan==1.60.0

WORKDIR /workspace
