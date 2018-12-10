#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "dobble-config.h"
#include "dobble.h"
#include "graphics.h"

/// Etat du compte à rebous (lancé/non lancé)
static bool timerRunning = false;
static int score = 0;
static int timer = 0;
static bool trouve = true;
double rotations[16];
double scales[16];
int icons[16];
int posX;
int posY;
char *Options[4];
int Nboptions;
int positionactuelle = -1;
SDL_Rect rectangles[4];
SDL_Point Souris;

void initMenu(char ** parametres , int Nb)
{
	for (int i = 0; i < Nb; i++) {
		Options[i]=parametres[i];
		rectangles[i].x = WIN_WIDTH / 2 - 40;
		rectangles[i].y = i * 100 + 100;
		rectangles[i].w = 80;
		rectangles[i].h = 40;
	}
	Nboptions=Nb;
	Souris.x = 0;
	Souris.y = 0;
}

void renderMenu()
{
	clearWindow();
	if (positionactuelle != -1) {
		char title[100];
		sprintf(title, "|%s|", Options[positionactuelle]);
		drawText(title, WIN_WIDTH / 2, positionactuelle * 100 + 100,
			 Center, Top);
	}
	for (int j = 0; j < Nboptions; j++) {
		if (j != positionactuelle) {
			drawText(Options[j], WIN_WIDTH / 2, j * 100 + 100,
				 Center, Top);
		}
	}
	showWindow();
}


void onMouseMoveMenu(int x, int y)
{
	Souris.x = x;
	Souris.y = y;
	for (int i = 0; i < Nboptions; i++) {
		if (SDL_PointInRect(&Souris, &rectangles[i])) {
			positionactuelle = i;
			i = Nboptions;
		} else {
			positionactuelle = -1;
		}

	}
	renderMenu();
}

void onMouseMove(int x, int y)
{
	posX = x;
	posY = y;
	printf("dobble: Position de la souris: (%3d %3d)\r", x, y);
	fflush(stdout);
}

void onMouseClick()
{
	printf("\ndobble: Clic de la souris.\n");

	if (1 == 1) {
		int cardCenterX, cardCenterY;
		getCardCenter(UpperCard, &cardCenterX, &cardCenterY);
		if (posX >=
		    CARD_RADIUS * 0.6 * cos(0. / 360. * (2. * M_PI)) +
		    cardCenterX - 45
		    && posX <=
		    CARD_RADIUS * 0.6 * cos(0. / 360. * (2. * M_PI)) +
		    cardCenterX + 45
		    && posY >=
		    CARD_RADIUS * 0.6 * sin(0. / 360. * (2. * M_PI)) +
		    cardCenterY - 45
		    && posY <=
		    CARD_RADIUS * 0.6 * sin(0. / 360. * (2. * M_PI)) +
		    cardCenterY + 45) {
			trouve = true;
			timer += 3;
			score += 1;
		} else {
			timer -= 3;
			if (timer <= 0) {
				stopTimer();
				printf("Fin du temps");
			}
		}
	} else {
		printf
		    ("Vous devez cliquer sur une icone de la carte du dessus");
	}

}

void onTimerTick()
{
	timer -= 1;
	if (timer <= 0) {
		stopTimer();
		printf("Fin du temps");
	}
	printf("\ndobble: Tic du compte à rebours\n");
	renderScene();

}

//Renvoi l'indice de l'image en commun sur la carte superieure 
int indicecommun(int Liste1[], int Liste2[])
{
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			if (Liste1[i] == Liste2[j]) {
				return i;
			}
		}
	}
	return -1;
}

