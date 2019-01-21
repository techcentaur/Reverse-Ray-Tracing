#ifndef COLOR_H
#define COLOR_H

class Color{

public:
	int red, green, blue;

	Color();
	Color(int);
	Color(int, int, int);

	Color& operator * (float f);

	void print();

};

#endif
