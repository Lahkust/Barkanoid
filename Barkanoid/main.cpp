/* En-tête du programme
*****************************************
Fichier :			main.cpp
Auteur:				Guillaume Bergs & Shawn Corriveau
Date de création :  2016/01/01
Description :		Fonction principale du jeu Barkanoid
Commentaires :
*****************************************/


//*************************************** Déclarations pré-processeur
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


//********************************* Variables globales (partie 1)

//La fenêtre dans laquelle le programme sera exécuté
SDL_Window* fenetreProgramme = NULL;

//Le 'renderer' associé à la fenêtre du programme. Le 'renderer' est l'endroit dans lequelle on placera des textures
SDL_Renderer* rendererFenetre = NULL;


//Les variables de type LTexture sont des objets qui découlent de la la classe LTexture créée dans ce fichier
LTexture balleTexture(rendererFenetre);
LTexture barreGTexture(rendererFenetre);
LTexture barreMTexture(rendererFenetre);
LTexture barreDTexture(rendererFenetre);
//LTexture blocTexture(rendererFenetre);

//Ce tableau de rectangles sera utilisé lors du chargement d'une image dans la structure 'hommeTexture'
//SDL_Rect blocRect[NOMBRE_IMAGES_BLOC_CHARSET];
SDL_Rect balleRect;
SDL_Rect barreGRect;
SDL_Rect barreMRect;
SDL_Rect barreDRect;



//********************************* Fonctions du programme

//Cette fonction initialise SDL et créé la fenêtre du programme
bool init()
{
  //Cette variable indique si l'initialisation a été effectuée avec succès
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

	//Création de la fenêtre du programme
	fenetreProgramme = SDL_CreateWindow("Titre fenetre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);

	if (fenetreProgramme == NULL)
	{
	  printf("Échec de création de la fenêtre ! -  SDL_Error %s\n", SDL_GetError());
	  success = false;
	}
	else
	{
	  //Creation du 'renderer' en l'associant à la fenêtre du programme
	  rendererFenetre = SDL_CreateRenderer(fenetreProgramme, -1, SDL_RENDERER_ACCELERATED);


	  if (rendererFenetre == NULL)
	  {
		printf("Échec de création du renderer ! - SDL Error: %s\n", SDL_GetError());
		success = false;
	  }
	  else
	  {
		//Initialize renderer color
		SDL_SetRenderDrawColor(rendererFenetre, 0xFF, 0xAA, 0xAA, 0xAA);

		balleTexture.rendererFenetre = rendererFenetre;
		barreGTexture.rendererFenetre = rendererFenetre;
		barreMTexture.rendererFenetre = rendererFenetre;
		barreDTexture.rendererFenetre = rendererFenetre;

		//Les commandes suivante permettent d'activer le chargement d'images dont le format est PNG
		int imgFlags = IMG_INIT_PNG;
		if (!(IMG_Init(imgFlags) & imgFlags))
		{
		  printf("Échec d'initialisation de SDL_image ! -  SDL_image Error: %s\n", IMG_GetError());
		  success = false;
		}
	  }
	}
  }

  return success;
}



