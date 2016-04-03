/* En-téte du programme
*****************************************
Fichier :			main.cpp
Auteur:				Guillaume Bergs & Shawn Corriveau
Date de création :  2016/01/01
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
void initialiserCharset(SDL_Rect tableauRectangles[], int nombreImages, int largeurChaqueImage, int hauteurChaqueImage);



//********************************* Variables globales (partie 1)

//La fenétre dans laquelle le programme sera exécuté
SDL_Window* fenetreProgramme = NULL;

//Le 'renderer' associé é la fenétre du programme. Le 'renderer' est l'endroit dans lequelle on placera des textures
SDL_Renderer* rendererFenetre = NULL;




//***************************************** Classe qui nous permet de manipuler les textures (Ne pas éditer)



//********************************* Variables globales (partie 2)

//Taille de l'écran en pixels
const int LARGEUR_FENETRE = 600;
const int HAUTEUR_FENETRE = 700;

const int FACTEUR_RALENTISSEMENT_ANIMATION = 25;  //Pour rendre l'animation plus rapide, indiquer un chiffre plus petit

//Valeurs reliées au charset 'hommeCharset.png'
const int NOMBRE_IMAGES_HOMME_CHARSET = 7;
const int LARGEUR_IMAGE_HOMME_CHARSET = 79;
const int HAUTEUR_IMAGE_HOMME_CHARSET = 113;


//Valeurs reliées é la balle
const int HAUTEUR_IMAGE_BALLE = 50;
const int LARGEUR_IMAGE_BALLE = 50;

////Valeurs reliées aux blocs
//const int NOMBRE_IMAGES_BLOC_CHARSET = 6;
//const int LARGEUR_IMAGE_BLOC_CHARSET = 40;
//const int HAUTEUR_IMAGE_BLOC_CHARSET = 20;


//Valeurs reliées é la barre
const int HAUTEUR_IMAGE_BARRE_G = 25;
const int LARGEUR_IMAGE_BARRE_G = 25;

const int HAUTEUR_IMAGE_BARRE_M = 25;
const int LARGEUR_IMAGE_BARRE_M = 25;

const int HAUTEUR_IMAGE_BARRE_D = 25;
const int LARGEUR_IMAGE_BARRE_D = 25;


//Les variables de type LTexture sont des objets qui découlent de la la classe LTexture créée dans ce fichier
LTexture hommeTexture;
LTexture balleTexture;
LTexture barreGTexture;
LTexture barreMTexture;
LTexture barreDTexture;
LTexture blocTexture;

//Ce tableau de rectangles sera utilisé lors du chargement d'une image dans la structure 'hommeTexture'
SDL_Rect hommeRect[NOMBRE_IMAGES_HOMME_CHARSET];
SDL_Rect blocRect[NOMBRE_IMAGES_BLOC_CHARSET];
SDL_Rect balleRect;
SDL_Rect barreGRect;
SDL_Rect barreMRect;
SDL_Rect barreDRect;



//********************************* Fonctions du programme

//Cette fonction initialise SDL et créé la fenétre du programme
bool init()
{
	//Cette variable indique si l'initialisation a été effectuée avec succés
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

		//Création de la fenétre du programme
		fenetreProgramme = SDL_CreateWindow("Titre fenetre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, LARGEUR_FENETRE, HAUTEUR_FENETRE, SDL_WINDOW_SHOWN);

		if (fenetreProgramme == NULL)
		{
			printf("échec de création de la fenétre ! -  SDL_Error %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Creation du 'renderer' en l'associant é la fenétre du programme
			rendererFenetre = SDL_CreateRenderer(fenetreProgramme, -1, SDL_RENDERER_ACCELERATED);
			if (rendererFenetre == NULL)
			{
				printf("échec de création du renderer ! - SDL Error: %s\n", SDL_GetError());
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
					printf("échec d'initialisation de SDL_image ! -  SDL_image Error: %s\n", IMG_GetError());
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
	//Cette variable indique si le chargément de l'élément a été effectué avec succés
	bool success = true;

	//Load homme sprite sheet texture
	if (!hommeTexture.loadFromFile("images/hommeCharset.png", rendererFenetre))
	{
		printf("échec de chargement de l'image ! \n");
		success = false;
	}
	else
	{
		//On initialise chaque rectangle du tableau 'hommeRect'
		initialiserCharset(hommeRect, NOMBRE_IMAGES_HOMME_CHARSET, LARGEUR_IMAGE_HOMME_CHARSET, HAUTEUR_IMAGE_HOMME_CHARSET);
	}

	//Load bloc sprite sheet texture
	if (!blocTexture.loadFromFile("images/blocCharset.png", rendererFenetre))
	{
		printf("échec de chargement de l'image ! \n");
		success = false;
	}
	else
	{
		//On initialise chaque rectangle du tableau 'blocRect'
		initialiserCharset(blocRect, NOMBRE_IMAGES_BLOC_CHARSET, LARGEUR_IMAGE_BLOC_CHARSET, HAUTEUR_IMAGE_BLOC_CHARSET);
	}

	//Load balle sprite texture
	if (!balleTexture.loadFromFile("images/ball.png", rendererFenetre))
	{
		printf("échec de chargement de l'image ! \n");
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
	if (!barreGTexture.loadFromFile("images/barreGauche.png", rendererFenetre))
	{
		printf("échec de chargement de l'image ! \n");
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
	if (!barreMTexture.loadFromFile("images/barreMilieu.png", rendererFenetre))
	{
		printf("échec de chargement de l'image ! \n");
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
	if (!barreDTexture.loadFromFile("images/barreDroite.png", rendererFenetre))
	{
		printf("échec de chargement de l'image ! \n");
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



//Cette fonction effectue une fermeture appropriée du programme, de l'environnement SDL et libére la mémoire des différents éléments SDL créés
void close()
{

	//On détruit les LTextures créées dans le programme
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


//Cette fonction est responsable de charger dans une texture l'image indiqueé en paramétre
SDL_Texture* loadTexture(std::string path)
{
	//La texture finale
	SDL_Texture* newTexture = NULL;

	//Chargement de l'image dans la texture
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("échec de chargement de l'image dans la texture ! -  SDL_image Error: %s\n", path.c_str(), IMG_GetError());
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
	int indexImageCharset = 0;  //Cette variable nous permet de sélectionner une image du charset de l'homme
	int compteur = 0;	  //Ce compteur est utilisé pour déterminer é quel moment changer d'image dans 'homeCharset'


	balle ball; //La balle
	ball.set_velocityC(1, 2); //Sa vitesse de départ

	barre labarre;
	labarre.multiply_size(0.5); //Pour une taille de 1

	bloc lebloc;

	SDL_Event e;        //Cette variable nous permet de détecter l'événement courant que le programme doit gérer (click, touche du clavier, etc.)

	SDL_Rect* currentHommeRect = &hommeRect[indexImageCharset];  //Ce rectangle correspond é celui qu'on prendra pour afficher l'une des images du charset 'homeCharset'

	//On définit la position initial de l'image
	//int positionHommeX = (LARGEUR_FENETRE - LARGEUR_IMAGE_HOMME_CHARSET) / 2;
	//int positionHommeY = (HAUTEUR_FENETRE - HAUTEUR_IMAGE_HOMME_CHARSET) / 2;

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

			//Netoyyer l'écran (Clear Screen)
			SDL_RenderClear(rendererFenetre);

			//Il est possible de définir une couleur de background du 'renderer'
			SDL_SetRenderDrawColor(rendererFenetre, 0xFF, 0xCC, 0xCC, 0xCC);

			//On dessine cette texture
			//hommeTexture.render(0, 0, currentHommeRect);
			barreGTexture.render(0, 0, &barreGRect);
			barreMTexture.render(0, 0, &barreMRect);
			barreDTexture.render(0, 0, &barreDRect);


			//Mise é jour de 'rendererFenetre' (on redesine les images (contenues dans leurs textures) dans le renderer)
			SDL_RenderPresent(rendererFenetre);


			//Le programme reste ouvert tant que quit != true 
			while (!quit)
			{
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0)
				{
					//Si l'utilisateur appuiie sur le bouton 'fermer' de la fenétre
					if (e.type == SDL_QUIT)
					{
						quit = true;
					}

					//Si l'utilisateur fait un click de souris
					else if (e.type == SDL_MOUSEBUTTONDOWN)
					{
						quit = true;
					}
					//Si l'utilisateur dépplace la souris
					else if (e.type == SDL_MOUSEMOTION)
					{
						//On définit comme nouvelle position du fantéme celle de la souris
						//positionHommeX = e.motion.x;
						//positionHommeY = e.motion.y;

						labarre.Gx = e.motion.x - 25;
						labarre.Dx = (labarre.Gx + LARGEUR_IMAGE_BARRE_G) + LARGEUR_IMAGE_BARRE_M;

					}

					//Si une touche du clavier a été appuyée
					else if (e.type == SDL_KEYDOWN)
					{

						//Avec ce switch on indique qoui faire lorsque l'utilisateur appuie sur une touche
						switch (e.key.keysym.sym)
						{
						case SDLK_w:  //La touche 'w' a été appuyée
							// positionHommeX = 0;
							// positionHommeY = 0;
							break;

						case SDLK_b:  ////La touche 'b' a été appuyée
							//  positionHommeX = 250;
							//  positionHommeY = 250;
							break;

						case SDLK_UP:
							//  positionHommeY -= 10;
							break;

						case SDLK_DOWN:
							//  positionHommeY += 10;
							break;

						case SDLK_LEFT:
							//  positionHommeX -= 10;

							labarre.Gx -= 10;
							labarre.Dx = (labarre.Gx + LARGEUR_IMAGE_BARRE_G) + LARGEUR_IMAGE_BARRE_M;
							break;

						case SDLK_RIGHT:
							//  positionHommeX += 10;

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

				//On détermine si on change d'image, selon le facteur de ralentissement
				if (compteur % FACTEUR_RALENTISSEMENT_ANIMATION == 0)
				{


					/*****************************/
					// Code test des rebonds
					{
						float balleX, balleY, balleR, balleA;

						ball.get_velocityC(balleX, balleY);
						ball.get_velocityP(balleR, balleA);

						//Gauche
						if (ball.x < 0)
						{
							ball.set_velocityC(-balleX, balleY);

						}
						//Droite
						if ((ball.x + LARGEUR_IMAGE_BALLE) > LARGEUR_FENETRE)
						{
							ball.set_velocityC(-balleX, balleY);
						}
						//Haut
						if (ball.y < 0)
						{
							ball.set_velocityC(balleX, -balleY);
						}
						//Bas
						if ((ball.y + HAUTEUR_IMAGE_BALLE) > HAUTEUR_FENETRE)
						{
							ball.set_velocityC(balleX, -balleY);
						}

						//BarreM
						if (labarre.contactMilieu(ball))
						{
							ball.set_velocityC(balleX, -balleY);
						}

						//BarreG
						if (labarre.contactGauche(ball))
						{
							ball.set_velocityP(balleR, (balleA + (M_PI / 3)));
						}

						//BarreD
						if (labarre.contactDroit(ball))
						{
							ball.set_velocityP(balleR, (balleA - (M_PI / 3)));
						}

						ball.get_velocityC(balleX, balleY);						//
						ball.set_velocityC(1.0001 * balleX, 1.0001 * balleY);	//	Code pour une légére accélération plus le temps avance
						ball.get_velocityC(balleX, balleY);						//

						ball.get_velocityP(balleR, balleA);

						ball.x += balleX;
						ball.y += balleY;

						system("cls");
						std::cout << balleX << std::endl << balleY;
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