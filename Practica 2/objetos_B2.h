//**************************************************************************
// Práctica 2 
//**************************************************************************

#include <vector>
#include <GL/gl.h>
#include "vertex.h"
#include <stdlib.h>


const float AXIS_SIZE=5000;
const int REALISTA=24; // numero de vertices de un poligono regular para que se "convierta" en circunferencia
typedef enum{POINTS,EDGES,SOLID,SOLID_COLORS,
			 COMPLETO, VERTICES_COLORES, SOLIDO_VERTICES_COLORES} _modo; // Modos de dibujo


// Clase punto, contiene vector de vertices y de colores
class _puntos3D{
	public:
		vector<_vertex3f> vertices;

		_puntos3D();
		void draw_puntos(float r, float g, float b, int grosor);
		void draw_vertices_colores(int grosor=0.5);
	protected:
		vector<_vertex3f> colores;
};

// clase triángulo, usada para dibujar, contiene vector de caras
class _triangulos3D: public _puntos3D{
	public:
		vector<_vertex3i> caras;
	
		_triangulos3D();
		void draw_aristas(float r, float g, float b, int grosor);
		void draw_solido(float r, float g, float b);
		void draw_solido_colores();
		void draw_completo();
		void draw_solido_vertices();
		void draw(_modo modo, float r, float g, float b, float grosor);
};

// clase cubo
class _cubo: public _triangulos3D{
	public:
		_cubo(float tam=0.5);
};

// clase piramide
class _piramide: public _triangulos3D{
	public:
		_piramide(float tam=0.5, float al=1.0);
};

// clase objeto ply
class _objeto_ply: public _triangulos3D{
	public:
		_objeto_ply(char *archivo);
};

// clase objeto por revolución, con metodos para girar puntos
class _rotacion: public _triangulos3D{
	public:
		_rotacion();
		void  parametros(const vector<_vertex3f> &perfil, int num_perfiles, int tipo, bool tapa_inf, bool tapa_sup);
	private:
		void rota_lateral(const vector<_vertex3f> &perfil, _vertex3f centro, int num_giros=REALISTA);
		void dibuja_circunferencia(_vertex3f centro, float radio, int num_perfiles);
		void pinta_cara(_vertex3f centro, int tam_perfil, int num_perfiles, int altura);

};


// objeto por extrusión
class _extrusion: public _triangulos3D{
	public:
		_extrusion(vector<_vertex3f> poligono, float x, float y, float z);
};

//Cono
class _cono: public _rotacion{
	public:
		_cono(_vertex3f centro, float r=0.5, float h=1.0);
};

//Cilindro
class _cilindro: public _rotacion{
	public:
		_cilindro(_vertex3f centro, float radio=0.5, float altura=1.0);
};

// Esfera
class _esfera: public _rotacion{
	public:
		_esfera(_vertex3f centro, float radio=0.5);
};

// Perfil de PLY que se gira
class _perfil_ply: public _rotacion{
	public:
		_perfil_ply(char* archivo);
	
};

// Semiesfera
class _semiesfera: public _rotacion{
	public:
		_semiesfera(_vertex3f centro, float radio);
};