//Cette fonction est utilisée pour charger les images du programme dans leurs textures correspondantes
bool loadMedia()
{
  //Cette variable indique si le chargément de l'élément a été effectué avec succès
  bool success = true;



  //Load balle sprite texture
  if (!balleTexture.loadFromFile("images/ball.png"))
  {
	  printf("Échec de chargement de l'image ! \n");
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
	  printf("Échec de chargement de l'image ! \n");
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
	  printf("Échec de chargement de l'image ! \n");
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
	  printf("Échec de chargement de l'image ! \n");
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



//Cette fonction effectue une fermeture appropriée du programme, de l'environnement SDL et libère la mémoire des différents éléments SDL créés
void close()
{

  //On détruit les LTextures créées dans le programme
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


//Cette fonction est responsable de charger dans une texture l'image indiqueé en paramètre
SDL_Texture* loadTexture(std::string path)
{
  //La texture finale
  SDL_Texture* newTexture = NULL;

  //Chargement de l'image dans la texture
  SDL_Surface* loadedSurface = IMG_Load(path.c_str());
  if (loadedSurface == NULL)
  {
	printf("Échec de chargement de l'image dans la texture ! -  SDL_image Error: %s\n", path.c_str(), IMG_GetError());
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



//Fonction principale du programme
int main(int argc, char* args[])
{

  bool quit = false;  //flag pour la boucle principale. Elle permet de déterminer si l'on doit quitter le programme
  int indexImageCharset = 0;  //Cette variable nous permet de sélectionner une image du charset du bloc
  int compteur = 0;	  //Ce compteur est utilisé pour déterminer quand rafraichir l'écran
 

  balle ball; //La balle
  ball.set_velocityP(10, 42); //Sa vitesse de départ

  barre labarre;
  labarre.multiply_size(0.5); //Pour une taille de 1

  bloc blocs[15][15]; //Les blocs

  //Attribuer une vie aux blocs
  for (int i = 0; i < 15; ++i)
	  for (int j = 0; j < 15; ++j)
	  {

	  if (j <= 4) blocs[i][j].decrementerVie(0);

	  else if (j <= 8) blocs[i][j].decrementerVie(-1);

	  else if (j <= 11) blocs[i][j].decrementerVie(-2);

	  else if (j <= 13) blocs[i][j].decrementerVie(-3);

	  else blocs[i][j].decrementerVie(-4);
	  }


  SDL_Event e;        //Cette variable nous permet de détecter l'événement courant que le programme doit gérer (click, touche du clavier, etc.)

  labarre.Gx = LARGEUR_FENETRE / 2;
  labarre.Gy = HAUTEUR_FENETRE - 50;
  labarre.Dx = (labarre.Gx + LARGEUR_IMAGE_BARRE_G) + LARGEUR_IMAGE_BARRE_M;
  labarre.Dy = HAUTEUR_FENETRE - 50;

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

	  //Netoyer l'écran (Clear Screen)
	  SDL_RenderClear(rendererFenetre);

	  //Il est possible de définir une couleur de background du 'renderer'
	  SDL_SetRenderDrawColor(rendererFenetre, 0xFF, 0xCC, 0xCC, 0xCC);

	  //On dessine cette texture
	  barreGTexture.render(0, 0, &barreGRect);
	  barreMTexture.render(0, 0, &barreMRect);
	  barreDTexture.render(0, 0, &barreDRect);


	  //Mise à jour de 'rendererFenetre' (on redessine les images (contenues dans leurs textures) dans le renderer)
	  SDL_RenderPresent(rendererFenetre);

	  //Donner un renderer aux blocs
	  for (int i = 0; i < 15; ++i)
		  for (int j = 0; j < 15; ++j)
			blocs[i][j].setRenderer(rendererFenetre);


	  //Le programme reste ouvert tant que quit != true 
	  while (!quit)
	  {
		  //SDL_get_keyboardstate
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
		  //Si l'utilisateur appuiie sur le bouton 'fermer' de la fenêtre
		  if (e.type == SDL_QUIT)
		  {
			quit = true;
		  }

		  //Si l'utilisateur fait un click de souris
		  else if (e.type == SDL_MOUSEBUTTONDOWN)
		  {
			quit = true;
		  }
		  //Si l'utilisateur déplace la souris
		  else if (e.type == SDL_MOUSEMOTION)
		  {
			//On définit comme nouvelle position de la barre celle de la souris en X
			  labarre.Gx = e.motion.x -25;
			  labarre.Dx = (labarre.Gx + LARGEUR_IMAGE_BARRE_G) + LARGEUR_IMAGE_BARRE_M;
		  }

		  //Si une touche du clavier a été appuyée
		  else if (e.type == SDL_KEYDOWN)
		  {

			//Avec ce switch on indique qoui faire lorsque l'utilisateur appuie sur une touche
			switch (e.key.keysym.sym)
			{
			case SDLK_w:  //La touche 'w' a été appuyée
				//lebloc.decrementerVie();
			  break;

			case SDLK_b:  ////La touche 'b' a été appuyée
				//lebloc.decrementerVie(-1);
			  break;

			case SDLK_UP:
				ball.set_velocityC(0, -2);
			  break;

			case SDLK_DOWN:
				ball.set_velocityC(0, 2);
			  break;

			case SDLK_LEFT:
				ball.set_velocityC(-2, 0);

				labarre.Gx -= 10;
				labarre.Dx = (labarre.Gx + LARGEUR_IMAGE_BARRE_G) + LARGEUR_IMAGE_BARRE_M;
			  break;

			case SDLK_RIGHT:
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


		//hommeTexture.render(positionHommeX, positionHommeY, currentHommeRect);
		barreGTexture.render(labarre.Gx, labarre.Gy, &barreGRect);
		barreMTexture.render((labarre.Gx + LARGEUR_IMAGE_BARRE_G), labarre.Gy, &barreMRect);
		barreDTexture.render(labarre.Dx, labarre.Dy, &barreDRect);
		balleTexture.render(ball.x, ball.y, &balleRect);


		for (int i = 0; i < 15; ++i)
			for (int j = 0; j < 15; ++j)
				blocs[i][j].blocTexture.render(i*40,
				j*20,
				&blocs[i][j].getRect());


		//Update screen
		SDL_RenderPresent(rendererFenetre);

		compteur++;

		//On détermine si on change d'image, selon le facteur de ralentissement
		if (compteur % FACTEUR_RALENTISSEMENT_ANIMATION == 0)
		{
		 

			/*****************************/
			// Code test des rebonds
			{
				float balleX, balleY, balleR, balleA, angle_mur;
				int ballePositionX, ballePositionY;

				angle_mur = 0;
				ball.get_velocityC(balleX, balleY);
				ball.get_velocityP(balleR, balleA);

				//Gauche
				if (ball.x < 0)
				{
					angle_mur = -5 * M_PI / 2;

				}
				//Droite
				if ((ball.x + LARGEUR_IMAGE_BALLE) > LARGEUR_FENETRE)
				{
					angle_mur = -5 * M_PI / 2;
				}
				//Haut
				if (ball.y < 0)
				{
					angle_mur = M_PI;
				}
				//Bas
				if ((ball.y + HAUTEUR_IMAGE_BALLE) > HAUTEUR_FENETRE)
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
					angle_mur = 3 * M_PI / 4;
				}

				//BarreD
				if (labarre.contactDroit(ball))
				{
					angle_mur = -3 * M_PI / 4;
				}

				if (angle_mur != 0)
					ball.set_velocityP(balleR, angle_mur - balleA);

				ball.get_velocityC(balleX, balleY);
				ball.set_velocityC(1.0001 * balleX, 1.0001 * balleY);	//	Code pour une légère accélération plus le temps avance
				ball.get_velocityC(balleX, balleY);						//

				ball.get_velocityP(balleR, balleA);

				ballePositionX = ball.get_x();
				ballePositionY = ball.get_y();
				ballePositionX += balleX;
				ballePositionY += balleY;

				ball.x = ballePositionX;
				ball.y = ballePositionY;

				system("cls");
				std::cout << balleX << std::endl << balleY << std::endl;
				std::cout << balleR << std::endl << balleA * 180 / M_PI << std::endl;
				std::cout << ballePositionX << std::endl << ballePositionY;

			}
			/********************************/

			///*****************************/
			//// Code test des rebonds
			//{
			//	float balleX, balleY,balleR,balleA,angle_mur;

			//	angle_mur = 0;
			//	ball.get_velocityC(balleX, balleY);
			//	ball.get_velocityP(balleR, balleA);

			//	//Gauche
			//	if (ball.x < 0)
			//	{
			//		angle_mur = -5 * M_PI / 2;
			//		
			//	}
			//	//Droite
			//	if ((ball.x+LARGEUR_IMAGE_BALLE) > LARGEUR_FENETRE)
			//	{
			//		angle_mur =  -5 * M_PI / 2;
			//	}
			//	//Haut
			//	if (ball.y < 0)
			//	{
			//		angle_mur = M_PI;
			//	}
			//	//Bas
			//	if ((ball.y+HAUTEUR_IMAGE_BALLE) > HAUTEUR_FENETRE)
			//	{
			//		angle_mur = 2 * M_PI;
			//	}

			//	//BarreM
			//	if (labarre.contactMilieu(ball))
			//	{
			//		angle_mur = M_PI;
			//	}

			//	//BarreG
			//	if (labarre.contactGauche(ball))
			//	{
			//		angle_mur = 3 *  M_PI / 4;
			//	}

			//	//BarreD
			//	if (labarre.contactDroit(ball))
			//	{
			//		angle_mur = -3 * M_PI / 4;
			//	}

			//	if (angle_mur !=0)
			//		ball.set_velocityP(balleR, angle_mur - balleA);
			//	/*
			//	ball.get_velocityP(balleR, balleA);					//	Code pour une légère accélération plus le temps avance
			//	if (balleR < 50)									//  mais la limiter à 50
			//		ball.set_velocityP(1.0001 * balleR, balleA);	//
			//		*/

			//	ball.get_velocityC(balleX, balleY);			
			//	ball.get_velocityP(balleR, balleA);

			//	ball.x += balleX;
			//	ball.y += balleY;

			//	//Empêcher la balle de quitter la fenêtre
			//	/*
			//	if (ball.x < 0)
			//	{
			//		ball.x += 1;
			//	}

			//	if (ball.y < 0)
			//	{
			//		ball.y += 1;
			//	}

			//	if (ball.x > LARGEUR_FENETRE)
			//	{
			//		ball.x -= 1;
			//	}

			//	if (ball.y > HAUTEUR_FENETRE)
			//	{
			//		ball.y -= 1;
			//	}*/
			//	

			//	system("cls");

			//	std::cout 
			//		<< "vX: " << balleX << std::endl 
			//		<< "vY: " << balleY << std::endl;
			//	std::cout 
			//		<< "vR: " << balleR << std::endl 
			//		<< "vA: " << balleA * 180 / M_PI << std::endl;

			//	std::cout
			//		<< "x: " << ball.get_x() << std::endl
			//		<< "y: " << ball.get_y() << std::endl;

			//}
			///********************************/


			compteur = 0;
		  
		}

		//SDL_Delay(10);

	  }//end while (!quit)
	}
  }

  //system("pause");

  //Free resources and close SDL
  close();

  return 0;

}
