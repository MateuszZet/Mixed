//Zalaczenie plikow naglowkowych
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <math.h>
#include <time.h>

//Definicja typu point3 - punkt w przestrzeni 3D
typedef float point3[3];

//Stala PI
const float PI = 3.14159265;
//Tablica na punkty
point3 **pointsTab;
static GLfloat theta[] = { 0.0, 0.0, 0.0 }; // trzy k¹ty obrotu
//Parametry programu
int N = 25;				//Liczba punktow na jaka dzielimy kwadrat jednostkowy
int model = 1;			//Rodzaj modelu: 1-punkty, 2-siatka, 3-kolorowe
float verLength = 1.0;  //Dlugosc boku kwadratu
point3 **pointsRGB; // Tablica kolorów pkt

//funkcja wyliczaj¹ca wspolrzedna x
float wzor_x(float u, float v){
	float x, a = v*PI;
	x = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(a);
	return x;
}
//funkcja wyliczajaca wspolrzedna y
float wzor_y(float u, float v){
	float y;
	y = (160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2));
	return y-5;
}
//funkcja wyliczajaca wspolrzedna z
float wzor_z(float u, float v) {
	float z, a = v*PI;

	z = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * sin(a);
	return z;
}

// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych
void Axes(void)
{
	point3  x_min = { -3.0, 0.0, 0.0 };
	point3  x_max = { 3.0, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -3.0, 0.0 };
	point3  y_max = { 0.0, 3.0, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -3.0 };
	point3  z_max = { 0.0, 0.0, 3.0 };
	//  pocz¹tek i koniec obrazu osi z

	glColor3f(1.0f, 0.0f, 0.0f);  // kolor rysowania osi - czerwony
	glBegin(GL_LINES); // rysowanie osi x
	glVertex3fv(x_min);
	glVertex3fv(x_max);
	glEnd();

	glColor3f(0.0f, 1.0f, 0.0f);  // kolor rysowania - zielony
	glBegin(GL_LINES);  // rysowanie osi y
	glVertex3fv(y_min);
	glVertex3fv(y_max);
	glEnd();

	glColor3f(0.0f, 0.0f, 1.0f);  // kolor rysowania - niebieski
	glBegin(GL_LINES); // rysowanie osi z
	glVertex3fv(z_min);
	glVertex3fv(z_max);
	glEnd();
}

//Funkcja generujaca siatke puntow, najpierw w 2D, potem w 3D
void genPointsMesh(){
	float stepXY = verLength / N; // dlugosc boku kwadratu przez liczbe pkt.

	//Przypisanie pkt. wspolrzednych
	for (int i = 0; i<N + 1; i++) {
		for (int j = 0; j<N + 1; j++) {
			pointsTab[i][j][0] = j*stepXY;
			pointsTab[i][j][1] = i*stepXY;
		}
	}

	//Przeksztalcenie wspolrzednych z dziedziny parametrycznej w przestrzen 3D
	float u, v;
	for (int i = 0; i<N + 1; i++) {
		for (int j = 0; j<N + 1; j++) {
			u = pointsTab[i][j][0];
			v = pointsTab[i][j][1];
			pointsTab[i][j][0] = wzor_x(u, v);
			pointsTab[i][j][1] = wzor_y(u, v);
			pointsTab[i][j][2] = wzor_z(u, v);
		}
	}
}

//obracanie jajkiem (z instrukcji)
void spinEgg()
{

	theta[0] -= 0.5;
	if (theta[0] > 360.0) theta[0] -= 360.0;

	theta[1] -= 0.5;
	if (theta[1] > 360.0) theta[1] -= 360.0;

	theta[2] -= 0.5;
	if (theta[2] > 360.0) theta[2] -= 360.0;

	glutPostRedisplay(); //odœwie¿enie zawartoœci aktualnego okna
}

//Funkcja renderujaca okreslony model jajka
void Egg(void){

	//Wygenerowanie siatki 3D punktow
	genPointsMesh();

	//Parametry rysowania
	glColor3f(1.0, 1.0, 1.0);

	//W zaleznosci od rodzaju modelu
	switch (model){
		//Jesli punkty
	case 1: {
		glBegin(GL_POINTS);
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				glVertex3fv(pointsTab[i][j]);
			}
		}
		glEnd();
	} break;
	case 2: {
		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				//Pion
				glBegin(GL_LINES);
				glVertex3fv(pointsTab[i][j]);
				glVertex3fv(pointsTab[i][j + 1]);
				glEnd();
				//Poziom
				glBegin(GL_LINES);
				glVertex3fv(pointsTab[i][j]);
				glVertex3fv(pointsTab[i + 1][j]);
				glEnd();
				//Prawo
				glBegin(GL_LINES);
				glVertex3fv(pointsTab[i][j]);
				glVertex3fv(pointsTab[i + 1][j + 1]);
				glEnd();
				//Lewo
				glBegin(GL_LINES);
				glVertex3fv(pointsTab[i + 1][j]);
				glVertex3fv(pointsTab[i][j + 1]);
				glEnd();

			}
		}
	} break;
	case 3: {for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			//W jedna strone
			glBegin(GL_TRIANGLES);
			glColor3fv(pointsRGB[i][j + 1]);
			glVertex3fv(pointsTab[i][j + 1]);
			glColor3fv(pointsRGB[i + 1][j]);
			glVertex3fv(pointsTab[i + 1][j]);
			glColor3fv(pointsRGB[i + 1][j + 1]);
			glVertex3fv(pointsTab[i + 1][j + 1]);
			glEnd();
			//W druga strone
			glBegin(GL_TRIANGLES);
			glColor3fv(pointsRGB[i][j]);
			glVertex3fv(pointsTab[i][j]);
			glColor3fv(pointsRGB[i + 1][j]);
			glVertex3fv(pointsTab[i + 1][j]);
			glColor3fv(pointsRGB[i][j + 1]);
			glVertex3fv(pointsTab[i][j + 1]);
			glEnd();
		}
	}} break;
	}
}

