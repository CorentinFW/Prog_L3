// --------------------------------------------------------------------------
// gMini,
// a minimal Glut/OpenGL app to extend
//
// Copyright(C) 2007-2009
// Tamy Boubekeur
//
// All rights reserved.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License (http://www.gnu.org/licenses/gpl.txt)
// for more details.
//
// --------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>

#define GLEW_STATIC 1
#include <GL/glew.h>
#include <GL/glut.h>

#include "src/Shader.h"
#include "src/Vec3D.h"
#include "src/Vertex.h"
#include "src/Triangle.h"
#include "src/Mesh.h"
#include "src/Camera.h"

using namespace std;

class PhongShader : public Shader {
public:
    PhongShader () { init ("shader.vert", "shader.frag"); }
    inline virtual ~PhongShader () {}

    void setAmbientRef (float s) {
        glUniform1fARB (ambientRefLocation, s);
    }

    void setDiffuseRef (float s) {
        glUniform1fARB (diffuseRefLocation, s);
    }

    void setSpecularRef (float s) {
        glUniform1fARB (specularRefLocation, s);
    }

    void setShininess (float s) {
        glUniform1fARB (shininessLocation, s);
    }

    void setexercice (int l) {
        glUniform1iARB (exerciceLocation, l);
    }

    void setPlaneNormal(Vec3 plane_normal ){
        glUniform3f(planeNormalLocation, plane_normal[0], plane_normal[1], plane_normal[2]);
    }

    void setPointOnPlane(Vec3 point_on_plane ){
        glUniform3f(pointOnPlaneLocation, point_on_plane[0], point_on_plane[1], point_on_plane[2]);
    }
private:
    void init (const std::string & vertexShaderFilename,
               const std::string & fragmentShaderFilename) {
        loadFromFile (vertexShaderFilename, fragmentShaderFilename);
        bind ();
        ambientRefLocation = getUniLoc ("ambientRef");
        diffuseRefLocation = getUniLoc ("diffuseRef");
        specularRefLocation = getUniLoc ("specularRef");
        shininessLocation = getUniLoc ("shininess");
        planeNormalLocation = getUniLoc ("planeNormal");
        pointOnPlaneLocation = getUniLoc ("pointOnPlane");
        exerciceLocation = getUniLoc ("exercice");
    }
    GLint ambientRefLocation;
    GLint diffuseRefLocation;
    GLint specularRefLocation;
    GLint shininessLocation;
    GLint planeNormalLocation;
    GLint pointOnPlaneLocation;
    GLint exerciceLocation;
};

static GLint window;
static unsigned int SCREENWIDTH = 1024;
static unsigned int SCREENHEIGHT = 768;
static Camera camera;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX=0, lastY=0, lastZoom=0;
static unsigned int FPS = 0;
static bool fullScreen = false;

static PhongShader * phongShader;

static Mesh your_shape_mesh;

static Mesh animated_mesh;
static Mesh animated_mesh_1;

static Mesh shape_mesh;
static Mesh shape_mesh_offset;

static Mesh plan_mesh;
static Vec3 plane_normal;
static Vec3 point_on_plane;

std::vector<Mesh *> meshes;
static GLuint glID;

static float ambientRef = 0.2f;
static float diffuseRef = 0.6f;
static float specularRef = 0.4f;
static float shininess = 30.0f;
static float angle = 0.f;
static float offset = 0.f;
static int vertices_on_cylinder_circle = 30;

GLfloat light_position_0[4] = {0., 2., 0., 0};
GLfloat light_position_1[4] = {0., -2., -0., 0};
GLfloat light_position_2[4] = {-2., 1., -0.5, 0};

typedef enum {Wire, Phong, Solid} RenderingMode;
typedef enum {Modelisation=1, Rendu=3, Animation=2, Exemple=4} Exercice;
static RenderingMode mode = Phong;
static Exercice exercice = Modelisation;
void initGLList ();

