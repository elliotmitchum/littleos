FROM ubuntu
ENV DEBIAN_FRONTEND noninteractive
RUN apt-get update && apt-get install -q --yes --force-yes --no-install-recommends \
	 build-essential \
	 nasm \
	 xorriso \
	 grub-pc \
	 qemu

