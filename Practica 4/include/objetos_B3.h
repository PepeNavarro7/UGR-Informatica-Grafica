//**************************************************************************
// Práctica 2 
//**************************************************************************
#ifndef _OBJETOS_B3
#define _OBJETOS_B3


#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS,
COMPLETO, SOLID_FLAT, SOLID_SMOOTH} _modo;

//*************************************************************************
// clase punto
//*************************************************************************

class _puntos3D
{
public:

  
	_puntos3D();
void 	draw_puntos(float r, float g, float b, int grosor);

vector<_vertex3f> vertices;
vector<_vertex3f> colores_vertices;
};

//*************************************************************************
// clase triángulo
//*************************************************************************

class _triangulos3D: public _puntos3D{
public:

       vector<_vertex3i> caras; // Ternas de vertices que componen cada cara (_0,_1,_2)
       vector<_vertex3f> colores_caras; // rgb del color de cada cara (r,g,b)
       vector<_vertex3f> normales_caras; // xyz del vector normal a cada cara
       vector<_vertex3f> normales_vertices; // xyz del vector normal a cada vertice

       // material
       _vertex4f ambiente_difuso; // coeficientes ambinete y difuso
       _vertex4f especular; // coeficiente especular
       float brillo; // exponente del brillo
       _triangulos3D();
       void 	draw_aristas(float r, float g, float b, int grosor);
       void   draw_solido(float r, float g, float b);
       void 	draw_solido_colores();
       void   draw_solido_plano();
       void   draw_solido_suave();
       void 	draw(_modo modo, float r, float g, float b, float grosor);

       /* asignación de colores */
       void 	colors_random();
       void 	colors_chess(float r1, float g1, float b1, float r2, float g2, float b2);
       void   colors_flat(float r, float g, float b, float p_lx, float p_ly, float p_lz);
// Hacer para punto extra
//       void   colors_smooth(float r, float g, float b, float p_lx, float p_ly, float p_lz);

       /* Calcular normales*/

       void   calcular_normales_caras();
       void   calcular_normales_vertices();

       
};

#endif