bool saveOFF( const std::string & filename ,
              Mesh * i_mesh ,
              bool save_normals = true ) {
    std::ofstream myfile;
    myfile.open(filename.c_str());
    if (!myfile.is_open()) {
        std::cout << filename << " cannot be opened" << std::endl;
        return false;
    }

    std::vector< Vertex > & i_vertices = i_mesh->getVertices();
    std::vector< Triangle > & i_triangles = i_mesh->getTriangles();

    myfile << "OFF" << std::endl ;

    unsigned int n_vertices = i_vertices.size() , n_triangles = i_triangles.size();
    myfile << n_vertices << " " << n_triangles << " 0" << std::endl;

    for( unsigned int v = 0 ; v < n_vertices ; ++v ) {
        myfile << i_vertices[v].position[0] << " " << i_vertices[v].position[1] << " " << i_vertices[v].position[2] << " ";
        if (save_normals) myfile << i_vertices[v].normal[0] << " " << i_vertices[v].normal[1] << " " << i_vertices[v].normal[2] << std::endl;
        else myfile << std::endl;
    }
    for( unsigned int f = 0 ; f < n_triangles ; ++f ) {
        myfile << 3 << " " << i_triangles[f][0] << " " << i_triangles[f][1] << " " << i_triangles[f][2];
        myfile << std::endl;
    }
    myfile.close();
    return true;
}

void openOFF (const std::string filename, Mesh &mesh, unsigned int normWeight) {
    vector<Vertex> V;
    vector<Triangle> T;

    ifstream in (filename.c_str ());
    if (!in)
        exit (EXIT_FAILURE);
    string offString;
    unsigned int sizeV, sizeT, tmp;
    in >> offString >> sizeV >> sizeT >> tmp;
    for (unsigned int i = 0; i < sizeV; i++) {
        Vec3 p;
        in >> p;
        V.push_back (Vertex (p));
    }
    int s;
    for (unsigned int i = 0; i < sizeT; i++) {
        in >> s;
        unsigned int v[3];
        for (unsigned int j = 0; j < 3; j++)
            in >> v[j];
        T.push_back (Triangle (v[0], v[1], v[2]));
    }
    in.close ();

    mesh = Mesh (V, T);
    mesh.recomputeSmoothVertexNormals (normWeight);

}

inline void glVertexVec3Df (const Vec3 & v) {
    glVertex3f (v[0], v[1], v[2]);
}

inline void glNormalVec3Df (const Vec3 & n) {
    glNormal3f (n[0], n[1], n[2]);
}

inline void glDrawPoint (const Vec3 & pos, const Vec3 & normal) {
    glNormalVec3Df (normal);
    glVertexVec3Df (pos);
}

inline void glDrawPoint (const Vertex & v) {
    glDrawPoint (v.getPosition (), v.getNormal ());
}

//Exercice 1
//Fonction à completer pour obtenir une pièce usinée
//Pour cela nous allons construire un cylindre
//Pour les cercles du haut et bas du cylindre avec une alternance de r1 et r2 un sommet sur 2
//n est le nombre de sommets que l'on souhaite avoir sur chacun des cercles du cylindre
void buildModel(Mesh & o_mesh, unsigned int n=3, float r1=0.5, float r2=0.4, float height=1., unsigned int ny = 2 ){

    std::vector<Vertex> & V = o_mesh.getVertices(); //Calculer les positions des sommets et les mettre dans le vecteur V
    std::vector<Triangle> & T = o_mesh.getTriangles(); //Discrétiser la forme et mettre les triangle dans le vecteur T

    V.clear();
    T.clear();

    //A completer :
    // Utiliser l'équation d'un cercle pour les bases de la forme
    // avec une alternance de r1 et r2 un sommet sur 2
    // La forme doit avoir une hauteur de height et être centrée en zéro
    // Lorsqu'on appuie sur N/n le nombre de sommets doit augmenter/diminuer
    // V.push_back(Vec3(0, height / 2,0)); // base
    // V.push_back(Vec3(0, -height / 2,0)); // base
    for(unsigned int i = 0; i < n; ++i) {
        float theta = (2 * M_PI * i) / n;
        float radius;
        if((i%2) == 0){
            radius = r2;
        }
        else {
            radius = r1;
        }
        float x =  radius*cos(theta);
        float y = radius*sin(theta);
        V.push_back(Vec3(x, height / 2,y)); // Sommet du haut
        V.push_back(Vec3(x,-height / 2, y)); // Sommet du bas
        
    }
      for(unsigned int i = 0; i < ((n) * 2); i += 2) {
        // Triangles de la paroi latérale
        T.push_back(Triangle(i, (i + 2) % (n * 2), i + 1));
        T.push_back(Triangle(i + 1, (i + 2) % (n * 2), (i + 3) % (n * 2)));
    }


    for(unsigned int i=0;i<n-1;i++){
        T.push_back(Triangle(2*i,0,2*(i+1)));
        T.push_back(Triangle(1,2*(i+1)+1,2*i+1));
    }
    //     T.push_back(Triangle(n+2,0,0));
    //     T.push_back(Triangle(1,n+1,1));
        // T.push_back(Triangle(1,0,n+1));
        // T.push_back(Triangle(1,n+2,1));
    //Creer les triangles du corps du cylindre

    //Creer les triangle du haut et bas du cylindre


}

