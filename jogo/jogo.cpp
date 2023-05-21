///  colisao de quadrados
//////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <limits.h>

#define janela_altura 500
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
void verificarColisaoMergulhadores();
void verificarColisoes();
void alocarMemoria();
void definirMergulhador();
void criarMergulhadorLeft(Objetos*, int);
void criarMergulhadorRight(Objetos*, int);
void desenharCoracoes();
void desenharBolhas();
void reduzirOxigenio(int);
void perderVida();

Objetos** peixesLeft;
Objetos** peixesRight;
Objetos** mergulhadorLeft;
Objetos** mergulhadorRight;
float transH = 30;
float transV = 110;
int tamPeixes = 3;
int tamMergulhadores = 2;
float transHInicial = transH;
float transVInicial = transV;
int oxigenio = 10;
int contadorMergulhadores = 0;
int vida = 3;
int pontuacao = 0;
int alturaPeixesLeft[3] = { -130, -30, 70 };
int alturaPeixesRight[3] = { -170, -70, 30 };
int alturaMergulhadoresLeft[2] = { 100, -105 };
int alturaMergulhadoresRight[2] = { -0, -205 };
int circ_pnt = 300;
float xLeftSub = 999;
float xRightSub = -999;
float yTopSub = 130;
float yDownSub = 110;

int main(int argc, char** argv)
{

	alocarMemoria();
	criarObjetos();
	glutInit(&argc, argv);	// suporte a janelas

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// PADRAO DE CORES

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela
	glutInitWindowPosition(100, 100); // posicao que surge a janela
	glutCreateWindow("Sea Quest"); // cria janela

	//glutFullScreen();
	glutKeyboardFunc(&keyboard);  // chama teclado
	glutReshapeFunc(tela);  // configura a tela
	glutDisplayFunc(display);
	glutTimerFunc(150, anima, 1);
	glutTimerFunc(2000, reduzirOxigenio, 1);
	glutMainLoop(); // redesenhar

	return(0);
}

void alocarMemoria() {
	peixesLeft = alocarVetorPeixes();
	peixesRight = alocarVetorPeixes();
	mergulhadorLeft = alocarVetorMergulhadores();
	mergulhadorRight = alocarVetorMergulhadores();
}

Objetos** alocarVetorPeixes() { //aloca memoria pros objetos
	Objetos** peixesLeft;
	peixesLeft = (Objetos**)malloc(sizeof(Objetos*) * tamPeixes);
	return peixesLeft;
}

Objetos** alocarVetorMergulhadores() { //aloca memoria para os mergulhadores
	Objetos** peixesLeft;
	peixesLeft = (Objetos**)malloc(sizeof(Objetos*) * tamPeixes);
	return peixesLeft;
}

void criarObjetos() {   //cria os vetores do objeto
	for (int i = 0; i < tamPeixes; i++) {
		peixesLeft[i] = alocarObjetos();
		peixesRight[i] = alocarObjetos();
		mergulhadorLeft[i] = alocarObjetos();
		mergulhadorRight[i] = alocarObjetos();
	}
}

void keyboard(unsigned char tecla, int x, int y)
{
	if (vida>0){
	if (tecla == 'a')
	{
		if ((transH - xLeftSub) > (-300)) {
			transH = transH - 2;
		}
	}
	if (tecla == 'd')
	{
		if ((transH + xRightSub) < 300 + transHInicial) {
			transH = transH + 2;
		}
	}

	if (tecla == 'w') {
		if (transV < 110) {
			transV += 2;
		}
	}

	if (tecla == 's') {
		if (transV > -250) {
			transV -= 2;
		}

	}
	}
	glutPostRedisplay();
}

void ceu() { //desenha o ceu
	glBegin(GL_QUADS);
	glColor3f(0.26, 0.9, 0.96);  // cor
	glVertex2f(-300, 250);
	glVertex2f(300, 250);
	glVertex2f(300, 130);
	glVertex2f(-300, 130);

	glEnd();
}

