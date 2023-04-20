#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

#define janela_altura 400
#define janela_largura 600
#define PI 3.1415926535898 

float trans = 0;
float circ1X;
float circ1Y;
float circ2X;
float circ2Y;

float distancia = 50;

float transV = 0;
GLfloat ang, raioX, raioY;
GLfloat circ_pnt = 100;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
float distance();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	// suporte a janelas

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// PADRAO DE CORES

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("colisao_circulos"); // cria janela

	//glutFullScreen();
	glutKeyboardFunc(&keyboard);  // chama teclado
	glutReshapeFunc(tela);  // configura a tela
	glutDisplayFunc(display);
	glutMainLoop(); // redesenhar

	return(0);
}


void keyboard(unsigned char tecla, int x, int y)
{
	if (tecla == '1')
	{
		trans = trans - 1;
		distancia -= 0.5;
	}
	if (tecla == '2')
	{
		trans = trans + 1;
		distancia += 0.5;

	}
	if (tecla == '3')
	{
		transV = transV - 1;
		distancia += 0.5;
	}

	if (tecla == '4')
	{
		transV = transV + 1;
		distancia += 0.5;
	}
	printf("\n o valor de translacao de X eh %.2f\n", trans);
	printf("\n o valor de translacao de Y eh %.2f\n", transV);
	printf("\n a distancia entre os circulos é de %.2f\n", distance());
	glutPostRedisplay();

}



void desenhar()
{
	circ_pnt = 100;
	raioX = 50;
	raioY = 50;

	glLineWidth(2); // grossura da linha

	glTranslatef(-100, 0, 0);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circ_pnt; i++)
	{
		glColor3f(1.0, 0.0, 0.0);  // cor
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
	}

	circ1X = (((cos(ang) * circ_pnt))/raioX);
	circ1Y = (sin(ang) * circ_pnt)/raioX;

	glEnd();

	glBegin(GL_LINES);  /// linha para ter a base
	glVertex3f(0, 0, 0);
	glVertex3f(raioX, 0, 0);
	glEnd();



	glTranslatef(trans, transV, 0);

	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < circ_pnt; i++)
	{
		glColor3f(1.0, 1.0, 0.0);  // cor
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
	}
	glEnd();

	circ2X = (((cos(ang) * circ_pnt))/raioX) + trans;
	circ2Y = (((sin(ang) * circ_pnt))/raioY) + transV;

	glBegin(GL_LINES);  // linha para ter a base
	glVertex3f(0, 0, 0);
	glVertex3f((raioX * (-1)), 0, 0);
	glEnd();

}


float distance() {
	return sqrt(pow((circ2X - circ1X),2) + pow((circ2Y- circ1Y), 2));
}
void display()
{
	glMatrixMode(GL_MODELVIEW);  //coordenadas de desenho
	glLoadIdentity();

	if (distance() <= (raioX*2))
	{
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // cor do fundo
	}
	else
	{
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	}

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
