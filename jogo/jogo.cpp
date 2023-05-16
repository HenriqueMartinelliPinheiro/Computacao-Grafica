///  colisao de quadrados
//////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <limits.h>

#define janela_altura 400
#define janela_largura 600
#define PI 3.14159

typedef struct {
	float xLeft;
	float xRight;
	float yTop;
	float yDown;
	float trans;
} PeixesLeft;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void submarino();
void peixe(PeixesLeft*, int);
PeixesLeft* alocarPeixesLeft();
PeixesLeft** alocarVetorPeixesLeft();
void criarPeixes();
void definirPeixe();
void anima(int);
int alturaPeixesLeft[3] = { -150, -50, 50 };
int circ_pnt = 300;
float xLeftSub = 999;
float xRightSub = -999;
float yTopSub = 100;
float yDownSub = 80;
float transH = 30;
float transV = 80;
PeixesLeft** peixesLeft;
int tamPeixes = 3;
void verificarColisao();

int main(int argc, char** argv)
{

	peixesLeft = alocarVetorPeixesLeft();
	criarPeixes();
	glutInit(&argc, argv);	// suporte a janelas

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// PADRAO DE CORES

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("colisao_quadrado"); // cria janela

	//glutFullScreen();
	glutKeyboardFunc(&keyboard);  // chama teclado
	glutReshapeFunc(tela);  // configura a tela
	glutDisplayFunc(display);
	glutTimerFunc(150, anima, 1);
	glutMainLoop(); // redesenhar

	return(0);
}

PeixesLeft** alocarVetorPeixesLeft() {
	PeixesLeft** peixesLeft;
	peixesLeft = (PeixesLeft**)malloc(sizeof(PeixesLeft*) * tamPeixes);
	return peixesLeft;
}

void criarPeixes() {
	for (int i = 0; i < tamPeixes; i++) {
		peixesLeft[i] = alocarPeixesLeft();
	}
}

void keyboard(unsigned char tecla, int x, int y)
{
	/*printf("\ntecla %c\n", tecla);
	printf("\n\nDigite 1 para esquerda: ");
	printf("\ntecla %c\n", tecla);
	printf("\no mouse estava em %d x %d\n", x, y);*/
	if (tecla == 'a')
	{
		if ((transH - xLeftSub) > (-300)) {
			transH = transH - 1;
			//printf("\n o valor de translacao H e %.2f\n", transH);
		}
	}
	if (tecla == 'd')
	{
		if ((transH + xRightSub) < 300) {
			transH = transH + 1;
			//printf("\n o valor de translacao H e %.2f\n", transH);
		}

	}

	if (tecla == 'w') {
		if (transV < 80) {
			transV += 1;
			//printf("\n o valor de translacao e  V %.2f\n", transV);
		}

	}

	if (tecla == 's') {
		if (transV > -200) {
			transV -= 1;
			//printf("\n o valor de translacao e V %.2f\n", transV);
		}

	}

	glutPostRedisplay();
}

void ceu() {
	glBegin(GL_QUADS);
	glColor3f(0.26, 0.9, 0.96);  // cor
	glVertex2f(-300, 200);
	glVertex2f(300, 200);
	glVertex2f(300, 100);
	glVertex2f(-300, 100);

	glEnd();
}



void submarino() {

	glPushMatrix();
	glTranslatef(transH, transV, 0);

	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);  // cor
	glVertex2f(0, 0);
	glVertex2f(60, 0);
	glVertex2f(60, 20);
	glVertex2f(0, 20);

	glEnd();

	glBegin(GL_QUADS);

	glVertex2f(15, 20);
	glVertex2f(45, 20);
	glVertex2f(45, 25);
	glVertex2f(15, 25);

	glEnd();

	int raioX = 13;
	int raioY = 10;
	float ang;
	glPushMatrix();
	glTranslatef(1, 10, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++)
	{
		glColor3f(1.0, 1.0, 0.0);  // cor
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
		if ((cos(ang) * raioX) < xLeftSub) {
			xLeftSub = (cos(ang) * raioX) + 1;
		}
	}

	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(54, 10, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++)
	{
		glColor3f(1.0, 1.0, 0.0);  // cor
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
		if ((cos(ang) * raioX) > xRightSub) {
			xRightSub = (cos(ang) * raioX) + 54;
		}
	}
	glEnd();
	glPopMatrix();

	glPointSize(5);


	glBegin(GL_POINTS);
	glColor3f(0, 0, 0.5);  // cor
	glVertex2f(5, 10);
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(0, 0, 0.5);  // cor
	glVertex2f(20, 10);
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(0, 0, 0.5);  // cor
	glVertex2f(35, 10);
	glEnd();

	glBegin(GL_POINTS);
	glColor3f(0, 0, 0.5);  // cor
	glVertex2f(50, 10);
	glEnd();

	glPopMatrix();
}

