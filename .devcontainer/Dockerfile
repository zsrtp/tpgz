# See here for image contents: https://github.com/microsoft/vscode-dev-containers/tree/v0.241.1/containers/ubuntu/.devcontainer/base.Dockerfile

# [Choice] Ubuntu version (use ubuntu-22.04 or ubuntu-18.04 on local arm64/Apple Silicon): ubuntu-22.04, ubuntu-20.04, ubuntu-18.04
ARG VARIANT="jammy"
FROM mcr.microsoft.com/vscode/devcontainers/base:0-${VARIANT}
USER vscode

# [Optional] Uncomment this section to install additional OS packages.
# RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
#     && apt-get -y install --no-install-recommends <your-package-list-here>

RUN sudo dpkg --add-architecture i386
RUN sudo apt-get update && sudo apt-get install -y build-essential
RUN sudo apt-get install -y python3-pip
RUN sudo apt-get install -y libarchive-tools 
RUN sudo apt-get install -y clang-format-10
RUN sudo apt-get install -y cmake
# RUN sudo apt-get install -y wine64
# RUN sudo apt-get install -y wine
RUN sudo apt-get install -y ninja-build
RUN sudo apt-get upgrade -y
RUN sudo apt-get install -y libtinfo5

RUN python3 -m pip install Pillow

# Install DevkitPPC
WORKDIR /tmp
COPY install-devkitpro-pacman install-devkitpro-pacman
RUN sudo chmod +x ./install-devkitpro-pacman
RUN sudo ./install-devkitpro-pacman
RUN sudo dkp-pacman -Syu --noconfirm
WORKDIR /etc
RUN sudo ln -sf /proc/self/mounts mtab
RUN sudo dkp-pacman -S --noconfirm gamecube-dev wii-dev

# Install the patchers
WORKDIR /workspaces/romhack/wii
RUN curl -L https://github.com/zsrtp/romhack-compiler/releases/download/v0.1.1-r2/romhack-v0.1.1-r2-linux-x64-musl.zip | bsdtar -xvf -
RUN chmod +x romhack
WORKDIR /workspaces/romhack/gc
RUN curl -L https://github.com/zsrtp/romhack-compiler/releases/download/v0.1.1-r2/romhack-v0.1.1-r2-linux-x64-musl-gc.zip | bsdtar -xvf -
RUN chmod +x romhack