void submarino() { //desenha o submarino

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
			xRightSub = (cos(ang) * raioX) + 86;
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

void peixeLeft(Objetos* peixe, int altura, float xLeft, float xRight) { //desenha os peixes da esquerda

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

void peixeRight(Objetos* peixe, int altura, float xLeft, float xRight) { //desenha os peixes da direita

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

void criarMergulhadorLeft(Objetos* mergulhador, int altura) {
	mergulhador->xLeft = -315;
	mergulhador->xRight = -305;
	mergulhador->yTop = altura;
	mergulhador->yDown = altura - 18;

	glEnable(GL_POINT_SMOOTH);
	glPointSize(6);
	glColor3ub(19, 55, 244);  // cor
	glBegin(GL_POINTS); // cabeça
	glVertex2f(mergulhador->xRight - 5, mergulhador->yTop);
	glEnd();

	// Desenhe o corpo
	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yTop - 3);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yDown + 5);
	glEnd();

	// Desenhe os braços
	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yTop - 4);
	glVertex2f(mergulhador->xLeft, mergulhador->yTop - 4);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yTop - 4);
	glVertex2f(mergulhador->xRight, mergulhador->yTop - 4);
	glEnd();

	// Desenhe as pernas
	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yDown + 5);
	glVertex2f(mergulhador->xLeft, mergulhador->yDown);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yDown + 5);
	glVertex2f(mergulhador->xRight, mergulhador->yDown);
	glEnd();

}

void criarMergulhadorRight(Objetos* mergulhador, int altura) {
	mergulhador->xLeft = 305; //-5
	mergulhador->xRight = 315; //5
	mergulhador->yTop = altura; //8
	mergulhador->yDown = altura - 18;//-10

	glEnable(GL_POINT_SMOOTH);
	glPointSize(6);
	glColor3ub(19, 55, 244);  // cor
	glBegin(GL_POINTS); // cabeça
	glVertex2f(mergulhador->xRight - 5, mergulhador->yTop);
	glEnd();

	// Desenhe o corpo
	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yTop - 3);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yDown + 5);
	glEnd();

	// Desenhe os braços
	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yTop - 4);
	glVertex2f(mergulhador->xLeft, mergulhador->yTop - 4);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yTop - 4);
	glVertex2f(mergulhador->xRight, mergulhador->yTop - 4);
	glEnd();

	// Desenhe as pernas
	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yDown + 5);
	glVertex2f(mergulhador->xLeft, mergulhador->yDown);
	glEnd();

	glBegin(GL_LINES);
	glVertex2f(mergulhador->xRight - 5, mergulhador->yDown + 5);
	glVertex2f(mergulhador->xRight, mergulhador->yDown);
	glEnd();

}

void definirMergulhador() {
	for (int i = 0; i < tamMergulhadores; i++) {
		glPushMatrix();
		glTranslatef(mergulhadorLeft[i]->trans, 0, 0);
		criarMergulhadorLeft(mergulhadorLeft[i], alturaMergulhadoresLeft[i]);
		glPopMatrix();
		glPushMatrix();
		glTranslatef(mergulhadorRight[i]->trans, 0, 0);
		criarMergulhadorRight(mergulhadorRight[i], alturaMergulhadoresRight[i]);
		glPopMatrix();
	}
}

void desenharCoracoes() {
	int x1 = -300, x2 = -290, x3 = -280, y1 = 250, y2 = 240, y3 = 230, i = vida;
	for (i = 0; i < vida; i++){
		glColor3ub(255, 0, 0);
		glBegin(GL_TRIANGLES);
		// Triângulo esquerdo do coração
		glVertex2f(x1, y2);
		glVertex2f(x1, y1);
		glVertex2f(x2, y2);

		// Triângulo direito do coração
		glVertex2f(x2, y2);
		glVertex2f(x3, y2);
		glVertex2f(x3, y1);

		glVertex2f(x1, y2);
		glVertex2f(x2, y3);
		glVertex2f(x3, y2);
		glEnd();

		x1 += 30, x2 += 30, x3 += 30;
	}
}

void reduzirOxigenio(int valor) {
	if (transV<110 && oxigenio>0) {
		oxigenio--;
	}
	if (oxigenio==0) {
		perderVida();
	}
	glutPostRedisplay();
	glutTimerFunc(2000, reduzirOxigenio, 1);
}

