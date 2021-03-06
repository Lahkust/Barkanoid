///* En-t�te du programme
//*****************************************
//Programme :			sdl2_ex2.cpp
//Auteur:				Alex J
//Date de cr�ation :  2016/01/01
//Description :		Ce programme affiche une image qui r�agit � certains �v�nements : il est possible de 
//					d�placer cette image en fonction du mouvement de la souris ou de certaines touches du clavier
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
//const int LARGEUR_FENETRE = 512;
//const int HAUTEUR_FENETRE = 512;
//
//const int LARGEUR_GRILLE_PACMAN = 512;
//const int HAUTEUR_GRILLE_PACMAN = 512;
//
//const int LARGEUR_IMAGE_FANTOME = 32;
//const int HAUTEUR_IMAGE_FANTOME = 34;
//
//
//
////Les variables de type LTexture sont des objets qui d�coulent de la la classe LTexture cr��e dans ce fichier
//LTexture pacmanGridTexture;	  //Texture utilis�e pour dessiner la grille du jeux pacman
//LTexture redGhostTexture;	  //Texture utilis�e pour dessiner un fant�me
//
////Les rectangles cr��s dans les variables suivants seront utilis�s lors du chargement des images dans leurs structures respectives
//SDL_Rect pacmanGridRect;
//SDL_Rect redGhostRect;
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
//  if (!redGhostTexture.loadFromFile("images/redGhost.png"))
//  {
//	printf("�chec de chargement de l'image ! \n");
//	success = false;
//  }
//  else
//  {
//	//On d�finit la taille du rectangle qui d�finira la taille de la texture 'redGhostTexture'
//	redGhostRect.x = 0;
//	redGhostRect.y = 0;
//	redGhostRect.w = LARGEUR_IMAGE_FANTOME;
//	redGhostRect.h = HAUTEUR_IMAGE_FANTOME;
//  }
//
//  return success;
//}
//
//
//
////Cette fonction effectue une fermeture appropri�e du programme, de l'environnement SDL et lib�re la m�moire des diff�rents �l�ments SDL cr��s
//void close()
//{
//
//  //On d�truit les LTextures cr��es dans le programme
//  pacmanGridTexture.free();
//  redGhostTexture.free();
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
//
//  bool quit = false;  //flag pour la boucle principale. Elle permet de d�terminer si l'on doit quitter le programme
//  SDL_Event e;        //Cette variable nous permet de d�tecter l'�v�nement courant que le programme doit g�rer (click, touche du clavier, etc.)
//
//  //On d�finit la position initiale du fant�me
//  int positionFantomeX = 0;
//  int positionFantomeY = 0;
//
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
//	  //Il est possible de d�finir une couleur de background du 'renderer'
//	  SDL_SetRenderDrawColor(rendererFenetre, 0xFF, 0xFF, 0xFF, 0xFF);
//
//	  //On dessine les deux textures cr��es sur 'rendererFenetre'
//	  pacmanGridTexture.render(0, 0, &pacmanGridRect);
//	  redGhostTexture.render(0, 0, &redGhostRect);
//
//	  //Mise � jour de 'rendererFenetre' (on redesinne les images (contenues dans leurs textures) dans le renderer)
//	  SDL_RenderPresent(rendererFenetre);
//
//
//	  //Le programme reste ouvert tant que quit != true 
//	  while (!quit)
//	  {
//		//Handle events on queue
//		while (SDL_PollEvent(&e) != 0)
//		{
//		  //Si l'utilisateur appuiie sur le bouton 'fermer' de la fen�tre
//		  if (e.type == SDL_QUIT)
//		  {
//			quit = true;
//		  }
//
//		  //Si l'utilisateur fait un click de souris
//		  else if (e.type == SDL_MOUSEBUTTONDOWN)
//		  {
//			quit = true;
//		  }
//		  //Si l'utilisateur d�pplace la souris
//		  else if (e.type == SDL_MOUSEMOTION)
//		  {
//			//On d�finit comme nouvelle position du fant�me celle de la souris
//			positionFantomeX = e.motion.x;
//			positionFantomeY = e.motion.y;
//
//		  }
//
//		  //Si une touche du clavier a �t� appuy�e
//		  else if (e.type == SDL_KEYDOWN)
//		  {
//
//			//Avec ce switch on indique qoui faire lorsque l'utilisateur appuie sur une touche
//			switch (e.key.keysym.sym)
//			{
//			case SDLK_w:  //La touche 'w' a �t� appuy�e
//			  positionFantomeX = 0;
//			  positionFantomeY = 0;
//			  break;
//
//			case SDLK_b:  ////La touche 'b' a �t� appuy�e
//			  positionFantomeX = 250;
//			  positionFantomeY = 250;
//			  break;
//
//			case SDLK_UP:
//			  positionFantomeY -= 10;
//			  break;
//
//			case SDLK_DOWN:
//			  positionFantomeY += 10;
//			  break;
//
//			case SDLK_LEFT:
//			  positionFantomeX -= 10;
//			  break;
//
//			case SDLK_RIGHT:
//			  positionFantomeX += 10;
//			  break;
//
//			default:
//			  break;
//			}//end switch
//		  }//end else if (e.type == SDL_KEYDOWN)
//		}//end while (SDL_PollEvent(&e) != 0)
//
//		//Clear screen
//		SDL_RenderClear(rendererFenetre);
//
//		pacmanGridTexture.render(0, 0, &pacmanGridRect);
//		redGhostTexture.render(positionFantomeX, positionFantomeY, &redGhostRect);
//
//		//Update screen
//		SDL_RenderPresent(rendererFenetre);
//
//	  }//end while (!quit)
//
//	}
//  }
//
//  //system("pause");
//
//  //Free resources and close SDL
//  close();
//
//  return 0;
//
//}
