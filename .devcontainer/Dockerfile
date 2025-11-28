FROM mcr.microsoft.com/devcontainers/cpp:latest

RUN apt update && apt install -y ninja-build
RUN git clone https://github.com/microsoft/vcpkg.git /opt/vcpkg && /opt/vcpkg/bootstrap-vcpkg.sh

ENV PATH="/opt/vcpkg:${PATH}"
