
FROM mcr.microsoft.com/devcontainers/base:ubuntu

# Install build essentials, cmake, git, and optional tools
RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    build-essential \
    cmake \
    git \
    gdb \
    ninja-build \
    pkg-config \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Optional: JSON and logging libs via apt (or use vcpkg/Conan later)
# RUN apt-get update && apt-get install -y nlohmann-json3-dev libspdlog-dev