//Construction du plan de la scène
void buildPlan(Mesh & o_mesh, unsigned int nx=30, unsigned int ny = 30, Vec3 origin = Vec3 (-25.,10,-25.), Vec3 right = Vec3 (25.,-10.,0.),  Vec3 up = Vec3(0.,0.,25.) ){

    std::vector<Vertex> & V = o_mesh.getVertices();
    std::vector<Triangle> & T = o_mesh.getTriangles();

    V.clear();
    T.clear();

    float sizeX = right.getLength();
    float sizeY = up.getLength();


    float stepX = sizeX/float (nx-1);
    float stepY = sizeY/float (ny-1);

    Vec3 normal = Vec3::crossProduct(up,right);
    normal.normalize();

    for( unsigned int j = 0 ; j < ny ; j ++ ){
        for( unsigned int i = 0 ; i < nx ; i ++ ){


            Vec3 position = origin+i*stepX*right +j*stepY*up;
            V.push_back( Vertex(position, normal)  );
        }
    }

    for( unsigned int j = 0 ; j < ny-1 ; j ++ ){
        for( unsigned int i = 0 ; i < nx-1 ; i ++ ){
            T.push_back(Triangle(j*nx+i, (j+1)*nx+i, j*nx+i+1));
            T.push_back(Triangle((j+1)*nx+i,(j+1)*nx+i+1,j*nx+i+1));
        }
    }


    plane_normal = normal;
    point_on_plane = origin-0.00001*normal;
}

//Exercice 2 a completer
void updateAnimation (){


    //Récupérer la position des sommets des maillages animés à mettre à jour
    vector<Vertex> & V = animated_mesh.getVertices ();
    vector<Vertex> & V1 = animated_mesh_1.getVertices ();

    vector<Vertex> & V0 = shape_mesh.getVertices ();

    Mat3 rotation = Mat3::Identity(); //matrice de rotation a appliquer a animated_mesh
    Mat3 rotation_1 = Mat3::Identity(); //matrice de rotation a appliquer a animated_mesh_1
    Vec3 translation(0.,0., 0.);
    

    Mat3 Rx, Ry, Rz;

    //Pour les 2 objets
    //Mettre à jour la matrice de rotation pour effectuer une rotation de PI/2. autour de l'axe X

    float fixed_angle = M_PI/2.;


    //Ajouter ensuite une rotation autour de l'axe z de angle (la variable globale mise à jour par l'appuie sur R/r) pour le modele animated_mesh
    Rx(0,0) = 1;
    Rx(1,1) = cos(angle);
    Rx(1,2) = -sin(angle);
    Rx(2,1) = sin(angle);
    Rx(2,2) = cos(angle);

    Ry(0,0) = cos(angle);
    Ry(0,2) = sin(angle);
    Ry(1,1) = 1;
    Ry(2,0) = -sin(angle);
    Ry(2,2) = cos(angle);




    //Ajouter ensuite une rotation autour de l'axe z de -angle (la variable globale mise à jour par l'appuie sur R/r) pour le modele animated_mesh_1
    Rz(0,0) = cos(-angle);
    Rz(0,1) = -sin(-angle);
    Rz(1,0) = sin(-angle);
    Rz(1,1) = cos(-angle);
    Rz(2,2) = 1;
    //Ajouter une translation en x de fixed_offset a animated_mesh_1
    float fixed_offset =0.9f;
    Vec3 translation_1(fixed_offset,0., 0.);
    //Appliquer les transformations précédentes au modèles (i.e. mettre à jour V et V1) en ajouter une translation de offset en x et de sin(angle) en y aux 2 modeles et une rotation autour de l'axe y de angle

    rotation = Ry*Rx*Rz;
    rotation_1 = Ry*Rx*Rz;

    for(  unsigned int i = 0 ; i < V.size() ; i++ ){
        V[i].position = rotation*V0[i].position + translation; // a mettre à jour
        V1[i].position = rotation_1*V0[i].position + translation_1; // a mettre à jour
    }

    //Bonus : faites tourner la lumière 0 autour de y

    initGLList ();
}

