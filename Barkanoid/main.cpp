/* En-t�te du programme
*****************************************
Fichier :			main.cpp
Auteur:				Guillaume Bergs & Shawn Corriveau
Date de cr�ation :  2016/01/01
Description :		Fonction principale du jeu Barkanoid
Commentaires :
*****************************************/

#include <iostream>
#include <stdio.h>
#include <string>
#include "../SDL2/include/SDL.h"
#include "../SDL2_image/include/SDL_image.h"

#include "balle.h"
#include "barre.h"
#include "bloc.h"
#include "bonus.h"
#include "visuel.h"


//***************************************** Prototypes
bool init();
bool loadMedia();
void close();
SDL_Texture* loadTexture(std::string path);
//void initialiserCharset(SDL_Rect tableauRectangles[], int nombreImages, int largeurChaqueImage, int hauteurChaqueImage);



//********************************* Variables globales (partie 1)

//La fen�tre dans laquelle le programme sera ex�cut�
SDL_Window* fenetreProgramme = NULL;

//Le 'renderer' associ� � la fen�tre du programme. Le 'renderer' est l'endroit dans lequelle on placera des textures
SDL_Renderer* rendererFenetre = NULL;


//Les variables de type LTexture sont des objets qui d�coulent de la la classe LTexture cr��e dans ce fichier
LTexture hommeTexture(rendererFenetre);
LTexture balleTexture(rendererFenetre);
LTexture barreGTexture(rendererFenetre);
LTexture barreMTexture(rendererFenetre);
LTexture barreDTexture(rendererFenetre);
LTexture blocTexture(rendererFenetre);

//Ce tableau de rectangles sera utilis� lors du chargement d'une image dans la structure 'hommeTexture'
SDL_Rect blocRect[NOMBRE_IMAGES_BLOC_CHARSET];
SDL_Rect balleRect;
SDL_Rect barreGRect;
SDL_Rect barreMRect;
SDL_Rect barreDRect;



//********************************* Fonctions du programme

//Cette fonction initialise SDL et cr�� la fen�tre du programme
bool init()
{
  //Cette variable indique si l'initialisation a �t� effectu�e avec succ�s
  bool success = true;

  //Initialisation de SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
	printf("Erreur lors de l'initialisation de SDL! - SDL Error: %s\n", SDL_GetError());
	success = false;
  }
  else
  {
	//Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
	  printf("Warning: Linear texture filtering not enabled!");
	}

	//Cr�ation de la fen�tre du programme
	fenetreProgramme = SDL_CreateWindow("Titre fenetre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);

	if (fenetreProgramme == NULL)
	{
	  printf("�chec de cr�ation de la fen�tre ! -  SDL_Error %s\n", SDL_GetError());
	  success = false;
	}
	else
	{
	  //Creation du 'renderer' en l'associant � la fen�tre du programme
	  rendererFenetre = SDL_CreateRenderer(fenetreProgramme, -1, SDL_RENDERER_ACCELERATED);

	  hommeTexture.rendererFenetre = rendererFenetre;
	  balleTexture.rendererFenetre = rendererFenetre;
	  barreGTexture.rendererFenetre = rendererFenetre;
	  barreMTexture.rendererFenetre = rendererFenetre;
	  barreDTexture.rendererFenetre = rendererFenetre;
	  blocTexture.rendererFenetre = rendererFenetre;

	  if (rendererFenetre == NULL)
	  {
		printf("�chec de cr�ation du renderer ! - SDL Error: %s\n", SDL_GetError());
		success = false;
	  }
	  else
	  {
		//Initialize renderer color
		SDL_SetRenderDrawColor(rendererFenetre, 0xFF, 0xAA, 0xAA, 0xAA);

		//Les commandes suivante permettent d'activer le chargement d'images dont le format est PNG
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
		  printf("�chec d'initialisation de SDL_image ! -  SDL_image Error: %s\n", IMG_GetError());
		  success = false;
		}
	  }
	}
  }

  return success;
}



