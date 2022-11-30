//**************************************************************************
// Práctica 3 
//**************************************************************************

#include "../include/objetos_B3.h"
#include <time.h> 


//*************************************************************************
// _puntos3D
//*************************************************************************
_puntos3D::_puntos3D(){}

//*************************************************************************
// dibujar puntos
//*************************************************************************
void _puntos3D::draw_puntos(float r, float g, float b, int grosor){
  //**** usando vertex_array ****
  glPointSize(grosor);
  glColor3f(r,g,b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
  glDrawArrays(GL_POINTS,0,vertices.size()); 
}


//*************************************************************************
// _triangulos3D
//*************************************************************************
_triangulos3D::_triangulos3D(){
  ambiente_difuso=_vertex4f(0.9,0.5,0.1,1.0);
  especular=_vertex4f(0.5,0.5,0.5,1.0);
  brillo=110.0;
}


//*************************************************************************
// dibujar en modo arista
//*************************************************************************
void _triangulos3D::draw_aristas(float r, float g, float b, int grosor){
  //**** usando vertex_array ****
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glLineWidth(grosor);
  glColor3f(r,g,b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
  glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]);
}

//*************************************************************************
// dibujar en modo sólido con un único color
//*************************************************************************

void _triangulos3D::draw_solido(float r, float g, float b){
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glColor3f(r,g,b);

  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(3,GL_FLOAT,0,&vertices[0]);
  glDrawElements(GL_TRIANGLES,caras.size()*3,GL_UNSIGNED_INT,&caras[0]); 
}

//*************************************************************************
// dibujar en modo sólido con colores diferentes para cada cara
//*************************************************************************

void _triangulos3D::draw_solido_colores(){
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);
  for (long unsigned int i=0;i<caras.size();i++){
    glColor3f(colores_caras[i].r,colores_caras[i].g,colores_caras[i].b);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
}

// Dibujar en modo iluminacion para las caras
void _triangulos3D::draw_solido_plano(){
  glEnable(GL_LIGHTING);
  glShadeModel(GL_FLAT);
  glEnable(GL_NORMALIZE); // esto no se si esta bien

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difuso);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,(GLfloat *) &especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,brillo);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);
  for (long unsigned int i=0;i<caras.size();i++){
    glNormal3f(normales_caras[i].x,normales_caras[i].y,normales_caras[i].z);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
  glDisable(GL_LIGHTING);
}
// Dibujar en modo iluminacion para los vertices
void _triangulos3D::draw_solido_suave(){
  glEnable(GL_LIGHTING);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_NORMALIZE); // esto no se si esta bien

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, (GLfloat *) &ambiente_difuso);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR,(GLfloat *) &especular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS,brillo);

  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
  glBegin(GL_TRIANGLES);
  
  for (long unsigned int i=0;i<caras.size();i++){
    glNormal3f(normales_vertices[caras[i]._0].x,
               normales_vertices[caras[i]._0].y,
               normales_vertices[caras[i]._0].z);
    glVertex3fv((GLfloat *) &vertices[caras[i]._0]);
    glNormal3f(normales_vertices[caras[i]._1].x,
               normales_vertices[caras[i]._1].y,
               normales_vertices[caras[i]._1].z);
    glVertex3fv((GLfloat *) &vertices[caras[i]._1]);
    glNormal3f(normales_vertices[caras[i]._2].x,
               normales_vertices[caras[i]._2].y,
               normales_vertices[caras[i]._2].z);
    glVertex3fv((GLfloat *) &vertices[caras[i]._2]);
    }
  glEnd();
  glDisable(GL_LIGHTING);
}

