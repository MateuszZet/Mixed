#pragma once

//Definicja typu point2
typedef float point2[2];

//Klasa Square reprezentuje klase obiektow - kwadratow
class Square
{
private:
	point2 p1;
	point2 p2;
	point2 p3;
	point2 p4;
	float verLength;
	float phase;
	float GetRandomFloat();
public:
	Square(point2 startPoint, float len, float ph);
	void Render();
	~Square(void);
};