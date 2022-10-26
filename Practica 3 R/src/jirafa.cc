#include "../include/jirafa.h"

//Parte mis clases

_cuerpo::_cuerpo(){
  ancho = 1.5;
  alto = 0.3;
  fondo = 0.8;
  altura = 1.0;
}


void _cuerpo::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

_cola::_cola(){
  largo=0.25;
  ancho=0.04;
}

void _cola::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

  glRotatef(90,0,0,1);
  glScalef(ancho, largo, ancho);
  cilindro.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

_cuello::_cuello(){
  this->largo=0.25;
  this->ancho=0.065;
}
void _cuello::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

  glScalef(ancho, largo, ancho);
  cilindro.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

_articulacion::_articulacion(){
  radio=0.065;
}

void _articulacion::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

  glScalef(radio, radio, radio);
  esfera.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

_jirafa::_jirafa(){
  giro_cuerpo=0.0;
  giro_cola=0.0;
  giro_cuello_1=0.0;
  giro_cuello_2=15.0;


  giro_cola_max=0.0;
  giro_cola_min=-75.0;
  giro_cuello_1_max=60;
  giro_cuello_1_min=0;
  giro_cuello_2_max=60;
  giro_cuello_2_min=0;
}

void _jirafa::draw(_modo modo, float r, float g, float b, float grosor){
  /*Hemos de respetar la jearquía
  Como van en el mismo push-pop matrix, los cambios del rotate y translate del cuerpo, afectan al cuello tambien.
  */ 
  glPushMatrix();
    // Desplazo y giro el cuerpo (en este da igual el orden)
    glRotatef(this->giro_cuerpo,0,1,0);
    glTranslatef(0,cuerpo.altura,0);
    this->cuerpo.draw(modo,r,g,b,grosor);

    // El cuello se centra en su base(empieza centrado en su mitad), se gira, y luego se coloca en su lugar
    glTranslatef(cuello.ancho-cuerpo.ancho/2,-cuello.ancho+cuerpo.alto/2, 0);
    glRotatef(this->giro_cuello_1,0,0,1);
    glTranslatef(0,cuello.largo,0);
    this->cuello.draw(modo,1,0,0,grosor);

    // Tras la primera parte del cuello, una esfera que haga de articulacion
    glTranslatef(0,cuello.largo,0);
    this->articulacion.draw(modo,0,1,0,grosor);

    // Segunda parte del cuello
    glRotatef(this->giro_cuello_2,0,0,1);
    glTranslatef(0,cuello.largo,0);
    this->cuello.draw(modo,0,0,1,grosor);

  glPopMatrix();

  glPushMatrix(); // La cola va aparte porque aunque sí le afecta el cuerpo, no la cabeza
    glRotatef(this->giro_cuerpo,0,1,0);
    glTranslatef(cuerpo.ancho/2,cuerpo.altura,0.0);
    glRotatef(this->giro_cola,0,0,1);
    glTranslatef(cola.largo,0,0);
    this->cola.draw(modo,r,g,b,grosor);
  glPopMatrix();  
}