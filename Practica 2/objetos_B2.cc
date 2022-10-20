//**************************************************************************
// Práctica 2 
//**************************************************************************

#include "objetos_B2.h"
#include "file_ply_stl.hpp"


//*************************************************************************
// _puntos3D
//*************************************************************************

_puntos3D::_puntos3D(){
	_vertex3f aux;
	for(int i=0;i<=2;++i){
		for(int j=0;j<=2;++j){
			for(int k=0;k<=2;++k){
				aux.r=(1.0*i)/2.0;
				aux.g=(1.0*j)/2.0;
				aux.b=(1.0*k)/2.0;
				colores.push_back(aux);
			}
		}
	}
	colores.pop_back(); // quitamos el blanco (1.0,1.0,1.0)
	colores.erase(colores.begin()); // y el negro (0.0,0.0,0.0)
}

//*************************************************************************
// dibujar puntos
//*************************************************************************

void _puntos3D::draw_puntos(float r, float g, float b, int grosor){
	glPointSize(grosor);
	glColor3f(r,g,b);
	glBegin(GL_POINTS);
	for (long unsigned int i=0;i<vertices.size();i++){
		glVertex3fv((GLfloat *) &vertices[i]);
		}
	glEnd();
}

// Dibujar un vertice de cada color
void _puntos3D::draw_vertices_colores(int grosor){
	glPointSize(grosor);
	glBegin(GL_POINTS);
	for (long unsigned int i=0; i<vertices.size(); i++){
		int aux = i%colores.size();
		glColor3f(
			colores[aux].r,
			colores[aux].g,
			colores[aux].b);
		glVertex3fv((GLfloat *) &vertices[i]);
	}
	glEnd();
}


//*************************************************************************
// _triangulos3D
//*************************************************************************

