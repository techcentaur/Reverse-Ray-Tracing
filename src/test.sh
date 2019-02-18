rm test
g++ test.cpp -o test -lglfw -lGLU -lGL -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lXinerama -lXcursor -lXi -ldl -lsfml-system -lsfml-window -lsfml-graphics
./test