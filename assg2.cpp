// ch01.cpp : Defines the entry point for the console application.
//
//////////////////////////////////////////////////////////
//  triangles.cpp  from the OpenGL Red Book   Chapter 1
//////////////////////////////////////////////////////////

#include <iostream>
#include <cmath>
#include <stdio.h>
using namespace std;

#include "vgl.h"
#include "LoadShaders.h"

const GLuint Triangles = 0, Triangle = 1, Circle = 2, NumVAOs = 3;
const GLuint ArrayBuffer=0, TriBuffer = 1, TriColorBuffer = 2, CircBuffer = 3, CircColorBuffer = 4, NumBuffers=5;
const GLuint trisVert = 0, triVert = 1, triColor = 2, circVert = 3, circColor = 4;

GLuint Program, Program2;

const int debug = 1, debug_level2 = 1;
bool X = 1, Y = 1, Z = 0, W = 0, S = 0;
float C1 = 0.0f, C2 = 0.0f, C3 = 1.0f, G_RAD = 0.5f;
int G_NUM = 21;

GLuint VAOs[NumVAOs];
GLuint Buffers[NumBuffers];
GLuint elementbuffer;
GLuint elementbuffer2;

GLfloat circ_vert2[6][2] = {
	{0.25, 0.43301},
	{-0.25, 0.433013},
	{-0.5, 0.0},
	{-0.25, -0.433012},
	{0.25, -0.433014},
	{0.5, 0.0}
};

const GLuint NumTrisVertices = 6, NumTriVertices = 3;
const GLfloat Pi = 3.14159f;
GLuint NumCircVertices = 6;
/*
struct VertexData {
	GLubyte color[4];
	GLfloat position[2];
};

struct Color {
	GLuint col[4];
};

struct Vertex {
	GLfloat position[4];
};
*/
/////////////////////////////////////////////////////
//  int
/////////////////////////////////////////////////////
void init (void )
{
	glGenVertexArrays( NumVAOs, VAOs );
	glBindVertexArray( VAOs[Triangles]);

	GLfloat tris_vertices[6][2] = {
		{ -0.90f, -0.90f },
		{ 0.85f, -0.90f },
		{ -0.90f, 0.85f },
		{ 0.90f, -0.85f },
		{ 0.90f, 0.90f },
		{ -0.85f, 0.90f }
	};

	glGenBuffers(NumBuffers, Buffers);
	glBindBuffer(GL_ARRAY_BUFFER, Buffers[ArrayBuffer]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(tris_vertices), tris_vertices, GL_STATIC_DRAW);


	ShaderInfo  shaders[] = {
		{ GL_VERTEX_SHADER, "triangles.vert" },
		{ GL_FRAGMENT_SHADER, "triangles.frag" },
		{ GL_NONE, NULL }
	};

	Program = LoadShaders( shaders );
	glUseProgram( Program );

	glVertexAttribPointer(trisVert, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(trisVert);

	GLfloat tri_vertices[3][2] = {
		{ -0.90f, -0.90f },
		{ 0.00f, 0.90f },
		{ 0.90f, -0.90f }
	};

	GLfloat tri_color[3][4] = {
		{ 0.0f, 0.0f, 1.0f, 1.0f },
		{ 1.0f, 0.0f, 0.0f, 1.0f },
		{ 0.0f, 1.0f, 0.0f, 1.0f }
	};


	glBindBuffer( GL_ARRAY_BUFFER, Buffers[TriBuffer] );
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri_vertices), tri_vertices, GL_STATIC_DRAW);

	glBindBuffer( GL_ARRAY_BUFFER, Buffers[TriColorBuffer] );
	glBufferData( GL_ARRAY_BUFFER, sizeof(tri_color), tri_color, GL_STATIC_DRAW );

	ShaderInfo  shaders2[] = {
                { GL_VERTEX_SHADER, "triangle.vert" },
                { GL_FRAGMENT_SHADER, "triangle.frag" },
                { GL_NONE, NULL }
        };

	Program2 = LoadShaders( shaders2 );
        glUseProgram( Program2 );

	glBindVertexArray( VAOs[Triangle] );
	glEnableVertexAttribArray(triVert);
	glEnableVertexAttribArray(triColor);

	glBindBuffer( GL_ARRAY_BUFFER, Buffers[TriBuffer] );
	glVertexAttribPointer(triVert, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer( GL_ARRAY_BUFFER, Buffers[TriColorBuffer] );
	glVertexAttribPointer(triColor, 4, GL_FLOAT, GL_FALSE, 0, NULL);

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[CircBuffer]);

	glUseProgram( Program );

	glBindVertexArray(VAOs[Circle]);
	glEnableVertexAttribArray(trisVert);

	glBindBuffer( GL_ARRAY_BUFFER, Buffers[CircBuffer] );
	glVertexAttribPointer(trisVert, 2, GL_FLOAT, GL_FALSE, 0, NULL);

}