_triangulos3D::_triangulos3D(){
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************

void _triangulos3D::draw_aristas(float r, float g, float b, int grosor){
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glLineWidth(grosor);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (long unsigned int i=0;i<caras.size();i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b){
  	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(r,g,b);
	glBegin(GL_TRIANGLES);
	for (long unsigned int i=0; i<caras.size(); i++){
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}

void _triangulos3D::draw_completo(){
	this->draw_puntos(1.0,0.0,0.0,0.5);
	this->draw_aristas(0.0,0.0,0.0,0.5);
	this->draw_solido_colores();
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores(){
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (long unsigned int i=0; i<caras.size(); i++){
		int aux = i%colores.size();
		glColor3f(
			colores[aux].r,
			colores[aux].g,
			colores[aux].b);
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}


//Dibujar con colores para cada vertice
void _triangulos3D::draw_solido_vertices(){
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_TRIANGLES);
	for (long unsigned int i=0; i<caras.size(); i++){
		glColor3f( colores[caras[i]._0%colores.size()].r, colores[caras[i]._0%colores.size()].g, colores[caras[i]._0%colores.size()].b );
		glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
		glColor3f( colores[caras[i]._1%colores.size()].r, colores[caras[i]._1%colores.size()].g, colores[caras[i]._1%colores.size()].b );
		glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
		glColor3f( colores[caras[i]._2%colores.size()].r, colores[caras[i]._2%colores.size()].g, colores[caras[i]._2%colores.size()].b );
		glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
	}
	glEnd();
}
//*************************************************************************
// dibujar con distintos modos
//*************************************************************************

void _triangulos3D::draw(_modo modo, float r, float g, float b, float grosor){
	switch (modo){
		case POINTS:draw_puntos(r, g, b, grosor);break;
		case EDGES:draw_aristas(r, g, b, grosor);break;
		case SOLID:draw_solido(r, g, b);break;
		case SOLID_COLORS:draw_solido_colores();break;
		case COMPLETO: draw_completo(); break;
		case VERTICES_COLORES: draw_vertices_colores(grosor); break;
		case SOLIDO_VERTICES_COLORES: draw_solido_vertices(); break;
	}
}



//*************************************************************************
// clase cubo
//*************************************************************************

_cubo::_cubo(float tam){

	vertices.resize(8); 
	// Dibujamos con el vertice inferior izquierdo (el 0) en el centro de los ejes
	vertices[0].x=0.0; vertices[0].y=0.0; vertices[0].z=0.0;
	vertices[1].x=tam; vertices[1].y=0.0; vertices[1].z=0.0;
	vertices[2].x=0.0; vertices[2].y=0.0; vertices[2].z=tam;
	vertices[3].x=tam; vertices[3].y=0.0; vertices[3].z=tam;
	vertices[4].x=0.0; vertices[4].y=tam; vertices[4].z=0.0;
	vertices[5].x=tam; vertices[5].y=tam; vertices[5].z=0.0;
	vertices[6].x=0.0; vertices[6].y=tam; vertices[6].z=tam;
	vertices[7].x=tam; vertices[7].y=tam; vertices[7].z=tam;
	for(int i=0;i<8;++i){ // Centramos el cubo en la interseccion de los ejes
		vertices[i].x-=tam/2; vertices[i].y-=tam/2; vertices[i].z-=tam/2;
	}

	caras.resize(12);
	caras[0]._0=0; caras[0]._1=1; caras[0]._2=2;
	caras[1]._0=1; caras[1]._1=3; caras[1]._2=2; // abajo
	caras[2]._0=0; caras[2]._1=1; caras[2]._2=4;
	caras[3]._0=1; caras[3]._1=5; caras[3]._2=4; // frente
	caras[4]._0=1; caras[4]._1=3; caras[4]._2=5;
	caras[5]._0=3; caras[5]._1=7; caras[5]._2=5; // derecha
	caras[6]._0=0; caras[6]._1=2; caras[6]._2=4;
	caras[7]._0=2; caras[7]._1=6; caras[7]._2=4; // izquierda
	caras[8]._0=2; caras[8]._1=3; caras[8]._2=6;
	caras[9]._0=3; caras[9]._1=7; caras[9]._2=6; // trasera
	caras[10]._0=4;caras[10]._1=5;caras[10]._2=6;
	caras[11]._0=5;caras[11]._1=7;caras[11]._2=6; // arriba

}


//*************************************************************************
// clase piramide (piramide cuadrada)
//*************************************************************************
_piramide::_piramide(float tam, float al){
	
	vertices.resize(5); 
	vertices[0].x=-tam;vertices[0].y=0;vertices[0].z=tam;
	vertices[1].x=tam;vertices[1].y=0;vertices[1].z=tam;
	vertices[2].x=tam;vertices[2].y=0;vertices[2].z=-tam;
	vertices[3].x=-tam;vertices[3].y=0;vertices[3].z=-tam;
	vertices[4].x=0;vertices[4].y=al;vertices[4].z=0;

	caras.resize(6);
	caras[0]._0=0;caras[0]._1=1;caras[0]._2=4;
	caras[1]._0=1;caras[1]._1=2;caras[1]._2=4;
	caras[2]._0=2;caras[2]._1=3;caras[2]._2=4;
	caras[3]._0=3;caras[3]._1=0;caras[3]._2=4;
	caras[4]._0=3;caras[4]._1=1;caras[4]._2=0;
	caras[5]._0=3;caras[5]._1=2;caras[5]._2=1;
}

//*************************************************************************
// clase objeto ply
//*************************************************************************
_objeto_ply::_objeto_ply(char* archivo){

	int n_ver,n_car;

	vector<float> ver_ply ;
	vector<int>   car_ply ;
	
	_file_ply::read(archivo, ver_ply, car_ply );

	n_ver=ver_ply.size()/3;
	n_car=car_ply.size()/3;

	printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

	vertices.resize(n_ver);
	for (int i=0;i<n_ver;++i){
		vertices[i].x=ver_ply[3*i];
		vertices[i].y=ver_ply[3*i+1];
		vertices[i].z=ver_ply[3*i+2];
	}

	caras.resize(n_car);
	for (int i=0;i<n_car;++i){
		caras[i].x=car_ply[3*i];
		caras[i].y=car_ply[3*i+1];
		caras[i].z=car_ply[3*i+2];
	}
}


//************************************************************************
// objeto por revolucion
//************************************************************************
_rotacion::_rotacion(){
}

void _rotacion::parametros(const vector<_vertex3f> &perfil, int num_perfiles, int tipo, bool tapa_inf, bool tapa_sup){
	switch (tipo){
		case 0: { // rotacion normal de un perfil centrado en el eje, con o sin tapas
			int tam_perfil = perfil.size();
			// Con la funcion rota_lateral() extrapolo la creacion de la cortina lateral, con vertices y caras
			this->rota_lateral(perfil, _vertex3f(0.0,0.0,0.0), num_perfiles);
			// Con las funciones pinta_cara(), añado el centro y pinto esa cara, sin repetir vertices
			if(tapa_inf){
				_vertex3f centro_down;
				centro_down.x=0.0; centro_down.z=0.0; centro_down.y=perfil[0].y; // La altura es la del primer vertice
				this->pinta_cara(centro_down, tam_perfil, num_perfiles, 0);
			}
			if(tapa_sup){
				_vertex3f centro_up;
				centro_up.x=0.0; centro_up.z=0.0; centro_up.y=perfil[tam_perfil-1].y; // La altura es la del ultimo vertice
				this->pinta_cara(centro_up, tam_perfil, num_perfiles, tam_perfil-1);
			}
		} break;
		case 1: { // cono, 3 puntos, el centro de la base, un punto lateral, y la cuspide
			// primero dibujamos la circunferencia
			float radio = perfil[1].x - perfil[0].x;
			this->dibuja_circunferencia(perfil[0],radio,num_perfiles);
			if(tapa_inf) // si nos lo piden, pintamos la circunferencia
				this->pinta_cara(perfil[0],1,num_perfiles,0);
			_vertex3i cara_aux;
			vertices.push_back(perfil[2]); // cuspide
			for(int i=0;i<num_perfiles;++i){
				cara_aux._0=vertices.size()-1; // la cuspide
				cara_aux._1=i; // primer vertice del "circulo"
				cara_aux._2=((i+1)%num_perfiles); // el siguiente en el plano, hasta que de la vuelta
				caras.push_back(cara_aux);
			}
		} break;
		case 2: { // esfera, el perfil tiene puntos en el eje (superior, inferior o ambos), y el centro
			_vertex3f centro = perfil[perfil.size()-1];
			vector<_vertex3f> lateral = perfil; lateral.pop_back();
			_vertex3f vert_down = lateral[0], vert_up = lateral[lateral.size()-1];

			if(tapa_inf)
				lateral.erase(lateral.begin());
			if(tapa_sup)
				lateral.pop_back();
			// Hago la rotacion lateral de los puntos que no cruzan el eje, para no repetir vertices
			this->rota_lateral(lateral, centro, num_perfiles);
			if(tapa_inf)
				this->pinta_cara(vert_down,lateral.size(),num_perfiles,0);
			if(tapa_sup)
				this->pinta_cara(vert_up,lateral.size(),num_perfiles,lateral.size()-1);
		} break;
		case 3: { // cilindro, 3 puntos, centro, abajo y arriba, no necesariamente centrado
			vector<_vertex3f> lateral=perfil;
			_vertex3f centro=lateral[0]; lateral.erase(lateral.begin());
			this->rota_lateral(lateral, centro, num_perfiles);
			// Con las funciones pinta_cara(), añado el centro y pinto esa cara, sin repetir vertices
			if(tapa_inf){
				_vertex3f centro_down=centro;
				centro_down.y=lateral[0].y; // La altura es la del primer vertice
				this->pinta_cara(centro_down, 2, num_perfiles, 0);
			}
			if(tapa_sup){
				_vertex3f centro_up=centro;
				centro_up.y=lateral[1].y; // La altura es la del ultimo vertice
				this->pinta_cara(centro_up, 2, num_perfiles, 1);
			}
		} break;
		default:{
			cout << "Esto no debería pasar" << endl;
		} 
	}
}

// Funcion auxiliar que toma un perfil y lo rota por el eje Y, haciendo una "cortina" circular
void _rotacion::rota_lateral(const vector<_vertex3f> &perfil, _vertex3f centro, int num_giros){
	int tam_perfil=perfil.size();
	_vertex3f vert_aux;
	vector<_vertex3f> lateral=perfil;
	for(int i=0; i<tam_perfil;++i){ // centro la esfera en los ejes
		lateral[i].x-=centro.x;
		lateral[i].y-=centro.y;
		lateral[i].z-=centro.z;
	}
	//hago el giro con los puntos centrados y luego lo desplazo
	for (int i=0; i<num_giros; i++){
		for (int j=0; j<tam_perfil; j++){ // de abajo a arriba
			vert_aux.x= lateral[j].x * cos(2.0*M_PI*i/(1.0*num_giros)) +
						lateral[j].z * sin(2.0*M_PI*i/(1.0*num_giros)) + centro.x;
			vert_aux.z= lateral[j].z * cos(2.0*M_PI*i/(1.0*num_giros)) -
						lateral[j].x * sin(2.0*M_PI*i/(1.0*num_giros)) + centro.z;
			vert_aux.y= lateral[j].y + centro.y; // Se rota en lo vertical, por eso "y" no cambia
			vertices.push_back(vert_aux);
		}
	}
	// Hacemos las caras 2*(tam_perfil-1)*num_giros
	// 2 porque cada cuadradito entre 4 vertices son 2 triangulos
	// tam_perfil-1 porque se une cada vertice con el superior, y el de arriba del todo se queda suelto
	_vertex3i cara_aux;
	for(int j=0; j<num_giros; ++j){ // se rota alrededor
		for(int i=0;i<tam_perfil-1; ++i){  // y de abajo a arriba
			cara_aux._0  =i   + tam_perfil * j; // vertice original
			cara_aux._1  =i   + tam_perfil * ( (j+1)%num_giros ); // derecha
			cara_aux._2  =i+1 + tam_perfil * j; // arriba
			caras.push_back(cara_aux);
			cara_aux._0=i   + tam_perfil * ( (j+1)%num_giros ); // derecha
			cara_aux._1=i+1 + tam_perfil * ( (j+1)%num_giros ); // derecha arriba
			cara_aux._2=i+1 + tam_perfil * j; // arriba
			caras.push_back(cara_aux);
		}
	}
}

// Funcion que rota un punto lateral alrededor de un centro, y crea vértices 
void _rotacion::dibuja_circunferencia(_vertex3f centro, float radio, int num_perfiles){
	_vertex3f aux, vertice;
	// Vertice es un punto de la circunferencia centrada en el eje
	vertice.x=0.0+radio; vertice.y=0.0; vertice.z=0.0;
	for (int i=0;i<num_perfiles;i++){ // se rota el lado para que de la vuelta  al centro
		// Despues de calcular la posicion centrada en el eje, la desplazamos
		aux.x= vertice.x*cos(2.0*M_PI*i/(1.0*num_perfiles)) +
			   vertice.z*sin(2.0*M_PI*i/(1.0*num_perfiles)) + centro.x;
		aux.z= vertice.z*cos(2.0*M_PI*i/(1.0*num_perfiles)) - 
			   vertice.x*sin(2.0*M_PI*i/(1.0*num_perfiles)) + centro.z;
		aux.y= vertice.y + centro.y;// Se rota en lo vertical, por eso "y" no cambia
		vertices.push_back(aux);
	}
}

// Funcion que pinta una tapa, usando los vertices ya creados de un cilindro o cono
void _rotacion::pinta_cara(_vertex3f centro,int tam_perfil, int num_perfiles, int altura){
	vertices.push_back(centro);
	_vertex3i cara_aux;
	for(int i=0;i<num_perfiles;++i){
		cara_aux._0=vertices.size()-1; // el ultimo vertice añadido es el del centro
		cara_aux._1=i * tam_perfil + altura; // primer vertice de cada perfil
		cara_aux._2=((i+1)%num_perfiles)*tam_perfil + altura; // el siguiente en el plano, hasta que de la vuelta
		caras.push_back(cara_aux);
	}
}

// objeto por extrusión
_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z){
	int i;
	_vertex3f vertice_aux;
	_vertex3i cara_aux;
	int num_aux;

	// tratamiento de los vértice, en pareja, original y desplazado
	num_aux=poligono.size();
	vertices.resize(num_aux*2);
	for (i=0;i<num_aux;i++){
		vertices[2*i]=poligono[i];
		vertices[2*i+1].x=poligono[i].x+x;
		vertices[2*i+1].y=poligono[i].y+y;
		vertices[2*i+1].z=poligono[i].z+z;
	}
		
	// tratamiento de las caras 
	caras.resize(num_aux*2);
	int c=0;
	for (i=0;i<num_aux;i++){
		caras[c]._0=i*2;
		caras[c]._1=(i*2+2)%(num_aux*2);
		caras[c]._2=i*2+1;    
		c=c+1;
		caras[c]._0=(i*2+2)%(num_aux*2);
		caras[c]._1=(i*2+2)%(num_aux*2)+1;
		caras[c]._2=i*2+1;    
		c=c+1;    
	}   
}

//Cono
_cono::_cono(_vertex3f centro, float r, float h){
	_vertex3f aux, cuspide; 
	aux.x=centro.x+r; aux.y=centro.y; aux.z=centro.z;
	cuspide.x=centro.x; cuspide.y=centro.y+h; cuspide.z=centro.z;
	vector<_vertex3f> perfil;
	perfil.push_back(centro);
	perfil.push_back(aux);
	perfil.push_back(cuspide);
	// El perfil tiene 3 puntos, el centro de la base, un punto lateral, y la cuspide
	this->parametros(perfil, REALISTA, 1, true, false);
}

//Cilindro, 3 puntos centro, abajo, y arriba
_cilindro::_cilindro(_vertex3f centro, float radio, float altura){
	vector<_vertex3f> perfil;
	_vertex3f  aux=centro;
	perfil.push_back(centro);
	aux.x+=radio;
	perfil.push_back(aux);
	aux.y+=altura;
	perfil.push_back(aux);
	this->parametros(perfil,REALISTA,3,true,true);
}

// Esfera
_esfera::_esfera(_vertex3f centro, float radio){
	vector<_vertex3f> perfil;
	_vertex3f aux;
	int tam_perfil=REALISTA; 
	for(int i=0;i<tam_perfil; ++i){ 
		// al multiplicar PI por i/R nos da una secuencia que va de 0 a PI, es decir, de 0 a 180º
		// como queremos que la semicircunferecia vaya de -90 a 90º, le restamos PI/2
		// la "x" es el coseno y la "y" el seno para que salga una semicurcunferencia vertical
		aux.x = radio * cos( (M_PI*i)/( (tam_perfil-1)*1.0 ) - M_PI/2 ) + centro.x;
		aux.y = radio * sin( (M_PI*i)/( (tam_perfil-1)*1.0 ) - M_PI/2 ) + centro.y;
		aux.z = centro.z;
		perfil.push_back(aux);
	}
	// tenemos el perfil, lo rotamos
	perfil.push_back(centro);
	this->parametros(perfil,REALISTA,2,true,true);
}

//semiesfera
_semiesfera::_semiesfera(_vertex3f centro, float radio){
	vector<_vertex3f> perfil;
	_vertex3f aux;
	int tam_perfil=REALISTA; 
	for(int i=0;i<tam_perfil; ++i){
		// Curva que va de 0 a 90º, es decir, de 0 a PI/2 rad, que luego giraremos y desplazaremos
		aux.x = radio * cos( (M_PI/2.0*i)/( (tam_perfil-1)*1.0 ) - M_PI/2 ) + centro.x;
		aux.y = radio * sin( (M_PI/2.0*i)/( (tam_perfil-1)*1.0 ) - M_PI/2 ) + centro.y;
		aux.z = centro.z;
		perfil.push_back(aux);
	}
	// Doble push back del centro, por ser el vértice al que se unen los últimos vértices
	perfil.push_back(centro); // Y por ser el centro propiamente dicho
	perfil.push_back(centro); 
	this->parametros(perfil,REALISTA,2,true,true);
}

// Perfil que se nos da en un archivo de PLY, y rotamos
_perfil_ply::_perfil_ply(char* archivo){
	int tam_per;
	vector<float> ver_ply ;
	vector<int>   car_ply ;
	vector<_vertex3f> perfil;
	
	_file_ply::read(archivo, ver_ply, car_ply );
	tam_per=ver_ply.size()/3;

	perfil.resize(tam_per);
	for (int i=0;i<tam_per;++i){
		perfil[i].x=ver_ply[3*i];
		perfil[i].y=ver_ply[3*i+1];
		perfil[i].z=ver_ply[3*i+2];
	}

	this->parametros(perfil,REALISTA,0,true,true);
}

