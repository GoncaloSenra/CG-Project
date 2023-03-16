
/*
		Gonçalo Senra nº2020213750

		WASD - mover o carro
		1 - 2 - 0 - camaras
		O - L - subir e baixar capo
		I - K - subir e baixar janelas
		H - N - ON/OFF Focos
		U - intensidade da luz pontual
		Y - luz ambiente
		F - V - aumentar e diminuir nº poligonos da malha
		9 - ON/OFF malha
		7 - 8 - subir e baixar luzes Focos
		6 - mudar material do capo
		R - G - B - alterar cor da luz pontual
*/





#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#include "RgbImage.h"
#define PI		 3.14159

//--------------------------------- Definir cores
#define BLUE     0.0, 0.0, 1.0, 1.0
#define YELLOW	 1.0, 1.0, 0.0, 1.0
#define GREEN    0.0, 1.0, 0.0, 1.0
#define ORANGE   1.0, 0.5, 0.1, 1.0
#define CYAN     0.0, 1.0, 1.0, 1.0
#define WHITE    1.0, 1.0, 1.0, 1.0
#define BLACK    0.0, 0.0, 0.0, 0.4
#define BLACK2    0.0, 0.0, 0.0, 1.0
#define GRAY     0.3, 0.3, 0.3, 1.0


//================================================================================
//------------------------------------------------------------ Sistema Coordenadas 
GLint		wScreen = 700, hScreen = 600;		//.. janela - pixeis
GLfloat		SIZE = 10.0;	//.. Mundo  SIZE=coordenadas x=y=z


//========================================================= Animacao objeto Mesa
float		centrox = 0;
float		rotacao = 0;

//CAPO
float		rotCapo = 0;
float		xCapo = 0.401;
float		yCapo = 0.502;
float		zCapo = 0.451;

//JANELAS
float transJanela = 0;

//MOVIMENTO CARRO
GLfloat theta = 0.;
GLfloat vel = 1.;
GLfloat pos[] = { 0., 0., 0. };
GLfloat rotRodas = 0;

GLint view = 0;


void cubefunc();

//============================================================= Observador
GLfloat  rVisao = 8, aVisao = 0.5 * PI, incVisao = 1;
GLfloat  obsP[] = { rVisao * cos(aVisao / 180.), 2.0, rVisao * sin(aVisao/ 180.) };
float	 anguloZ = 35;

//=================================================================== TEXTURAS
RgbImage imag;
GLuint   texture[5];

GLUquadricObj* esfera = gluNewQuadric();

//===========================================================Variaveis e constantes
GLint     msec = 50;


GLfloat tam = 0.5;

static GLfloat cube[] = {
	//base
	-tam,  -tam, tam,	// 0
	tam,  -tam, tam,    // 1
	tam,  -tam, -tam,   // 2
	-tam, -tam, -tam,   // 3
	//cima
	-tam,  tam,  tam,   // 4
	tam,  tam,  tam,    // 5
	tam,  tam, -tam,    // 6
	-tam,  tam, -tam,   // 7
	//tras
	-tam,  tam, -tam,	// 8
	tam,  tam, -tam,	// 9
	tam,  -tam, -tam,	// 10
	-tam,  -tam, -tam,	// 11
	//esquerda
	-tam,  -tam,  tam,  // 12 
	-tam,   tam,  tam,  // 13 
	-tam,   tam, -tam,  // 14 
	-tam,  -tam, -tam,  // 15 
	//frente
	-tam,  -tam, tam,   // 16
	tam,  -tam, tam,    // 17
	tam,  tam, tam,    // 18
	-tam,  tam,  tam,    // 19
   //direita
	tam,  -tam, -tam,   // 20 
	tam,   tam, -tam,   // 21
	tam,   tam,  tam,   // 22 
	tam,  -tam,  tam,   // 23
};

