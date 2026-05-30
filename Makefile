all: make_things
make_things: main.cpp
  g++ main.cpp -o reader -std=c++23 -O3 -march=native -flto=auto
