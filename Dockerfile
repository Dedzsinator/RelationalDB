# Use an official lightweight image as a base
FROM debian:bullseye-slim

# Install necessary packages
RUN apt-get update && apt-get install -y \
    g++ \
    cmake \
    libboost-system-dev \
    libboost-thread-dev \
    libboost-filesystem-dev \
    && rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /app

# Copy the source files into the container
COPY src/ ./src/
COPY CMakeLists.txt ./

# Compile the application
RUN cmake . && make

# Expose the port the server will run on
EXPOSE 8080

# Run the database daemon
CMD ["./mydb_daemon"]