static GLfloat CubeTexture[] = {
	//base
	 1, 0,
	0, 0,
	0, 1,
	1, 1,
	//cima
	0, 0,
	1, 0,
	1, 1,
	0, 1,
	//tras
	1, 1,
	0, 1,
	0, 0,
	1, 0,
	//esquerda
	 1, 1,
	0, 1,
	0, 0,
	1, 0,
	//frente
	0, 1,
	1, 1,
	1, 0,
	0, 0,
	//direita
	 0, 1,
	1, 1,
	1, 0,
	0, 0
};

static GLfloat normais[] = {
	//…………………………………………………………………………………………………… Base
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  0.0,  -1.0,  0.0,
	  //…………………………………………………………………………………………………… Cima
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  0.0,  1.0,  0.0,
	  
	   //…………………………………………………………………………………………………… Tras
	   -1.0,  0.0,  0.0,
	   -1.0,  0.0,  0.0,
	   -1.0,  0.0,  0.0,
	   -1.0,  0.0,  0.0,
	   //…………………………………………………………………………………………………… Esquerda
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   0.0,  0.0,  -1.0,
	   //…………………………………………………………………………………………………… Frente
	   1.0,  0.0,  0.0,
	   1.0,  0.0,  0.0,
	   1.0,  0.0,  0.0,
	   1.0,  0.0,  0.0,
	   //…………………………………………………………………………………………………… Direita
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	   0.0,  0.0,  1.0,
	  
};

static GLfloat cores[] = {
	//base
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	//cima
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	//tras
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	//esquerda
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	//frente
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	//direita	
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
	1., 0., 0.,
};


static GLuint cbase[] = { 0, 1, 2, 3 };
static GLuint ccima[] = { 4, 5, 6, 7 };
static GLuint ctras[] = { 8, 9, 10, 11};
static GLuint cesquerda[] = { 12, 13, 14, 15 };
static GLuint cfrente[] = { 16, 17, 18, 19};
static GLuint cdireita[] = { 20, 21, 22, 23 };


//Ambiente
GLint   Dia = 0; 
GLfloat intensidadeDia = 0.0;
GLfloat luzGlobalCorAmb[4] = { intensidadeDia, intensidadeDia,intensidadeDia, 1.0 };


//Pontual
GLint   ligaTeto = 1;		  
GLfloat intensidadeT = 0.3;   
GLint   luzR = 1;
GLint   luzG = 1; 
GLint   luzB = 1;
GLfloat localPos[4] = { 0.0, 5.0, 0.0, 1.0 };
GLfloat localCorAmb[4] = { 0, 0, 0, 0.0 };
GLfloat localCorDif[4] = { luzR, luzG, luzB, 1.0 };
GLfloat localCorEsp[4] = { luzR, luzG, luzB, 1.0 };

GLfloat dim = 64;


//Focos
bool 		Focos[] = { 1,1 };
GLfloat		aberturaFoco = 70.0;	
GLfloat		anguloINC = 3.0;		
GLfloat		anguloMIN = 3.0;		
GLfloat		anguloMAX = 70.0;		

GLfloat p1 = 3.0, p2 = 3.0;
GLfloat Pos1[] = { 0.0f, p1,  1.0f, 1.0f };   
GLfloat Pos2[] = { 0.0f, p1,  -1.0f, 1.0f };    


int malha = 1;
int mater = 0;

void initLights()
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
	
}

void defineLuzes() {
	GLfloat Foco_direccao[] = { 0, -1, 0, 0 };	 
	GLfloat Foco1_cor[] = { 0, 0, 1.0, 1 };
	GLfloat Foco2_cor[] = { 1.0, 0,  0, 1 };
	GLfloat Foco_ak = 1.0;
	GLfloat Foco_al = 0.05f;
	GLfloat Foco_aq = 0.0f;
	GLfloat Foco_Expon = 2.0;

	glLightfv(GL_LIGHT2, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, Foco_Expon);

	glLightfv(GL_LIGHT1, GL_POSITION, Pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco2_cor);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);
}

void iluminacao() {
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
	if (ligaTeto)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
}

void initTexturas()
{
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("red.bmp"); 
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	imag.LoadBmpFile("carbon.bmp");
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("sky.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	imag.LoadBmpFile("ground.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());

}