void perderVida() {
	vida--;
	transH = transHInicial;
	transV = transVInicial;
}
void desenharBolhas() {
	float ang;
	float raioX = 7;
	float raioY=7;
	float transX = -290;
	for (int i = 0; i < oxigenio; i++){
		glPushMatrix();
		glTranslatef(transX, 215, 0);
		glBegin(GL_POLYGON);
		glColor3ub(235, 235, 255);
		for (int i = 0; i < circ_pnt; i++)
		{
			ang = (2 * PI * i) / circ_pnt;
			glVertex2f(cos(ang) * raioX, sin(ang) * raioY);
		}
		glEnd();
		glPopMatrix();
		transX += 14;
	}
}

void verificarColisoes() {
	verificarColisaoPeixes();
	verificarColisaoMergulhadores();
}

void verificarColisaoPeixes() { //verifica a colisao dos peixes com o submarino
	for (int i = 0; i < tamPeixes; i++){
		if (((yTopSub + transV - transVInicial >= peixesLeft[i]->yDown && yTopSub + transV - transVInicial <= peixesLeft[i]->yTop)
			|| (yDownSub + transV - transVInicial <= peixesLeft[i]->yTop && yDownSub + transV - transVInicial >= peixesLeft[i]->yDown))) {
			if ((xRightSub + transH - transHInicial >= peixesLeft[i]->xLeft + peixesLeft[i]->trans && xRightSub + transH - transHInicial <= peixesLeft[i]->xRight + peixesLeft[i]->trans)
				|| (xLeftSub + transH - transHInicial <= peixesLeft[i]->xRight + peixesLeft[i]->trans && xLeftSub + transH - transHInicial >= peixesLeft[i]->xLeft + peixesLeft[i]->trans)) {
				transH = transHInicial;
				transV = transVInicial;
				peixesLeft[i]->trans = 0;
				if (vida > 0) {
					perderVida();
				}
			}
			else if (peixesLeft[i]->xLeft + peixesLeft[i]->trans > xLeftSub + transH - transHInicial && peixesLeft[i]->xRight + peixesLeft[i]->trans < xRightSub + transH - transHInicial) {
				transH = transHInicial;
				transV = transVInicial;
				peixesLeft[i]->trans = 0;
				if (vida > 0) {
					perderVida();
				}
			}
		}
		if (((yTopSub + transV - transVInicial >= peixesRight[i]->yDown && yTopSub + transV - transVInicial <= peixesRight[i]->yTop)
			|| (yDownSub + transV - transVInicial <= peixesRight[i]->yTop && yDownSub + transV - transVInicial >= peixesRight[i]->yDown))) {
			if ((xRightSub + transH - transHInicial >= peixesRight[i]->xLeft + peixesRight[i]->trans && xRightSub + transH - transHInicial <= peixesRight[i]->xRight + peixesRight[i]->trans)
				|| (xLeftSub + transH - transHInicial <= peixesRight[i]->xRight + peixesRight[i]->trans && xLeftSub + transH - transHInicial >= peixesRight[i]->xLeft + peixesRight[i]->trans)) {
				transH = transHInicial;
				transV = transVInicial;
				peixesRight[i]->trans = 0;
				if (vida > 0) {
					perderVida();
				}
			}else if (peixesRight[i]->xLeft + peixesRight[i]->trans > xLeftSub + transH - transHInicial && peixesRight[i]->xRight + peixesRight[i]->trans < xRightSub + transH - transHInicial) {
				transH = transHInicial;
				transV = transVInicial;
				peixesRight[i]->trans = 0;
				if (vida > 0) {
					perderVida();
				}
			}
		}
	}
}

