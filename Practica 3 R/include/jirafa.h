//**************************************************************************
// Práctica 2 
//**************************************************************************
#ifndef _JIRAFA
#define _JIRAFA


#include <vector>
#include <GL/gl.h>
#include "../include/vertex.h"
#include <stdlib.h>
#include "objetos_B3.h"


//Parte mis clases
class _cuerpo: public _triangulos3D{
       public:
              _cuerpo();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float ancho;
              float alto;
              float fondo;
              float altura;

       protected:
              _cubo cubo;
};

class _cola: public _triangulos3D{
       public:
              _cola();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float largo;
              float ancho;
       protected:
              _cilindro cilindro;
};

class _cuello: public _triangulos3D{
       public:
              _cuello();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float largo;
              float ancho;
       protected:
              _cilindro cilindro;

};

class _jirafa: public _triangulos3D{
       public:
              _jirafa();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float giro_cuerpo;
              float giro_cola;
              float giro_cuello_1;
              float giro_cuello_2;

              float giro_cola_max;
              float giro_cola_min;
              float giro_cuello_1_max;
              float giro_cuello_1_min;
              float giro_cuello_2_max;
              float giro_cuello_2_min;
       protected:
       _cuerpo cuerpo;
       _cola cola;
       _cuello cuello; // cuello tiene 2 partes
};

#endif