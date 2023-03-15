// rotacao – translação e escala
//////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

#define janela_altura 400
#define janela_largura 600
float rotacao = 1;
float zoom = 1;
float trans = 1;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void quadrado();
void retangulo();
void triangulo();
void rotacaoQuadrado();

int main(int argc, char** argv)
{
	glutInit(&argc, argv);	// suporte a janelas

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // PADRAO DE CORES
	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("rotacao escala e  translacao"); // cria janela

	//glutFullScreen();
	glutReshapeFunc(tela);  // configura a tela
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);  // chama teclado
	glutMainLoop(); // redesenhar

	return(0);
}


void keyboard(unsigned char tecla, int x, int y)
{
	printf("\ntecla %c\n", tecla);
	printf("\n\nDigite 1 para esquerda, 2 para direita: ");
	printf("\ntecla %c\n", tecla);
	printf("\no mouse estava em %d x %d\n", x, y);
	if (tecla == '1') // rotacao triangulo
	{
		rotacao = rotacao + 0.05;
		quadrado();
		printf("\n o valor de rotacao e %.2f\n", rotacao);
	}
	if (tecla == '2') //rotacao quadrado
	{
		rotacao = rotacao - 0.05;
		printf("\n o valor de escala e %.2f\n", rotacao);
	}
	if (tecla == '3') // rotacao retangulo
	{
		zoom = zoom + 0.05;
		printf("\n o valor do zoom e %.2f\n", zoom);
	}
	if (tecla == '4') // 
	{
		trans = trans + 0.05;
		printf("\n o valor do zoom e %.2f\n", zoom);
	}
	if (tecla == '5')
	{
		trans = trans - 0.05;
		printf("\n o valor do zoom e %.2f\n", zoom);
	}


	glutPostRedisplay();


}

void rotacaoQuadrado() {
	glPushMatrix();
	glRotated(rotacao, 0, 0, 1);
	quadrado();
	glRotated(0, 0, 0, 1);
	glPopMatrix();
}

void quadrado() {
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);  // cor
	glVertex2f(-30, 30);
	glVertex2f(-10, 30);
	glVertex2f(-10, 50);
	glVertex2f(-30, 50);

	glEnd();	
}

void triangulo() {
	glBegin(GL_TRIANGLES);
	glColor3f(1.0, 0.0, 0.0);  // cor
	glVertex2f(-100, -100);
	glVertex2f(0, 0);
	glVertex2f(100, -100);

	glEnd();
}

void retangulo() {

}

void desenhar()
{

	// rotacao (angulo, eixo x, eixo y, eixo z);
	//glRotated(rotacao, 0, 0, 1);


	//glScalef(zoom, zoom, 0);
	//glTranslatef(trans, trans, 0);

	//quadrado();
	//rotacaoQuadrado();
	rotacaoQuadrado();
	triangulo();
	retangulo();
	//glRotated(0, 0, 0,1);
	//glScalef(1, 1, 0);
	//glTranslatef(1, 1, 0);
}

void display()
{
	glMatrixMode(GL_MODELVIEW);  //coordenadas de desenho
	glLoadIdentity();

	glClearColor(0.0f, 0.0f, 1.0f, 1.0f); // cor do fundo
	glClear(GL_COLOR_BUFFER_BIT); // EXECUTA LIMPESA

	// Especificar o local aonde o desenho acontece: bem no centro da janela mais translacao
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