void verificarColisaoMergulhadores() {
	for (int i = 0; i < tamMergulhadores; i++)
	{
		if (((yTopSub + transV - transVInicial >= mergulhadorLeft[i]->yDown && yTopSub + transV - transVInicial <= mergulhadorLeft[i]->yTop)
			|| (yDownSub + transV - transVInicial <= mergulhadorLeft[i]->yTop && yDownSub + transV - transVInicial >= mergulhadorLeft[i]->yDown))) {
			if ((xRightSub + transH - transHInicial >= mergulhadorLeft[i]->xLeft + mergulhadorLeft[i]->trans && xRightSub + transH - transHInicial <= mergulhadorLeft[i]->xRight + mergulhadorLeft[i]->trans)
				|| (xLeftSub + transH - transHInicial <= mergulhadorLeft[i]->xRight + mergulhadorLeft[i]->trans && xLeftSub + transH - transHInicial >= mergulhadorLeft[i]->xLeft + mergulhadorLeft[i]->trans)) {
				mergulhadorLeft[i]->trans = 0;
				if (contadorMergulhadores< 5) {
					contadorMergulhadores++;
				}
			}
			else if (mergulhadorLeft[i]->xLeft + mergulhadorLeft[i]->trans > xLeftSub + transH - transHInicial && mergulhadorLeft[i]->xRight + mergulhadorLeft[i]->trans < xRightSub + transH - transHInicial) {
				mergulhadorLeft[i]->trans = 0;
				if (contadorMergulhadores < 5) {
					contadorMergulhadores++;
				}
			}
		}

		if (((yTopSub + transV - transVInicial >= mergulhadorRight[i]->yDown && yTopSub + transV - transVInicial <=mergulhadorRight[i]->yTop)
			|| (yDownSub + transV - transVInicial <= mergulhadorRight[i]->yTop && yDownSub + transV - transVInicial >= mergulhadorRight[i]->yDown))) {
			if ((xRightSub + transH - transHInicial >= mergulhadorRight[i]->xLeft + mergulhadorRight[i]->trans && xRightSub + transH - transHInicial <= mergulhadorRight[i]->xRight + mergulhadorRight[i]->trans)
				|| (xLeftSub + transH - transHInicial <= mergulhadorRight[i]->xRight + mergulhadorRight[i]->trans && xLeftSub + transH - transHInicial >= mergulhadorRight[i]->xLeft + mergulhadorRight[i]->trans)) {
				mergulhadorRight[i]->trans = 0;
				if (contadorMergulhadores < 5) {
					contadorMergulhadores++;
				}
			}
			else if (mergulhadorRight[i]->xLeft + mergulhadorRight[i]->trans > xLeftSub + transH - transHInicial && mergulhadorRight[i]->xRight + mergulhadorRight[i]->trans < xRightSub + transH - transHInicial) {
				mergulhadorRight[i]->trans = 0;
				if (contadorMergulhadores < 5) {
					contadorMergulhadores++;
				}
			}
		}
	}
}
void anima(int valor)  //animacao
{
	for (int i = 0; i < tamPeixes; i++)
	{
		//printf("Translate direita %i : %f, Translate: %f, Soma: %f \n", i, peixesRight[i]->xRight, peixesRight[i]->trans, peixesRight[i]->trans + peixesRight[i]->xRight);
		if ((peixesLeft[i]->xLeft + peixesLeft[i]->trans) >= 300) {
			peixesLeft[i]->trans = 0;
		}
		if ((peixesRight[i]->xRight + peixesRight[i]->trans) <= -300) {
			peixesRight[i]->trans = 0;
		}

		peixesLeft[i]->trans += 5;
		peixesRight[i]->trans -= 5;
	}

	for (int i = 0; i < tamMergulhadores; i++) {
		if (mergulhadorLeft[i]->xLeft + mergulhadorLeft[i]->trans > 300) {
			mergulhadorLeft[i]->trans = 0;
		}
		mergulhadorLeft[i]->trans += 3;

		if (mergulhadorRight[i]->xRight + mergulhadorRight[i]->trans < -300) {
			mergulhadorRight[i]->trans = 0;
		}
		mergulhadorRight[i]->trans -= 3;
	}

	glutPostRedisplay();
	glutTimerFunc(150, anima, valor);
}

void desenhar() //desenha tudo
{
	ceu();

	glPushMatrix();
	submarino();
	glPopMatrix();
	definirMergulhador();
	verificarColisoes();
	definirPeixe();
	desenharCoracoes();
	desenharBolhas();
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
