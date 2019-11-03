'''
THIS PROGRAM CREATES A CG-MODEL OF A BUS STOP LOCATED INSIDE THE 
UNIVERSITY CAMPI. 

AUTHOR: RAFAEL M. ESCHER
FEDERAL UNIVERSITY OF RIO GRANDE
FURG
RIO GRANDE DO SUL
BRASIL

'''

#include <stdlib.h>
#include <GL/glut.h>

GLfloat angle, fAspect;

// usado para criar cilindros
GLUquadric* qobj;

GLfloat curvedSurface[4][4][3] = {

	// curva 1
	{{-40, 0, -15}, {-40, 20, -40},
	 {-40, 70, -15}, {-40, 45, 20}}, 

	// curva 2
	{{-40, 0, -15}, {-40, 20, -40},
	 {-40, 70, -15}, {-40, 45, 20}},

	// curva 3
	{{40, 0, -15}, {40, 20, -40},
	 {40, 70, -15}, {40, 45, 20}},

	// curva 4
	{{40, 0, -15}, {40, 20, -40},
	 {40, 70, -15}, {40, 45, 20}}
};


void cilindro(float x, float y, float z, float r, float h, float a, int da){
	/* x,y,z: posições desejadas | r: raio | h: altura | a: angulo | da: direção do angulo (x:1,y:2,z:3) */

	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix ();
		// define direção do cilindro (vertical/horizontal)
		switch (da) {
		case 1:
			glRotatef(a, 1.0, 0.0, 0.0);
			break;
		case 2:
			glRotatef(a, 0.0, 1.0, 0.0);
			break;
		case 3:
			glRotatef(a, 0.0, 0.0, 1.0);
			break;
		}

		glTranslatef(x, y, z);
		// cria cilindro
		gluCylinder(qobj, r, r, h, 100, 100);
	glPopMatrix ();
}


