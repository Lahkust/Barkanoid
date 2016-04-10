/* En-tête du programme
*****************************************
Fichier :			balle.h
Auteur:				Guillaume Bergs & Shawn Corriveau
Date de création :  2016/01/01
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

#include "visuel.h"
#include <math.h>

//Valeurs reliées à la balle
const int HAUTEUR_IMAGE_BALLE = 25;
const int LARGEUR_IMAGE_BALLE = 25;

//Les définitions de fonctions

class balle{
public:

	//La position en x et y du coin supérieur gauche
	int x;
	int y;

	//Obtenir la vélocité carthésienne pour les déplacements
	void get_velocityC(float &x, float &y)
	{
		x = velocity_x; 
		y = velocity_y;
	}

	//Obtenir la vélocité polaire pour les rebonds
	void get_velocityP(float &r, float &theta)
	{
		r = rayon;
		theta = angle;
	}

	//Changer la véolocité avec des données polaires
	void set_velocityP(float r, float theta)
	{
		//Change la vélocité polaire
		rayon = r;
		angle = theta;

		//Change la vélocité carthésienne
		velocity_x = r * cos(theta);
		velocity_y = r * sin(theta);
	}

	//Changer la vélocité avec des données cathésiennes
	void set_velocityC(float x, float y)
	{
		//Change la vélocité carthésienne
		velocity_x = x;
		velocity_y = y;

		//Change la vélocité polaire
		rayon = sqrt((x*x) + (y*y));
		angle = atan2(velocity_x, velocity_y);
	}

	//Faire un rebond sur une surface avec sa normale
	void rebond(double angle);

	int get_x() { return x; }
	int get_y() { return y; }
	int get_taille_x() { return taille_x; }
	int get_taille_y() { return taille_y; }

	void set_taille_x(int taille){ taille_x = taille; }
	void set_taille_y(int taille){ taille_y = taille; }

private:

	//La vélocité carthésienne
	float velocity_x = 0;
	float velocity_y = 0;

	//La vélocité polaire
	float rayon = 0;
	float angle = 0;

	//La taille de la balle
	int taille_x = LARGEUR_IMAGE_BALLE;
	int taille_y = HAUTEUR_IMAGE_BALLE;
};

//Faire un rebond sur une surface avec sa normale
void balle::rebond(double theta)
{
	set_velocityP(rayon, 2 * theta - angle + M_PI);
	
	//****** Patch: si angle >/< 2PI/-2PI, retire/ajoute 2PI jusqu'à ce qu'il soit entre -2PI et 2PI
	while (angle > 2 * M_PI) angle -= (2 * M_PI);
	while (angle < ((-2) * M_PI)) angle += (2 * M_PI);


	//****** Patch: Si la vélocité en x/y envoie la balle hors de l'écran, inversion de la vélocité en x/y
	if ((x < 0) && (velocity_x < 0))
		set_velocityC(-velocity_x, velocity_y);
	if ((y < 0) && (velocity_y < 0))
		set_velocityC(velocity_x, -velocity_y);
	if (((x+LARGEUR_IMAGE_BALLE) > LARGEUR_FENETRE) && (velocity_x > 0))
		set_velocityC(-velocity_x, velocity_y);
	if (((y+HAUTEUR_IMAGE_BALLE) > HAUTEUR_FENETRE) && (velocity_y > 0))
		set_velocityC(velocity_x, -velocity_y);
	//****** Fin patch

	x += velocity_x;
	y += velocity_y;
}

#endif