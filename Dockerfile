# GCC support can be specified at major, minor, or micro version
# (e.g. 8, 8.2 or 8.2.0).
# See https://hub.docker.com/r/library/gcc/ for all supported GCC
# tags from Docker Hub.
# See https://docs.docker.com/samples/library/gcc/ for more on how to use this image
FROM gcc:latest

# These commands copy your files into the specified directory in the image
# and set that as the working location

RUN apt-get -y update && apt-get install -y git
RUN git clone https://github.com/google/benchmark.git
RUN git clone https://github.com/google/googletest.git benchmark/googletest
WORKDIR /benchmark
RUN apt-get -y update && apt-get install -y cmake sudo
RUN cmake -E make_directory "build"
WORKDIR /benchmark/build
RUN cmake -DBENCHMARK_DOWNLOAD_DEPENDENCIES=ON -DCMAKE_BUILD_TYPE=Release ../ 
WORKDIR /benchmark
RUN cmake --build "build" --config Release
RUN sudo cmake --build "build" --config Release --target install
WORKDIR  /

COPY . /usr/src/myapp
WORKDIR /usr/src/myapp


RUN apt-get update && \
      apt-get -y install sudo
RUN sudo apt-get install -y cmake libcpprest-dev libjsoncpp-dev



RUN git clone https://github.com/open-source-parsers/jsoncpp 
RUN cd jsoncpp && mkdir -p build/debug && cd build/debug && cmake -DCMAKE_BUILD_TYPE=debug -DBUILD_STATIC_LIBS=ON -DBUILD_SHARED_LIBS=OFF -DARCHIVE_INSTALL_DIR=. -G "Unix Makefiles" ../.. && make -j32 && sudo make install
RUN cd jsoncpp && python3 amalgamate.py && cp -r -p ./dist/* ../src/
# This command compiles your app using GCC, adjust for your source code
RUN rm -r jsoncpp

RUN mkdir build && cd build && mkdir release && cd release && cmake -DCMAKE_BUILD_TYPE=Release ../.. \
&& cmake --build .
#Enter Container with: docker run --rm -it  cpp:latest
#Run With ./build/coin (else process cannot be stopped directly with Ctrl-C)
LABEL Name=CoinPP Version=0.0.1
