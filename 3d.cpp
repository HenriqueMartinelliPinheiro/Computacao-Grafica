#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#define janela_altura 480
#define janela_largura 640
void reshape(GLsizei largura, GLsizei altura);
void display();
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Ligar GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Display com Duplo Buffer
	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela
	glutInitWindowPosition(50, 50); // Pos. onde surge a janela
	glutCreateWindow("desenho 3d"); // Criar Janela
	glutDisplayFunc(display); // imagem
	glutReshapeFunc(reshape); // config telas
	glutMainLoop(); // loop
	return 0;
}
void reshape(GLsizei largura, GLsizei altura)
{
	if (altura == 0) altura = 1; // previne a divisão por zero
	GLfloat aspecto = (GLfloat)largura / (GLfloat)altura;
	glViewport(0, 0, largura, altura);
	glMatrixMode(GL_PROJECTION); // manipulando matriz de projeção
	glLoadIdentity(); // zerando a matriz
	gluPerspective(45.0f, aspecto, 0.1f, 100.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // configura fundo sem transparencia
	glEnable(GL_DEPTH_TEST); // alunos devem testar
	glShadeModel(GL_SMOOTH); // acabamento com suavização
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // correcao de perspectiva
}
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // executa a limpeza
	glMatrixMode(GL_MODELVIEW); // operando com a camera de modelos
	// desenho da piramide 3d
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f); // posiciona a piramide

	glBegin(GL_TRIANGLES);


		// triangulo 1 de 4 frente
	glColor3f(1.0f, 0.0f, 0.0f); // vermelho troca em todos
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); // verde para ficar
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); // azul lindo!!!!!!!! ui
	glVertex3f(1.0f, -1.0f, 1.0f);
	// triangulo 2 de 4 direita
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	// triangulo 3 de 4 atras
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	// triangulo 4 de 4 esquerda
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();

	glLineWidth(2.0f);
	glColor3f(1.0f, 1.0f, 1.0f); // vermelho troca em todos
	glBegin(GL_LINE_LOOP);

	// triangulo 1 de 4 frente
	glVertex3f(1.0,0.0,1.0);
	glVertex3f(1.0, -1.0, 1.0);
	glVertex3f(1.0, -1.0, 0);
	glVertex3f(1.0, 0.0, 0);

	glVertex3f(2.0, 0.0, 1.0);
	glVertex3f(2.0, -1.0, 1.0);
	glVertex3f(2.0, -1.0, 0);
	glVertex3f(2.0, 0.0, 0);

	// triangulo 3 de 4 atras

	// triangulo 4 de 4 esquerda

	glEnd();
 
	glBegin(GL_LINE_LOOP);

	// triangulo 1 de 4 frente
	glColor3ub(128, 0,0); //vermelho
	glVertex3f(1.0, -0.5, 1.0);
	glColor3ub(255,255,0); //branco
	glVertex3f(1.0, -1.0, 0);

	glColor3ub(0, 128, 0); //verde
	glVertex3f(2.0, -0.5, 0);
	glColor3ub(0, 0, 128); //azul
	glVertex3f(2.0, -1.0, 1);

	glEnd();

	glutSwapBuffers(); // trocar a matriz da tela por esta aqui.
}
