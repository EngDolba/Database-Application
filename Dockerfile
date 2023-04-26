FROM ubuntu:23.04

RUN apt-get update && \
    apt-get install -y gcc g++ cmake

WORKDIR /app

# Copy CMakeLists.txt and all source files to the container
COPY CMakeLists.txt .
COPY main.cpp .
COPY ProductDatabase.h .
COPY ProductDatabase.cpp .

# Compile the project
RUN mkdir build && cd build && cmake .. && make


# Run the program

CMD ["./build/Database_Application"]
