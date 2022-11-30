//**************************************************************************
// Práctica 2 
//**************************************************************************
#ifndef _JIRAFA
#define _JIRAFA


#include <vector>
#include <GL/gl.h>
#include "../include/vertex.h"
#include <stdlib.h>
#include "objetos_solidos.h"
#include "objetos_revolucion.h"

const float ALTURA=1.0, ARTIC=0.065;

//Mis clases
// Cuerpo de la jirafa, el eje central
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

// Cola de la jirafa, se moverá arriba y abajo
class _cola: public _triangulos3D{
       public:
              _cola();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float largo;
              float ancho;
       protected:
              _cilindro cilindro;
};

// El cuello tendrá dos instancias distintas, para permitir más mobilidad
class _cuello: public _triangulos3D{
       public:
              _cuello();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float largo;
              float ancho;
       protected:
              _cilindro cilindro;

};

// Pequeña articulación esférica para que no quede muy feo el cruce entre objetos
class _articulacion: public _triangulos3D{
       public: 
              _articulacion();
              void draw(_modo modo, float r, float g, float b, float grosor);
              float radio;
       protected:
              _esfera esfera;
};

// Las 4 patas
class _pata: public _triangulos3D{
       public:
              _pata();
              void draw(_modo modo, float r, float g, float b, float grosor);

              float largo, ancho;
       protected:
              _cilindro cilindro;
};

// La cabeza viene detallada en el archivo PLY
class _cabeza: public _triangulos3D{
       public:
              _cabeza();
              void draw(_modo modo, float r, float g, float b, float grosor);
              float largo;
       protected:
             _objeto_ply ply;
};

// La clase que aglutina las demás
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
              _articulacion articulacion; // pequeña esfera
              _pata pata;
              _cabeza cabeza;
};

#endif