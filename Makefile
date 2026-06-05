all: make_things
make_things: main.cpp
	g++ main.cpp -o coreutils-uruguayo-bin -std=c++23 -Oz -march=native -flto=auto -static
	strip -s coreutils-uruguayo-bin