void initialize(void)
{
	glClearColor(WHITE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH);

	initTexturas();
	
	defineLuzes();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	

	initLights();
	

	glVertexPointer(3, GL_FLOAT, 0, cube);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);	
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cores);
	glEnableClientState(GL_COLOR_ARRAY);

	glTexCoordPointer(2, GL_FLOAT, 0, texture);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

}

void drawEixos()
{
	glColor4f(ORANGE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5 * SIZE, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5 * SIZE, 0);
	glEnd();
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5 * SIZE);
	glEnd();

}

void cubefuncNoTex() {

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cfrente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cbase);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ccima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ctras);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cesquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cdireita);

}

void cubefunc() {

	//glEnable(GL_COLOR_MATERIAL);
	//glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	glTexCoordPointer(2, GL_FLOAT, 0, CubeTexture);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cfrente);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cbase);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ccima);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, ctras);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cesquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cdireita);

	glDisable(GL_TEXTURE_2D);
}

void drawMalhaPoligonos() {
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	defineLuzes();

	float corAmb[] = { 1,1,1,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, corAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corAmb);

	glBindTexture(GL_TEXTURE_2D, texture[3]);

	glPushMatrix();

	glTranslatef(0, -1.0, 0);
	glScalef(50, 1, 50);
	glRotatef(-90, 1, 0, 0);
	glTranslatef(-1, -1, 0);

	glNormal3f(0, 0, 1);
	float med_dim = (float)dim / 2;
	glBegin(GL_QUADS);
	for (int i = 0; i < dim; i++)
		for (int j = 0; j < dim; j++) {
			glTexCoord2f((float)j / dim, (float)i / dim);
			glVertex3d((float)j / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)i / med_dim, 0);
			glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
			glVertex3d((float)(j + 1) / med_dim, (float)(i + 1) / med_dim, 0);
			glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
			glVertex3d((float)j / med_dim, (float)(i + 1) / med_dim, 0);
		}
	glEnd();
	glPopMatrix();
}

void drawGround() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPushMatrix();
	glTranslatef(0, -3, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);    glVertex3i(-50, 2, 50);
	glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(50, 2, 50);
	glTexCoord2f(1.0f, 1.0f);    glVertex3i(50, 2, -50);
	glTexCoord2f(0.0f, 1.0f);  	 glVertex3i(-50, 2, -50);
	glEnd();
	glPopMatrix();
}

