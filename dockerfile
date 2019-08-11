FROM ubuntu:18.04

MAINTAINER Kyle Davison <kdavison at gmail.com>

RUN apt-get update \
  && apt-get dist-upgrade -y \
  && apt-get install -y \
## libs
      mesa-common-dev \
      libpthread-stubs0-dev \
      libx11-dev \
      freeglut3-dev \
      libxcb-image0-dev \
      libudev-dev \
      libjpeg8-dev \
      libopenal-dev \
      libsndfile1-dev \
      libfreetype6-dev \
      libxrandr-dev \
      libglu1-mesa-dev \
      libgl1-mesa-dev \
      libgl-dev \
      libfontconfig-dev \
      libxinerama-dev \
      libxcursor-dev \
      libxi-dev \
## tools
      wget \
      mercurial \
      git \
      unzip \
      python3 \
      python3-pip \
      python3-setuptools

## CMAKE
RUN cd /tmp \
  && wget https://cmake.org/files/v3.10/cmake-3.10.0.tar.gz \
  && tar -xzvf cmake-3.10.0.tar.gz \
  && cd cmake-3.10.0 \
  && ./bootstrap \
  && make -j10 install \
  && rm -r /tmp/cmake-*

## GYP
RUN cd /tmp \
  && git clone https://chromium.googlesource.com/external/gyp \
  && cd gyp \
  && python3 setup.py install \
  && rm -r /tmp/gyp

## NINJA
RUN cd /tmp \
  && wget https://github.com/ninja-build/ninja/releases/download/v1.8.2/ninja-linux.zip \
  && unzip ninja-linux.zip -d . \
  && mv ninja /usr/local/bin \
  && rm -r /tmp/ninja-linux*

## COMPILERS
RUN \
  echo 'deb http://apt.llvm.org/xenial/ llvm-toolchain-xenial-5.0 main' >> /etc/apt/sources.list.d/llvm.list \
  && wget -O - http://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - \
  && apt-get update \
  && apt-get install -y \
      clang-5.0 \
      lldb-5.0 \
      lld-5.0 \
      libc++-dev \
  && cd /usr/local/bin \
  && ln -s /usr/bin/clang-5.0 clang \
  && ln -s /usr/bin/clang++-5.0 clang++ \
  && ln -s /usr/bin/clang-cpp-5.0 clang-cpp \
  && cd -

## clean out the apt-get files
RUN apt-get -y clean

RUN useradd -ms /bin/bash developer
USER developer
WORKDIR /home/developer
RUN mkdir -p /home/developer/workspace
