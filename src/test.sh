rm test
g++ test.cpp -o test -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lGLEW -lsfml-system -lsfml-window -lsfml-graphics
./test