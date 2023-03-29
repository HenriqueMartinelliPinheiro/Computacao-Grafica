#include <GL/glut.h>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#define xpix 500
#include <cstring>

using namespace std;

float r, g, b, x, y;
bool flag = true;
int counter = 0;

//prototipaçao
void mouse(int button, int state, int mousex, int mousey);


// Função do mouse
void mouse(int button, int state, int mousex, int mousey) {

    //ao clicar com o botão esquerdo, desenha o triângulo
    if (button == GLUT_LEFT_BUTTON
        && state == GLUT_DOWN) {
        flag = true;
        x = mousex;
        y = 600 - mousey;
    }

    // muda a cor do triangulo quando clica com o botao direito
    else if (button == GLUT_RIGHT_BUTTON
        && state == GLUT_DOWN) {
        if (counter > 4) {
            counter = 0;
        }

        counter++;

        // Redisplay
        glutPostRedisplay();
    }
}

// Função para limpar a tela
void keyboard(unsigned char key,
    int x, int y)
{
    switch (key) {
    case 27:
        glutHideWindow();
    }
}

// Função desenha o triângulo
void display(void) {

    //add cor ao triângulo
    float angle_theta;
    if (counter == 1) {
        glColor3f(1, 0, 0);
    }
    else if (counter == 2) {
        glColor3f(0, 1, 0);
    }
    else if (counter == 3) {
        glColor3f(0, 1, 1);
    }
    else if (counter == 4) {
        glColor3f(0.5, 0, 1);
    }
    else if (counter == 5) {

        glColor3f(0, 0.5, 1);
    }

    // Matrix mode
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // Given the coordinates
    gluOrtho2D(0.0, 800.0, 0.0, 600.0);

    // If the flag is true
    if (flag) {

        // Begin the pointer

        glBegin(GL_TRIANGLES);
        glVertex2f(x - 20, y - 20);
        glVertex2f(x + 20, y - 20);
        glVertex2f(x, y + 20);

        glEnd();

        //glBegin(GL_POLYGON);

        //// Iterate through all the
        //// 360 degrees
        //for (int i = 0; i < 360; i++) {

        //    // Find the angle
        //    angle_theta = i * 3.142 / 180;
        //    glVertex2f(x + 50 * cos(angle_theta),
        //        y + 50 * sin(angle_theta));
        //}

        //// Sets vertex
        //glEnd();
    }

    // Flushes the frame buffer
    // to the screen
    glFlush();
}

// Driver Code
int main(int argc, char** argv)
{

    glutInit(&argc, argv);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Creates the window as
    // specified by the user
    glutCreateWindow("Circle Creation "
        "on mouse click");

    // Sets the background color
    glClearColor(0, 0, 0, 0);

    // Clears the frame buffer
    glClear(GL_COLOR_BUFFER_BIT);

    // Links display event with the
    // display event handler(display)
    glutDisplayFunc(display);

    // Mouse event handler
    glutMouseFunc(mouse);

    // Keyboard event handler
    glutKeyboardFunc(keyboard);

    // Loops the current event
    glutMainLoop();
}