void setShaderValues () {
    phongShader->setAmbientRef(ambientRef);
    phongShader->setDiffuseRef (diffuseRef);
    phongShader->setSpecularRef (specularRef);
    phongShader->setShininess (shininess);
    phongShader->setexercice((int)exercice);
    phongShader->setPlaneNormal(plane_normal);
    phongShader->setPointOnPlane(point_on_plane);
}

void drawMesh (Mesh * mesh, float flat = true ) {

    const vector<Vertex> & V = mesh->getVertices ();
    const vector<Triangle> & T = mesh->getTriangles();
    glBegin (GL_TRIANGLES);
    for (unsigned int i = 0; i < T.size (); i++) {
        const Triangle & t = T[i];
        if (flat) {
            Vec3 normal = Vec3::crossProduct (V[t.getVertex (1)].getPosition ()
                    - V[t.getVertex (0)].getPosition (),
                    V[t.getVertex (2)].getPosition ()
                    - V[t.getVertex (0)].getPosition ());
            normal.normalize ();
            glNormalVec3Df (normal);
        }
        for (unsigned int j = 0; j < 3; j++)
            if (!flat) {
                glNormalVec3Df (V[t.getVertex (j)].getNormal ());
                glVertexVec3Df (V[t.getVertex (j)].getPosition ());
            } else
                glVertexVec3Df (V[t.getVertex (j)].getPosition ());
    }
    glEnd ();
}

void drawSolidModel () {
    glEnable (GL_LIGHTING);
    glEnable (GL_COLOR_MATERIAL);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    glPolygonOffset (1.0, 1.0);
    glEnable (GL_POLYGON_OFFSET_FILL);
    glShadeModel (GL_FLAT);
    phongShader->bind ();
    for(unsigned int i = 0; i < meshes.size() ; i ++)
        drawMesh (meshes[i]);

    glPolygonMode (GL_FRONT, GL_LINE);
    glPolygonMode (GL_BACK, GL_FILL);
    glColor3f (0.0, 0.0, 0.0);
    for(unsigned int i = 0; i < meshes.size() ; i ++)
        drawMesh (meshes[i]);
    glDisable (GL_POLYGON_OFFSET_FILL);
    glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
    glDisable (GL_COLOR_MATERIAL);
    glDisable (GL_LIGHTING);
    glShadeModel (GL_SMOOTH);
}

void drawPhongModel () {
    glCallList (glID);
}

void initLights () {



    GLfloat direction_0[3] = {0., -2., 0.};
    GLfloat direction_1[3] = {0., 2., 0.};
    GLfloat direction_2[3] = {2., -1., 0.5};

    GLfloat diffuse_color_0[4] = {0.8, 0.8, 0.8, 1};
    GLfloat diffuse_color_1[4] = {0.08, 0.29, 0.8, 1};
    GLfloat diffuse_color_2[4] = {0.8, 0.29, 0.03, 1};

    GLfloat specular_color_0[4] = {0.2, 0.0, 0.0, 1};
    GLfloat specular_color_1[4] = {0.0, 0.2, 0.0, 1};
    GLfloat specular_color_2[4] = {0.0, 0.0, 0.2, 1};


    GLfloat cut_off_0 = 45.f;
    GLfloat cut_off_1 = 45.f;
    GLfloat cut_off_2 = 45.f;

    GLfloat ambient[4] = {0.4f, 0.4f, 0.4f, 1.f};

    glLightfv (GL_LIGHT0, GL_POSITION, light_position_0);
    glLightfv (GL_LIGHT0, GL_SPOT_DIRECTION, direction_0);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse_color_0);
    glLightfv (GL_LIGHT0, GL_SPECULAR, specular_color_0);
    glLightfv (GL_LIGHT0, GL_SPOT_CUTOFF, &cut_off_0);

    glLightfv (GL_LIGHT1, GL_POSITION, light_position_1);
    glLightfv (GL_LIGHT1, GL_SPOT_DIRECTION, direction_1);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, diffuse_color_1);
    glLightfv (GL_LIGHT1, GL_SPECULAR, specular_color_1);
    glLightfv (GL_LIGHT1, GL_SPOT_CUTOFF, &cut_off_1);

    glLightfv (GL_LIGHT2, GL_POSITION, light_position_2);
    glLightfv (GL_LIGHT2, GL_SPOT_DIRECTION, direction_2);
    glLightfv (GL_LIGHT2, GL_DIFFUSE, diffuse_color_2);
    glLightfv (GL_LIGHT2, GL_SPECULAR, specular_color_2);
    glLightfv (GL_LIGHT2, GL_SPOT_CUTOFF, &cut_off_2);

    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambient);

    glEnable (GL_LIGHTING);
}

