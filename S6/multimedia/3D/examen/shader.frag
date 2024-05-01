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
uniform vec3 planeNormal;
uniform vec3 pointOnPlane;

uniform int exercice;

varying vec4 p;
varying vec3 n;


void main (void) {

    if( exercice == 3 ){
        //Exercice 3 à completer
        //Nous allons ignorer les fragments pour lesquels les points se trouvent sous le plan
        //Le plan est définit par un point : pointOnPlane et une normale : planeNormal
        //compléter le condition du if
        if( false ) //condition à completer : vrai si la position du point se trouve au dessous du plan
            discard;
    }

    vec3 P = vec3 (gl_ModelViewMatrix * p);
    vec3 N = normalize (gl_NormalMatrix * n);
    vec3 V = normalize (-P);

    vec4 Isa = gl_LightModel.ambient;
    vec4 Ka = gl_FrontMaterial.ambient;
    vec4 Ia = Isa*Ka;

    vec4 I = ambientRef * Ia ;

    for (int i = 0; i < 3; i++) {

        vec4 Isd = gl_LightSource[i].diffuse;
        vec4 Kd = gl_FrontMaterial.diffuse;

        vec3 L = normalize (vec3(gl_ModelViewMatrix *gl_LightSource[i].position) - P);

        //Bonus ajouter une lumière à la position de la caméra
        float dotLN = max(dot (L, N), 0.);
        if(dotLN >0.){

            vec4 Id = Isd*Kd*dotLN;

            vec4 Iss = gl_LightSource[i].specular;
            vec4 Ks = gl_FrontMaterial.specular;

            vec3 R = reflect (-L, N);

            float dotRV = max(dot(R, V), 0.0);
            vec4 Is = Iss*Ks*max (0.0, pow (dotRV, shininess));

            I += diffuseRef * Id + specularRef * Is;
        }

    }

    gl_FragColor =vec4 (I.xyz, 1.);
}

