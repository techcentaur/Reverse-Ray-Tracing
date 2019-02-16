rm test
g++ test.cpp -o test -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl
./test