void drawScene() {
	glEnable(GL_LIGHTING);

	//chao
	/*
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glPushMatrix();
	glTranslatef(0, -3, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);    glVertex3i(-50, 2, 50); 
	glTexCoord2f(1.0f, 0.0f); 	 glVertex3i(50, 2, 50);  
	glTexCoord2f(1.0f, 1.0f);    glVertex3i(50, 2, -50); 
	glTexCoord2f(0.0f, 1.0f);  	 glVertex3i(-50, 2, -50); 
	glEnd();
	glPopMatrix();*/

	
	
	//skybox
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(esfera, GLU_FILL);
	gluQuadricNormals(esfera, GLU_SMOOTH);
	gluQuadricTexture(esfera, GL_TRUE);
	gluSphere(esfera, 60.0, 100, 100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);


	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(pos[0], pos[1], pos[2]);
	glRotatef(theta, 0, 1, 0);
	glPushMatrix();
	

	//base
	glPushMatrix();

	glScalef(4.5, 1, 2);
	glColorPointer(3, GL_FLOAT, 0, cores);
	glEnableClientState(GL_COLOR_ARRAY);
	cubefunc();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	
	//tras
	glPushMatrix();
	glTranslatef(-1.8, 0.8, 0.0);
	glScalef(0.10, 1.5, 1.5);
	glColorPointer(3, GL_FLOAT, 0, cores);
	glEnableClientState(GL_COLOR_ARRAY);
	cubefunc();
	glPopMatrix();
	
	//cima
	glPushMatrix();
	glTranslatef(-0.9, 1.5, 0.0);
	glScalef(1.8, 0.10, 1.5);
	glColorPointer(3, GL_FLOAT, 0, cores);
	glEnableClientState(GL_COLOR_ARRAY);
	cubefunc();
	glPopMatrix();

	//aste
	glPushMatrix();
	glTranslatef(0.0, 0.8, 0.7);
	glScalef(0.10, 1.5, 0.10);
	glColorPointer(3, GL_FLOAT, 0, cores);
	glEnableClientState(GL_COLOR_ARRAY);
	cubefunc();
	glPopMatrix();
	
	//aste
	glPushMatrix();
	glTranslatef(0.0, 0.8, -0.7);
	glScalef(0.10, 1.5, 0.10);
	glColorPointer(3, GL_FLOAT, 0, cores);
	glEnableClientState(GL_COLOR_ARRAY);
	cubefunc();
	glPopMatrix();

	glDisable(GL_LIGHTING);
	//janela frente
	glPushMatrix();
	glDisableClientState(GL_COLOR_ARRAY);
	glColor4f(BLACK);
	glTranslatef(0.0, 1.0, 0.0);
	glScalef(0.10, 1.0, 1.5);
	cubefuncNoTex();
	glPopMatrix();
	
	
	//janela direita
	glPushMatrix();
	glTranslatef(0, -transJanela, 0);
	
	glPushMatrix();
	glDisableClientState(GL_COLOR_ARRAY);
	glColor4f(BLACK);
	glTranslatef(-0.9, 1.0, 0.71);
	glScalef(1.7, 1.0, 0.10);
	cubefuncNoTex();
	glPopMatrix();
	

	//janela esquerda
	glPushMatrix();
	glDisableClientState(GL_COLOR_ARRAY);
	glColor4f(BLACK);
	glTranslatef(-0.9, 1.0, -0.71);
	glScalef(1.7, 1.0, 0.10);
	cubefuncNoTex();
	glPopMatrix();
	
	glPopMatrix();

	//interior capo
	glPushMatrix();
	glTranslatef(1.1, 0.451, 0.0);
	glScalef(1.9, 0.10, 1.5);
	glColor4f(BLACK2);
	cubefuncNoTex();
	glPopMatrix();
	
	glEnable(GL_LIGHTING);
	glDisable(GL_BLEND);
	//capo
	glPushMatrix();

	glTranslatef(xCapo, yCapo, zCapo);
	glRotatef(rotCapo, 0.0, 0.0, 1.0);
	glTranslatef(-xCapo, -yCapo, -zCapo);
	glPushMatrix();
	glTranslatef(1.1, 0.50, 0.0);
	glScalef(1.9, 0.10, 1.5);
	//glColorPointer(3, GL_FLOAT, 0, cores);
	//glEnableClientState(GL_COLOR_ARRAY);
	
	if (mater == 0) {
		//Ruby
		float mat_ambient[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
		float mat_diffuse[] = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
		float mat_specular[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
		float shine = 76.8f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
	}
	else if (mater == 1) {
		//Emerald
		float mat_ambient [] = {0.0215f, 0.1745f, 0.0215f, 0.55f};
		float mat_diffuse [] = {0.07568f, 0.61424f, 0.07568f, 0.55f};
		float mat_specular [] = {0.633f, 0.727811f, 0.633f, 0.55f};
		float shine = 76.8f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
	}
	else if (mater == 2) {
		//Polished gold
		float mat_ambient []  = {0.24725f, 0.2245f, 0.0645f, 1.0f};
		float mat_diffuse [] = {0.34615f, 0.3143f, 0.0903f, 1.0f};
		float mat_specular [] = {0.797357f, 0.723991f, 0.208006f, 1.0f};
		float shine = 83.2f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
	}
	else if (mater == 3) {
		//Cyan plastic
		float mat_ambient[] = { 0.0f,0.1f,0.06f ,1.0f };
		float mat_diffuse[] = { 0.0f,0.50980392f,0.50980392f,1.0f };
		float mat_specular[] = { 0.50196078f,0.50196078f,0.50196078f,1.0f };
		float shine = 32.0f;
		glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
		glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
		glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
		glMaterialf(GL_FRONT, GL_SHININESS, shine);
	}

	
	cubefuncNoTex();
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	

	glPopMatrix();

	//pneu traseiro direito
	glPushMatrix();
	glTranslatef(-1.2, -0.3, 1.2);
	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glDisableClientState(GL_COLOR_ARRAY);
	//glColor4f(BLACK2);

	float mat[] = { 0, 0, 0,1 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);



	glutSolidTorus(0.5, 1.0, 30, 30);
	glPopMatrix();
	glRotatef(-rotRodas, 0, 0, 1);
	glScalef(0.10, 1.1, 0.10);
	//glColor4f(YELLOW);

	mat[0] = 1;
	mat[1] = 1; 
	mat[2] = 0;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);


	cubefuncNoTex();
	glScalef(5, 0.10, 0.10);
	cubefuncNoTex();
	glPopMatrix();

	//pneu traseiro esquerdo
	glPushMatrix();
	glTranslatef(-1.2, -0.3, -1.2);
	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glDisableClientState(GL_COLOR_ARRAY);
	//glColor4f(BLACK2);

	mat[0] = 0;
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);


	glutSolidTorus(0.5, 1.0, 30, 30);
	glPopMatrix();
	glRotatef(-rotRodas, 0, 0, 1);
	glScalef(0.10, 1.1, 0.10);
	//glColor4f(YELLOW);

	mat[0] = 1;
	mat[1] = 1;
	mat[2] = 0;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);

	cubefuncNoTex();
	glScalef(5, 0.10, 0.10);
	cubefuncNoTex();
	glPopMatrix();
	
	//pneu dianteiro direito
	glPushMatrix();
	glTranslatef(1.2, -0.3, 1.2);
	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glDisableClientState(GL_COLOR_ARRAY);
	glRotatef(-rotRodas, 0, 0, 1);
	//glColor4f(BLACK2);

	mat[0] = 0;
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);

	glutSolidTorus(0.5, 1.0, 30, 30);
	glPopMatrix();
	glRotatef(-rotRodas, 0, 0, 1);
	glScalef(0.10, 1.1, 0.10);
	//glColor4f(YELLOW);

	mat[0] = 1;
	mat[1] = 1;
	mat[2] = 0;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);

	cubefuncNoTex();
	glScalef(5, 0.10, 0.10);
	cubefuncNoTex();
	glPopMatrix();

	//pneu dianteiro esquerdo
	glPushMatrix();
	glTranslatef(1.2, -0.3, -1.2);
	glPushMatrix();
	glScalef(0.4, 0.4, 0.4);
	glDisableClientState(GL_COLOR_ARRAY);
	//glColor4f(BLACK2);

	mat[0] = 0;
	mat[1] = 0;
	mat[2] = 0;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);


	glutSolidTorus(0.5, 1.0, 30, 30);
	glPopMatrix();
	glRotatef(-rotRodas, 0, 0, 1);
	glScalef(0.10, 1.1, 0.10);
	//glColor4f(YELLOW);

	mat[0] = 1;
	mat[1] = 1;
	mat[2] = 0;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);

	cubefuncNoTex();
	glScalef(5, 0.10, 0.10);
	cubefuncNoTex();
	glPopMatrix();

	glPopMatrix();
	
	//farol esquerdo
	glPushMatrix();
	glTranslatef(2.12, 0, -0.5);
	
	glScalef(0.4, 0.4, 0.4);
	//glColor4f(YELLOW);

	mat[0] = 1;
	mat[1] = 1;
	mat[2] = 0;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);

	cubefuncNoTex();
	glPopMatrix();

	//farol direito
	glPushMatrix();
	glTranslatef(2.12, 0, 0.5);

	glScalef(0.4, 0.4, 0.4);
	//glColor4f(YELLOW);

	mat[0] = 1;
	mat[1] = 1;
	mat[2] = 0;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);

	cubefuncNoTex();
	glPopMatrix();
	
	mat[0] = 1;
	mat[1] = 1;
	mat[2] = 1;
	mat[3] = 1;

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat);

	
	glEnable(GL_LIGHTING);

}