void setSunriseLight () {
    glDisable (GL_LIGHT0);
    glDisable (GL_LIGHT1);
    glDisable (GL_LIGHT2);
}

void setSingleSpotLight () {
    glEnable (GL_LIGHT0);
    glDisable (GL_LIGHT1);
    glDisable (GL_LIGHT2);
}

void setDefaultMaterial () {
    GLfloat material_color[4] = {1.0, 1.0, 1., 1.0f };
    GLfloat material_specular[4] = {0.5, 0.5, 0.5, 1.0 };
    GLfloat material_ambient[4] = {1.0, 0.0, 0.0, 1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_ambient);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128);

    glDisable (GL_COLOR_MATERIAL);
}


void drawVector( Vec3 const & i_from, Vec3 const & i_to ) {

    glBegin(GL_LINES);
    glVertex3f( i_from[0] , i_from[1] , i_from[2] );
    glVertex3f( i_to[0] , i_to[1] , i_to[2] );
    glEnd();
}

void initGLList () {
    glID = glGenLists (1);
    glNewList (glID, GL_COMPILE);
    for(unsigned int i = 0; i < meshes.size() ; i ++){
        drawMesh (meshes[i], (exercice != Rendu));
    }
    glEndList ();
}

void setExercice( int numero ){
    meshes.clear();

    glID = glGenLists (1);
    glNewList (glID, GL_COMPILE);

    setDefaultMaterial();

    if( numero == 1 ) {
        exercice = Modelisation;
        buildModel(your_shape_mesh, vertices_on_cylinder_circle);
        meshes.push_back(&your_shape_mesh);
        drawMesh (&your_shape_mesh);
    }
    if( numero == 2 ) {
        exercice = Animation;

        meshes.push_back(&animated_mesh  );
        drawMesh (&animated_mesh);

        meshes.push_back(&animated_mesh_1);
        drawMesh (&animated_mesh_1);
    }
    if( numero == 3 ) {
        exercice = Rendu;

        //Exercice 3 a completer
        //Changer la couleur diffuse du plan en rouge et lacouleur du reflet spéculaire en bleu
        //Ajouter ici la définition des couleurs et utiliser la fonction d'envoie au GPU
        meshes.push_back(&plan_mesh);
        drawMesh (&plan_mesh, false);

        //Changer la couleur diffuse de laforme en vert et le spéculaire en orange

        meshes.push_back(&shape_mesh);
        drawMesh (&shape_mesh);
    }
    if( numero == 4 ) {
        exercice = Exemple;
        meshes.push_back(&shape_mesh_offset);
        drawMesh (&shape_mesh_offset);
        buildModel(your_shape_mesh, vertices_on_cylinder_circle);
        meshes.push_back(&your_shape_mesh);
        drawMesh (&your_shape_mesh);
    }

    glEndList ();
}

