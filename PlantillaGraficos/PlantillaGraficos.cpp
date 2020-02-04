// PlantillaGraficos.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

using namespace std;
//Declarar una ventana
GLFWwindow* window;

float posXTriangulo=0.0f, posYTriangulo=0.0f, angulo = 0.0f;
double tiempoActual, tiempoAnterior;
double velocidadTriangulo = 0.8;
double velocidadRotacion = 0.1;

void actualizar() {
	tiempoActual = glfwGetTime();
	double tiempoDiferencial = tiempoActual - tiempoAnterior;
	int anguloDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (anguloDerecha == GLFW_PRESS) { 
		angulo -= velocidadRotacion;
	}
	int anguloIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (anguloIzquierda == GLFW_PRESS) {
		angulo += velocidadRotacion;
	}
	int estadoArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoArriba == GLFW_PRESS) {
		double comX = sin(angulo * 3.1416 / 180);
		double comY = cos(angulo * 3.1416 / 180);
		posYTriangulo += comY*(velocidadTriangulo*tiempoDiferencial);
		posXTriangulo -= comX*(velocidadTriangulo * tiempoDiferencial);
	}
	tiempoAnterior = tiempoActual;
	if (angulo >= 360)
	{
		angulo -= 360;
	}
	if (angulo<360)
	{
		angulo += 360;
	}

}

void dibujar() {
	glPushMatrix();
	glTranslatef(posXTriangulo,posYTriangulo,0.0f);
	glRotatef(angulo, 0.0f, 0.0f, 1.0f);

	glBegin(GL_TRIANGLES);

	glColor3f(0.02f, 0.6f, 0.1f);
	glVertex3f(0.0f, 0.15f, 0.0f);
	glVertex3f(-0.15f, -0.15f, 0.0f);
	glVertex3f(0.15f, -0.15f, 0.0f);

	glEnd();

	glPopMatrix();
}

int main()
{

	//Si no se pudo iniciar GLFW
	//Terminamos la ejecución
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
	//Si se pudo iniciar GLFW
	//Inicializamos la ventana
	window = glfwCreateWindow(600, 600, "Ventana", NULL, NULL); 

	//Si no se pudo crear la ventana
	//Terminamos la ejecución
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	//Establecemos la ventana como contexto

	glfwMakeContextCurrent(window);

	//una vez establecido el contexto
	//se activan las funciones "modernas" (gpu)
	glewExperimental = true;

	GLenum errores = glewInit();
	if (errores != GLEW_OK) {
		glewGetErrorString(errores);
	}

	const GLubyte* versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//Establecemos que con cada evento de teclado se llama a la funcion teclado_Callback

	//glfwSetKeyCallback(window, teclado_Callback);
	tiempoActual = glfwGetTime();
	tiempoAnterior = tiempoActual;
	//Ciclo de dibujo (DrawLoop)
	while (!glfwWindowShouldClose(window)) {

		//Establecer región de dibujo
		glViewport(00, 0, 600, 600);
		//Establecemos el color de borrado
		//Valores RGBA
		glClearColor(1, 1, 0.5, 1);
		//Borrar
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Actualizar valores y dibujar
		actualizar();
		dibujar();
		glfwPollEvents();
		glfwSwapBuffers(window);

	}
	//Después del ciclo de dibujo
	//Eliminamos ventana y procesos de GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

}