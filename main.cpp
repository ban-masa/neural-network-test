#include "lib.h"

#define W 320
#define H 240

class Neuron neuron;
std::vector<struct pt> stuck;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glFlush();
}

void resize(int w, int h)
{
    glViewport(0, 0, w, h);
    glLoadIdentity();
    glOrtho(-0.5, (GLdouble)w - 0.5, (GLdouble)h - 0.5, -0.5, -1.0, 1.0);
}

void mouse(int button, int state, int x, int y)
{
    struct pt temp;
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                temp.val[0] = (double)x/W;
                temp.val[1] = (double)y/H;
                temp.type = 1.0;
                neuron.data.push_back(temp);
                temp.val[0] = x;
                temp.val[1] = y;
                stuck.push_back(temp);
                glPointSize(5);
                glColor3d(1.0, 0.0, 0.0);
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
                glFlush();
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            std::cout << "x = " << x << " y = " << y << std::endl;
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                temp.val[0] = (double)x/W;
                temp.val[1] = (double)y/H;
                temp.type = 0.0;
                neuron.data.push_back(temp);
                temp.val[0] = x;
                temp.val[1] = y;
                stuck.push_back(temp);

                glPointSize(5);
                glColor3d(0.0, 1.0, 0.0);
                glBegin(GL_POINTS);
                glVertex2i(x, y);
                glEnd();
                glFlush();
            }
            break;
        default:
            break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    double tmp[2];
    switch (key) {
        case 'q':
        case 'Q':
            exit(0);
        case 'a':
            neuron.study();
            break;
        case 'b':
            glPointSize(1);
            for (int i = 0; i < W; i++) {
                for (int j = 0; j < H; j++) {
                    tmp[0] = (double)i/W;
                    tmp[1] = (double)j/H;
                    glBegin(GL_POINTS);
                    if (neuron.output(tmp)) {
                        glColor3d(1.0, 0.0, 0.0);
                    } else {
                        glColor3d(0.0, 1.0, 0.0);
                    }
                    glVertex2i(i, j);
                    glEnd();
                }
            }
            glFlush();
            break;
        case 'c':
            for (int i = 0; i < neuron.data.size(); i++) {
                tmp[0] = neuron.data[i].val[0];
                tmp[1] = neuron.data[i].val[1];
                if (neuron.output(tmp)) {
                    glPointSize(3);
                    glBegin(GL_POINTS);
                    glColor3d(1.0, 1.0, 1.0);
                    glVertex2i(stuck[i].val[0], stuck[i].val[1]);
                    glEnd();
                    glFlush();
                } else {
                    glPointSize(3);
                    glBegin(GL_POINTS);
                    glColor3d(0.0, 0.0, 0.0);
                    glVertex2i(stuck[i].val[0], stuck[i].val[1]);
                    glEnd();
                    glFlush();
                }
            }
            break;
        case 'd':
            neuron.show_para();
            break;
        default:
            break;
    }
}

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char *argv[])
{
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(W, H);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutCreateWindow(argv[0]);
    glutDisplayFunc(display);
    glutReshapeFunc(resize);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
    return 0;
}

