all: make_things
make_things: main.cpp
	g++ main.cpp -o reader -std=c++23 -Oz -march=native -flto=auto -static
	strip -s reader
