#include "../include/jirafa.h"

//Parte mis clases
_cuerpo::_cuerpo(){
  ancho = ALTURA*1.5;
  alto = ALTURA*0.3;
  fondo = ALTURA*0.8;
}


void _cuerpo::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();
  glScalef(ancho, alto, fondo);
  cubo.draw(modo, r, g, b, grosor);
  glPopMatrix();
};

_cola::_cola(){
  largo=ALTURA*0.25;
  ancho=ARTIC*0.6;
}

void _cola::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

  glRotatef(90,0,0,1);
  glScalef(ancho, largo, ancho);
  cilindro.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

_cuello::_cuello(){
  this->largo=ALTURA*0.25;
  this->ancho=ARTIC;
}
void _cuello::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

  glScalef(ancho, largo, ancho);
  cilindro.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

_articulacion::_articulacion(){
  radio=ARTIC;
}

void _articulacion::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

  glScalef(radio, radio, radio);
  esfera.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

_pata::_pata(){
  this->largo=ALTURA*0.5;
  this->ancho=ARTIC;
}
void _pata::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();

  glScalef(ancho, largo, ancho);
  cilindro.draw(modo, r, g, b, grosor);

  glPopMatrix();
}

_cabeza::_cabeza(){ 
  char* path = "txt/jirafa";
  ply.parametros(path);
  largo=ALTURA*0.08;
}
void _cabeza::draw(_modo modo, float r, float g, float b, float grosor){
  glPushMatrix();
  glRotatef(90,0,1,0); // y lo roto
  glScalef(largo,largo,largo); // lo achico
  glTranslatef(-0.25,-2,-1); // lo centro en el eje
  ply.draw(modo,r,g,b,grosor);
  glPopMatrix();
}

_jirafa::_jirafa(){
  giro_cuerpo=0.0;
  giro_cola=0.0;
  giro_cuello_1=20.0;
  giro_cuello_2=20.0;
  giro_cabeza=-60;


  giro_cola_max=0.0;
  giro_cola_min=-75.0;
  giro_cuello_1_max=70;
  giro_cuello_1_min=20;
  giro_cuello_2_max=70;
  giro_cuello_2_min=20;
  giro_cabeza_max=-60;
  giro_cabeza_min=-90;

  int color=0;
  piezas=9;
  grosor_select=2;
  color_pick=_vertex3f(1.0,0.0,0.0); 
  color_select.resize(piezas);
  activo.resize(piezas);

  for (int i=0;i<piezas;i++){
    activo[i]=0;
    color_select[i].r=color_select[i].g=color_select[i].b=color;
    color+=20;
  }
}

void _jirafa::draw(_modo modo, float r, float g, float b, float grosor){
  float r_p, g_p, b_p;
  r_p=color_pick.r;
  g_p=color_pick.g;
  b_p=color_pick.b;

  //Hemos de respetar la jerarquía
  glPushMatrix();
    // Desplazo y giro el cuerpo (en este da igual el orden)
    glRotatef(this->giro_cuerpo,0,1,0);
    glTranslatef(0,ALTURA+cuerpo.alto/2,0);
    if(activo[0]==1) this->cuerpo.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->cuerpo.draw(modo,0,1,0,grosor);

    // Pierna delante izquierda
    // No se pone en la esquina, se deja un pequeño offset (/2.4 en vez de /2)
    glTranslatef(-cuerpo.ancho/3,-cuerpo.alto/2,+cuerpo.fondo/3);
    if(activo[1]==1) this->articulacion.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->articulacion.draw(modo,0,1,0,grosor);
    glTranslatef(0,-ALTURA/2,0);
    if(activo[1]==1) this->pata.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->pata.draw(modo,0,0,1,grosor);

    // Pierna detras izquierda
    glTranslatef(0,ALTURA/2,-cuerpo.fondo/1.5);
    if(activo[2]==1) this->articulacion.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->articulacion.draw(modo,0,1,0,grosor);
    glTranslatef(0,-ALTURA/2,0);
    if(activo[2]==1) this->pata.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->pata.draw(modo,0,0,1,grosor);

    // Pierna detras derecha
    glTranslatef(cuerpo.ancho/1.5,ALTURA/2,0);
    if (activo[3]==1) this->articulacion.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->articulacion.draw(modo,0,1,0,grosor);
    glTranslatef(0,-ALTURA/2,0);
    if (activo[3]==1) this->pata.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->pata.draw(modo,0,0,1,grosor);

    // Pierna delante derecha
    glTranslatef(0,ALTURA/2,cuerpo.fondo/1.5);
    if (activo[4]==1) this->articulacion.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->articulacion.draw(modo,0,1,0,grosor);
    glTranslatef(0,-ALTURA/2,0);
    if (activo[4]==1) this->pata.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->pata.draw(modo,0,0,1,grosor);
  glPopMatrix();

  glPushMatrix(); // Cuello y cabeza
    glRotatef(this->giro_cuerpo,0,1,0);
    glTranslatef(0,ALTURA+cuerpo.alto/2,0);

    // El cuello se centra en su base(empieza centrado en su mitad), se gira, y luego se coloca en su lugar
    glTranslatef(cuello.ancho-cuerpo.ancho/2,-cuello.ancho+cuerpo.alto/2, 0);
    glRotatef(this->giro_cuello_1,0,0,1);
    glTranslatef(0,cuello.largo,0);
    if(activo[5]==1) this->cuello.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->cuello.draw(modo,0,0,1,grosor);
    // Tras la primera parte del cuello, una esfera que haga de articulacion
    glTranslatef(0,cuello.largo,0);
    if(activo[5]==1) this->articulacion.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->articulacion.draw(modo,0,1,0,grosor);

    // Segunda parte del cuello
    glRotatef(this->giro_cuello_2,0,0,1);
    glTranslatef(0,cuello.largo,0);
    if(activo[6]==1) this->cuello.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->cuello.draw(modo,1,0,0,grosor);

    glTranslatef(0,cuello.largo,0); // Cabeza al final del cuello
    glRotatef(this->giro_cabeza,0,0,1);
    if (activo[7]==1) this->cabeza.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->cabeza.draw(modo,0,0,1,grosor);
  glPopMatrix();

  glPushMatrix(); // Cola
    glRotatef(this->giro_cuerpo,0,1,0);
    glTranslatef(0,ALTURA+cuerpo.alto/2,0);

    glTranslatef(cuerpo.ancho/2,0,0.0);
    glRotatef(this->giro_cola,0,0,1);
    glTranslatef(cola.largo,0,0);
    if(activo[8]==1) this->cola.draw(EDGES,r_p,g_p,b_p,grosor_select);
    else this->cola.draw(modo,0,0,1,grosor);
  glPopMatrix();
}