void init () {
    glewInit();
    if (glewGetExtension ("GL_ARB_vertex_shader")        != GL_TRUE ||
            glewGetExtension ("GL_ARB_shader_objects")       != GL_TRUE ||
            glewGetExtension ("GL_ARB_shading_language_100") != GL_TRUE) {
        cerr << "Driver does not support OpenGL Shading Language" << endl;
        exit (EXIT_FAILURE);
    }
    if (glewGetExtension ("GL_ARB_vertex_buffer_object") != GL_TRUE) {
        cerr << "Driver does not support Vertex Buffer Objects" << endl;
        exit (EXIT_FAILURE);
    }

    camera.resize (SCREENWIDTH, SCREENHEIGHT);
    camera.move(0.,-0.15,0.);

    glClearColor (0.8, 0.8, 0.8, 1.0);

    initLights ();
    setSunriseLight ();
    setDefaultMaterial ();


    openOFF(std::string("./data/shape.off"), shape_mesh, 0);
    openOFF(std::string("./data/shape_offset.off"), shape_mesh_offset, 0);


    buildPlan(plan_mesh);
    buildModel(your_shape_mesh, vertices_on_cylinder_circle);
    animated_mesh = shape_mesh;
    animated_mesh_1 = shape_mesh;

    updateAnimation();

    setExercice(4);

    initGLList ();


    try {
        phongShader = new PhongShader;
        phongShader->bind ();
        setShaderValues ();
    } catch (ShaderException e) {
        cerr << e.getMessage () << endl;
        exit (EXIT_FAILURE);
    }
}

void clear () {
    delete phongShader;
    glDeleteLists (glID, 1);
}

void reshape(int w, int h) {
    camera.resize (w, h);
}

void display () {
    glLoadIdentity ();
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    camera.apply ();
    drawPhongModel ();
    glFlush ();
    glutSwapBuffers ();
}

void idle () {
    static float lastTime = glutGet ((GLenum)GLUT_ELAPSED_TIME);
    static unsigned int counter = 0;
    counter++;
    float currentTime = glutGet ((GLenum)GLUT_ELAPSED_TIME);
    if (currentTime - lastTime >= 1000.0f) {
        FPS = counter;
        counter = 0;
        static char FPSstr [128];
        unsigned int numOfTriangles = shape_mesh.getTriangles ().size ();
        if (mode == Solid)
            sprintf (FPSstr, "HAI60I - Examen TP: %d tri. - solid shading - %d FPS.",
                     numOfTriangles, FPS);
        else if (mode == Phong)
            sprintf (FPSstr, "HAI60I - Examen TP: %d tri. - Phong shading - %d FPS.",
                     numOfTriangles, FPS);
        glutSetWindowTitle (FPSstr);
        lastTime = currentTime;

    }
    glutPostRedisplay ();
}

void printUsage () {
    cerr << endl
         << "--------------------------------------" << endl
         << "HAI60I - Examen TP" << endl
         << "--------------------------------------" << endl
         << "USAGE: ./Main <file>.off" << endl
         << "--------------------------------------" << endl
         << "Keyboard commands" << endl
         << "--------------------------------------" << endl
         << " ?: Print help" << endl
         << " w: Toggle wireframe Mode" << endl
         << " f: Toggle full screen mode" << endl
         << " A/a: Increase/Decrease ambient reflection" << endl
         << " D/d: Increase/Decrease diffuse reflection" << endl
         << " S/s: Increase/Decrease specular reflection" << endl
         << " +/-: Increase/Decrease shininess" << endl
         << " R/r : Augmente/Diminue l’angle de rotation" << endl
         << " T/t : Augmente/Diminue l’offset du maillage pour la translation" << endl
         << " <drag>+<left button>: rotate model" << endl
         << " <drag>+<right button>: move model" << endl
         << " <drag>+<middle button>: zoom" << endl
         << " q, <esc>: Quit" << endl << endl
         << "--------------------------------------" << endl;
}



