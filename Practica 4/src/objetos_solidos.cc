#include "../include/objetos_solidos.h"
#include "../include/file_ply_stl.hpp"

//*************************************************************************
// clase cubo, con el centro en el eje, y 2*tam de lado
//*************************************************************************
_cubo::_cubo(float tam){
  //vertices
  vertices.resize(8);
  vertices[0].x=-tam;vertices[0].y=-tam;vertices[0].z=tam;
  vertices[1].x=tam;vertices[1].y=-tam;vertices[1].z=tam;
  vertices[2].x=tam;vertices[2].y=tam;vertices[2].z=tam;
  vertices[3].x=-tam;vertices[3].y=tam;vertices[3].z=tam;
  vertices[4].x=-tam;vertices[4].y=-tam;vertices[4].z=-tam;
  vertices[5].x=tam;vertices[5].y=-tam;vertices[5].z=-tam;
  vertices[6].x=tam;vertices[6].y=tam;vertices[6].z=-tam;
  vertices[7].x=-tam;vertices[7].y=tam;vertices[7].z=-tam;

  // triangulos
  caras.resize(12);
  caras[0]._0=0;caras[0]._1=1;caras[0]._2=3;
  caras[1]._0=3;caras[1]._1=1;caras[1]._2=2;
  caras[2]._0=1;caras[2]._1=5;caras[2]._2=2;
  caras[3]._0=5;caras[3]._1=6;caras[3]._2=2;
  caras[4]._0=5;caras[4]._1=4;caras[4]._2=6;
  caras[5]._0=4;caras[5]._1=7;caras[5]._2=6;
  caras[6]._0=0;caras[6]._1=7;caras[6]._2=4;
  caras[7]._0=0;caras[7]._1=3;caras[7]._2=7;
  caras[8]._0=3;caras[8]._1=2;caras[8]._2=7;
  caras[9]._0=2;caras[9]._1=6;caras[9]._2=7;
  caras[10]._0=0;caras[10]._1=1;caras[10]._2=4;
  caras[11]._0=1;caras[11]._1=5;caras[11]._2=4; 


  // normales
  calcular_normales_caras();
  calcular_normales_vertices();
  //colores de las caras
  colors_random();
}


//*************************************************************************
// clase piramide, pirámide cuadrada con el centro de la base en el eje,
// 2*tam de lado del cuadrado de la base,  la cúspide en el eje, y altura "al"
//*************************************************************************
_piramide::_piramide(float tam, float al){
  //vertices 
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

  // normales
  calcular_normales_caras();
  calcular_normales_vertices();
  //colores de las caras
  colors_random();
}

//*************************************************************************
// clase objeto ply, se crea vacío, luego se llama a "parametros" con el path del archivo
//*************************************************************************
_objeto_ply::_objeto_ply() {
   // leer lista de coordenadas de vértices y lista de indices de vértices
}

void _objeto_ply::parametros(char *archivo){
  int n_ver,n_car;
  vector<float> ver_ply ;
  vector<int>   car_ply ;
  
  _file_ply::read(archivo, ver_ply, car_ply );

  n_ver=ver_ply.size()/3;
  n_car=car_ply.size()/3;

  printf("Number of vertices=%d\nNumber of faces=%d\n", n_ver, n_car);

  vertices.resize(n_ver);
  caras.resize(n_car);
  // vértices

  for (int i=0;i<n_ver;i++){
    vertices[i].x=ver_ply[3*i];
    vertices[i].y=ver_ply[3*i+1];
    vertices[i].z=ver_ply[3*i+2];
  }

  // vértices
  for (int i=0;i<n_car;i++){
    caras[i].x=car_ply[3*i];
    caras[i].y=car_ply[3*i+1];
    caras[i].z=car_ply[3*i+2];
  }

  // normales
  calcular_normales_caras();
  calcular_normales_vertices();

  colors_flat(0.9, 0.7, 0.0, 0.0, 10.0, -20.0);

  /*colores_caras.resize(n_car);
  srand(10);
  
  // colores
  float sum;
  int n;
  colores_caras.resize(caras.size());
  for (long unsigned int i=0;i<caras.size();i++){
    if (vertices[caras[i]._0].y>=0){
      colores_caras[i].r=rand()%1000/1000.0;
      colores_caras[i].b=0.0;
      colores_caras[i].g=0.8;
    } else {
      n=rand()%10;
      sum=rand()%100/500.0;
      if (n<5) colores_caras[i].r=0.251+sum;
      else colores_caras[i].r=0.251-sum;
      if (n>5) colores_caras[i].b=0.805+sum; 
      else colores_caras[i].b=0.805-sum; 
      if (n>5) colores_caras[i].g=0.816+sum; 
      else colores_caras[i].g=0.816-sum; 
    }
  }*/
}

//************************************************************************
// objeto por extrusión
// se pasan los vertices del poligono y la direccion en la que se mueven
//************************************************************************
_extrusion::_extrusion(vector<_vertex3f> poligono, float x, float y, float z){
  int i;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;

  // tratamiento de los vértice

  num_aux=poligono.size();
  vertices.resize(num_aux*2);
  for (i=0;i<num_aux;i++)
      {
        vertices[2*i]=poligono[i];
        vertices[2*i+1].x=poligono[i].x+x;
        vertices[2*i+1].y=poligono[i].y+y;
        vertices[2*i+1].z=poligono[i].z+z;
      }
      
  // tratamiento de las caras 

  caras.resize(num_aux*2);
  int c=0;
  for (i=0;i<num_aux;i++)         
    {
    caras[c]._0=i*2;
    caras[c]._1=(i*2+2)%(num_aux*2);
    caras[c]._2=i*2+1;    
    c=c+1;
    caras[c]._0=(i*2+2)%(num_aux*2);
    caras[c]._1=(i*2+2)%(num_aux*2)+1;
    caras[c]._2=i*2+1;    
    c=c+1;    
    }  
  
  // normales
  calcular_normales_caras();
  calcular_normales_vertices();

  //colores de las caras
  colors_random();
}