#include <iostream>
#include "color.h"

using namespace std;

Color::Color(){
	red=0; green=0; blue=0;
}
Color::Color(int value){
	red = value; green = value; blue = value;
}
Color::Color(int r, int g, int b){
	red = r; green = g; blue = b;
}
Color& Color::operator * (float f){
	red*=f; green*=f; blue*=f;
	return *this;
}

void Color::print(){
	cout<<"("<<red <<", "<<green <<", "<<blue <<")"<<endl;
}
