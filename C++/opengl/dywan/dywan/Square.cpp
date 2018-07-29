//Zalaczenie plikow naglowkowych
#include <windows.h>
#include <stdlib.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include "Square.h"

//Konstruktor klasy Square
Square::Square(point2 startPoint, float len, float ph)
{
	this->verLength = len;
	this->phase = ph;

	this->p1[0] = startPoint[0];
	this->p1[1] = startPoint[1];

	this->p2[0] = this->p1[0] + this->verLength + this->phase;
	this->p2[1] = this->p1[1] + this->phase;

	this->p3[0] = this->p2[0] + this->phase;
	this->p3[1] = this->p2[1] - this->verLength - this->phase;

	this->p4[0] = this->p1[0] - this->phase;
	this->p4[1] = this->p1[1] - this->verLength - this->phase;
}

//Funkcja rysujaca kwadrat
void Square::Render(void)
{
	glBegin(GL_QUADS);
	glColor3f(this->GetRandomFloat(), this->GetRandomFloat(), this->GetRandomFloat());
	glVertex2fv(this->p1);
	glColor3f(this->GetRandomFloat(), this->GetRandomFloat(), this->GetRandomFloat());
	glVertex2fv(this->p2);
	glColor3f(this->GetRandomFloat(), this->GetRandomFloat(), this->GetRandomFloat());
	glVertex2fv(this->p3);
	glColor3f(this->GetRandomFloat(), this->GetRandomFloat(), this->GetRandomFloat());
	glVertex2fv(this->p4);
	glEnd();
}

//Funkcja losuje losowa liczbe rzeczywista z przedzialu 0-1
float Square::GetRandomFloat()
{
	return ((float)(rand() % 10) + 1) / 10;
}

//Dekstruktor
Square::~Square(void)
{
}