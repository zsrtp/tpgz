FROM devkitpro/devkitppc
ARG USERNAME=vscode
ARG USER_UID=1000
ARG USER_GID=$USER_UID

RUN sudo dpkg --add-architecture i386
RUN sudo apt-get update
RUN sudo apt-get install -y sudo
RUN sudo apt-get install -y build-essential
RUN sudo apt-get install -y python3-pip
RUN sudo apt-get install -y libarchive-tools
RUN sudo apt-get install -y cmake
RUN sudo apt-get install -y ninja-build
RUN sudo apt-get install -y libtinfo5

# # Install the patchers
# WORKDIR /workspaces/romhack/wii
# RUN curl -L https://github.com/zsrtp/romhack-compiler/releases/download/v0.1.1-r2/romhack-v0.1.1-r2-linux-x64-musl.zip | bsdtar -xvf -
# RUN chmod +x romhack
# WORKDIR /workspaces/romhack/gc
# RUN curl -L https://github.com/zsrtp/romhack-compiler/releases/download/v0.1.1-r2/romhack-v0.1.1-r2-linux-x64-musl-gc.zip | bsdtar -xvf -
# RUN chmod +x romhack

# Setup user
RUN groupadd --gid $USER_GID $USERNAME
RUN useradd -s /bin/bash --uid $USER_UID --gid $USER_GID -G sudo -m $USERNAME
RUN echo $USERNAME ALL=\(root\) NOPASSWD:ALL > /etc/sudoers.d/$USERNAME
RUN chmod 0440 /etc/sudoers.d/$USERNAME
USER vscode

RUN python3 -m pip install Pillow pycryptodome
