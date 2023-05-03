///  colisao de quadrados
//////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define janela_altura 400
#define janela_largura 600
#define PI 3.14159
float transH = 0;
float transV = 0;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void submarino();
void peixe();
int circ_pnt = 300;

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
		printf("\n o valor de translacao e %.2f\n", transH);
	}
	if (tecla == 'd')
	{
		transH = transH + 1;
		printf("\n o valor de translacao e %.2f\n", transH);
	}

	if (tecla == 'w') {
		transV += 1;
		printf("\n o valor de translacao e %.2f\n", transV);

	}

	if (tecla == 's') {
		transV -= 1;
		printf("\n o valor de translacao e %.2f\n", transV);
	}

	glutPostRedisplay();


}

void submarino() {
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);  // cor
	glVertex2f(0, 0);
	glVertex2f(40, 0);
	glVertex2f(40, 20);
	glVertex2f(0, 20);

	glEnd();

	glBegin(GL_QUADS);

	glVertex2f(5, 20);
	glVertex2f(35, 20);
	glVertex2f(35, 25);
	glVertex2f(5, 25);

	glEnd();

	int raioX = 15;
	int raioY = 15;
	float ang;

	glPushMatrix();
	glTranslatef(0,25,0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++)
	{
		glColor3f(1.0, 0.0, 0.0);  // cor
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
	}

	glEnd();

	glPopMatrix();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);  // cor
	glVertex2f(0, 10);
	glVertex2f(10, 10);
	glVertex2f(10, 20);
	glVertex2f(0, 20);

	glEnd();
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
	glPushMatrix();
	glTranslatef(transH, transV, 0);

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
