#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define janela_altura 480
#define janela_largura 640
int on = 1;
int onc = 0;
float x = 0.0, y = 0.0, z = 0.0;
void reshape(GLsizei largura, GLsizei altura);
void display();
void keyboard(unsigned char key, int a, int b);
void conf_luz();
int main(int argc, char** argv)
{
	glutInit(&argc, argv); // Ligar GLUT
	glutInitDisplayMode(GLUT_DOUBLE); // Display com Duplo Buffer
	glutInitWindowSize(janela_largura, janela_altura); // tamanho da janela
	glutInitWindowPosition(50, 50); // Pos. onde surge a janela
	glutCreateWindow("iluminacao"); // Criar Janela
	conf_luz(); // configuração de luz
	glutDisplayFunc(display); // imagem
	glutReshapeFunc(reshape); // config telas
	glutKeyboardFunc(keyboard); // funcoes de teclado
	glutMainLoop(); // loop
	return 0;
}
void conf_luz(void)
{
	float ambiente[] = { 0.0, 0.0, 0.0, 1.0 };
	float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float specular[] = { 1.0, 1.0, 1.0, 1.0 };
	float posicao[] = { 0.0 + sin(x * 2 * 3.14 / 360), 3.0, 2.0 + sin(x * 2 * 3.14 / 360), 0.0 };
	float lmodel_ambiente[] = { 0.2, 0.2, 0.2, 1.0 };
	float local_view[] = { 0.0 };
	glClearColor(0.0, 0.1, 0.1, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, posicao);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiente);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHT0);

	float diffuse2[] = { 0.11764705882, 0.50588235294, 0.69019607843, 1.0 };
	float posicao2[] = { 2.0 + sin(x * 2 * 3.14 / 360), 3.0, 0.0 + sin(x * 2 * 3.14 / 360), 0.0 };
	glClearColor(0.0, 0.1, 0.1, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse2);
	glLightfv(GL_LIGHT1, GL_POSITION, posicao2);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambiente);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
	glEnable(GL_LIGHTING);
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
void display()
{
	float padrao[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat ambient_color[] = { 0.23125f, 0.23125f, 0.23125f, 1.0f };
	GLfloat diffuse_color[] = { 0.2775f, 0.2775f, 0.2775f, 1.0f };
	GLfloat specular_color[] = { 0.773911f, 0.773911f, 0.773911f, 1.0f };
	float alto_brilho[] = { 100.0 };
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // executa a limpesa
	glMatrixMode(GL_MODELVIEW); // operando com a camera de modelos

	glLoadIdentity();

	glTranslatef(1.5f, 0.0f, -6.0f);
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_color);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_color);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular_color);
	glMaterialfv(GL_FRONT, GL_SHININESS, alto_brilho);
	glMaterialfv(GL_FRONT, GL_EMISSION, padrao);
	glutSolidSphere(1.0, 60, 60);
	glTranslatef(-2.5f, 0.0f, -4.0f); 
	glRotatef(145.0, 8.0, -5.0, 0.0);

	glutSolidCube(2.0f);

	glutSwapBuffers();
}
void keyboard(unsigned char key, int a, int b)
{
	switch (key)
	{
	case 'x':
	{
		x+= 10.0;
		conf_luz();

		if (!on)
		{
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			on = 0;
		}
		else
		{
			if (onc)
			{
				glEnable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
			}
			else
			{
				glEnable(GL_LIGHT1);
				glDisable(GL_LIGHT0);
			}
			on = 1;
		}

		glutPostRedisplay();
	} break;
	case 'o':
	{
		if (on)
		{
			glDisable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			on = 0;
		}
		else
		{
			if (onc)
			{
				glEnable(GL_LIGHT0);
				glDisable(GL_LIGHT1);
			}
			else
			{
				glEnable(GL_LIGHT1);
				glDisable(GL_LIGHT0);
			}
			on = 1;
		}
		glutPostRedisplay();
	} break;
	case 'c':
	{
		if (onc)
		{
			glEnable(GL_LIGHT0);
			glDisable(GL_LIGHT1);
			onc = 0;
		}
		else
		{
			glEnable(GL_LIGHT1);
			glDisable(GL_LIGHT0);
			onc = 1;
		}
		glutPostRedisplay();
	} break;
	}
}
