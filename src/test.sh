rm lines
g++ lines.cpp color.cpp tracer.cpp vector.cpp light.cpp object.cpp transformation.cpp matrix.cpp -o lines -lglfw -lSOIL -lGLU -lGL -lglut  -lGLEW -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lXinerama -lXcursor -lXi -ldl -lsfml-system -lsfml-window -lsfml-graphics
./lines