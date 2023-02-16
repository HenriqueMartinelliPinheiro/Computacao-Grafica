
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

void display()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.003, 0.478, 0.705, 0);  // cor do fundo

    glClear(GL_COLOR_BUFFER_BIT);  // limpa a tela com a cor do fundo

    glBegin(GL_QUADS);
    glColor3ub(255, 215, 0);
    glVertex2f(-80, 100);
    glVertex2f(-80, -100);
    glVertex2f(80, -100);
    glVertex2f(80, 100);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(46, 139, 8);
    glVertex2f(-200, -200);
    glVertex2f(-200, -100);
    glVertex2f(200, -100);
    glVertex2f(200, -200);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3ub(227, 58, 38);
    glVertex2f(-80, 100);
    glVertex2f(80, 100);
    glVertex2f(0, 150);
    glEnd();

    glBegin(GL_QUADS);
    glColor3ub(191, 112, 34);
    glVertex2f(-80, -60);
    glVertex2f(-40, -60);
    glVertex2f(-40, -100);
    glVertex2f(-80, -100);
    glEnd();

    glPointSize(7);
    glBegin(GL_POINTS);
    glColor3ub(0, 0, 0);
    glVertex2f(-55, -75);
    glEnd();

    glFlush(); // executa o desenho

}