void chao(float compxz, float alty){
    glColor3f(0.1f, 0.4f, 0.1f);
	
    // Desenha varios retangulos formando uma 'parede'
	glBegin(GL_QUADS);			// Face frontal
		glNormal3f(0.0, 0.0, 1.0);	// Normal da face
		glVertex3f(compxz/2, 0, compxz/2);
		glVertex3f(-compxz/2, 0, compxz/2);
		glVertex3f(-compxz/2, -alty, compxz/2);
		glVertex3f(compxz/2, -alty, compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face traseira
		glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
		glVertex3f(compxz/2, 0, -compxz/2);
		glVertex3f(compxz/2, -alty, -compxz/2);
		glVertex3f(-compxz/2, -alty, -compxz/2);
		glVertex3f(-compxz/2, 0, -compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(-compxz/2, 0, compxz/2);
		glVertex3f(-compxz/2, 0, -compxz/2);
		glVertex3f(-compxz/2, -alty, -compxz/2);
		glVertex3f(-compxz/2, -alty, compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral direita
		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
		glVertex3f(compxz/2, 0, compxz/2);
		glVertex3f(compxz/2, -alty, compxz/2);
		glVertex3f(compxz/2, -alty, -compxz/2);
		glVertex3f(compxz/2, 0, -compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face superior
		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
		glVertex3f(-compxz/2, 0, -compxz/2);
		glVertex3f(-compxz/2, 0, compxz/2);
		glVertex3f(compxz/2, 0, compxz/2);
		glVertex3f(compxz/2, 0, -compxz/2);
	glEnd();
	glBegin(GL_QUADS);			// Face inferior
		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
		glVertex3f(-compxz/2, -alty, -compxz/2);
		glVertex3f(compxz/2, -alty, -compxz/2);
		glVertex3f(compxz/2, -alty, compxz/2);
		glVertex3f(-compxz/2, -alty, compxz/2);
	glEnd();
}


void faceCurva(){
	/* desenha esqueleto da superficie curva */

	// ativa blending (para transparencia)
	glEnable (GL_BLEND);
	glBlendFunc (GL_ONE_MINUS_DST_COLOR, GL_ONE);
	glDepthMask (GL_FALSE); // atrapalha blending

	// desenha linhas da face curva (coordenadas foram definidas no MAP em init)
	glColor3f(0.0f, 0.6f, 0.8f);
	for (int j = 0; j <= 3; j++) {
		glBegin(GL_LINE_STRIP);
			for (int i = 0; i <= 30; i++)
				glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/2.0);								
		glEnd();
		glBegin(GL_LINE_STRIP);
			for (int i = 0; i <= 30; i++)
				glEvalCoord2f((GLfloat)j/3.0, (GLfloat)i/30.0);
		glEnd();		
	}

	// preenche face curva
	glEvalMesh2(GL_FILL, 0, 20, 0, 20);
	
	// finaliza blending
	glDepthMask (GL_TRUE);
	glDisable (GL_BLEND);

	// barras de suporte
	cilindro(25, 26, -40, 0.5, 80, 90.0, 2); // x,y,z, raio, altura, angulo, direçãoAngulo	
	cilindro(10, 49, -40, 0.5, 80, 90.0, 2);
	cilindro(-20, 45, -40, 0.5, 80, 90.0, 2);
}


void banco(){
    glColor4f(0.7f, 0.1f, 0.0f, 10.0f);	

	float x, y, y2, z, z2;
	x = 39;
	y = 13; y2 = 15;
	z = -8; z2 = -18;

    // Desenha varios retangulos
	glBegin(GL_QUADS);			// Face frontal
		glNormal3f(0.0, 0.0, 1.0);	// Normal da face
		glVertex3f(x, y, z);
		glVertex3f(-x, y, z);
		glVertex3f(-x, y2, z);
		glVertex3f(x, y2, z);
	glEnd();
	glBegin(GL_QUADS);			// Face traseira
		glNormal3f(0.0, 0.0, -1.0); 	// Normal da face
		glVertex3f(x, y, z2);
		glVertex3f(-x, y, z2);
		glVertex3f(-x, y2, z2);
		glVertex3f(x, y2, z2);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(-x, y, z);
		glVertex3f(-x, y, z2);
		glVertex3f(-x, y2, z2);
		glVertex3f(-x, y2, z);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral direita
		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
		glVertex3f(x, y, z);
		glVertex3f(x, y, z2);
		glVertex3f(x, y2, z2);
		glVertex3f(x, y2, z);
	glEnd();
	glBegin(GL_QUADS);			// Face superior
		glNormal3f(0.0, 1.0, 0.0);  	// Normal da face
		glVertex3f(x, y2, z);
		glVertex3f(-x, y2, z);
		glVertex3f(-x, y2, z2);
		glVertex3f(x, y2, z2);
	glEnd();
	glBegin(GL_QUADS);			// Face inferior
		glNormal3f(0.0, -1.0, 0.0); 	// Normal da face
		glVertex3f(x, y, z);
		glVertex3f(-x, y, z);
		glVertex3f(-x, y, z2);
		glVertex3f(x, y, z2);
	glEnd();	

	// pés do banco
	cilindro(0.0, 13.0, 0.0, 1, 15, 270.0, 1); // x,y,z, raio, altura, angulo, direçãoAngulo
	cilindro(-35.0, 13.0, 0.0, 1, 15, 270.0, 1);
	cilindro(35.0, 13.0, 0.0, 1, 15, 270.0, 1);

		
}


void facesLaterais_parada(float distancia, float tamanho){
    
	
	///
    ///// FACES LATERAIS ESQUERDAS
    glColor3f(0.0f, 0.6f, 0.8f);
	glEnable (GL_BLEND);
	glDepthMask (GL_FALSE);
	glBlendFunc (GL_ONE_MINUS_DST_COLOR, GL_ONE);
	glBegin(GL_QUADS);			// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(-distancia/2, 0, 0);
		glVertex3f(-distancia/2, 0, -tamanho);
		glVertex3f(-distancia/2, tamanho, -tamanho);
		glVertex3f(-distancia/2, tamanho, 0);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(-distancia/2, 0, 0);
		glVertex3f(-distancia/2, 0, -tamanho);
		glVertex3f(-distancia/2, tamanho*2, -tamanho);
		glVertex3f(-distancia/2, tamanho*2, 0);
	glEnd();
	glBegin(GL_QUADS);			// Face lateral esquerda
		glNormal3f(-1.0, 0.0, 0.0); 	// Normal da face
		glVertex3f(-distancia/2, 0, 0);
		glVertex3f(-distancia/2, 0, -tamanho);
		glVertex3f(-distancia/2, tamanho*3, -tamanho);
		glVertex3f(-distancia/2, tamanho*3, 0);
	glEnd();  
	glDisable (GL_BLEND);
	glDepthMask (GL_TRUE);

	// suporte das faces laterais esquerdas
	cilindro(-40.0, 0.0, 0.0, 0.5, 45, 270, 1);		// vertical 1
	cilindro(-40.0, 15.0, 0.0, 0.5, 45, 270, 1);	// vertical 2
	cilindro(-40.0, -15.0, 0.0, 0.5, 15, 180, 1);	// horizontal 1
	cilindro(-40.0, -30.0, 0.0, 0.5, 15, 180, 1);	// horizontal 2
	cilindro(-40.0, -45.0, 0.0, 0.5, 15, 180, 1);	// horizontal 3
	////
	/// 	
	
	///
    ///// FACES LATERAIS DIREITAS
	glEnable (GL_BLEND);
	glDepthMask (GL_FALSE);
	glBlendFunc (GL_ONE_MINUS_DST_COLOR, GL_ONE);
	glColor3f(0.0f, 0.6f, 0.8f);
	glBegin(GL_QUADS);			// Face lateral direita
		glNormal3f(1.0, 0.0, 0.0);	// Normal da face
		glVertex3f(distancia/2, 0, 0);
		glVertex3f(distancia/2, 0, -tamanho);
		glVertex3f(distancia/2, tamanho, -tamanho);
		glVertex3f(distancia/2, tamanho, 0);
	glEnd();    
	glBegin(GL_QUADS);			
		glNormal3f(1.0, 0.0, 0.0);	
		glVertex3f(distancia/2, 0, 0);
		glVertex3f(distancia/2, 0, -tamanho);
		glVertex3f(distancia/2, tamanho*2, -tamanho);
		glVertex3f(distancia/2, tamanho*2, 0);
	glEnd();  
	glBegin(GL_QUADS);			
		glNormal3f(1.0, 0.0, 0.0);	
		glVertex3f(distancia/2, 0, 0);
		glVertex3f(distancia/2, 0, -tamanho);
		glVertex3f(distancia/2, tamanho*3, -tamanho);
		glVertex3f(distancia/2, tamanho*3, 0);
	glEnd();    

	glDisable (GL_BLEND);
	glDepthMask (GL_TRUE);

	// suporte das faces laterais direitas
	cilindro(40.0, 0.0, 0.0, 0.5, 45, 270, 1);		// vertical 1
	cilindro(40.0, 15.0, 0.0, 0.5, 45, 270, 1);		// vertical 2
	cilindro(40.0, -15.0, 0.0, 0.5, 15, 180, 1);	// horizontal 1
	cilindro(40.0, -30.0, 0.0, 0.5, 15, 180, 1);	// horizontal 2
	cilindro(40.0, -45.0, 0.0, 0.5, 15, 180, 1);	// horizontal 3	
	////
	///     
}


void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	// desenha chao verde
    chao(160, 4); // x: 160, z: 160, y: 4  || ORIGEM NO CENTRO

	//desenha faces laterais
    facesLaterais_parada(80,15);

	// desenha face curva
	faceCurva();

	// desenha banco
	banco();
  
    glutSwapBuffers();
	  			
}


void Rotaciona(int opcao){

	switch (opcao) {
		case 1: // em x
			glRotatef(3.0, 1.0, 0.0, 0.0);
			break;
		case (-1): // em -x
			glRotatef(-3.0, 1.0, 0.0, 0.0);
			break;
		case 2: // em y
			glRotatef(3.0, 0.0, 1.0, 0.0);
			break;
		case (-2): // em -y
			glRotatef(-3.0, 0.0, 1.0, 0.0);						
			break;
	}

    glutPostRedisplay();
}


void EspecificaParametrosVisualizacao(void)
{
	// Especifica sistema de coordenadas de projeção
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de projeção
	glLoadIdentity();

	// Especifica a projeção perspectiva
	gluPerspective(angle,fAspect,0.4,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posição do observador e do alvo
	gluLookAt(0,80,200, 0,0,0, 0,1,0); // 1º,2º,3º -> coordenadas do observador | 4º,5º,6º -> coordenadas do alvo | 7º,8º,9º -> vetor UP, estabelece o 'lado de cima'
}


void keyboard(unsigned char key, int x, int y)
{
	int hor, ver;
	hor = 0; ver = 0;

	switch (key) {
		case 27:
			exit(0);
			break;
		case 'f':
			// desliga luzes
			glDisable(GL_LIGHTING);  
			break;	
		case 'g':
			// liga luzes
			glEnable(GL_LIGHTING);
			break;
		case 'r':
			// reseta
			EspecificaParametrosVisualizacao();
			break;
   }
   
   glutPostRedisplay();
}

void SpecialKeyboard(int key, int x, int y)
{
    if(key == GLUT_KEY_UP) {
		Rotaciona(1); // em x
    }
    else if(key == GLUT_KEY_DOWN) {
		Rotaciona(-1); // em -x
    }
	else if(key == GLUT_KEY_RIGHT) {
		Rotaciona(2); // em y
    }
	else if(key == GLUT_KEY_LEFT) {
		Rotaciona(-2); // em -y
    }
	
    glutPostRedisplay();
}


void GerenciaMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-in
			if (angle >= 10) angle -= 5;
		}
	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN) {  // Zoom-out
			if (angle <= 130) angle += 5;
		}
	EspecificaParametrosVisualizacao();
	glutPostRedisplay();
}


