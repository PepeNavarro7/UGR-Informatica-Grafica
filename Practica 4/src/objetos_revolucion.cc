#include "../include/objetos_revolucion.h"

//************************************************************************
// objeto por revolucion, se crea vacío y luego se llama al "parámetros"
// con el perfil, numero de revoluciones, tipo, y si tiene tapas (1 o 0)
// tipo 0 -> cilindro, tipo 1 -> cono, tipo 2 -> esfera
// Aunque a simple vista, no parece que se usen las variables de las tapas, solo los tipos
//************************************************************************
_rotacion::_rotacion(){}

void _rotacion::parametros(vector<_vertex3f> perfil, int num, int tipo, int tapa_in, int tapa_su){
  int i,j;
  _vertex3f vertice_aux;
  _vertex3i cara_aux;
  int num_aux;
  float radio;

  // tratamiento de los vértice
  radio=sqrt(perfil[0].x*perfil[0].x+perfil[0].y*perfil[0].y);

  num_aux=perfil.size();
  if (tipo==1) 
    num_aux=num_aux-1;

  vertices.resize(num_aux*num+2);
  for (j=0;j<num;j++){
    for (i=0;i<num_aux;i++){
      vertice_aux.x=perfil[i].x*cos(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*sin(2.0*M_PI*j/(1.0*num));
      vertice_aux.z=-perfil[i].x*sin(2.0*M_PI*j/(1.0*num))+
                    perfil[i].z*cos(2.0*M_PI*j/(1.0*num));
      vertice_aux.y=perfil[i].y;
      vertices[i+j*num_aux]=vertice_aux;
    }
  }

  caras.resize(2*(num_aux-1)*num+2*num);
  int c=0;
  for (j=0;j<num;j++){
    for (i=0;i<num_aux-1;i++){
      caras[c]._0=i+j*num_aux;
      caras[c]._1=((j+1)%num)*num_aux+i;
      caras[c]._2=1+i+j*num_aux;
      c+=1;
      caras[c]._0=((j+1)%num)*num_aux+i;
      caras[c]._1=((j+1)%num)*num_aux+1+i;
      caras[c]._2=1+i+j*num_aux;
      c+=1;
    }
  }
  
  //tapa inferior
  int total=num_aux*num;
  vertices[total].x=0.0;
  if (tipo==2) 
    vertices[total].y=-radio;
  else 
    vertices[total].y=perfil[0].y;
  vertices[total].z=0.0;

  for (j=0;j<num;j++){
    caras[c]._0=j*num_aux;
    caras[c]._1=((j+1)%num)*num_aux;
    caras[c]._2=total;
    c+=1;
  } 
  
  //tapa superior
  vertices[total+1].x=0.0;
  if (tipo==1) 
    vertices[total+1].y=perfil[1].y;
  if (tipo==0) 
    vertices[total+1].y=perfil[num_aux-1].y;
  if (tipo==2) 
    vertices[total+1].y=radio;
  vertices[total+1].z=0.0;
  
  for (j=0;j<num;j++){
    caras[c]._0=total+1;
    caras[c]._1=((j+1)%num)*num_aux+num_aux-1;
    caras[c]._2=num_aux-1+j*num_aux;
    c+=1;
  }

  calcular_normales_caras();
  if (tipo==2){ // esfera
    float modulo;

    int n_v=vertices.size();
    normales_vertices.resize(n_v);
    for(int i=0;i<n_v;++i){
      modulo=sqrt(vertices[i].x*vertices[i].x+vertices[i].y*vertices[i].y+vertices[i].z*vertices[i].z);
      normales_vertices[i].x=vertices[i].x/modulo;
      normales_vertices[i].y=vertices[i].y/modulo;
      normales_vertices[i].z=vertices[i].z/modulo;
    }

  } else{
    calcular_normales_vertices();
  }

  //colores de las caras
  colors_random();
}


//************************************************************************
// objeto cilindro (caso especial de rotacion)
// el centro está en el eje (medio cilindro encima de y, medio debajo)
// y gira sobre el eje y
//************************************************************************

_cilindro::_cilindro(float radio, float altura, int num){
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x=radio; aux.y=-altura/2.0; aux.z=0.0;
  perfil.push_back(aux);
  aux.x=radio; aux.y=altura/2.0; aux.z=0.0;
  perfil.push_back(aux);
  parametros(perfil,num,0,1,1);
}


//************************************************************************
// objeto cono (caso especial de rotacion)
// el centro de la base está en el eje, y el cono se levanta altura
//************************************************************************

_cono::_cono(float radio, float altura, int num){
  vector<_vertex3f> perfil;
  _vertex3f aux;

  aux.x=radio; aux.y=0; aux.z=0.0;
  perfil.push_back(aux);
  aux.x=0.0; aux.y=altura; aux.z=0.0;
  perfil.push_back(aux);
  parametros(perfil,num,1,1,1);
}

//************************************************************************
// objeto esfera (caso especial de rotacion)
// se dibuja una semicircunferencia con z=0, centrada en el eje
//************************************************************************

_esfera::_esfera(float radio, int num1, int num2){
  vector<_vertex3f> perfil;
  _vertex3f aux;
  int i;
  for (i=1;i<num1;i++){
    aux.x=radio*cos(M_PI*i/(num1*1.0)-M_PI/2.0);
    aux.y=radio*sin(M_PI*i/(num1*1.0)-M_PI/2.0);
    aux.z=0.0;
    perfil.push_back(aux);
  }
  parametros(perfil,num2,2,1,1);
}


//************************************************************************
// rotacion archivo PLY (caso especial de rotacion)
//************************************************************************
_rotacion_PLY::_rotacion_PLY(){}
void _rotacion_PLY::parametros_PLY(char *archivo, int num){}