void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Czyszczenie okna aktualnym kolorem czyszcz¹cym
	glLoadIdentity(); // Czyszczenie macierzy bie¿¹cej
	
	
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);



	//Renderowanie osi
	Axes();

	//Renderowanie jajka
	Egg();
	Egg();
	Egg();
	Egg();

	glFlush();

	glutSwapBuffers();

}

//Funkcja - callback dla klawiszy
void Keys(unsigned char key, int x, int y)
{
	//Zmiana rodzaju modelu w zaleznosci od klawisza
	if (key == '1') model = 1;
	if (key == '2') model = 2;
	if (key == '3') model = 3;

	RenderScene();
}

// Funkcja ustalaj¹ca stan renderowania
void MyInit(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// Kolor czyszc¹cy (wype³nienia okna) ustawiono na czarny
}


// Funkcja ma za zadanie utrzymanie sta³ych proporcji rysowanych 
// w przypadku zmiany rozmiarów okna.
// Parametry vertical i horizontal (wysokoœæ i szerokoœæ okna) s¹ 
// przekazywane do funkcji za ka¿dym razem gdy zmieni siê rozmiar okna.
void ChangeSize(GLsizei horizontal, GLsizei vertical)
{
	GLfloat AspectRatio;
	// Deklaracja zmiennej AspectRatio  okreœlaj¹cej proporcjê
	// wymiarów okna

	if (vertical == 0)  // Zabezpieczenie przed dzieleniem przez 0
		vertical = 1;

	glViewport(0, 0, horizontal, vertical);
	// Ustawienie wielkoœciokna okna widoku (viewport)
	// W tym przypadku od (0,0) do (horizontal, vertical) 

	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej           

	AspectRatio = (GLfloat)horizontal / (GLfloat)vertical;
	// Wyznaczenie wspó³czynnika  proporcji okna
	// Gdy okno nie jest kwadratem wymagane jest okreœlenie tak zwanej
	// przestrzeni ograniczaj¹cej pozwalaj¹cej zachowaæ w³aœciwe
	// proporcje rysowanego obiektu.
	// Do okreslenia przestrzeni ograniczj¹cej s³u¿y funkcja
	// glOrtho(...)           

	if (horizontal <= vertical)
		glOrtho(-7.5, 7.5, -7.5 / AspectRatio, 7.5 / AspectRatio, 10.0, -10.0);
	else
		glOrtho(-7.5*AspectRatio, 7.5*AspectRatio, -7.5, 7.5, 10.0, -10.0);
	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu                                    
	glLoadIdentity();
	// Czyszcenie macierzy bie¿¹cej
}

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli
void main(void)
{
	//Dynamiczna alokacja tablicy punktow
	pointsTab = new point3*[N + 1];
	for (int i = 0; i<N + 1; i++){
		pointsTab[i] = new point3[N + 1];
	}
	//Dynamiczna alokacja tablicy i wygenerowanie kolorow losowych dla punktow
	pointsRGB = new point3*[N + 1];
	for (int i = 0; i < N + 1; i++){
		pointsRGB[i] = new point3[N + 1];
	}
	for (int i = 0; i < N + 1; i++){
		for (int j = 0; j < N + 1; j++){
			pointsRGB[i][j][0] = ((float)(rand() % 10) + 1) / 10;
			pointsRGB[i][j][1] = ((float)(rand() % 10) + 1) / 10;
			pointsRGB[i][j][2] = ((float)(rand() % 10) + 1) / 10;
		}
	}
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);

	glutCreateWindow("JAJKO");

	glutDisplayFunc(RenderScene);
	// Okreœlenie, ¿e funkcja RenderScene bêdzie funkcj¹ zwrotn¹
	// (callback function).  Bedzie ona wywo³ywana za ka¿dym razem 
	// gdy zajdzie potrzba przeryswania okna

	// Dla aktualnego okna ustala funkcjê zwrotn¹ odpowiedzialn¹
	// zazmiany rozmiaru okna  
	glutReshapeFunc(ChangeSize);

	MyInit();
	// Funkcja MyInit() (zdefiniowana powy¿ej) wykonuje wszelkie
	// inicjalizacje konieczne  przed przyst¹pieniem do renderowania 

	glEnable(GL_DEPTH_TEST);
	// W³¹czenie mechanizmu usuwania powierzchni niewidocznych

	//Rejestracja funkcji zwrotnej dla klawiatury
	glutKeyboardFunc(Keys);

	glutIdleFunc(spinEgg);
	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

	//Zwolnienie pamiêci
	for (int i = 0; i < N + 1; i++){
		delete[] pointsTab[i];
		pointsTab[i] = 0;
	}
	delete[] pointsTab;
	pointsTab = 0;
}