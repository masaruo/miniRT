FROM ubuntu

RUN apt update && apt upgrade -y && apt install -y \
	gcc \
	make \
	xorg \
	libxext-dev \
	libbsd-dev \
	build-essential \
	vim \
	git \
	valgrind \
	x11-apps && \
	git clone https://github.com/42paris/minilibx-linux mlx

RUN cd mlx && ./configure && \
	cp libmlx.a /usr/local/lib/ && \
	cp mlx.h /usr/local/include/

