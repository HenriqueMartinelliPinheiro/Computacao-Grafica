
// aula 3 ----- primitivas programa minimo
//////////////////////////////////////////

#include <stdlib.h>
#include <GL/glut.h>

#define alturra_janela 400
#define largura_janela 400

void keyboard(unsigned char key, int x, int y);
void resize(GLsizei w, GLsizei h);
void display(void);


int main(int argc, char** argv)
{
    glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

    glutInitWindowSize(largura_janela, alturra_janela);  // tamanho da janela

    //glutFullScreen();  // full screen

    glutInitWindowPosition(10, 300); // posicao inicial da janela

    glutCreateWindow("Casa");   /// cria a janela

    glutKeyboardFunc(&keyboard);

    glutReshapeFunc(&resize); // 

    glutDisplayFunc(display);

    glutMainLoop();

    return EXIT_SUCCESS;
}


void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '\x1B':
        exit(EXIT_SUCCESS);
        break;
    }
}

void resize(GLsizei w, GLsizei h)
{

    if (h == 0) h = 1;  // Evita a divisao por zero

    glViewport(0, 0, w, h);  // Especifica as dimensões da Viewport

    // Inicializa o sistema de coordenadas
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Estabelece a janela de seleção (left, right, bottom, top)
    if (w <= h)
    {
        gluOrtho2D(0.0f, largura_janela, 0.0f, alturra_janela * h / w);
    }
    else
    {
        gluOrtho2D(0.0f, largura_janela * w / h, 0.0f, alturra_janela);
    }
    glTranslatef(largura_janela / 2, alturra_janela / 2, 0.0);

    glMatrixMode(GL_MODELVIEW);


}

void aviao(){
    glBegin(GL_QUADS);
    glColor3ub(124, 124, 124);
    glVertex2f(-100, 140);
    glVertex2f(-100, 100);
    glVertex2f(20, 100);
    glVertex2f(20, 140);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(124, 124, 124);
    glVertex2f(-60, 100);
    glVertex2f(-40, 60);
    glVertex2f(-20, 100);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(124, 124, 124);
    glVertex2f(0, 100);
    glVertex2f(20, 180);
    glVertex2f(20, 100);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(124, 124, 124);
    glVertex2f(-100, 140);
    glVertex2f(-130, 120);
    glVertex2f(-100, 100);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(102, 255, 255);
    glVertex2f(-100, 140);
    glVertex2f(-100, 125);
    glVertex2f(-80, 125);
    glVertex2f(-80, 140);
    glEnd();

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(-60, 130);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(-40, 130);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(-20, 130);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(0, 130);
    glEnd();

}

void torre() {
    glBegin(GL_QUADS);
    glColor3ub(64, 64, 64);
    glVertex2f(140, 60);
    glVertex2f(140, -80);
    glVertex2f(200, -80);
    glVertex2f(200, 60);
    glEnd();

//janelas 1

    glPointSize(4);
    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(160, -40);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(160, -20);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(160, 0);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(160, 20);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(160, 40);
    glEnd();

    //janelas 2
    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(180, -40);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(180, -20);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(180, 0);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(180, 20);
    glEnd();

    glBegin(GL_POINTS);
    glColor3ub(102, 255, 255);
    glVertex2f(180, 40);
    glEnd();


    //porta
    glBegin(GL_QUADS);
    glVertex2f(160, -60);
    glVertex2f(160, -80);
    glVertex2f(180, -80);
    glVertex2f(180, -60);
    glEnd();


}

void pista(){
    glBegin(GL_QUADS);
    glColor3ub(160, 160, 160);
    glVertex2f(-200, -200);
    glVertex2f(-200, -80);
    glVertex2f(200, -80);
    glVertex2f(200, -200);
    glEnd();
}

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.003, 0.478, 0.705, 0);  // cor do fundo

    glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo

    pista();
    aviao();
    torre();
    
    glFlush(); // executa o desenho

}

