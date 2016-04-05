/* En-tête du programme
*****************************************
Fichier :			bloc.h
Auteur:				Guillaume Bergs & Shawn Corriveau
Date de création :  2016/01/01
Description :		Tout ce qui concerne les blocs
Commentaires :
*****************************************/

#ifndef BLOC_H
#define BLOC_H

#include <iostream>
#include <stdio.h>
#include <string>
#include "../SDL2/include/SDL.h"
#include "../SDL2_image/include/SDL_image.h"
#include "visuel.h"

//Valeurs reliées aux blocs
const int NOMBRE_IMAGES_BLOC_CHARSET = 7;
const int LARGEUR_IMAGE_BLOC_CHARSET = 40;
const int HAUTEUR_IMAGE_BLOC_CHARSET = 20;

//Les définitions de fonctions

class bloc{
public:
	bloc();
	~bloc();

	LTexture blocTexture;
	SDL_Rect blocRect[NOMBRE_IMAGES_BLOC_CHARSET];

	//Décrémente la vie du bloc, par défaut, de 1
	void decrementerVie(int nb_PV = 1)
	{
		vie -= nb_PV;
		if (vie < 0){ vie = 0; }
	}

	//Tue le bloc
	void kill()
	{
		vie = 0;
	}

private:

	int vie = 0; //Indique la vie restant au bloc; correspond à l'index du charset; si négatif, indique la suppression du bloc
};

bloc::bloc()
{
	//Load bloc sprite sheet texture
	if (!blocTexture.loadFromFile("images/blocCharset.png"))
	{
		printf("Échec de chargement de l'image ! \n");
		//success = false;
	}
	else
	{
		//On initialise chaque rectangle du tableau 'blocRect'
		initialiserCharset(blocRect, NOMBRE_IMAGES_BLOC_CHARSET, LARGEUR_IMAGE_BLOC_CHARSET, HAUTEUR_IMAGE_BLOC_CHARSET);
	}
}

bloc::~bloc()
{
	blocTexture.free();
}

#endif