//Cette fonction est utilis�e pour charger les images du programme dans leurs textures correspondantes
bool loadMedia()
{
  //Cette variable indique si le charg�ment de l'�l�ment a �t� effectu� avec succ�s
  bool success = true;

 

  //Load bloc sprite sheet texture
  if(!blocTexture.loadFromFile("images/blocCharset.png"))
  {
	  printf("�chec de chargement de l'image ! \n");
	  success = false;
  }
  else
  {
	  //On initialise chaque rectangle du tableau 'blocRect'
	  initialiserCharset(blocRect, NOMBRE_IMAGES_BLOC_CHARSET, LARGEUR_IMAGE_BLOC_CHARSET, HAUTEUR_IMAGE_BLOC_CHARSET);
  }

  //Load balle sprite texture
  if (!balleTexture.loadFromFile("images/ball.png"))
  {
	  printf("�chec de chargement de l'image ! \n");
	  success = false;
  }
  else
  {
	  balleRect.h = HAUTEUR_IMAGE_BALLE;
	  balleRect.w = LARGEUR_IMAGE_BALLE;
	  balleRect.x = 0;
	  balleRect.y = 0;
  }

  //Load sprite barre G texture
  if (!barreGTexture.loadFromFile("images/barreGauche.png"))
  {
	  printf("�chec de chargement de l'image ! \n");
	  success = false;
  }
  else
  {
	  barreGRect.h = HAUTEUR_IMAGE_BARRE_G;
	  barreGRect.w = LARGEUR_IMAGE_BARRE_G;
	  barreGRect.x = 0;
	  barreGRect.y = 0;
  }

  //Load sprite barre M texture
  if (!barreMTexture.loadFromFile("images/barreMilieu.png"))
  {
	  printf("�chec de chargement de l'image ! \n");
	  success = false;
  }
  else
  {
	  barreMRect.h = HAUTEUR_IMAGE_BARRE_M;
	  barreMRect.w = LARGEUR_IMAGE_BARRE_M;
	  barreMRect.x = 0;
	  barreMRect.y = 0;
  }

  //Load sprite barre D texture
  if (!barreDTexture.loadFromFile("images/barreDroite.png"))
  {
	  printf("�chec de chargement de l'image ! \n");
	  success = false;
  }
  else
  {
	  barreDRect.h = HAUTEUR_IMAGE_BARRE_D;
	  barreDRect.w = LARGEUR_IMAGE_BARRE_D;
	  barreDRect.x = 0;
	  barreDRect.y = 0;
  }


  return success;
}



//Cette fonction effectue une fermeture appropri�e du programme, de l'environnement SDL et lib�re la m�moire des diff�rents �l�ments SDL cr��s
void close()
{

  //On d�truit les LTextures cr��es dans le programme
  hommeTexture.free();
  blocTexture.free();
  balleTexture.free();
  barreGTexture.free();
  barreMTexture.free();
  barreDTexture.free();


  //Destroy window
  SDL_DestroyRenderer(rendererFenetre);
  SDL_DestroyWindow(fenetreProgramme);
  fenetreProgramme = NULL;
  rendererFenetre = NULL;

  //Quit SDL subsystems
  IMG_Quit();
  SDL_Quit();
}


//Cette fonction est responsable de charger dans une texture l'image indique� en param�tre
SDL_Texture* loadTexture(std::string path)
{
  //La texture finale
  SDL_Texture* newTexture = NULL;

  //Chargement de l'image dans la texture
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL)
  {
	printf("�chec de chargement de l'image dans la texture ! -  SDL_image Error: %s\n", path.c_str(), IMG_GetError());
  }
  else
  {
	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface(rendererFenetre, loadedSurface);
	if (newTexture == NULL)
	{
	  printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
	}

	//Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);
  }

  return newTexture;
}



