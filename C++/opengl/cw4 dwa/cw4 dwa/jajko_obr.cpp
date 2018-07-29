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
//Tablica na kolory punktow
point3 **pointsRGB;

static GLfloat viewer[] = { 0.0, 0.0, 10.0 };
// inicjalizacja po³o¿enia obserwatora

static GLfloat	fi = 0.0,		// k¹ty obrotu, elewacja i azymut
theta = 0.0;
static GLfloat	pix2angle_x,	// przelicznik pikseli na stopnie
pix2angle_y;
static GLint	status = 0;		// stan klawiszy myszy
// 0 - nie naciœniêto ¿adnego klawisza
// 1 - naciœniêty zosta³ lewy klawisz, 2 - prawy
static int	x_pos_old = 0,		// poprzednia pozycja kursora myszy
y_pos_old = 0;
static int	delta_x = 0,		// ró¿nica pomiêdzy pozycj¹ bie¿¹c¹
delta_y = 0;        // i poprzedni¹ kursora myszy

//Parametry programu
int N = 40;				//Liczba punktow na jaka dzielimy kwadrat jednostkowy
int model = 1;			//Rodzaj modelu: 1-punkty, 2-siatka, 3-kolorowe trojkaty
float verLength = 1.0;  //Dlugosc boku kwadratu
float viewerR = 10.0;	//Promien sfery obserwatora

//Funkcja wyliczajaca wspolrzedna X punktu (u,v) w przestrzeni 3D
float calc3Dx(float u, float v) {
	float x, a = v*PI;

	x = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * cos(a);
	return x;
}

//Funkcja wyliczajaca wspolrzedna Y punktu (u,v) w przestrzeni 3D
float calc3Dy(float u, float v) {
	float y;

	y = 160 * pow(u, 4) - 320 * pow(u, 3) + 160 * pow(u, 2);
	return y - 5;
}

//Funkcja wyliczajaca wspolrzedna Z punktu (u,v) w przestrzeni 3D
float calc3Dz(float u, float v) {
	float z, a = v*PI;

	z = (-90 * pow(u, 5) + 225 * pow(u, 4) - 270 * pow(u, 3) + 180 * pow(u, 2) - 45 * u) * sin(a);
	return z;
}

//Funkcja generujaca siatke puntow, najpierw w 2D, potem w 3D
void genPointsMesh(){
	float stepXY = verLength / N;

	//Przypisanie punktom wspolrzednych
	for (int i = 0; i<N + 1; i++) {
		for (int j = 0; j<N + 1; j++) {
			pointsTab[i][j][0] = j*stepXY;
			pointsTab[i][j][1] = i*stepXY;
		}
	}

	//Przeksztalcenie wspolrzednych z dziedziny parametrycznej
	//w przestrzen 3D
	float u, v;
	for (int i = 0; i<N + 1; i++) {
		for (int j = 0; j<N + 1; j++) {
			u = pointsTab[i][j][0];
			v = pointsTab[i][j][1];
			pointsTab[i][j][0] = calc3Dx(u, v);
			pointsTab[i][j][1] = calc3Dy(u, v);
			pointsTab[i][j][2] = calc3Dz(u, v);
		}
	}
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
		for (int i = 0; i<N; i++){
			for (int j = 0; j<N; j++){
				glVertex3fv(pointsTab[i][j]);
			}
		}
		glEnd();
	} break;
		//Jesli siatka
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
				//glBegin(GL_LINES);
				//glVertex3fv(pointsTab[i + 1][j]);
				//glVertex3fv(pointsTab[i][j + 1]);
				//glEnd();
			}
		}
	} break;
		//Jesli wypelnienie 
	case 3: {
		for (int i = 0; i < N; i++){
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
		}
	} break;
	
	}
}