void peixe(PeixesLeft* peixe, int altura) {

	peixe->xLeft = -345;
	peixe->xRight = -305;
	peixe->yTop = altura;
	peixe->yDown = altura - 20;

	glBegin(GL_TRIANGLES);
	glColor3ub(237, 216, 146);  // cor
	glVertex2f(peixe->xLeft + 10, peixe->yDown);
	glVertex2f(peixe->xLeft + 10, peixe->yTop);
	glVertex2f(peixe->xRight, peixe->yTop - 10);
	glEnd();

	glColor3ub(235, 192, 52);  // cor
	glBegin(GL_TRIANGLES);
	glVertex2f(peixe->xLeft, peixe->yDown);
	glVertex2f(peixe->xLeft, peixe->yTop);
	glVertex2f(peixe->xLeft + 20, peixe->yTop - 10);
	glEnd();

	glColor3ub(0, 0, 0);  // cor
	glBegin(GL_POINTS);
	glVertex2f(peixe->xLeft + 25, peixe->yTop - 10);
	glEnd();
}

void desenhar()
{
	ceu();
	glPushMatrix();

	submarino();
	glPopMatrix();
	verificarColisao();
	definirPeixe();
}

void display()
{
	glMatrixMode(GL_MODELVIEW);  //coordenadas de desenho
	glLoadIdentity();

	glClearColor(0.5f, 0.5f, 1.0f, 1.0f); // cor do fundo

	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA
	// Especificar o local aonde o desenho acontece: bem no centro da janela
	glTranslatef(janela_largura / 2, janela_altura / 2, 0.0f);

	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();

	glFlush();  // execute o desenho

}

void definirPeixe() {
	for (int i = 0; i < tamPeixes; i++)
	{
		glPushMatrix();
		glTranslatef(peixesLeft[i]->trans, 0, 0);
		peixe(peixesLeft[i], alturaPeixesLeft[i]);
		glPopMatrix();
	}
}

PeixesLeft* alocarPeixesLeft() {
	PeixesLeft* peixe = (PeixesLeft*)malloc(sizeof(PeixesLeft));
	peixe->trans = 0;

	return peixe;
}

void tela(GLsizei w, GLsizei h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// cria a janela (esq, direita, embaixo, em cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);

}

void verificarColisao() {

	for (int i = 0; i < tamPeixes; i++)
	{
		printf("\n Peixe1 Top: %f, Peixe1 Down: %f, Cord Submarino: %f\n", peixesLeft[i]->yTop, peixesLeft[i]->yDown, yTopSub + transV);

		if (yTopSub + transV -80>= peixesLeft[i]->yDown && yTopSub + transV -80<= peixesLeft[i]->yTop) {
			printf("COLISAAAAAAAAAAAAAAAAAAAAO");
		}
	/*	if (((xRightSub + transH) >= (peixesLeft[i]->xLeft + peixesLeft[i]->trans)) && ((xRightSub + transH) <= (peixesLeft[i]->xRight + peixesLeft[i]->trans)) && ((yTopSub + transV) >= (peixesLeft[i]->yDown)) && ((yTopSub + transV) <= (peixesLeft[i]->yTop))) {
			printf("Trans H: %f", transH);
		}*/
	}
}	

void anima(int valor)
{
	for (int i = 0; i < tamPeixes; i++)
	{
		if ((peixesLeft[i]->xLeft + peixesLeft[i]->trans) >= 300) {
			peixesLeft[i]->trans = 0;
		}
		peixesLeft[i]->trans += 5;
	}
	glutPostRedisplay();
	glutTimerFunc(150, anima, 1);
}