void print_circ()
{
/*	if(debug) {
		for(int i = 0; i < G_NUM; i++)
		{
			for(int j = 0; j < 2; j++)
			{
				cout << "circ_vert2: " << circ_vert2[i][j] << " " << &circ_vert2[i][j] << endl;
				cout << "circ_vertices: " << circ_vertices[i][j] << " " << &circ_vertices[i][j] << endl;
			}
			cout << endl;
		}
	}
*/}

////////////////////////////////////////////////////////////////////
//	display
////////////////////////////////////////////////////////////////////
void display (void )
{
	glClear( GL_COLOR_BUFFER_BIT );

	if(W)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		W = !W;
	}
	if(S)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		S= !S;
	}

	glUseProgram( Program );
	glBindVertexArray( VAOs[Triangles] );
	glDrawArrays( GL_TRIANGLES, 0, NumTrisVertices );
//	else glDrawArrays( GL_LINE_LOOP, 0, NumTrisVertices );

	glUseProgram( Program2 );
	glBindVertexArray( VAOs[Triangle] );
        glDrawArrays( GL_TRIANGLES, 0, NumTriVertices );
//	else glDrawArrays( GL_LINE_LOOP, 0, NumTrisVertices );

	if(Z)
	{
		glUseProgram( Program );
		glBindVertexArray( VAOs[Circle] );
		glDrawArrays(GL_TRIANGLE_FAN, 0, G_NUM+2 );
//		else glDrawArrays( GL_LINE_LOOP, 0, G_NUM );
	}


	glFlush();
}

void generate_circle_verts(GLuint num)
{
	GLfloat yval = 0.0f, xval = 0.0f;

	GLfloat circ_vertices[num+1][2];

	if(debug) {
		cout << "Size of circ_vert2: " << sizeof(circ_vert2) << endl;
		cout << "Size of circ_vertices: " << sizeof(circ_vertices)*G_NUM << endl;
		cout << "Size of circ_vertices_memory: " << sizeof(GLfloat) << endl;
	}

	circ_vertices[0][0] = 0.0f;
	circ_vertices[0][1] = 0.0f;

	for(int i = 2; i <= num+2; i++)
	{
		for(int j = 1; j <= 2; j++)
		{
			if(j == 1)
			{
				xval = G_RAD*std::cos((2*Pi/(num))*i);
				cout << xval;
				circ_vertices[i-1][j-1] = xval;
			}
			if(j == 2)
			{
				yval = G_RAD*std::sin((2*Pi/(num))*i);
				cout << " " << yval << endl;
				circ_vertices[i-1][j-1] = yval;
			}
		}
	}

	glBindBuffer(GL_ARRAY_BUFFER, Buffers[CircBuffer]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(circ_vertices)*num, circ_vertices, GL_DYNAMIC_DRAW);
}

void generate_circle()
{
	fflush(stdin);
	if(debug | debug_level2)
		cout << "User has selected to generate a circle. Please input radius value as float: ";
	cin >> G_RAD;
	if(debug | debug_level2)
		cout << "Please input number of steps to estimate circle: ";
	cin >> G_NUM;
	generate_circle_verts(G_NUM);
	return;
}

void set_color()
{
	GLint TrisLoc = glGetUniformLocation(Program, "myColor");
	float newCol[4] = { C1, C2, C3, 1.0 };
	glProgramUniform4fv(Program, TrisLoc, 1, newCol);
}

void change_color()
{
	fflush(stdin);
	if(debug | debug_level2)
		cout << "User has selected to change the color. Please input color value for red as float: ";
	cin >> C1;
	if(debug | debug_level2)
		cout << "Please input color value for green as float: ";
	cin >> C2;
	if(debug | debug_level2)
                cout << "Please input color value for blue as float: ";
        cin >> C3;
	set_color();
	return;
}

