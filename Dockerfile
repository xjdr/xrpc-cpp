## -*- docker-image-name: "xjdr/xrpc-cpp" -*-
FROM xjdr/proxygen-base:latest
MAINTAINER Jeff Rose <jeff.rose12@gmail.com>
LABEL name="xrpc-cpp" \ 
      version="0.1" \
      description="Development and Test environment for xrpc-cpp"
COPY . /xrpc-cpp/

WORKDIR /xrpc-cpp
RUN git clean -dfx
RUN if [ -f CMakeCache.txt ] ; then rm CMakeCache.txt ; fi
RUN cmake . 
RUN make 
run ./example_server
