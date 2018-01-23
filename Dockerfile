## -*- docker-image-name: "xjdr/xrpc-cpp" -*-
FROM xjdr/proxygen-base:latest
MAINTAINER Jeff Rose <jeff.rose12@gmail.com>
LABEL name="xrpc-cpp" \ 
      version="0.1" \
      description="Development and Test environment for xrpc-cpp"

WORKDIR /cmake
RUN git clone https://gitlab.kitware.com/cmake/cmake
RUN ls -al
WORKDIR /cmake/cmake
RUN ls -al
RUN ./bootstrap && \
  make && \
  make install

RUN cmake --version

COPY . /xrpc-cpp/

WORKDIR /xrpc-cpp
RUN git clean -dfx
RUN cmake .
RUN make 
RUN ./example_server