void updateLuz() {
	localCorAmb[0] = luzR * intensidadeT;
	localCorAmb[1] = luzG * intensidadeT;
	localCorAmb[2] = luzB * intensidadeT;
	localCorDif[0] = luzR * intensidadeT;
	localCorDif[1] = luzG * intensidadeT;
	localCorDif[2] = luzB * intensidadeT;
	localCorEsp[0] = luzR * intensidadeT;
	localCorEsp[1] = luzG * intensidadeT;
	localCorEsp[2] = luzB * intensidadeT;;
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//================================================================= Viewport 2
	glViewport(0, 0, wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85, (float)wScreen / hScreen, 0.1, 9999);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (view == 1) {
		gluLookAt(-8, 5, 0, obsP[0], obsP[1], obsP[2], 0, 1, 0);
		//gluLookAt(pos[0]-0.8, pos[1]+0.8, pos[2], , , , 0, 1, 0);
		//printf("%f-%f-%f\n", m[12], m[13], m[14]);
	} else if (view == 2) {
		gluLookAt(0, 20, 0, obsP[0], obsP[1], obsP[2], 1, 0, 0);
	} else {
		gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);
	}
	
	//…………………………………………………………………………………………………………………………………………………………Objectos


	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	if (Focos[0]) {
		glPushMatrix();
		glColor3f(0.0f, 1.0f, 0.0f);
		glTranslatef(Pos1[0], Pos1[1], Pos1[2]);
		glutSolidSphere(0.1f, 100, 100);
		glPopMatrix();
	}
	if (Focos[1]) {
		glPushMatrix();
		glColor3f(1.0f, 0.0f, 0.0f);
		glTranslatef(Pos2[0], Pos2[1], Pos2[2]);
		glutSolidSphere(0.1f, 100, 100);
		glPopMatrix();
	}
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	defineLuzes();
	if (malha)
		drawMalhaPoligonos();
	else
		drawGround();
	glDisable(GL_LIGHTING);

	iluminacao();

	glEnable(GL_LIGHTING);

	drawEixos();
	drawScene();

	glViewport(0, 450, wScreen * 0.25, hScreen * 0.25);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(85, (float)wScreen / hScreen, 0.1, 9999);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(0, 20, 0, 0, 0, 0, obsP[0], 0, obsP[2]);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	defineLuzes();
	if (malha)
		drawMalhaPoligonos();
	else
		drawGround();
	glDisable(GL_LIGHTING);

	iluminacao();

	glEnable(GL_LIGHTING);

	drawEixos();
	drawScene();

	glutSwapBuffers();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

