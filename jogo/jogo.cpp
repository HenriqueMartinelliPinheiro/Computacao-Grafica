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
} Objetos;

void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char tecla, int x, int y);
void submarino();
void peixeLeft(Objetos*, int, float xLeft, float xRight);
void peixeRight(Objetos*, int, float xLeft, float xRight);
Objetos* alocarObjetos();
Objetos** alocarVetorPeixes();
Objetos** alocarVetorMergulhadores();
void criarObjetos();
void definirPeixe();
void anima(int);
void verificarColisaoPeixes();
void verificarColisao();
void alocarMemoria();
void definirMergulhador();

Objetos** peixesLeft;
Objetos** peixesRight;
Objetos** mergulhadorLeft;
Objetos** mergulhadorRight;
float transH = 30;
float transV = 80;
int tamPeixes = 3;
int tamMergulhadores = 3;
float transHInicial = transH;
float transVInicial = transV;
int oxigenio = 10;
int vida = 3;
int pontuacao = 0;
int alturaPeixesLeft[3] = { -130, -30, 70 };
int alturaPeixesRight[3] = { -170, -70, 30 };
int circ_pnt = 300;
float xLeftSub = 999;
float xRightSub = -999;
float yTopSub = 100;
float yDownSub = 80;


int main(int argc, char** argv)
{

	alocarMemoria();
	criarObjetos();
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

void alocarMemoria() {
	peixesLeft = alocarVetorPeixes();
	peixesRight = alocarVetorPeixes();
	mergulhadorLeft = alocarVetorMergulhadores();
	mergulhadorRight = alocarVetorMergulhadores();
}

Objetos** alocarVetorPeixes() {
	Objetos** peixesLeft;
	peixesLeft = (Objetos**)malloc(sizeof(Objetos*) * tamPeixes);
	return peixesLeft;
}

Objetos** alocarVetorMergulhadores() {
	Objetos** peixesLeft;
	peixesLeft = (Objetos**)malloc(sizeof(Objetos*) * tamPeixes);
	return peixesLeft;
}

void criarObjetos() {
	for (int i = 0; i < tamPeixes; i++) {
		peixesLeft[i] = alocarObjetos();
		peixesRight[i] = alocarObjetos();
		mergulhadorLeft[i] = alocarObjetos();
		mergulhadorRight[i] = alocarObjetos();
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
			transH = transH - 2;
			//printf("\n o valor de translacao H e %.2f\n", transH);
		}
	}
	if (tecla == 'd')
	{
		if ((transH + xRightSub) < 300) {
			transH = transH + 2;
			//printf("\n o valor de translacao H e %.2f\n", transH);
		}

	}

	if (tecla == 'w') {
		if (transV < 80) {
			transV += 2;
			//printf("\n o valor de translacao e  V %.2f\n", transV);
		}

	}

	if (tecla == 's') {
		if (transV > -200) {
			transV -= 2;
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

void peixeLeft(Objetos* peixe, int altura, float xLeft, float xRight) {

	peixe->xLeft = xLeft;
	peixe->xRight = xRight;
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

void peixeRight(Objetos* peixe, int altura, float xLeft, float xRight) {

	peixe->xLeft = xLeft;
	peixe->xRight = xRight;
	peixe->yTop = altura;
	peixe->yDown = altura - 20;

	glBegin(GL_TRIANGLES);
	glColor3ub(237, 216, 146);  // cor
	glVertex2f(peixe->xRight - 10, peixe->yDown);
	glVertex2f(peixe->xRight - 10, peixe->yTop);
	glVertex2f(peixe->xLeft, peixe->yTop - 10);
	glEnd();

	glColor3ub(235, 192, 52);  // cor
	glBegin(GL_TRIANGLES);
	glVertex2f(peixe->xRight, peixe->yDown);
	glVertex2f(peixe->xRight, peixe->yTop);
	glVertex2f(peixe->xRight - 20, peixe->yTop - 10);
	glEnd();

	glColor3ub(0, 0, 0);  // cor
	glBegin(GL_POINTS);
	glVertex2f(peixe->xRight - 25, peixe->yTop - 10);
	glEnd();
}

void desenhar()
{
	ceu();
	glPushMatrix();
	definirMergulhador();
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
		peixeLeft(peixesLeft[i], alturaPeixesLeft[i], -345, -305);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(peixesRight[i]->trans, 0, 0);
		peixeRight(peixesRight[i], alturaPeixesRight[i], 305, 345);
		glPopMatrix();
	}
}

Objetos* alocarObjetos() {
	Objetos* peixe = (Objetos*)malloc(sizeof(Objetos));
	peixe->trans = 0;

	return peixe;
}

void mergulhador(Objetos* mergulhador) {
	mergulhador->xLeft = -30;
	mergulhador->xRight = -20;
	mergulhador->yTop = -999;
	mergulhador->yDown = -20;
	glEnable(GL_POINT_SMOOTH);
	glPointSize(6);
	glColor3ub(19, 55, 244);  // cor
	glBegin(GL_POINTS); // cabeça
	glVertex2f(0.0f, 8);
	glEnd();

	// Desenhe o corpo
	glBegin(GL_LINES);
	glVertex2f(0, 5);
	glVertex2f(0, -5);
	glEnd();

	// Desenhe os braços
	glBegin(GL_LINES);
	glVertex2f(0, 4);
	glVertex2f(-5, 4);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0, 4);
	glVertex2f(5, 4);
	glEnd();

	// Desenhe as pernas
	glBegin(GL_LINES);
	glVertex2f(0, -5);
	glVertex2f(-5, -10);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(0, -5);
	glVertex2f(5, -10);
	glEnd();

}

void definirMergulhador(){
	for (int i = 0; i < tamMergulhadores; i++){
		mergulhador(mergulhadorLeft[i]);
		mergulhador(mergulhadorRight[i]);
	}
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
	verificarColisaoPeixes();
}

void verificarColisaoPeixes() {
	for (int i = 0; i < tamPeixes; i++)
	{
		if (((yTopSub + transV - transVInicial >= peixesLeft[i]->yDown && yTopSub + transV - transVInicial <= peixesLeft[i]->yTop)
			|| (yDownSub + transV - transVInicial <= peixesLeft[i]->yTop && yDownSub + transV - transVInicial >= peixesLeft[i]->yDown))) {
			if ((xRightSub + transH - transHInicial >= peixesLeft[i]->xLeft + peixesLeft[i]->trans && xRightSub + transH - transHInicial <= peixesLeft[i]->xRight + peixesLeft[i]->trans)
				|| (xLeftSub + transH - transHInicial <= peixesLeft[i]->xRight + peixesLeft[i]->trans && xLeftSub + transH - transHInicial >= peixesLeft[i]->xLeft + peixesLeft[i]->trans)) {
				transH = transHInicial;
				transV = transVInicial;
				peixesLeft[i]->trans = 0;
			}
		}
		if (((yTopSub + transV - transVInicial >= peixesRight[i]->yDown && yTopSub + transV - transVInicial <= peixesRight[i]->yTop)
			|| (yDownSub + transV - transVInicial <= peixesRight[i]->yTop && yDownSub + transV - transVInicial >= peixesRight[i]->yDown))) {
			if ((xRightSub + transH - transHInicial >= peixesRight[i]->xLeft + peixesRight[i]->trans && xRightSub + transH - transHInicial <= peixesRight[i]->xRight + peixesRight[i]->trans)
				|| (xLeftSub + transH - transHInicial <= peixesRight[i]->xRight + peixesRight[i]->trans && xLeftSub + transH - transHInicial >= peixesRight[i]->xLeft + peixesRight[i]->trans)) {
				transH = transHInicial;
				transV = transVInicial;
				peixesRight[i]->trans = 0;
			}
		}
	}
}
void anima(int valor)
{
	for (int i = 0; i < tamPeixes; i++)
	{
		printf("Translate direita %i : %f, Translate: %f, Soma: %f \n", i, peixesRight[i]->xRight, peixesRight[i]->trans, peixesRight[i]->trans + peixesRight[i]->xRight);
		if ((peixesLeft[i]->xLeft + peixesLeft[i]->trans) >= 300) {
			peixesLeft[i]->trans = 0;
		}
		if ((peixesRight[i]->xRight + peixesRight[i]->trans) <= -300) {
			peixesRight[i]->trans = 0;
		}
		peixesLeft[i]->trans += 5;
		peixesRight[i]->trans -= 5;
	}
	glutPostRedisplay();
	glutTimerFunc(150, anima, 1);
}
