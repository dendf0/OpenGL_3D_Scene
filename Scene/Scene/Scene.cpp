#include "pch.h"
#include <stdlib.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#include <soil.h>

#define LOGLENGTH 6
#define LOGQUANTITY 6
#define ROOF0 4.8,5,7
#define ROOF1 1.2,1.5,3.5
#define ROOF2 7.7,1.5,3.5
#define ROOF3 7.7,8.4,3.5
#define ROOF4 1.2,8.4,3.5

#define BLADE0 -1,-.08,1.2
#define BLADE1 1,-.08,1.2
#define BLADE2 1,-.08,5.5
#define BLADE3 -1,-.08,5.5
#define BLADE4 -1,.08,1.2
#define BLADE5 1,.08,1.2
#define BLADE6 1,.08,5.5
#define BLADE7 -1,.08,5.5

GLuint texture[15];

float viewX = 0;
float viewY = 10;
float viewZ = 15;

float millAngle = 0;

void reshape(int w, int h) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(55, 1.777777, 1, 50);
	
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

static void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(viewX, viewY, viewZ, 0, 0, 3, 0, 0, 1);

	//свет
	//фоновое освещение

	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	GLfloat ambient0[] = { 0.4, 0.4, 0.4, 1 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient0);

	//луна
	GLfloat pos1[] = { 1, -1, -1, 0 };
	GLfloat light1_diffuse[] = { .7,.7,.7,1 };
	GLfloat light1_specular[] = { .2,.2,.2,1 };
	glLightfv(GL_LIGHT1, GL_POSITION, pos1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);

	//фонарь
	GLfloat light2_position[] = { -5, 5, 3.64, 1 };
	GLfloat light2_diffuse[] = { .9, .7, .5, 1 };
	GLfloat light2_specular[] = { .3, .2, .1, 1 };
	GLfloat light2_linear_attenuation[] = { .015 };
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_LINEAR_ATTENUATION, light2_linear_attenuation);


	GLfloat material_emission[] = { 0, 0, 0, 1 };
	GLfloat material_diffuse[] = { .8, .8, .8, 1.0 };
	GLfloat material_ambient[] = { .5, .5, .5, 1.0 };
	GLfloat material_specular[] = { .1, .1, .1, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	
	GLUquadricObj *cylinder;
	cylinder = gluNewQuadric();
	GLUquadricObj *disk;
	disk = gluNewQuadric();
	GLUquadricObj *sphere;
	sphere = gluNewQuadric();

	gluQuadricTexture(cylinder, GLU_TRUE);
	gluQuadricNormals(cylinder, GLU_SMOOTH);
	gluQuadricDrawStyle(cylinder, GLU_FILL);
	gluQuadricTexture(disk, GLU_TRUE);
	gluQuadricNormals(disk, GLU_SMOOTH);
	gluQuadricDrawStyle(disk, GLU_FILL);


	//grass
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	gluDisk(disk, 0, 15, 50, 50);

	/*glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(-10, -10, 0.);
		glTexCoord2f(10, 0);
		glVertex3f(10, -10, 0.);
		glTexCoord2f(10, 10);
		glVertex3f(10, 10, 0.);
		glTexCoord2f(0, 10);
		glVertex3f(-10, 10, 0.);
	glEnd();*/

	

	
	glPushMatrix();

	//дом
	glTranslatef(2, 2, 0);
	glRotatef(-90, 1, 0, 0);

	GLfloat material1_specular[] = { 0, 0, 0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material1_specular);
	//левая стена
	glPushMatrix();
	for (int i = 0; i < LOGQUANTITY+1; i++) {
		//ствол
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		
		gluCylinder(cylinder, .3, .3, LOGLENGTH, 30, 30);
		//основание ствола
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		gluDisk(disk, 0, .3, 30, 30);
		glTranslatef(0, 0, LOGLENGTH);
		gluDisk(disk, 0, .3, 30, 30);
		glTranslatef(0, 0, -LOGLENGTH);
		glTranslatef(0, -.6, 0);
	}
	glPopMatrix();
	glPushMatrix();
	//правая стена
	glTranslatef(5, 0, 0);
	for (int i = 0; i < LOGQUANTITY+1; i++) {
		//ствол
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		gluCylinder(cylinder, .3, .3, LOGLENGTH, 30, 30);
		//основание ствола
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		gluDisk(disk, 0, .3, 30, 30);
		glTranslatef(0, 0, LOGLENGTH);
		gluDisk(disk, 0, .3, 30, 30);
		glTranslatef(0, 0, -LOGLENGTH);
		glTranslatef(0, -.6, 0);
	}
	glPopMatrix();
	glTranslatef(-.5, 0, .5);
	glTranslatef(0, -.3, 0);
	glRotatef(90, 0, 1, 0);
	glPushMatrix();
	//передняя стена
	for (int i = 0; i < LOGQUANTITY; i++) {
		//ствол
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		gluCylinder(cylinder, .3, .3, LOGLENGTH, 30, 30);
		//основание ствола
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		gluDisk(disk, 0, .3, 30, 30);
		glTranslatef(0, 0, LOGLENGTH);
		gluDisk(disk, 0, .3, 30, 30);
		glTranslatef(0, 0, -LOGLENGTH);
		glTranslatef(0, -.6, 0);
	}
	glPopMatrix();
	glPushMatrix();
	//задняя стена
	glTranslatef(-5, 0, 0);
	for (int i = 0; i < LOGQUANTITY; i++) {
		//ствол
		glBindTexture(GL_TEXTURE_2D, texture[1]);
		gluCylinder(cylinder, .3, .3, LOGLENGTH, 30, 30);
		//основание ствола
		glBindTexture(GL_TEXTURE_2D, texture[2]);
		gluDisk(disk, 0, .3, 30, 30);
		glTranslatef(0, 0, LOGLENGTH);
		gluDisk(disk, 0, .3, 30, 30);
		glTranslatef(0, 0, -LOGLENGTH);
		glTranslatef(0, -.6, 0);
	}
	glPopMatrix();
	glPopMatrix();


	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	//крыша
	glFrontFace(GL_CW);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glBegin(GL_TRIANGLES);
	//перед
		glNormal3f(1, 0, -1);
		glTexCoord2f(0, 0);
		glVertex3f(ROOF1);
		glTexCoord2f(1, 0);
		glVertex3f(ROOF2);
		glTexCoord2f(.5, 1);
		glVertex3f(ROOF0);
		//право
		glNormal3f(0, -1, 1);
		glTexCoord2f(0, 0);
		glVertex3f(ROOF2);
		glTexCoord2f(1, 0);
		glVertex3f(ROOF3);
		glTexCoord2f(.5, 1);
		glVertex3f(ROOF0);
		//сзади
		glNormal3f(-1, 0, -1);
		glTexCoord2f(0, 0);
		glVertex3f(ROOF3);
		glTexCoord2f(1, 0);
		glVertex3f(ROOF4);
		glTexCoord2f(.5, 1);
		glVertex3f(ROOF0);
		//слева
		glNormal3f(0, 1, 1);
		glTexCoord2f(0, 0);
		glVertex3f(ROOF4);
		glTexCoord2f(1, 0);
		glVertex3f(ROOF1);
		glTexCoord2f(.5, 1);
		glVertex3f(ROOF0);
	glEnd();
	glFrontFace(GL_CCW);

	//потолок
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,
		GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(ROOF4);
	glTexCoord2f(3, 0);
	glVertex3f(ROOF3);
	glTexCoord2f(3, 3);
	glVertex3f(ROOF2);
	glTexCoord2f(0, 3);
	glVertex3f(ROOF1);
	glEnd();

	//труба
	glPushMatrix();
	glTranslatef(3.3, 5, 5);
	glRotatef(45, 0, 0, 1);
	glBindTexture(GL_TEXTURE_2D, texture[5]);
	gluCylinder(cylinder, .5, .5, 2, 4, 4);
	gluCylinder(cylinder, .3, .3, 2, 4, 4);
	glTranslatef(0, 0, 2);
	gluDisk(disk, .3, .5, 4, 4);
	glPopMatrix();

	//мельница
	glPushMatrix();
	glTranslatef(-5, -5, 0);
	glBindTexture(GL_TEXTURE_2D, texture[6]);
	gluCylinder(cylinder, 2.35, 1.7, 7, 50, 50);
	glTranslatef(0, 0, 6.9);
	//крыша мельницы
	glBindTexture(GL_TEXTURE_2D, texture[7]);
	gluCylinder(cylinder, 1.8, 0, 2, 50, 50);
	


	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material1_specular);
	//крепление

	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTranslatef(2, 2, -1);
	glRotatef(90, 1, 0, 0);
	glRotatef(-45, 0, 1, 0);

	//управление
	glRotatef(millAngle, 0, 0, 1);

	gluCylinder(cylinder, .15, .15, 1.5, 10, 10);
	gluDisk(disk, 0, .15, 10, 10);

	//лопасти
	glTranslatef(0, 0, .2);
	glPushMatrix();
	glRotatef(90,1,0,0);
	
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);*/
	for (int i = 0; i < 4; i++) {
		gluCylinder(cylinder, .1, 0, 3, 10, 10);
		//наклон
		glPushMatrix();
		glRotatef(15, 0, 0, 1);
		
		glFrontFace(GL_CW);

		glBegin(GL_QUADS);
			glNormal3f(0, 1, 0);
			glTexCoord2f(0, 0);
			glVertex3f(BLADE0);
			glTexCoord2f(1, 0);
			glVertex3f(BLADE1);
			glTexCoord2f(1, 3);
			glVertex3f(BLADE2);
			glTexCoord2f(0, 3);
			glVertex3f(BLADE3);

			glNormal3f(0, -1, 0);
			glTexCoord2f(0, 0);
			glVertex3f(BLADE7);
			glTexCoord2f(1, 0);
			glVertex3f(BLADE6);
			glTexCoord2f(1, 3);
			glVertex3f(BLADE5);
			glTexCoord2f(0, 3);
			glVertex3f(BLADE4);

			glNormal3f(1, 0, 0);
			glTexCoord2f(0, 0);
			glVertex3f(BLADE0);
			glTexCoord2f(1, 0);
			glVertex3f(BLADE3);
			glTexCoord2f(1, 3);
			glVertex3f(BLADE7);
			glTexCoord2f(0, 3);
			glVertex3f(BLADE4);

			glNormal3f(-1, 0, 0);
			glTexCoord2f(0, 0);
			glVertex3f(BLADE1);
			glTexCoord2f(1, 0);
			glVertex3f(BLADE5);
			glTexCoord2f(1, 3);
			glVertex3f(BLADE6);
			glTexCoord2f(0, 3);
			glVertex3f(BLADE2);

			glNormal3f(0, 0, 1);
			glTexCoord2f(0, 0);
			glVertex3f(BLADE0);
			glTexCoord2f(1, 0);
			glVertex3f(BLADE4);
			glTexCoord2f(1, 3);
			glVertex3f(BLADE5);
			glTexCoord2f(0, 3);
			glVertex3f(BLADE1);

			glNormal3f(0, 0, -1);
			glTexCoord2f(0, 0);
			glVertex3f(BLADE3);
			glTexCoord2f(1, 0);
			glVertex3f(BLADE2);
			glTexCoord2f(1, 3);
			glVertex3f(BLADE6);
			glTexCoord2f(0, 3);
			glVertex3f(BLADE7);
		glEnd();
		glFrontFace(GL_CCW);

		glPopMatrix();

		glRotatef(90, 0, 1, 0);
	}
	

	glPopMatrix();
	glPopMatrix();


	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	//фонарь
	glPushMatrix();
	glTranslatef(-5, 5, 0);
	glBindTexture(GL_TEXTURE_2D, texture[8]);
	gluCylinder(cylinder, .2, .15, .25, 20, 20);
	glTranslatef(0, 0, .25);
	gluCylinder(cylinder, .15, .15, 3, 20, 20);
	glTranslatef(0, 0, 3);
	gluCylinder(cylinder, .15, .2, .1, 20, 20);
	gluCylinder(cylinder, .03, .03, .2, 10, 5);
	glPopMatrix();

	
	glTranslatef(-5, 5, 3.64);
	glBindTexture(GL_TEXTURE_2D, 0);
	GLfloat material_emission9[] = { .7, .6, .3, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission9);
	gluSphere(sphere, .2, 40, 40);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission);
	
	glDisable(GL_LIGHTING);
	glColor4f(.7, .7, .7, .2);
	gluSphere(sphere, .32, 40, 40);
	gluSphere(sphere, .35, 40, 40);
	glColor4f(1, 1, 1, 1);
	glEnable(GL_LIGHTING);

	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	gluDeleteQuadric(cylinder);
	gluDeleteQuadric(disk);
	gluDeleteQuadric(sphere);
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 27)
		exit(0);
	switch (key) {
	case 113:
		viewX++;
		break;
	case 97:
		viewX--;
		break;
	case 119:
		viewY++;
		break;
	case 115:
		viewY--;
		break;
	case 101:
		viewZ++;
		break;
	case 100:
		viewZ--;
		break;
	default:
		break;
	}
}

void specialkeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		millAngle--;
		break;
	case GLUT_KEY_RIGHT:
		millAngle++;
		break;
	}
}

int main(int argc,char **argv)
{
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1920, 1080);

	glutCreateWindow("Scene");
	glutFullScreen();
	glClearColor(1, 1, 1, 0.0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_LIGHTING);
	glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_NORMALIZE);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	texture[0] = SOIL_load_OGL_texture (
		"images/biggrass.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	texture[1] = SOIL_load_OGL_texture(
		"images/log1.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	texture[2] = SOIL_load_OGL_texture(
		"images/cut.png",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	texture[3] = SOIL_load_OGL_texture(
		"images/roof.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	texture[4] = SOIL_load_OGL_texture(
		"images/planks.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	texture[5] = SOIL_load_OGL_texture(
		"images/bricks.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	texture[6] = SOIL_load_OGL_texture(
		"images/grain.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	texture[7] = SOIL_load_OGL_texture(
		"images/darkgrain.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	texture[8] = SOIL_load_OGL_texture(
		"images/metal.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);


	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
	glutIdleFunc(display);
	
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(specialkeyboard);

	glutMainLoop();

	return EXIT_SUCCESS;
}