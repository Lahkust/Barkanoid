/* En-t�te du programme
*****************************************
Fichier :			bloc.h
Auteur:				Guillaume Bergs & Shawn Corriveau
Date de cr�ation :  2016/01/01
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

//Les d�finitions de fonctions

class bloc{
public:
	//D�cr�mente la vie du bloc, par d�faut, de 1
	void decrementerVie(int nb_PV = 1)
	{
		vie -= nb_PV;
	}

	//Tue le bloc
	void kill()
	{
		vie = -1;
	}

private:

	int vie = 0; //Indique la vie restant au bloc; correspond � l'index du charset; si n�gatif, indique la suppression du bloc
};

#endif