// objeto jerarquico con seleccion
void _jirafa::seleccion(){
  _vertex3i color;

  //Hemos de respetar la jerarquía
  glPushMatrix();
    color=color_select[0];

    // Desplazo y giro el cuerpo (en este da igual el orden)
    glRotatef(this->giro_cuerpo,0,1,0);
    glTranslatef(0,ALTURA+cuerpo.alto/2,0);
    this->cuerpo.draw(SELECT,color.r,color.g,color.b,1);

    // Pierna delante izquierda
    // No se pone en la esquina, se deja un pequeño offset (/2.4 en vez de /2)
    color=color_select[1];

    glTranslatef(-cuerpo.ancho/3,-cuerpo.alto/2,+cuerpo.fondo/3);
    this->articulacion.draw(SELECT,color.r,color.g,color.b,1);
    glTranslatef(0,-ALTURA/2,0);
    this->pata.draw(SELECT,color.r,color.g,color.b,1);

    // Pierna detras izquierda
    color=color_select[2];

    glTranslatef(0,ALTURA/2,-cuerpo.fondo/1.5);
    this->articulacion.draw(SELECT,color.r,color.g,color.b,1);
    glTranslatef(0,-ALTURA/2,0);
    this->pata.draw(SELECT,color.r,color.g,color.b,1);

    // Pierna detras derecha
    color=color_select[3];

    glTranslatef(cuerpo.ancho/1.5,ALTURA/2,0);
    this->articulacion.draw(SELECT,color.r,color.g,color.b,1);
    glTranslatef(0,-ALTURA/2,0);
    this->pata.draw(SELECT,color.r,color.g,color.b,1);

    // Pierna delante derecha
    color=color_select[4];

    glTranslatef(0,ALTURA/2,cuerpo.fondo/1.5);
    this->articulacion.draw(SELECT,color.r,color.g,color.b,1);
    glTranslatef(0,-ALTURA/2,0);
    this->pata.draw(SELECT,color.r,color.g,color.b,1);
  glPopMatrix();

  glPushMatrix(); // Cuello y cabeza
    glRotatef(this->giro_cuerpo,0,1,0);
    glTranslatef(0,ALTURA+cuerpo.alto/2,0);

    // El cuello se centra en su base(empieza centrado en su mitad), se gira, y luego se coloca en su lugar
    color=color_select[5];

    glTranslatef(cuello.ancho-cuerpo.ancho/2,-cuello.ancho+cuerpo.alto/2, 0);
    glRotatef(this->giro_cuello_1,0,0,1);
    glTranslatef(0,cuello.largo,0);
    this->cuello.draw(SELECT,color.r,color.g,color.b,1);
    // Tras la primera parte del cuello, una esfera que haga de articulacion
    glTranslatef(0,cuello.largo,0);
    this->articulacion.draw(SELECT,color.r,color.g,color.b,1);

    // Segunda parte del cuello
    color=color_select[6];

    glRotatef(this->giro_cuello_2,0,0,1);
    glTranslatef(0,cuello.largo,0);
    this->cuello.draw(SELECT,color.r,color.g,color.b,1);

    // Cabeza al final del cuello
    color=color_select[7];

    glTranslatef(0,cuello.largo,0); 
    glRotatef(this->giro_cabeza,0,0,1);
    this->cabeza.draw(SELECT,color.r,color.g,color.b,1);
  glPopMatrix();

  glPushMatrix(); // Cola
    color=color_select[8];

    glRotatef(this->giro_cuerpo,0,1,0);
    glTranslatef(0,ALTURA+cuerpo.alto/2,0);

    glTranslatef(cuerpo.ancho/2,0,0.0);
    glRotatef(this->giro_cola,0,0,1);
    glTranslatef(cola.largo,0,0);
    this->cola.draw(SELECT,color.r,color.g,color.b,1);
  glPopMatrix();
}