void idle_CB()
{
//	glutPostRedisplay();
}

void SpecialInput(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:
			if(debug)
                                cout << key << " up received" << endl;
			break;
		case GLUT_KEY_DOWN:
			if(debug)
                                cout << key << " down received" << endl;
                        break;
		case GLUT_KEY_LEFT:
			if(debug)
                                cout << key << " left received" << endl;
                        break;
		case GLUT_KEY_RIGHT:
			if(debug)
                                cout << key << " right received" << endl;
                        break;
		default:
			if(debug)
                                cout << "[default] " << key << " received and not handled." << endl;
                        break;
	}
}

void key_CB(unsigned char key, int x_cord, int y_cord)
{
	switch (key)
	{
		case 'd': case 'D':
			if(debug)
                                cout << key << " received" << endl;
			break;
                case 'f': case 'F':
			if(debug)
                                cout << key << " received" << endl;
                        break;
                case 'c': case 'C':
			if(debug)
                                cout << key << " received" << endl;
                        break;
                case 'v': case 'V':
			if(debug)
                                cout << key << " received" << endl;
                      	break;
		case 'r': case 'R':
			if(debug)
                                cout << key << " received" << endl;
                        break;
		case 'w': case 'W':
			W = !W;
			if(debug)
                                cout << key << " received" << endl;
			display();
                        glutPostRedisplay();
                        break;
		case 's': case 'S':
			S = !S;
			if(debug)
                                cout << key << " received" << endl;
			display();
                       	glutPostRedisplay();
                        break;
                case 'x': case 'X':
			if(debug)
                                cout << key << " received" << endl;
                        break;
                case 'z': case 'Z':
			if(debug)
                                cout << key << " received" << endl;
                        break;
                // Quits application
                case 'q': case 'Q': case 27:
			if(debug)
				cout << key << " received" << endl;
                        exit(0); 
                        break;
                
                default:
			if(debug)
                        	cout << "[default] " << key << " received and not handled." << endl;
                        break;
	}
}                


////////////////////////////////////////////////////////////////////////
//	main
////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[])
{
	// initialize GLUT system
	glutInit( &argc, argv );

	// initialize display format
//	glutInitDisplayMode( GLUT_RGB );
	/* UNCOMMENT THIS LINE FOR GS930*/
	glutInitDisplayMode( GLUT_3_2_CORE_PROFILE | GLUT_RGBA );

	// initialize window size
	glutInitWindowSize( 512, 512 );


//	glutInitContextVersion( 4, 3 );
//	glutInitContextProfile( GLUT_CORE_PROFILE );// GLUT_COMPATIBILITY_PROFILE );
	/*UNCOMMENT THESE 2 LINES FOR GS 930*/


	// create window with name from executable
	glutCreateWindow( argv[0] );

	glutIdleFunc(idle_CB);

	glutKeyboardFunc(key_CB);

	glutSpecialFunc(SpecialInput);

	glewExperimental = GL_TRUE;	// added for glew to work!
	if ( glewInit() )
	{
		cerr << "Unable to initialize GLEW ... exiting" << endl;
		exit (EXIT_FAILURE );
	}

	// code from OpenGL 4 Shading Language cookbook, second edition
	const GLubyte *renderer = glGetString( GL_RENDERER );
	const GLubyte *vendor = glGetString( GL_VENDOR );
	const GLubyte *version = glGetString( GL_VERSION );
	const GLubyte *glslVersion = glGetString (GL_SHADING_LANGUAGE_VERSION );
	GLint major, minor;
	glGetIntegerv( GL_MAJOR_VERSION, &major );
	glGetIntegerv( GL_MINOR_VERSION, &minor );

	cout << "GL Vendor            :" << vendor << endl;
	cout << "GL Renderer          :" << renderer  << endl;
	cout << "GL Version (string)  :" << version << endl;
	cout << "GL Version (integer) :" << major << " " << minor << endl;
	cout << "GLSL Version         :" << glslVersion << endl;
	//
	//GLint nExtensions;
	//glGetIntegerv( GL_NUM_EXTENSIONS, &nExtensions );
	//for ( int i = 0; i < nExtensions; i++ )
	//	cout << glGetStringi( GL_EXTENSIONS, i )  << endl;

	init();
	glutDisplayFunc( display );
	glutMainLoop();

	return 0;
}

