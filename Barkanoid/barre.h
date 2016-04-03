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

class barre{
public:

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

private:
	int nb_blocs = 2;	//Nombre de blocs intermédiaires de la barre.
	//ex: /|##|\ a un bloc de début /|, un bloc de fin |\ et deux blocs intermédiares #

};

//Les définitions de fonctions

#endif