void _triangulos3D::calcular_normales_caras(){
  int n_c;
  
  _vertex3f va, vb;
  float modulo;

  n_c=caras.size();
  normales_caras.resize(n_c);

  for(int i=0;i<n_c;++i){
    va=vertices[caras[i]._1]-vertices[caras[i]._0];
    vb=vertices[caras[i]._2]-vertices[caras[i]._0];
    normales_caras[i].x=va.y*vb.z-va.z*vb.y;
    normales_caras[i].y=va.z*vb.x-va.x*vb.z;
    normales_caras[i].z=va.x*vb.y-va.y*vb.x;
    modulo=sqrt(normales_caras[i].x * normales_caras[i].x +
               normales_caras[i].y * normales_caras[i].y +
               normales_caras[i].z * normales_caras[i].z);
    normales_caras[i].x/=modulo;
    normales_caras[i].y/=modulo;
    normales_caras[i].z/=modulo;
  }
}
void _triangulos3D::calcular_normales_vertices(){
  int n_v, n_c;
  float modulo;
  n_v=vertices.size();
  normales_vertices.resize(n_v);
  for(int i=0;i<n_v;++i){
    normales_vertices[i].x=0.0;
    normales_vertices[i].y=0.0;
    normales_vertices[i].z=0.0;
  }
  n_c=caras.size();
  for(int i=0; i<n_c; ++i){
    normales_vertices[caras[i]._0]+=normales_caras[i];
    normales_vertices[caras[i]._1]+=normales_caras[i];
    normales_vertices[caras[i]._2]+=normales_caras[i];
  }
  for(int i=0;i<n_v;++i){
      modulo=sqrt(normales_vertices[i].x*normales_vertices[i].x+
                  normales_vertices[i].y*normales_vertices[i].y+
                  normales_vertices[i].z*normales_vertices[i].z);
      normales_vertices[i].x/=modulo;
      normales_vertices[i].y/=modulo;
      normales_vertices[i].z/=modulo;
  }
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
    case COMPLETO: 
      draw_puntos(1, 0, 0, grosor);
      draw_aristas(0, 0, 0, grosor);
      draw_solido_colores();
      break;
    case SOLID_FLAT: draw_solido_plano(); break;
    case SOLID_SMOOTH: draw_solido_suave(); break;
	}
}

//*************************************************************************
// asignación colores
//*************************************************************************

void _triangulos3D::colors_random(){
  int i, n_c;
  n_c=caras.size();
  colores_caras.resize(n_c);
  srand (time(NULL));
  for (i=0;i<n_c;i++){
    colores_caras[i].r=rand()%1000/1000.0;
    colores_caras[i].g=rand()%1000/1000.0;
    colores_caras[i].b=rand()%1000/1000.0;
  }
}

//*************************************************************************
// Llamar a colors_random o colors_chess da valores a colores_caras, que será llamado por draw_solido_colores
void _triangulos3D::colors_chess(float r1, float g1, float b1, float r2, float g2, float b2){
  int i, n_c;
  n_c=caras.size();
  colores_caras.resize(n_c);
  for (i=0;i<n_c;i++) {
    if (i%2==0){
      colores_caras[i].r=r1;
      colores_caras[i].g=g1;
      colores_caras[i].b=b1;
    }else{
      colores_caras[i].r=r2;
      colores_caras[i].g=g2;
      colores_caras[i].b=b2;
      } 
    }
}

// solo cogemos las 2/3 primeras partes de la ecuacion
void _triangulos3D::colors_flat(float r, float g, float b, float p_lx, float p_ly, float p_lz){
  int n_c=caras.size();
  _vertex3f l;
  float modulo, escalar;
  colores_caras.resize(n_c);

  for(int i=0; i<n_c;++i){
    colores_caras[i].r=0.1*r;
    colores_caras[i].g=0.1*g;
    colores_caras[i].b=0.11*b; // las sombras son un pelin mas azuladas
    l.x = p_lx - vertices[caras[i]._0].x;
    l.y = p_ly - vertices[caras[i]._0].y;
    l.z = p_lz - vertices[caras[i]._0].z;
    modulo=sqrt(l.x*l.x + l.y*l.y + l.z*l.z);
    l.x/=modulo;
    l.y/=modulo;
    l.z/=modulo;
    escalar = normales_caras[i].x*l.x + normales_caras[i].y*l.y + normales_caras[i].z*l.z;
    if(escalar > 0.0){
      colores_caras[i].r+=r*escalar;
      colores_caras[i].g+=g*escalar;
      colores_caras[i].b+=b*escalar;
    }
  }
}