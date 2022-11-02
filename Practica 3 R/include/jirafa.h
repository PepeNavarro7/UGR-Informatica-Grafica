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

const float ALTURA=1.0, ARTIC=0.065;

//Parte mis clases
class _cuerpo: public _triangulos3D{
       public:
              _cuerpo();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float ancho;
              float alto;
              float fondo;

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
class _articulacion: public _triangulos3D{
       public: 
              _articulacion();
              void draw(_modo modo, float r, float g, float b, float grosor);
              float radio;
       protected:
              _esfera esfera;
};

class _pata: public _triangulos3D{
       public:
              _pata();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float largo, ancho;
       protected:
              _cilindro cilindro;
};

class _cabeza: public _triangulos3D{
       public:
              _cabeza();
              void draw(_modo modo, float r, float g, float b, float grosor);
              float largo;
       protected:
             _objeto_ply ply;
};

class _jirafa: public _triangulos3D{
       public:
              _jirafa();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float giro_cuerpo,giro_cola, giro_cuello_1, giro_cuello_2, giro_cabeza;

              float giro_cola_max, giro_cola_min, giro_cuello_1_max, giro_cuello_1_min,
              giro_cuello_2_max, giro_cuello_2_min, giro_cabeza_max, giro_cabeza_min;
       protected:
       _cuerpo cuerpo;
       _cola cola;
       _cuello cuello; // cuello son 2 partes
       _articulacion articulacion;
       _pata pata;
       _cabeza cabeza;
};

#endif