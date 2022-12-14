#ifndef _EXCAVADORA
#define _EXCAVADORA

#include "objetos_solidos.h"
#include "objetos_revolucion.h"

//************************************************************************
// práctica 3, objeto jerárquico articulado excavadora
//************************************************************************

//************************************************************************
// piezas
//************************************************************************

//************************************************************************
// pala
//************************************************************************

class _pala: public _triangulos3D
{
public:
      _pala(float radio=1.0, float ancho=2.0, int num=8);
};

//************************************************************************
// brazo
//************************************************************************

class _brazo: public _triangulos3D
{
public:
      _brazo();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

//************************************************************************
// cabina
//************************************************************************

class _cabina: public _triangulos3D
{
public:
       _cabina();
void  draw(_modo modo, float r, float g, float b, float grosor);

float ancho;
float alto;
float fondo;

protected:
_cubo cubo;
};

//************************************************************************
// sustentación
//************************************************************************

class _sustentacion: public _triangulos3D
{
public:
      _sustentacion();
void  draw(_modo modo, float r, float g, float b, float grosor);
       
float ancho;
float alto;
float fondo;

float radio;

protected:
_cilindro rueda;
_cubo base;
};

//************************************************************************
// excavadora (montaje del objeto final)
//************************************************************************

class _excavadora: public _triangulos3D
{
public:
       _excavadora();
       
void  draw(_modo modo, float r, float g, float b, float grosor);

float giro_cabina;
float giro_primer_brazo;
float giro_segundo_brazo;
float giro_pala;

float giro_primer_brazo_max;
float giro_primer_brazo_min;
float giro_segundo_brazo_max;
float giro_segundo_brazo_min;
float giro_pala_max;
float giro_pala_min;

float tamanio_pala;

protected:
_pala pala;
_brazo brazo;
_cabina cabina;
_sustentacion sustentacion;
};

#endif