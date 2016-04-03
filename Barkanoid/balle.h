/* En-t�te du programme
*****************************************
Fichier :			balle.h
Auteur:				Guillaume Bergs & Shawn Corriveau
Date de cr�ation :  2016/01/01
Description :		Tout ce qui concerne la balle
Commentaires :
*****************************************/

#ifndef BALLE_H
#define BALLE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include "../SDL2/include/SDL.h"
#include "../SDL2_image/include/SDL_image.h"

#include <math.h>


//Les d�finitions de fonctions


class balle{
public:
	const int TAILLE_X = 50; //La largeur de la balle
	const int TAILLE_Y = 50; //La hauteur de la balle

	//Obtenir la v�locit� carth�sienne pour les d�placements
	void get_velocityC(float &x, float &y)
	{
		x = velocity_x; 
		y = velocity_y;
	}

	//Obtenir la v�locit� polaire pour les rebonds
	void get_velocityP(float &r, float &phi)
	{
		r = rayon;
		phi = angle;
	}

	//Changer la v�olocit� avec des donn�es polaires
	void set_velocityP(float r, float phi)
	{
		//Change la v�locit� polaire
		rayon = r;
		angle = phi;

		//Change la v�locit� carth�sienne
		velocity_x = r * cos(phi);
		velocity_y = r * sin(phi);
	}

	//Changer la v�locit� avec des donn�es cath�siennes
	void set_velocityC(float x, float y)
	{
		//Change la v�locit� carth�sienne
		velocity_x = x;
		velocity_y = y;

		//Change la v�locit� polaire
		rayon = sqrt((x*x) + (y*y));
		angle = acos(x / rayon);
		if (y < 0) angle -= angle;
	}

private:

	//La v�locit� carth�sienne
	float velocity_x = 0;
	float velocity_y = 0;

	//La v�locit� polaire
	float rayon = 0;
	float angle = 0;
};

#endif