// Funkcja rysuj¹ca osie uk³adu wspó³rzêdnych
void Axes(void)
{
	point3  x_min = { -2.0, 0.0, 0.0 };
	point3  x_max = { 2.0, 0.0, 0.0 };
	// pocz¹tek i koniec obrazu osi x

	point3  y_min = { 0.0, -2.0, 0.0 };
	point3  y_max = { 0.0, 2.0, 0.0 };
	// pocz¹tek i koniec obrazu osi y

	point3  z_min = { 0.0, 0.0, -2.0 };
	point3  z_max = { 0.0, 0.0, 2.0 };
	//  pocz¹tek i koniec obrazu osi y

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

// Funkcja okreœlaj¹ca co ma byæ rysowane (zawsze wywo³ywana gdy trzeba 
// przerysowaæ scenê)
void RenderScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Czyszczenie okna aktualnym kolorem czyszcz¹cym
	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej

	if (status == 1) {	// jeœli lewy klawisz myszy wciœniêty
		theta += delta_x*pix2angle_x;		// modyfikacja k¹ta obrotu o k¹t proporcjonalny
		fi += delta_y*pix2angle_y;		// do ró¿nicy po³o¿eñ kursora myszy

		if (theta >= 360.0)
			theta = 0.0;
		if (fi >= 360.0)
			fi = 0.0;
	}
	else if (status == 2) {	// jeœli prawy klawisz myszy wciœniêty
		viewerR += 0.1* delta_y;	// modyfikacja polozenia obserwatora(zoom)
		if (viewerR <= 5.0)	// ograniczenie zblizenia
			viewerR = 5.0;
		if (viewerR >= 25.0)	// ograniczenie oddalenia
			viewerR = 25.0;
	}

	//Wspolrzedne obserwatora - wzorki z ZSK
	viewer[0] = viewerR * cos(theta) * cos(fi);
	viewer[1] = viewerR * sin(fi);
	viewer[2] = viewerR * sin(theta) * cos(fi);

	gluLookAt(viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, cos(fi), 0.0);
	// Zdefiniowanie po³o¿enia obserwatora

	Axes();
	// Narysowanie osi przy pomocy funkcji zdefiniowanej powy¿ej

	//Renderowanie jajka
	Egg();

	glFlush();
	// Przekazanie poleceñ rysuj¹cych do wykonania

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
void ChangeSize(GLsizei horizontal, GLsizei vertical) {
	pix2angle_x = 360.0*0.1 / (float)horizontal; // przeliczenie pikseli na stopnie
	pix2angle_y = 360.0*0.1 / (float)vertical;

	glMatrixMode(GL_PROJECTION);
	// Prze³¹czenie macierzy bie¿¹cej na macierz projekcji

	glLoadIdentity();
	// Czyszcznie macierzy bie¿¹cej

	gluPerspective(70.0, 1.0, 1.0, 30.0);
	// Ustawienie parametrów dla rzutu perspektywicznego

	if (horizontal <= vertical)
		glViewport(0, (vertical - horizontal) / 2, horizontal, horizontal);
	else
		glViewport((horizontal - vertical) / 2, 0, vertical, vertical);
	// Ustawienie wielkoœci okna okna widoku (viewport) w zale¿noœci
	// relacji pomiêdzy wysokoœci¹ i szerokoœci¹ okna

	glMatrixMode(GL_MODELVIEW);
	// Prze³¹czenie macierzy bie¿¹cej na macierz widoku modelu  

	glLoadIdentity();
	// Czyszczenie macierzy bie¿¹cej
}

// Funkcja bada stan myszy i ustawia wartosci odpowiednich zmiennych globalnych
void Mouse(int btn, int state, int x, int y) {
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		x_pos_old = x;        // przypisanie aktualnie odczytanej pozycji kursora
		y_pos_old = y;        // jako pozycji poprzedniej
		status = 1;         // wciœniêty zosta³ lewy klawisz myszy
	}
	else if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		y_pos_old = y;		// przypisanie aktualnie odczytanej pozycji kursora
		// jako pozycji poprzedniej
		status = 2;			//wciœniêty zosta³ prawy klawisz myszy
	}
	else
		status = 0;         // nie zosta³ wciœniêty ¿aden klawisz
}

// Funkcja monitoruje polozenie kursora myszy i ustawia wartosci odpowiednich 
// zmiennych globalnych
void Motion(GLsizei x, GLsizei y) {
	delta_x = x - x_pos_old;    // obliczenie ró¿nicy po³o¿enia kursora myszy
	x_pos_old = x;	// podstawienie bie¿acego po³o¿enia jako poprzednie

	delta_y = y - y_pos_old;	// obliczenie ró¿nicy po³o¿enia kursora myszy
	y_pos_old = y;	// podstawienie bie¿acego po³o¿enia jako poprzednie

	glutPostRedisplay();	// przerysowanie obrazu sceny
}

// G³ówny punkt wejœcia programu. Program dzia³a w trybie konsoli
void main(void)
{
	//Ziarno losowosci
	srand((unsigned)time(NULL));

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
			pointsRGB[i][j][0] = 1.8; //((float)(rand() % 10) + 1) / 10;
			pointsRGB[i][j][1] = 0.9;//((float)(rand()%10)+1)/10;
			pointsRGB[i][j][2] = ((float)(rand()%10)+1)/10;
		}
	}

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);

	glutCreateWindow("Rzutowanie perspektywyczne, interakcja, jajko");

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

	glutMouseFunc(Mouse);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie stanu myszy

	glutMotionFunc(Motion);
	// Ustala funkcjê zwrotn¹ odpowiedzialn¹ za badanie ruchu myszy

	//Rejestracja funkcji zwrotnej dla klawiatury
	glutKeyboardFunc(Keys);

	glutMainLoop();
	// Funkcja uruchamia szkielet biblioteki GLUT

	//Zwolnienie pamiêci
	for (int i = 0; i < N + 1; i++){
		delete[] pointsTab[i];
		delete[] pointsRGB[i];
		pointsTab[i] = 0;
		pointsRGB[i] = 0;
	}
	delete[] pointsTab;
	delete[] pointsRGB;
	pointsTab = 0;
	pointsRGB = 0;
}