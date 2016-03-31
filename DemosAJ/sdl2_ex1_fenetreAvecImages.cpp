///* En-t�te du programme
//*****************************************
//Programme :			sdl2_ex1.cpp
//Auteur:				Alex J
//Date de cr�ation :  2016/01/01
//Description :		Ce programme affiche plusieurs images dans une fen�tre
//Commentaires :		Ce code est inspir� du site : http://lazyfoo.net/tutorials/SDL/
//*****************************************/
//
//#include <iostream>
//#include <stdio.h>
//#include <string>
//#include "../SDL2/include/SDL.h"
//#include "../SDL2_image/include/SDL_image.h"
//
//
////***************************************** Prototypes
//bool init();
//bool loadMedia();
//void close();
//SDL_Texture* loadTexture(std::string path);
//
//
//
////********************************* Variables globales (partie 1)
//
////La fen�tre dans laquelle le programme sera ex�cut�
//SDL_Window* fenetreProgramme = NULL;
//
////Le 'renderer' associ� � la fen�tre du programme. Le 'renderer' est l'endroit dans lequelle on placera des textures
//SDL_Renderer* rendererFenetre = NULL;
//
//
//
//
////***************************************** Classe qui nous permet de manipuler les textures
//
//////Texture wrapper class
//class LTexture
//{
//public:
//  //Initializes variables
//  LTexture();
//
//  //Deallocates memory
//  ~LTexture();
//
//  //Loads image at specified path
//  bool loadFromFile(std::string path);
//
//  //Deallocates texture
//  void free();
//
//  //Set color modulation
//  void setColor(Uint8 red, Uint8 green, Uint8 blue);
//
//  //Set blending
//  void setBlendMode(SDL_BlendMode blending);
//
//  //Set alpha modulation
//  void setAlpha(Uint8 alpha);
//
//  //Renders texture at given point
//  void render(int x, int y, SDL_Rect* clip = NULL);
//
//  //Gets image dimensions
//  int getWidth();
//  int getHeight();
//
//private:
//  //The actual hardware texture
//  SDL_Texture* mTexture;
//
//  //Image dimensions
//  int mWidth;
//  int mHeight;
//};
//
//
//LTexture::LTexture()
//{
//  //Initialize
//  mTexture = NULL;
//  mWidth = 0;
//  mHeight = 0;
//}
//
//LTexture::~LTexture()
//{
//  //Deallocate
//  free();
//}
//
//bool LTexture::loadFromFile(std::string path)
//{
//  //Get rid of preexisting texture
//  free();
//
//  //The final texture
//  SDL_Texture* newTexture = NULL;
//
//  //Load image at specified path
//  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//  if (loadedSurface == NULL)
//  {
//	printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//  }
//  else
//  {
//	//Color key image
//	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
//
//	//Create texture from surface pixels
//	newTexture = SDL_CreateTextureFromSurface(rendererFenetre, loadedSurface);
//	if (newTexture == NULL)
//	{
//	  printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//	}
//	else
//	{
//	  //Get image dimensions
//	  mWidth = loadedSurface->w;
//	  mHeight = loadedSurface->h;
//	}
//
//	//Get rid of old loaded surface
//	SDL_FreeSurface(loadedSurface);
//  }
//
//  //Return success
//  mTexture = newTexture;
//  return mTexture != NULL;
//}
//
//void LTexture::free()
//{
//  //Free texture if it exists
//  if (mTexture != NULL)
//  {
//	SDL_DestroyTexture(mTexture);
//	mTexture = NULL;
//	mWidth = 0;
//	mHeight = 0;
//  }
//}
//
//void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
//{
//  //Modulate texture rgb
//  SDL_SetTextureColorMod(mTexture, red, green, blue);
//}
//
//void LTexture::setBlendMode(SDL_BlendMode blending)
//{
//  //Set blending function
//  SDL_SetTextureBlendMode(mTexture, blending);
//}
//
//void LTexture::setAlpha(Uint8 alpha)
//{
//  //Modulate texture alpha
//  SDL_SetTextureAlphaMod(mTexture, alpha);
//}
//
//void LTexture::render(int x, int y, SDL_Rect* clip)
//{
//  //Set rendering space and render to screen
//  SDL_Rect renderQuad = { x, y, mWidth, mHeight };
//
//  //Set clip rendering dimensions
//  if (clip != NULL)
//  {
//	renderQuad.w = clip->w;
//	renderQuad.h = clip->h;
//  }
//
//  //Render to screen
//  SDL_RenderCopy(rendererFenetre, mTexture, clip, &renderQuad);
//}
//
//int LTexture::getWidth()
//{
//  return mWidth;
//}
//
//int LTexture::getHeight()
//{
//  return mHeight;
//}
//
//
//
////********************************* Variables globales (partie 2)
//
////Taille de l'�cran en pixels
//const int LARGEUR_FENETRE = 640;
//const int HAUTEUR_FENETRE = 512;
//
//const int LARGEUR_GRILLE_PACMAN = 512;
//const int HAUTEUR_GRILLE_PACMAN = 512;
//
//const int LARGEUR_IMAGE_DONKEY = 84;
//const int HAUTEUR_IMAGE_DONKEY = 95;
//
//
////Une texture est un conteneur d'image. Pour placer une image dans le 'renderer', il faut la placer d'abord dans une texture
////La texture suivante prendra toute la taille du 'renderer'
//SDL_Texture* greenGrassTexture = NULL;
//
////Les variables de type LTexture sont des objets qui d�coulent de la la classe LTexture cr��e dans ce fichier
//LTexture pacmanGridTexture;	  //Texture utilis�e pour dessiner la grille du jeux pacman
//LTexture donkey1Texture;	  //Texture utilis�e pour dessiner un donkey
//
////Les rectangles cr��s dans les variables suivants seront utilis�s lors du chargement des images dans leurs structures respectives
//SDL_Rect pacmanGridRect;
//SDL_Rect donkey1Rect;
//
//
//
////********************************* Fonctions du programme
//
////Cette fonction initialise SDL et cr�� la fen�tre du programme
//bool init()
//{
//  //Cette variable indique si l'initialisation a �t� effectu�e avec succ�s
//  bool success = true;
//
//  //Initialisation de SDL
//  if (SDL_Init(SDL_INIT_VIDEO) < 0)
//  {
//	printf("Erreur lors de l'initialisation de SDL! - SDL Error: %s\n", SDL_GetError());
//	success = false;
//  }
//  else
//  {
//	//Set texture filtering to linear
//	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
//	{
//	  printf("Warning: Linear texture filtering not enabled!");
//	}
//
//	//Cr�ation de la fen�tre du programme
//	fenetreProgramme = SDL_CreateWindow("Titre fenetre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);
//
//	if (fenetreProgramme == NULL)
//	{
//	  printf("�chec de cr�ation de la fen�tre ! -  SDL_Error %s\n", SDL_GetError());
//	  success = false;
//	}
//	else
//	{
//	  //Creation du 'renderer' en l'associant � la fen�tre du programme
//	  rendererFenetre = SDL_CreateRenderer(fenetreProgramme, -1, SDL_RENDERER_ACCELERATED);
//	  if (rendererFenetre == NULL)
//	  {
//		printf("�chec de cr�ation du renderer ! - SDL Error: %s\n", SDL_GetError());
//		success = false;
//	  }
//	  else
//	  {
//		//Initialize renderer color
//		SDL_SetRenderDrawColor(rendererFenetre, 0xFF, 0xAA, 0xAA, 0xAA);
//
//		//Les commandes suivante permettent d'activer le chargement d'images dont le format est PNG
//		int imgFlags = IMG_INIT_PNG;
//		if (!(IMG_Init(imgFlags) & imgFlags))
//		{
//		  printf("�chec d'initialisation de SDL_image ! -  SDL_image Error: %s\n", IMG_GetError());
//		  success = false;
//		}
//	  }
//	}
//  }
//
//  return success;
//}
//
//
//
////Cette fonction est utilis�e pour charger les images du programme dans leurs textures correspondantes
//bool loadMedia()
//{
//  //Cette variable indique si le charg�ment de l'�l�ment a �t� effectu� avec succ�s
//  bool success = true;
//
//  //Chargement d'une image PNG dans 'greenGrassTexture'
//  greenGrassTexture = loadTexture("images/greenGrass.png");
//  if (greenGrassTexture == NULL)
//  {
//	printf("�chec de chargement de l'image ! \n");
//	success = false;
//  }
//
//  //Load sprite sheet texture
//  if (!pacmanGridTexture.loadFromFile("images/pacmanGrid.png"))
//  {
//	printf("�chec de chargement de l'image ! \n");
//	success = false;
//  }
//  else
//  {
//	//On d�finit la taille du rectangle qui d�finira la taille de la texture 'pacmanTexture'
//	pacmanGridRect.x = 0;
//	pacmanGridRect.y = 0;
//	pacmanGridRect.w = LARGEUR_GRILLE_PACMAN;
//	pacmanGridRect.h = HAUTEUR_GRILLE_PACMAN;
//  }
//
//  //Load sprite sheet texture
//  if (!donkey1Texture.loadFromFile("images/donkey1.png"))
//  {
//	printf("�chec de chargement de l'image ! \n");
//	success = false;
//  }
//  else
//  {
//	//On d�finit la taille du rectangle qui d�finira la taille de la texture 'donkey1TExture'
//	donkey1Rect.x = 0;
//	donkey1Rect.y = 0;
//	donkey1Rect.w = LARGEUR_IMAGE_DONKEY;
//	donkey1Rect.h = HAUTEUR_IMAGE_DONKEY;
//  }
//
//
//  return success;
//}
//
//
//
////Cette fonction effectue une fermeture appropri�e du programme, de l'environnement SDL et lib�re la m�moire des diff�rents �l�ments SDL cr��s
//void close()
//{
//  //Free loaded image
//  SDL_DestroyTexture(greenGrassTexture);
//  greenGrassTexture = NULL;
//
//  //On d�truit les LTextures cr��es dans le programme
//  pacmanGridTexture.free();
//  donkey1Texture.free();
//
//  //Destroy window
//  SDL_DestroyRenderer(rendererFenetre);
//  SDL_DestroyWindow(fenetreProgramme);
//  fenetreProgramme = NULL;
//  rendererFenetre = NULL;
//
//  //Quit SDL subsystems
//  IMG_Quit();
//  SDL_Quit();
//}
//
//
////Cette fonction est responsable de charg� dans une texture une image indique� en param�tre
//SDL_Texture* loadTexture(std::string path)
//{
//  //La texture finale
//  SDL_Texture* newTexture = NULL;
//
//  //Chargement de l'image dans la texture
//  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
//  if (loadedSurface == NULL)
//  {
//	printf("�chec de chargement de l'image dans la texture ! -  SDL_image Error: %s\n", path.c_str(), IMG_GetError());
//  }
//  else
//  {
//	//Create texture from surface pixels
//	newTexture = SDL_CreateTextureFromSurface(rendererFenetre, loadedSurface);
//	if (newTexture == NULL)
//	{
//	  printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
//	}
//
//	//Get rid of old loaded surface
//	SDL_FreeSurface(loadedSurface);
//  }
//
//  return newTexture;
//}
//
//
//
////Fonction principale du programme
//int main(int argc, char* args[])
//{
//  //Start up SDL and create window
//  if (!init())
//  {
//	printf("Failed to initialize!\n");
//  }
//  else
//  {
//	//Load media
//	if (!loadMedia())
//	{
//	  printf("Failed to load media!\n");
//	}
//	else
//	{
//	  printf("Programme OK!\n");
//
//	  //Netoyyer l'�cran (Clear Screen)
//	  SDL_RenderClear(rendererFenetre);
//
//
//	  //On Desine 'greenGrassTexture' dans 'rendererFenetre'
//	  SDL_RenderCopy(rendererFenetre, greenGrassTexture, NULL, NULL);
//
//	  //On dessine les deux textures cr��es sur 'rendererFenetre'
//	  pacmanGridTexture.render(0, 0, &pacmanGridRect);
//	  donkey1Texture.render(0, 0, &donkey1Rect);
//
//	  //Mise � jour de 'rendererFenetre' (on redesinne les images (contenues dans leurs textures) dans le renderer)
//	  SDL_RenderPresent(rendererFenetre);
//
//	}
//  }
//
//  system("pause");
//
//  //Free resources and close SDL
//  close();
//
//  return 0;
//
//}
