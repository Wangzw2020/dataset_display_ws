#include "ros/ros.h"
#include <GL/glut.h>
#include "data_loader.h"

string dataset_txt = "/home/wzw/wks/dataset_display_ws/src/EWAP_display/src/ewap_dataset/seq_eth/obsmat.txt";

//string dataset_txt = "/home/wzw/wks/dataset_display_ws/src/EWAP_display/src/ewap_dataset/seq_hotel/obsmat.txt"

GLsizei winWidth = 1600;
GLsizei winHeight = 900;
bool act = false;
double now_frame;
Data_loader data;

void drawPed();
void drawCircle(float x, float y, float z, float r, Color color, int slices = 90);

void init();
void display();
void update();
void reshape(int width, int height);
void normalKey(unsigned char key, int xMousePos, int yMousePos);

int main(int argc, char *argv[])
{
	data.openFile(dataset_txt);
	now_frame = data.getDataset()[0].frame_time;
	cout << "start frame: " << now_frame << endl;
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("dataset display");
	init();
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(normalKey);
	glutIdleFunc(update);
	glutMainLoop();

	return 0;
}

void init(void)
{
	GLfloat gnrlAmbient[] = { 0.8F, 0.8F, 0.8F, 1.0 };	//一般光强度
	GLfloat lghtDiffuse[] = { 0.7F, 0.7F, 0.7F, 1.0 };	//物体光强度
	GLfloat lghtPosition[] = { 4.0, -4.0, 4.0, 0.0 };	//灯光位置
	
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);

	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, gnrlAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lghtDiffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, lghtPosition);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_LINE_SMOOTH);

	return;
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(10.0, 0.0, 50.0,		//相机位置
			  10.0, 0.0, 0.0,		//相机镜头方向对准物体在世界坐标位置
			  10.0, 1.0, 0.0);		//镜头向上方向在世界坐标的方向

	glPushMatrix();
	glScalef(1.0, 1.0, 1.0);
	
	drawPed();
	
	
	glutSwapBuffers();
}

void update()
{
	double currTime, frameTime;
	static double prevTime;
	
	currTime = glutGet(GLUT_ELAPSED_TIME);
	frameTime = currTime - prevTime;
	prevTime = currTime;
	
	if(act)
	{
		now_frame += frameTime;
		cout << "now_frame: " << now_frame << endl;
	}
	
	glutPostRedisplay();
	glutIdleFunc(update);
}

void drawPed()
{
	Color color;
	color.r = 0.0;
	color.g = 0.0;
	color.b = 1.0;
	for (int i=0; i<data.getNum(); ++i)
	{
		if (data.getDataset()[i].frame_time <= now_frame)
		{
			drawCircle(data.getDataset()[i].pos_x, data.getDataset()[i].pos_y, data.getDataset()[i].pos_z, 1, color);
		}
	}

}

void drawCircle(float x, float y, float z, float r, Color color, int slices)
{
	float sliceAngle;
	Point current, next;

	glPushMatrix();
	glColor3f(color.r,color.g,color.b);
	glTranslatef(x, y, z); 
	sliceAngle = static_cast<float>(360.0 / slices);
	current.x = r;
	current.y = 0;
	current.z = 0.0f;
	next.z = 0.0f;
	for (float angle = sliceAngle; angle <= 360; angle += sliceAngle) {
		next.x = r * cos(angle * PI / 180);
		next.y = r * sin(angle * PI / 180);

		glBegin(GL_TRIANGLES);
			glVertex3f(0.0, 0.0, 0.0);
			glVertex3f(current.x, current.y, current.z);
			glVertex3f(next.x, next.y, next.z);
		glEnd();

		current = next;
	}
	glPopMatrix();
}

void reshape(int width, int height)
{
	glViewport(0, 0, static_cast<GLsizei>(width), static_cast<GLsizei>(height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, static_cast<GLfloat>(width) / height, 1.0, 100.0);

	glMatrixMode(GL_MODELVIEW);

	winWidth = width;  
	winHeight = height;
}

void normalKey(unsigned char key, int xMousePos, int yMousePos) {
	switch (key) {
	case 'a':
		act = (!act) ? true : false;
		break;
	case 'b':
		break;
	case 27:
		exit(0);
		break;
	}
}


