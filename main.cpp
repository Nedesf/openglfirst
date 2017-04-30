#include <GL/freeglut.h>
#include <iostream>
GLdouble eyex = 0;
GLdouble eyey = 0;
GLdouble eyez = 0;
GLint centerx = 0;
GLint centery = 0;
GLint centerz = -90;
GLint sensitivity = 25;
GLint old_x = 0;
GLint old_y = 0;
enum
{
    LEFT,
    RIGHT,
    UP,
    DOWN
};
void Display()
{
    glClearColor(1, 1, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyex, eyey, eyez, centerx, centery, centerz, 0, 90, 0);
    glTranslatef(0, 0, -3);
    glColor3f(0, 0, 0);
    glutWireCube(1);
    glFlush();
    glutSwapBuffers();
}
void Reshape(int width, int height)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = 1;
    if(height > 0)
        aspect = width/height;
    gluPerspective(90, aspect, 1, 5);
    Display();
}
void LookAroundXZ(int &cntrx, int &cntrz, short dir, int angle)
{
    short anglebit = angle;
    do
    {
        if(angle > 90)
        {
            angle -= 90;
            anglebit = 90;
        }
        if(dir == LEFT)
        {
            if(cntrz < 0 || cntrx == 90)
                cntrx -= anglebit;
            else if(cntrz > 0 || cntrx == -90)
                cntrx += anglebit;
            if(cntrx > 0 || cntrz == 90 || (cntrx == 0 && cntrz == -89))
                cntrz -= anglebit;
            else if(cntrx < 0 || cntrz == -90 || (cntrx == 0 && cntrz == 89))
                cntrz += anglebit;
        }
        else if(dir == RIGHT)
        {
            if(cntrz > 0 || cntrx == 90)
                cntrx -= anglebit;
            else if(cntrz < 0 || cntrx == -90)
                cntrx += anglebit;
            if(cntrx < 0 || cntrz == 90 || (cntrx == 0 && cntrz == -89))
                cntrz -= anglebit;
            else if(cntrx > 0 || cntrz == -90 || (cntrx == 0 && cntrz == 89))
                cntrz += anglebit;
        }
        if(cntrx > 90)
            cntrx = 90 - (cntrx - 90);
        else if(cntrx < -90)
            cntrx = -90 - (cntrx + 90);
        if(cntrz > 90)
            cntrz = 90 - (cntrz - 90);
        else if(cntrz < -90)
            cntrz = -90 - (cntrz + 90);
    }while(angle > 90);
}
void LookUpDown(int &cntry, short dir, int angle)
{
    if(dir == UP && cntry < 90)
        cntry += angle;
    else if(dir == DOWN && cntry > -90)
        cntry -= angle;
    if(cntry > 90)
        cntry = 90;
    else if(cntry < -90)
        cntry = -90;

}
int func(int value)
{
    if(value < 0)
        return value - value * -2;
}
int zamienZnaki(int value)
{
    if(value > 0)
    {
        return value - value * 2;
    }
    return value + value * -2;
}
void Keyboard(unsigned char key, int width, int height)
{
    if(key == 'w')
    {
        std::cout << "Test: " << centerx << "       " << centerz <<std::endl;
        eyex += (double)centerx / 90 / 10;
        eyez += (double)centerz / 90 / 10;
        std::cout << eyex << "      " << eyez << std::endl;
    }
    else if(key == 's')
    {
        eyex += (double)zamienZnaki(centerx) / 90 / 10;
        eyez += (double)zamienZnaki(centerz) / 90 / 10;
    }
    else if(key == 'a')
    {
        int leftx = centerx;
        int leftz = centerz;
        LookAroundXZ(leftx, leftz, LEFT, 90);
        eyex += (double)leftx / 90 / 10;
        eyez += (double)leftz / 90 / 10;
    }
    else if(key == 'd')
    {
        int rightx = centerx;
        int rightz = centerz;
        LookAroundXZ(rightx, rightz, RIGHT, 90);
        eyex += (double)rightx / 90 / 10;
        eyez += (double)rightz / 90 / 10;
    }
    else if(key == 'l')
        LookAroundXZ(centerx, centerz, RIGHT, 1);
    else if(key == 'k')
        LookAroundXZ(centerx, centerz, LEFT, 1);
    else if(key == 'u')
        LookUpDown(centery, UP, 1);
    else if(key == 'j')
        LookUpDown(centery, DOWN, 1);
    glutPostRedisplay();
}
void MouseMotion(int x, int y)
{
    int angle_x = 0, angle_y =  0;
    if(x - 200 != 0)
        angle_x = (x - 200);
    if(y - 200 != 0)
        angle_y = (y - 200);
    if(angle_x != 0 || angle_y != 0)
    std::cout << angle_x << "   " << angle_y << std::endl;
    LookAroundXZ(centerx, centerz, RIGHT, angle_x);
    LookUpDown(centery, UP, angle_y);
    Display();
    old_x = x;
    old_y = y;
    glutWarpPointer(200, 200);
}
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Projekcik");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutPassiveMotionFunc(MouseMotion);
    //glutSetCursor(GLUT_CURSOR_NONE);
    glutMainLoop();
}