void initLights(){
	GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={0.7,0.7,0.7,-.2};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={0.0, -100.0, 250.0, 1.0};      

	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;    
	// Define a refletância do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentração do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial); 
	GLfloat mat_transparent[] = { 0.0, 0.8, 0.8, 0.6 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_transparent); 

	// Define os parâmetros da luz de número 0
	//glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); // melhor SEM
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );    

	// Habilita a definição da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);  
	// Habilita a luz de número 0
	glEnable(GL_LIGHT0);	
    // Habilita o MultiSampling Anti-Aliasing
    glEnable(GL_MULTISAMPLE_ARB);	
}


void init(void)
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	
	angle=45; // angulo de visao
	
	//glMap2f( type of value generated, 0, 1, number of floats inside [0][0], dimension of array in 'u' axis,
	// 0, 1, number of floats in [0], dimension of array in 'v' axis, pointer to array )
	glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
			0, 1, 12, 4, &curvedSurface[0][0][0]);		
	// cria vertex do curvedSurface
	glEnable(GL_MAP2_VERTEX_3);

	// preenchimento da superficie curva
	glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	glShadeModel(GL_SMOOTH);

	// cria quadradric usado para criar cilindros
	qobj = gluNewQuadric();
  	gluQuadricNormals(qobj, GLU_SMOOTH);

	// inicia configurações de iluminação
	initLights();

	// configura buffer de profundidade
	glEnable(GL_DEPTH_TEST);
}


void reshape(int w, int h)
{
	// Para previnir uma divisão por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a correção de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;

	EspecificaParametrosVisualizacao();
}


int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
   glutInitWindowSize (700, 700);
   glutInitWindowPosition (100, 100);
   glutCreateWindow ("Parada FURG");
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keyboard);
   glutSpecialFunc(SpecialKeyboard); 
   glutMouseFunc(GerenciaMouse);
   init ();
   glutMainLoop();
}