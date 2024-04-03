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

uniform float ambientRef;
uniform float diffuseRef;
uniform float specularRef;
uniform float shininess;
uniform int levels;

varying vec4 p;
varying vec3 n;


void main (void) {
    vec3 P = vec3 (gl_ModelViewMatrix * p); //Position du point à éclairer
    vec3 N = normalize (gl_NormalMatrix * n); //Normal en ce point
    vec3 V = normalize (-P); //Vecteur de vue
    
    vec4 Isa = gl_LightModel.ambient;
    vec4 Ka = gl_FrontMaterial.ambient;
    vec4 Ia = Isa * Ka;

    vec4 I = ambientRef * Ia ;

    ////////////////////////////////////////////////
    //Eclairage de Phong à calculer en utilisant
    ///////////////////////////////////////////////
    // gl_LightSource[i].position.xyz Position de la lumière i
    // gl_LightSource[i].diffuse Couleur diffuse de la lumière i
    // gl_LightSource[i].specular Couleur speculaire de la lumière i
    // gl_FrontMaterial.diffuse Matériaux diffus de l'objet
    // gl_FrontMaterial.specular Matériaux speculaire de l'objet

    float pas = 1./float(levels);
    vec3 Ps = gl_LightSource[0].position.xyz;
    vec4 Isd = gl_LightSource[0].diffuse;
    vec4 Kd = gl_FrontMaterial.diffuse;
    float LNdot = max(0.f,dot(N,normalize(Ps-P)));//remplacer

    for(int i = 0;i<levels;i++){
        if(LNdot > (1.0-(pas*float(i+1)))){
            LNdot = 1.0-(pas*float(i+1));
            break;
        }
    }


    vec4 Id = Isd * Kd * LNdot;

    I += Id * diffuseRef;
    //dot() produit scalaire

    //reflexion speculaire
    vec4 Iss = gl_LightSource[0].specular;
    vec4 Ks = gl_FrontMaterial.specular;
    vec3 R = 2.f*LNdot*N-normalize(Ps-P);//remplacer
    vec4 Is = Iss * Ks *  pow(max(0.f,dot(normalize(R),V)),shininess);
    I += Is * specularRef;
    
    
    
    
    for(int i = 1;i<3;i++){
    // lumiere diffuse
    vec3 Ps = gl_LightSource[i].position.xyz;
    vec4 Isd = gl_LightSource[i].diffuse;
    vec4 Kd = gl_FrontMaterial.diffuse;
    float LNdot = max(0.f,dot(N,normalize(Ps-P))); //remplacer
    vec4 Id = Isd * Kd * LNdot;

    I += Id * diffuseRef;
    //dot() produit scalaire

    //reflexion speculaire
    vec4 Iss = gl_LightSource[i].specular;
    vec4 Ks = gl_FrontMaterial.specular;
    vec3 R = 2.f*LNdot*N-normalize(Ps-P);//remplacer
    vec4 Is = Iss * Ks *  pow(max(0.f,dot(normalize(R),V)),shininess);
    I += Is * specularRef;
    }
    gl_FragColor =vec4 (I.xyz, 1);
}

