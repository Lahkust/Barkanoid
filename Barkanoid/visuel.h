/* En-tête du programme
*****************************************
Fichier :			visuel.h
Auteur:				Guillaume Bergs & Shawn Corriveau
Date de création :  2016/01/01
Description :		Tout ce qui concerne l'affichage d'images à l'écran
Commentaires :
*****************************************/

#ifndef VISUEL_H
#define VISUEL_H

#include <iostream>
#include <stdio.h>
#include <string>
#include "../SDL2/include/SDL.h"
#include "../SDL2_image/include/SDL_image.h"

//Taille de l'écran en pixels
const int LARGEUR_FENETRE = 600;
const int HAUTEUR_FENETRE = 700;
const int FACTEUR_RALENTISSEMENT_ANIMATION = 10;  //Pour rendre l'animation plus rapide, indiquer un chiffre plus petit


//Les définitions de fonctions

//***************************************** Classe qui nous permet de manipuler les textures (Ne pas éditer)

////Texture wrapper class
class LTexture
{
public:
	//Initializes variables
	LTexture();
	LTexture(SDL_Renderer *renderer);


	//Deallocates memory
	~LTexture();

	//Loads image at specified path
	bool loadFromFile(std::string path);

	//Deallocates texture
	void free();

	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	//Set blending
	void setBlendMode(SDL_BlendMode blending);

	//Set alpha modulation
	void setAlpha(Uint8 alpha);

	//Renders texture at given point
	void render(int x, int y, SDL_Rect* clip = NULL);

	//Gets image dimensions
	int getWidth();
	int getHeight();

	//Renderer
	SDL_Renderer *rendererFenetre;
private:
	//The actual hardware texture
	SDL_Texture* mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	rendererFenetre = NULL;
}

LTexture::LTexture(SDL_Renderer *renderer)
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
	rendererFenetre = renderer;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(rendererFenetre, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopy(rendererFenetre, mTexture, clip, &renderQuad);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

//Initialisation des rectangles qui vont s'associer aux différentes images du charset
void initialiserCharset(SDL_Rect tableauRectangles[], int nombreImages, int largeurChaqueImage, int hauteurChaqueImage)
{
	for (int i = 0; i < nombreImages; i++)
	{
		tableauRectangles[i].x = largeurChaqueImage * i;
		tableauRectangles[i].y = 0;
		tableauRectangles[i].w = largeurChaqueImage;
		tableauRectangles[i].h = hauteurChaqueImage;
	}
}

#endif