void key (unsigned char keyPressed, int x, int y) {
    switch (keyPressed) {
    case 'f':
        if (fullScreen == true) {
            glutReshapeWindow (SCREENWIDTH, SCREENHEIGHT);
            fullScreen = false;
        } else {
            glutFullScreen ();
            fullScreen = true;
        }
        break;
    case 'q':
    case 27:
        clear ();
        exit (0);
        break;
    case 'w':
        if( mode == Wire ){
            glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
            phongShader->bind ();
            mode = Phong;
        } else {
            glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
            phongShader->bind ();
            mode = Wire;
        }
        break;

    case 'D':
        diffuseRef += 0.1f;
        phongShader->setDiffuseRef (diffuseRef);
        break;
    case 'd':
        if (diffuseRef > 0.1f) {
            diffuseRef -= 0.1f;
            phongShader->setDiffuseRef (diffuseRef);
        }
        break;
    case 'S':
        specularRef += 0.1f;
        phongShader->setSpecularRef (specularRef);
        break;
    case 's':
        if (specularRef > 0.1f) {
            specularRef -= 0.1f;
            phongShader->setSpecularRef (specularRef);
        }
        break;
    case 'A':
        ambientRef += 0.1f;
        phongShader->setAmbientRef (ambientRef);
        break;
    case 'a':
        if (ambientRef > 0.1f) {
            ambientRef -= 0.1f;
            phongShader->setAmbientRef (ambientRef);
        }
        break;
    case '+':
        shininess += 1.0f;
        phongShader->setShininess (shininess);
        break;
    case '-':
        if (shininess > 1.0f) {
            shininess -= 1.0f;
            phongShader->setShininess (shininess);
        }
        break;
    case 'N':
        if(exercice==Modelisation){
            vertices_on_cylinder_circle +=2;
            buildModel(your_shape_mesh, vertices_on_cylinder_circle);
            initGLList();
        }
        break;
    case 'n':
        if(exercice==Modelisation){
            if (vertices_on_cylinder_circle > 5) {
                vertices_on_cylinder_circle -=2;
                buildModel(your_shape_mesh, vertices_on_cylinder_circle);
                initGLList();
            }
        }
        break;

    case '1':
        setExercice(1);
        break;
    case '2':
        setExercice(2);
        break;
    case '3':
        setExercice(3);
        break;
    case '4':
        setExercice(4);
        break;
    case 'R':
        if(exercice==Animation){
            angle += 0.1f;
            if( angle >= (float)M_PI*2.f ) angle = 0.;
            updateAnimation();
        }
        break;
    case 'r':
        if(exercice==Animation){
            angle -= 0.1f;
            if( angle <= 0.f ) angle = (float)M_PI*2.f;
            updateAnimation();
        }
        break;
    case 'T':
        if(exercice==Animation){
            offset += 0.01f;
            updateAnimation();
        }
        break;

    case 't':
        if(exercice==Animation){
            offset -= 0.01f;
            updateAnimation();
        }
        break;

    case '?':
    default:
        printUsage ();
        break;
    }
    setShaderValues ();
    idle ();
}

void mouse (int button, int state, int x, int y) {
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    } else {
        if (button == GLUT_LEFT_BUTTON) {
            camera.beginRotate (x, y);
            mouseMovePressed = false;
            mouseRotatePressed = true;
            mouseZoomPressed = false;
        } else if (button == GLUT_RIGHT_BUTTON) {
            lastX = x;
            lastY = y;
            mouseMovePressed = true;
            mouseRotatePressed = false;
            mouseZoomPressed = false;
        } else if (button == GLUT_MIDDLE_BUTTON) {
            if (mouseZoomPressed == false) {
                lastZoom = y;
                mouseMovePressed = false;
                mouseRotatePressed = false;
                mouseZoomPressed = true;
            }
        }
    }
    idle ();
}

void motion (int x, int y) {
    if (mouseRotatePressed == true)
        camera.rotate (x, y);
    else if (mouseMovePressed == true) {
        camera.move ((x-lastX)/static_cast<float>(SCREENWIDTH),
                     (lastY-y)/static_cast<float>(SCREENHEIGHT),
                     0.0);
        lastX = x;
        lastY = y;
    }
    else if (mouseZoomPressed == true) {
        camera.zoom (float (y-lastZoom)/SCREENHEIGHT);
        lastZoom = y;
    }
}

void usage () {
    printUsage ();
    exit (EXIT_FAILURE);
}



int main (int argc, char ** argv) {
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (SCREENWIDTH, SCREENHEIGHT);
    window = glutCreateWindow ( "HAI60I - Examen TP");


    init ();

    glutIdleFunc (idle);
    glutDisplayFunc (display);
    glutKeyboardFunc (key);
    glutReshapeFunc (reshape);
    glutMotionFunc (motion);
    glutMouseFunc (mouse);

    key ('?', 0, 0);

    glDepthFunc (GL_LESS);
    glEnable (GL_DEPTH_TEST);

    phongShader->bind ();
    glutMainLoop ();
    return EXIT_SUCCESS;
}

