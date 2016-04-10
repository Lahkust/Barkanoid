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
	bloc(int v);
	bloc(int v, SDL_Renderer *r);
	~bloc();
	void setRenderer(SDL_Renderer *renderer);

	LTexture blocTexture;
	SDL_Rect blocRect[NOMBRE_IMAGES_BLOC_CHARSET];

	//La position en x et en y d'un bloc
	int x;
	int y;

	bool contact(balle &ball);

	// Retourne la vie d'un bloc
	int getVie(){ return vie; };

	// Retourne le rectangle d'un bloc
	SDL_Rect &getRect(){ return blocRect[vie]; }

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

	int vie = 1; //Indique la vie restant au bloc; correspond à l'index du charset; si négatif, indique la suppression du bloc


};

bloc::bloc()
{
	vie = 1;
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


bloc::bloc(int v)
{
	vie = v;


	//Load bloc sprite sheet texture
	if (!blocTexture.loadFromFile("images/blocCharset.png"))
	{
		printf("Échec de chargement de l'image ! \n");
		//system("pause");
		//success = false;
	}
	else
	{
		//On initialise chaque rectangle du tableau 'blocRect'
		initialiserCharset(blocRect, NOMBRE_IMAGES_BLOC_CHARSET, LARGEUR_IMAGE_BLOC_CHARSET, HAUTEUR_IMAGE_BLOC_CHARSET);
	}

}

bloc::bloc(int v, SDL_Renderer *renderer)
{
	vie = v;
	LTexture blocTexture(renderer);
	/*

	//Load bloc sprite sheet texture
	if (!blocTexture.loadFromFile("images/blocCharset.png"))
	{
		printf("Échec de chargement de l'image ! \n");
		//system("pause");
		//success = false;
	}
	else
	{
		//On initialise chaque rectangle du tableau 'blocRect'
		initialiserCharset(blocRect, NOMBRE_IMAGES_BLOC_CHARSET, LARGEUR_IMAGE_BLOC_CHARSET, HAUTEUR_IMAGE_BLOC_CHARSET);
	}

	blocTexture.rendererFenetre = renderer;*/
}


bloc::~bloc()
{
	blocTexture.free();
}

void bloc::setRenderer(SDL_Renderer *renderer)
{
	this->blocTexture.rendererFenetre = renderer;

	//Load bloc sprite sheet texture
	if (!blocTexture.loadFromFile("images/blocCharset.png"))
	{
		printf("Échec de chargement de l'image ! \n");
		//system("pause");
		//success = false;
	}
	else
	{
		//On initialise chaque rectangle du tableau 'blocRect'
		printf("Chargement OK ! \n");
		//system("pause");
		initialiserCharset(blocRect, NOMBRE_IMAGES_BLOC_CHARSET, LARGEUR_IMAGE_BLOC_CHARSET, HAUTEUR_IMAGE_BLOC_CHARSET);
	}
}

bool bloc::contact(balle &ball)
{
	//La coordonnée en y du haut de la balle
	int balleHaut = ball.get_y();
	//La coordonnée en y du bas de la balle
	int balleBas = balleHaut + ball.get_taille_y();
	//la coordonnée en x du gauche de la balle
	int balleGauche = ball.get_x();
	//la coordonnée en x du droit de la balle
	int balleDroit = balleGauche + ball.get_taille_x();

	//la coordonnée en y du haut du bloc
	int blocHaut = y;
	//la coordonnée en y du bas du bloc
	int blocBas = y + HAUTEUR_IMAGE_BLOC_CHARSET;
	//la coordonnée en x du gauche du bloc
	int blocGauche = x;
	//la coordonnée en x du droit du bloc
	int blocDroit = x + LARGEUR_IMAGE_BLOC_CHARSET;

	//Si contact avec le côté haut du bloc
	if ((balleBas > blocHaut) && (!(balleDroit <blocGauche) && !(balleGauche > blocDroit) && !(balleHaut > blocBas)))return true;

	//si contact avec le coté bas du bloc
	if ((balleHaut < blocBas) && (!(balleDroit <blocGauche) && !(balleGauche > blocDroit) && !(balleBas < blocHaut)))return true;

	//si contact avec le coté gauche du bloc
	if ((balleDroit > blocGauche) && (!(balleHaut > blocBas) && !(balleGauche > blocDroit) && !(balleBas < blocHaut)))return true;

	//si contact avec le coté droit du bloc
	if ((balleGauche < blocDroit) && (!(balleHaut > blocBas) && !(balleDroit < blocGauche) && !(balleBas < blocHaut)))return true;
	
	//Sinon
	return false;
}

#endif