void renderScene()
{
	char title[100];

	// Efface le contenu de la fenêtre
	clearWindow();
	// Crée le titre qui sera affiché. Utile pour afficher le score.
	sprintf(title, "RICM3-Dobble    Score %d", score);
	drawText(title, WIN_WIDTH / 2, 0, Center, Top);
	sprintf(title, "Temps %d", timer);
	drawText(title, WIN_WIDTH / 2, 25, Center, Top);
	double radius = CARD_RADIUS * 0.6;
	double angle;
	double rotation;
	double scale = 1.;
	int icon;
	int cx, cy;
	int i = 0;
	if (trouve) {
		CardPosition currentCard = UpperCard;
		// Dessin du fond de carte de la carte supérieure
		drawCardShape(currentCard, 5, 252, 252, 252, 155, 119, 170);

		// Affichage des icônes de la carte du haut (régulièrement en cercle)
		for (angle = 0.; angle < 360.; angle += 360. / 7.) {
			//scale = (double)(rand() % 5 + 1) / 5;
			rotation = rand() % 360;
			icon = rand() % 80;
			rotations[i] = rotation;
			scales[i] = scale;
			icons[i] = icon;
			i++;
			drawIcon(currentCard, icon, radius, angle, rotation,
				 scale, &cx, &cy);

			// (cx, cy) est le centre de l'icône placé à l'écran (en pixels)
		}
		//scale = (double)(rand() % 5 + 1) / 5;
		icon = rand() % 80;
		rotation = rand() % 360;
		rotations[i] = rotation;
		scales[i] = scale;
		icons[i] = icon;
		i++;
		drawIcon(currentCard, icon, 0., angle, rotation, scale, &cx,
			 &cy);

		// Dessin de la carte inférieure
		currentCard = LowerCard;

		// Dessin du fond de carte
		drawCardShape(currentCard, 5, 252, 252, 252, 155, 119, 170);

		// Affichage des icônes de la carte du bas (régulièrement en cercle)
		for (angle = 0.; angle < 360.; angle += 360. / 7.) {
			//scale = (double)(rand() % 5 + 1) / 5;
			rotation = rand() % 360;
			icon = rand() % 80;
			rotation = sin(angle) * angle + 70.;
			rotations[i] = rotation;
			scales[i] = scale;
			icons[i] = icon;
			i++;
			drawIcon(currentCard, icon, radius, angle, rotation,
				 scale, NULL, NULL);
		}
		//scale = (double)(rand() % 5 + 1) / 5;
		rotation = rand() % 360;
		icon = rand() % 80;
		rotations[i] = rotation;
		scales[i] = scale;
		icons[i] = icon;
		i++;
		drawIcon(currentCard, icon, 0., angle, rotation, scale, NULL,
			 NULL);
		trouve = false;
	} else {
		int j = 0;
		drawCardShape(UpperCard, 5, 252, 252, 252, 155, 119, 170);
		drawCardShape(LowerCard, 5, 252, 252, 252, 155, 119, 170);
		for (angle = 0.; angle < 360.; angle += 360. / 7.) {
			drawIcon(UpperCard, icons[j], radius, angle,
				 rotations[j], scales[j], &cx, &cy);
			drawIcon(LowerCard, icons[j + 8], radius, angle,
				 rotations[j + 8], scales[j + 8], &cx, &cy);
			j++;
		}
		drawIcon(UpperCard, icons[7], 0., angle, rotations[7],
			 scales[7], NULL, NULL);
		drawIcon(LowerCard, icons[15], 0., angle, rotations[15],
			 scales[15], NULL, NULL);
	}
	// Met au premier plan le résultat des opérations de dessin
	showWindow();
}

void printstat()
{
	char title[100];
	// Efface le contenu de la fenêtre
	clearWindow();
	sprintf(title, "RICM3-Dobble    Score %d", score);
	drawText(title, WIN_WIDTH / 2, 0, Center, Top);
	sprintf(title, "Temps %d", timer);
	drawText(title, WIN_WIDTH / 2, 25, Center, Top);
	showWindow();
}

void sauvegarder()
{
}

void printresultat()
{
	char title[100];
	// Efface le contenu de la fenêtre
	clearWindow();
	sprintf(title, "Votre score est : ");
	drawText(title, WIN_WIDTH / 2, 0, Center, Top);
	sprintf(title, "%d", score);
	drawText(title, WIN_WIDTH / 2, 25, Center, Top);
	sprintf(title, "Bravo!");
	drawText(title, WIN_WIDTH / 2, 50, Center, Top);
	showWindow();
}

void menuLoop()
{
	int quit = 0;
	SDL_Event event;
	char *parametres[4]={ "Jouer", "Options", "Statistiques", "Quitter" };
	initMenu(parametres,4);
	while (!quit) {
		SDL_WaitEvent(&event);

		switch (event.type) {
		case SDL_MOUSEMOTION:
			onMouseMoveMenu(event.motion.x, event.motion.y);
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (positionactuelle) {
			case 0:
				printf
				    ("\ndobble: Démarrage du compte à rebours.\n");
				timer = 60;
				startTimer();
				timerRunning = true;
				mainLoop();
				printresultat();
				sauvegarder();
				break;
			case 1:
				parametres[0]="Facile";
				parametres[1]="Normal";
				parametres[2]="Difficile";
				initMenu(parametres,3);
				break;
			case 2:
				printstat();
				break;
			case 3:
				quit = 1;
				break;
			}

			break;
		case SDL_WINDOWEVENT:
			renderMenu();
			break;
		case SDL_QUIT:
			printf("Merci d'avoir joué!\n");
			quit = 1;
			break;
		}

	}
}




int main(int argc, char **argv)
{
	srand(time(NULL));
	if (!initializeGraphics()) {
		printf
		    ("dobble: Echec de l'initialisation de la librairie graphique.\n");
		return 1;
	}

	if (loadIconMatrix(DATA_DIRECTORY "/Matrice8x10_Icones90x90.png") != 1) {
		printf("dobble: Echec du chargement des icônes.\n");
		return -1;
	}
	SDL_init(SDL_INIT_AUDIO);
	menuLoop();
	freeGraphics();

	return 0;
}