////Initialisation des rectangles qui vont s'associer aux diff�rentes images du charset
//void initialiserCharset(SDL_Rect tableauRectangles[], int nombreImages, int largeurChaqueImage, int hauteurChaqueImage)
//{
//  for (int i = 0; i < nombreImages; i++)
//  {
//	tableauRectangles[i].x = largeurChaqueImage * i;
//	tableauRectangles[i].y = 0;
//	tableauRectangles[i].w = largeurChaqueImage;
//	tableauRectangles[i].h = hauteurChaqueImage;
//  }
//}



//Fonction principale du programme
int main(int argc, char* args[])
{

  bool quit = false;  //flag pour la boucle principale. Elle permet de d�terminer si l'on doit quitter le programme
  int indexImageCharset = 0;  //Cette variable nous permet de s�lectionner une image du charset de l'homme
  int compteur = 0;	  //Ce compteur est utilis� pour d�terminer � quel moment changer d'image dans 'homeCharset'
 

  balle ball; //La balle
  ball.set_velocityP(10, 42); //Sa vitesse de d�part

  barre labarre;
  labarre.multiply_size(0.5); //Pour une taille de 1


  SDL_Event e;        //Cette variable nous permet de d�tecter l'�v�nement courant que le programme doit g�rer (click, touche du clavier, etc.)


  labarre.Gx = LARGEUR_FENETRE / 2;
  labarre.Gy = 650;
  labarre.Dx = (labarre.Gx + LARGEUR_IMAGE_BARRE_G) + LARGEUR_IMAGE_BARRE_M;
  labarre.Dy = 650;

  ball.x = LARGEUR_FENETRE / 2;
  ball.y = HAUTEUR_FENETRE / 2;


  //Start up SDL and create window
  if (!init())
  {
	printf("Failed to initialize!\n");
  }
  else
  {
	//Load media
	if (!loadMedia())
	{
	  printf("Failed to load media!\n");
	}
	else
	{
	  printf("Programme OK!\n");

	  //Netoyyer l'�cran (Clear Screen)
	  SDL_RenderClear(rendererFenetre);

	  //Il est possible de d�finir une couleur de background du 'renderer'
	  SDL_SetRenderDrawColor(rendererFenetre, 0xFF, 0xCC, 0xCC, 0xCC);

	  //On dessine cette texture
	  //hommeTexture.render(0, 0, currentHommeRect);
	  barreGTexture.render(0, 0, &barreGRect);
	  barreMTexture.render(0, 0, &barreMRect);
	  barreDTexture.render(0, 0, &barreDRect);


	  //Mise � jour de 'rendererFenetre' (on redesine les images (contenues dans leurs textures) dans le renderer)
	  SDL_RenderPresent(rendererFenetre);


	  //Le programme reste ouvert tant que quit != true 
	  while (!quit)
	  {
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
		  //Si l'utilisateur appuiie sur le bouton 'fermer' de la fen�tre
		  if (e.type == SDL_QUIT)
		  {
			quit = true;
		  }

		  //Si l'utilisateur fait un click de souris
		  else if (e.type == SDL_MOUSEBUTTONDOWN)
		  {
			quit = true;
		  }
		  //Si l'utilisateur d�pplace la souris
		  else if (e.type == SDL_MOUSEMOTION)
		  {
			//On d�finit comme nouvelle position du fant�me celle de la souris
			//positionHommeX = e.motion.x;
			//positionHommeY = e.motion.y;

			  labarre.Gx = e.motion.x -25;
			  labarre.Dx = (labarre.Gx + LARGEUR_IMAGE_BARRE_G) + LARGEUR_IMAGE_BARRE_M;

		  }

		  //Si une touche du clavier a �t� appuy�e
		  else if (e.type == SDL_KEYDOWN)
		  {

			//Avec ce switch on indique qoui faire lorsque l'utilisateur appuie sur une touche
			switch (e.key.keysym.sym)
			{
			case SDLK_w:  //La touche 'w' a �t� appuy�e
			 // positionHommeX = 0;
			 // positionHommeY = 0;
			  break;

			case SDLK_b:  ////La touche 'b' a �t� appuy�e
			//  positionHommeX = 250;
			//  positionHommeY = 250;
			  break;

			case SDLK_UP:
			//  positionHommeY -= 10;
				ball.set_velocityC(0, -2);
			  break;

			case SDLK_DOWN:
			//  positionHommeY += 10;
				ball.set_velocityC(0, 2);
			  break;

			case SDLK_LEFT:
			//  positionHommeX -= 10;
				ball.set_velocityC(-2, 0);

				labarre.Gx -= 10;
				labarre.Dx = (labarre.Gx + LARGEUR_IMAGE_BARRE_G) + LARGEUR_IMAGE_BARRE_M;
			  break;

			case SDLK_RIGHT:
			//  positionHommeX += 10;
				ball.set_velocityC(2, 0);

				labarre.Gx += 10;
				labarre.Dx = (labarre.Gx + LARGEUR_IMAGE_BARRE_G) + LARGEUR_IMAGE_BARRE_M;
			  break;

			default:
			  break;
			}//end switch
		  }//end else if (e.type == SDL_KEYDOWN)
		}//end while (SDL_PollEvent(&e) != 0)

		
		//Clear screen
		SDL_RenderClear(rendererFenetre);

		/*std::cout << "indexImageCharset = " << indexImageCharset << std::endl;
		std::cout << "compteur = " << compteur << std::endl;*/

		//currentHommeRect = &hommeRect[indexImageCharset];





		//hommeTexture.render(positionHommeX, positionHommeY, currentHommeRect);
		barreGTexture.render(labarre.Gx, labarre.Gy, &barreGRect);
		barreMTexture.render((labarre.Gx + LARGEUR_IMAGE_BARRE_G), labarre.Gy, &barreMRect);
		barreDTexture.render(labarre.Dx, labarre.Dy, &barreDRect);
		balleTexture.render(ball.x, ball.y, &balleRect);

		//Update screen
		SDL_RenderPresent(rendererFenetre);

		compteur++;

		//On d�termine si on change d'image, selon le facteur de ralentissement
		if (compteur % FACTEUR_RALENTISSEMENT_ANIMATION == 0)
		{
		 

			/*****************************/
			// Code test des rebonds
			{
				float balleX, balleY,balleR,balleA,angle_mur;

				angle_mur = 0;
				ball.get_velocityC(balleX, balleY);
				ball.get_velocityP(balleR, balleA);

				//Gauche
				if (ball.x < 0)
				{
					angle_mur = -5 * M_PI / 2;
					
				}
				//Droite
				if ((ball.x+LARGEUR_IMAGE_BALLE) > LARGEUR_FENETRE)
				{
					angle_mur =  -5 * M_PI / 2;
				}
				//Haut
				if (ball.y < 0)
				{
					angle_mur = M_PI;
				}
				//Bas
				if ((ball.y+HAUTEUR_IMAGE_BALLE) > HAUTEUR_FENETRE)
				{
					angle_mur = 2 * M_PI;
				}

				//BarreM
				if (labarre.contactMilieu(ball))
				{
					angle_mur = M_PI;
				}

				//BarreG
				if (labarre.contactGauche(ball))
				{
					angle_mur = 3 *  M_PI / 4;
				}

				//BarreD
				if (labarre.contactDroit(ball))
				{
					angle_mur = -3 * M_PI / 4;
				}

				if (angle_mur !=0)
					ball.set_velocityP(balleR, angle_mur - balleA);

				ball.get_velocityC(balleX, balleY);		
				ball.set_velocityC(1.0001 * balleX, 1.0001 * balleY);	//	Code pour une l�g�re acc�l�ration plus le temps avance
				ball.get_velocityC(balleX, balleY);						//

				ball.get_velocityP(balleR, balleA);

				ball.x += balleX;
				ball.y += balleY;

				system("cls");
				std::cout << balleX << std::endl << balleY << std::endl;
				std::cout << balleR << std::endl << balleA * 180 / M_PI;

			}
			/********************************/


			compteur = 0;
		  
		}

		//SDL_Delay(1000);

	  }//end while (!quit)
	}
  }

  //system("pause");

  //Free resources and close SDL
  close();

  return 0;

}
