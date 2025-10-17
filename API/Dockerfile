# Stage 1: The Build Environment (Builder)
# Use a robust image that includes development tools, like Ubuntu or a specific GCC image.
FROM ubuntu:22.04 AS builder

# 1. Install necessary build tools and dependencies
# CMake is required, and we'll install git to clone vcpkg.
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    g++ \
    cmake \
    git \
    ninja-build \
    autoconf \
    bison\
    flex\
    zip \
    tar\
    unzip \
    curl \
    pkg-config \
    doxygen \
    && rm -rf /var/lib/apt/lists/*

# 2. Setup vcpkg
# Clone vcpkg and bootstrap it.
WORKDIR /vcpkg
RUN git clone https://github.com/microsoft/vcpkg.git . && \
    ./bootstrap-vcpkg.sh -disableMetrics && \
    ./vcpkg integrate install

# Set the working directory for your project
WORKDIR /app

# 3. Copy source files and configuration
# Copy the project files now, before running vcpkg install, to cache the installation step
# if only source files change.
COPY . /app

# Clean the build folder

RUN rm -rf /app/build*

# 4. Install dependencies via vcpkg
# vcpkg uses the manifest file (vcpkg.json) to install dependencies.
# We also use the vcpkg toolchain file with CMake for integration.
RUN /vcpkg/vcpkg install

# 5. Configure and Build the Project
# Create a build directory, run CMake, and then build the project.
RUN cmake -B build \
    -S . \
    -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake \
    -DCMAKE_BUILD_TYPE=Release \
    && cmake --build build --config Release 

# debug only
RUN echo "📁 Contents of /app/build (if any):" && ls -la /app/build || echo "⚠️  Directory not found"

# Stage 2: The Runtime Environment (Minimal Image)
# Use a minimal base image, only including the essential runtime libraries.
FROM debian:stable-slim

# Install the C++ runtime libraries (libstdc++6)
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y \
    libstdc++6 \
    && rm -rf /var/lib/apt/lists/*

ENV PORT="8080"

# Optional: Indicate the port the container listens on (for documentation)
EXPOSE 8080

# Set the working directory for the executable
WORKDIR /usr/local/bin

COPY --from=builder /app/build/job-application-handler-api /usr/local/bin/

# Copy any necessary shared libraries that vcpkg might have installed for runtime.
# This assumes the vcpkg "installed" directory for the target triplet is used.
# You may need to adjust the path based on your project's vcpkg triplet (e.g., x64-linux).
# If your project uses ONLY static linking, this step can be skipped.
# RUN mkdir -p /usr/local/lib
# COPY --from=builder /vcpkg/installed/x64-linux/lib /usr/local/lib

# Set the entrypoint command
CMD ["/usr/local/bin/job-application-handler-api"]
