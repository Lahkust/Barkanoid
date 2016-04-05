/* En-tête du programme
*****************************************
Fichier :			barre.h
Auteur:				Guillaume Bergs & Shawn Corriveau
Date de création :  2016/01/01
Description :		Tout ce qui concerne la barre
Commentaires :
*****************************************/

#ifndef BARRE_H
#define BARRE_H

#include <iostream>
#include <stdio.h>
#include <string>
#include "../SDL2/include/SDL.h"
#include "../SDL2_image/include/SDL_image.h"

#include "balle.h"


//Valeurs reliées à la barre
const int HAUTEUR_IMAGE_BARRE_G = 25;
const int LARGEUR_IMAGE_BARRE_G = 25;

const int HAUTEUR_IMAGE_BARRE_M = 25;
const int LARGEUR_IMAGE_BARRE_M = 25;

const int HAUTEUR_IMAGE_BARRE_D = 25;
const int LARGEUR_IMAGE_BARRE_D = 25;

class barre{
public:

	//La position en x et y du coin supérieur gauche du bord gauche
	int Gx;
	int Gy;

	//La position en x et y du coin supérieur gauche du bord gauche
	int Dx;
	int Dy;


	//Remet la barre à sa taille initiale
	void reset_taille()
	{
		nb_blocs = 2;
	}

	//Change la taille de la barre en fonction d'un facteur multiplicatif
	void multiply_size(float factor)
	{
		nb_blocs = int(factor * float(nb_blocs));
	}

	//Retourne la largeur de la barre
	int get_sizeX()
	{
		return 50 + (25 * nb_blocs);
	}

	//Retourne la hauteur de la barre
	int get_sizeY()
	{
		return 25;
	}

	//retourne vrai si la balle touche le côté gauche
	bool contactGauche(balle ball)
	{
		
		if (((ball.y + ball.get_taille_y()) > (Gy + 12)) &&
			!((ball.x > (Gx + 25)) || ((ball.x + ball.get_taille_x()) < Gx)))
		{
			return true;
		}
			
		else
		{
			return false;
		}
	}

	//retourne vrai si la balle touche le côté droit
	bool contactDroit(balle ball)
	{

		if (((ball.y + ball.get_taille_x()) > (Dy + 12)) &&
			!((ball.x > (Dx + 25)) || ((ball.x + ball.get_taille_x()) < Dx)))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

	//retourne vrai si la balle touche le milieu
	bool contactMilieu(balle ball)
	{

		if (((ball.y + ball.get_taille_x()) > Dy) &&
			!((ball.x > (Dx + 25)) || ((ball.x + ball.get_taille_x()) < (Gx + 25))))
		{
			return true;
		}

		else
		{
			return false;
		}
	}

private:
	int nb_blocs = 2;	//Nombre de blocs intermédiaires de la barre.
	//ex: /|##|\ a un bloc de début /|, un bloc de fin |\ et deux blocs intermédiares #

};

//Les définitions de fonctions

#endif