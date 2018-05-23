#include <GL/glew.h>

#if defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#include <GL/wglew.h>
#endif

#if defined(__APPLE__) || defined(MACOSX)
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include <iostream>

using namespace std;  
  

//<<<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>>>
 void myInit(void)
 {
    glClearColor(0.0, 0.0, 0.0, 0.0);      // 设置背景颜色为亮白
    glColor3f(1.0f, 1.0f, 1.0f);           // 设置绘制颜色为黑
     glPointSize(4.0);                    //设置点的大小为4*4像素
    glMatrixMode(GL_PROJECTION);// 设置合适的投影矩阵-以后解释 
    glLoadIdentity();// 以后解释
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);// 以后解释
 };
//<<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>
// 重绘函数
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);     // 清屏幕 
    glBegin(GL_POINTS);
        glVertex2i(100, 50);         // 绘制若干个点
        glVertex2i(100, 130);
        glVertex2i(150, 130);
    glEnd();    
    glFlush();                         // 将所有输出到显示屏上 
};
//<<<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
    glutInit(&argc, argv);          // 初始化工具包
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 设置显式模式
    glutInitWindowSize(640,480);     // 设置窗口大小
    glutInitWindowPosition(100, 150); // 设置窗口位置
    glutCreateWindow("my first attempt"); // 打开屏幕窗口
    glutDisplayFunc(myDisplay);     // 注册绘制函数
    myInit();                   
    glutMainLoop();              // 进入主循环
};