#include "../include/jirafa.h"

//Parte mis clases

_cuerpo::_cuerpo(){
  ancho = 2.0;
  alto = 0.4;
  fondo = 1.0;
  altura = 1.0;
}


void _cuerpo::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

_cola::_cola(){
  largo=0.3;
  ancho=0.05;
}

void _cola::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

  glRotatef(90,0,0,1);
  glScalef(ancho, largo, ancho);
  cilindro.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

_cuello::_cuello(){
  this->largo=0.4;
  this->ancho=0.1;
}
void _cuello::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

  //glRotatef(90,0,0,1);
  glScalef(ancho, largo, ancho);
  cilindro.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

_jirafa::_jirafa(){
  giro_cuerpo=0.0;
  giro_cola=0.0;
  giro_cuello_1=0;

  giro_cola_max=0.0;
  giro_cola_min=-75.0;
  giro_cuello_1_max=90;
  giro_cuello_1_min=0;
}

void _jirafa::draw(_modo modo, float r, float g, float b, float grosor){
  /*Hemos de respetar la jearquía
  Como van en el mismo push-pop matrix, los cambios del rotate y translate del cuerpo, afectan al cuello tambien.
  */ 
  glPushMatrix();

  glRotatef(this->giro_cuerpo,0,1,0);
  glTranslatef(0,cuerpo.altura,0);
  this->cuerpo.draw(modo,r,g,b,grosor);

  glTranslatef(cuello.ancho-cuerpo.ancho/2,-cuello.ancho+cuerpo.alto/2, 0);
  glRotatef(this->giro_cuello_1,0,0,1);
  glTranslatef(0,cuello.largo,0);
  this->cuello.draw(modo,r,g,b,grosor);


  
  /*glTranslatef(cuerpo.ancho/2,0.0,0.0);
  glRotatef(this->giro_cola,0,0,1);
  glTranslatef(cola.largo,0,0);
  this->cola.draw(modo,r,g,b,grosor);*/

  
  
  glPopMatrix();
}