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
int circ_pnt = 300;
float xLeftSub = 999;
float xRightSub = -999;
float yTopSub = 100;
float yDownSub = 80;
float transH = 30;
float transV = ((yTopSub - yDownSub) / 2) + yDownSub;;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void submarino();
void peixe();


int main(int argc, char** argv)
{
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
	glutMainLoop(); // redesenhar

	return(0);
}


void keyboard(unsigned char tecla, int x, int y)
{
	printf("\ntecla %c\n", tecla);
	printf("\n\nDigite 1 para esquerda: ");
	printf("\ntecla %c\n", tecla);
	printf("\no mouse estava em %d x %d\n", x, y);
	if (tecla == 'a')
	{
		transH = transH - 1;
		printf("\n o valor de translacao H e %.2f\n", transH);
	}
	if (tecla == 'd')
	{
		transH = transH + 1;
		printf("\n o valor de translacao H e %.2f\n", transH);
	}

	if (tecla == 'w') {
		transV += 1;
		printf("\n o valor de translacao e  V %.2f\n", transV);

	}

	if (tecla == 's') {
		transV -= 1;
		printf("\n o valor de translacao e V %.2f\n", transV);
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
		if ((cos(ang) * raioX)<xLeftSub) {
			xLeftSub = (cos(ang) * raioX);
			printf("Esquerda %f\n",xLeftSub);
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
			xRightSub = (cos(ang) * raioX);
			printf("Direita %f \n", xRightSub);
		}
	}
	glEnd();
	glPopMatrix();

	glPointSize(5);


	glBegin(GL_POINTS);
	glColor3f(0, 0, 0.5);  // cor
	glVertex2f(5,10);
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

void peixe() {
	glBegin(GL_QUADS);
	glColor3ub(237, 216, 146);  // cor
	glVertex2f(-30, 0);
	glVertex2f(-10, 0);
	glVertex2f(-10, 10);
	glVertex2f(-30, 10);

	glEnd();


}

void desenhar()
{
	ceu();
	glPushMatrix();

	submarino();
	glPopMatrix();

	peixe();
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

void tela(GLsizei w, GLsizei h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// cria a janela (esq, direita, embaixo, em cima)
	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);

}