void keyboard(unsigned char key, int x, int y) {


	switch (key) {

	case 'W': case 'w':
		pos[0] = pos[0] + vel * cos(theta * PI / 180.);
		pos[2] = pos[2] - vel * sin(theta * PI / 180.);
		rotRodas += 20;
		glutPostRedisplay();
		break;
	case 'S': case 's':
		pos[0] = pos[0] - vel * cos(theta * PI / 180.);
		pos[2] = pos[2] + vel * sin(theta * PI / 180.);
		rotRodas -= 20;
		glutPostRedisplay();
		break;
	case 'A': case 'a':
		theta += 3.;
		glutPostRedisplay();
		break;
	case 'D': case 'd':
		theta -= 3.;
		glutPostRedisplay();
		break;
	case 'E': case 'e':
		rotacao = rotacao + 2.5;
		glutPostRedisplay();
		break;

	case 'L': case 'l':
		rotCapo = rotCapo - 2.5;
		if (rotCapo < 0) rotCapo = 0;
		glutPostRedisplay();
		break;
	case 'O': case 'o':
		rotCapo = rotCapo + 2.5;
		if (rotCapo > 62.5) rotCapo = 62.5;
		glutPostRedisplay();
		break;
	case 'I': case 'i':
		transJanela = transJanela - 0.2;
		if (transJanela < 0) transJanela = 0;
		glutPostRedisplay();
		break;
	case 'K': case 'k':
		transJanela = transJanela + 0.1;
		if (transJanela > 0.9) transJanela = 0.9;
		glutPostRedisplay();
		break;
	case 'y': case 'Y':
		Dia = !Dia;
		if (Dia) {
			luzGlobalCorAmb[0] = 1.0;
			luzGlobalCorAmb[1] = 1.0;
			luzGlobalCorAmb[2] = 1.0;
		}
		else {
			luzGlobalCorAmb[0] = 0.0;
			luzGlobalCorAmb[1] = 0.0;
			luzGlobalCorAmb[2] = 0.0;
		}
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
		glutPostRedisplay();
		break;
	case 'u': case 'U':
		intensidadeT = intensidadeT + 0.1;
		if (intensidadeT > 1.1) intensidadeT = 0;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'r':case 'R':
		if (luzR == 0 || (luzR==1 && luzG==1 && luzB==1)) {
			luzR = 1;
			luzG = 0;
			luzB = 0;
		}
		else {
			luzR = 1;
			luzG = 1;
			luzB = 1;
		}
		
		updateLuz();
		glutPostRedisplay();
		break;
	case 'g':case 'G':
		if (luzG == 0 || (luzR == 1 && luzG == 1 && luzB == 1)) {
			luzG = 1;
			luzR = 0;
			luzB = 0;
		}
		else {
			luzR = 1;
			luzG = 1;
			luzB = 1;
		}
		updateLuz();
		glutPostRedisplay();
		break;
	case 'b':case 'B':
		if (luzB == 0 || (luzR == 1 && luzG == 1 && luzB == 1)) {
			luzB = 1;
			luzR = 0;
			luzG = 0;
		}
		else {
			luzR = 1;
			luzG = 1;
			luzB = 1;
		}
		
		updateLuz();
		glutPostRedisplay();
		break;
	case 'f':case 'F':
		dim = 2 * dim;
		if (dim > 500) dim = 500;
		glutPostRedisplay();
		break;
	case 'v':case 'V':
		dim = 0.5 * dim;
		if (dim < 6) dim = 6;
		glutPostRedisplay();
		break;
	case 'H':case 'h':
		Focos[0] = !Focos[0];
		if (Focos[0] == 0)
			glDisable(GL_LIGHT2);
		else
			glEnable(GL_LIGHT2);
		glutPostRedisplay();
		break;
	case 'N':case 'n':
		Focos[1] = !Focos[1];
		if (Focos[1] == 0)
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);
		glutPostRedisplay();
		break;
	case '9':
		if (malha == 0)
			malha = 1;
		else
			malha = 0;
		glutPostRedisplay();
		break;
	case '7':
		p1 -= 0.2;
		if (p1 <= 3) p1 = 3;
		Pos1[1] = p1;
		Pos2[1] = p1;
		glutPostRedisplay();
		break;
	case '8':
		p1 += 0.2;
		if (p1 >= 15) p1 = 15;
		Pos1[1] = p1;
		Pos2[1] = p1;
		glutPostRedisplay();
		break;
	case '6':
		mater += 1;
		if (mater == 4) mater = 0;
		glutPostRedisplay();
		break;
	case '1':
		view = 1;
		glutPostRedisplay();
		break;
	case '2':
		view = 2;
		glutPostRedisplay();
		break;
	case '0':
		view = 0;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}

}

void teclasNotAscii(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
		obsP[1] += 0.5;
	}
	if (key == GLUT_KEY_DOWN) {
		obsP[1] -= 0.5;
	}
	if (key == GLUT_KEY_LEFT) {
		aVisao += incVisao;
	}
	if (key == GLUT_KEY_RIGHT) {
		aVisao -= incVisao;
	}
	obsP[0] = rVisao * cos(aVisao * PI / 180.);
	obsP[2] = rVisao * sin(aVisao * PI / 180.);

	glutPostRedisplay();
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("Goncalo Senra |Observador:'SETAS'| Janelas 'I/K' | Capo 'O/L' | Camaras '1/2' | Camara normal '0'");

	initialize();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}


