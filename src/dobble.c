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

//Score et temps et difficulté choisie (Facile de base)
static int score = 0;
static int timer = 0;
int difficulte = 1;

//Informations sur les cartes
int Nbicons=7;
static bool trouve = true;
double rotations[16];
double scales[16];
int radiuss[16];
int icons[16];
int indiceimage=0;

//Informations pour le menu
int posX;
int posY;
char *Options[4];
int Nboptions;
int positionactuelle = -1;
SDL_Rect rectangles[4];
SDL_Point Souris;
SDL_Texture *TextureImage;

//Informations pour la musique
SDL_AudioSpec audioSortie;
Uint32 audioLen, audioPos;
SDL_AudioSpec audioBufferSpec;
Uint8 *audioBuffer;
Uint32 audioBufferLen;


//initialise le menu avec les options choisies
void initMenu(char **parametres, int Nb)
{
	for (int i = 0; i < Nb; i++) {
		Options[i] = parametres[i];
		rectangles[i].x = WIN_WIDTH / 2 - 40;
		rectangles[i].y = i * 50 + 300;
		rectangles[i].w = 80;
		rectangles[i].h = 40;
	}
	Nboptions = Nb;
	Souris.x = 0;
	Souris.y = 0;
}

void renderMenu()
{
	clearWindow();
	RenderImage(TextureImage);
	if (positionactuelle != -1) {
		char title[100];
		sprintf(title, "|%s|", Options[positionactuelle]);
		drawText(title, WIN_WIDTH / 2, positionactuelle * 50 + 300,
			 Center, Top);
	}
	for (int j = 0; j < Nboptions; j++) {
		if (j != positionactuelle) {
			drawText(Options[j], WIN_WIDTH / 2, j * 50 + 300,
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
		    CARD_RADIUS * 0.6 * cos(indiceimage / 360. * (2. * M_PI)) +
		    cardCenterX - 45
		    && posX <=
		    CARD_RADIUS * 0.6 * cos(indiceimage / 360. * (2. * M_PI)) +
		    cardCenterX + 45
		    && posY >=
		    CARD_RADIUS * 0.6 * sin(indiceimage / 360. * (2. * M_PI)) +
		    cardCenterY - 45
		    && posY <=
		    CARD_RADIUS * 0.6 * sin(indiceimage / 360. * (2. * M_PI)) +
		    cardCenterY + 45) {
			trouve = true;
			timer += 3;
			score += 1;
			renderScene();
		} else {
			timer -= 3;
			if (timer <= 0) {
				stopTimer();
				printf("Fin du temps");
			}
			else{renderScene();}
		}
	} else {
		printf
		    ("Vous devez cliquer sur une icone de la carte du dessus");
	}

}

//On decremente le temps toute les secondes et on met a jour l'affichage, si le temps est <=0 on arrete le timer et on renvoi 1 pour indiquer qu'il faut arreter la boucle
int onTimerTick()
{
	timer -= 1;
	if (timer <= 0) {
		stopTimer();
		printf("Fin du temps");
		return 1;
	}
	printf("\ndobble: Tic du compte à rebours\n");
	renderScene();
	return 0;
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
	sprintf(title, "Temps restant %d", timer);
	drawText(title, WIN_WIDTH / 2, 25, Center, Top);
	//Crée les informations necessaires pour la creation des cartes
	double radius ;
	double angle;
	double rotation;
	double scale;
	int icon;
	int cx, cy;
	int i = 0;
	//Si on commence la partie ou que le joueur a trouvé le symbole en commun on genere les cartes
	if (trouve) {
		CardPosition currentCard = UpperCard;
		// Dessin du fond de carte de la carte supérieure
		drawCardShape(currentCard, 5, 252, 252, 252, 155, 119, 170);

		// Affichage des icônes de la carte du haut (régulièrement en cercle)
		for (angle = 0.; angle < 360.; angle += 360. / Nbicons) {
			radius=CARD_RADIUS * ((30+rand()%40)/100);
			scale = radius/(CARD_RADIUS*0.6);
			printf("%f\n",radius);
			rotation = rand() % 360;
			icon = rand() % 80;
			radiuss[i]=radius;
			rotations[i] = rotation;
			scales[i] = scale;
			icons[i] = icon;
			i++;
			drawIcon(currentCard, icon, radius, angle, rotation,
				 scale, &cx, &cy);

			// (cx, cy) est le centre de l'icône placé à l'écran (en pixels)
		}
		radius=CARD_RADIUS * ((100-rand()%50)/100);
		scale = radius/(CARD_RADIUS*0.6);
		icon = rand() % 80;
		rotation = rand() % 360;
		radiuss[i]=radius;
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
		for (angle = 0.; angle < 360.; angle += 360. / Nbicons) {
			radius=CARD_RADIUS * ((100-rand()%50)/100);
			scale = radius/(CARD_RADIUS*0.6);
			rotation = rand() % 360;
			icon = rand() % 80;
			rotation = sin(angle) * angle + 70.;
			radiuss[i]=radius;
			rotations[i] = rotation;
			scales[i] = scale;
			icons[i] = icon;
			i++;
			drawIcon(currentCard, icon, radius, angle, rotation,
				 scale, NULL, NULL);
		}
		radius=CARD_RADIUS * ((100-rand()%50)/100);
		scale = radius/(CARD_RADIUS*0.6);
		rotation = rand() % 360;
		icon = rand() % 80;
		radiuss[i]=radius;
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
		for (angle = 0.; angle < 360.; angle += 360. / Nbicons) {
			drawIcon(UpperCard, icons[j], radiuss[j], angle,
				 rotations[j], scales[j], &cx, &cy);
			drawIcon(LowerCard, icons[j + 8], radiuss[j+8], angle,
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

//affiche les scores
void printstat()
{
	char title[100];
	// Efface le contenu de la fenêtre
	clearWindow();
	RenderImage(TextureImage);
	sprintf(title, "Cliquez pour retourner au menu");
	drawText(title, WIN_WIDTH / 2, WIN_HEIGHT/2 -60, Center, Top);
	sprintf(title, "Facile");
	drawText(title, WIN_WIDTH / 2 - 80, WIN_HEIGHT / 2, Center, Top);
	sprintf(title, "Normal");
	drawText(title, WIN_WIDTH / 2, WIN_HEIGHT / 2, Center, Top);
	sprintf(title, "Difficile");
	drawText(title, WIN_WIDTH / 2 + 90, WIN_HEIGHT / 2, Center, Top);
	sprintf(title, "Meilleur");
	drawText(title, WIN_WIDTH / 2 - 140, WIN_HEIGHT / 2 + 80, Center, Top);
	sprintf(title, "Score");
	drawText(title, WIN_WIDTH / 2 - 140, WIN_HEIGHT / 2 + 100, Center, Top);
	sprintf(title, "Score");
	drawText(title, WIN_WIDTH / 2 - 140, WIN_HEIGHT / 2 + 130, Center, Top);
	sprintf(title, "Moyen");
	drawText(title, WIN_WIDTH / 2 - 140, WIN_HEIGHT / 2 + 150, Center, Top);
	sprintf(title, "%d", score);
	drawText(title, WIN_WIDTH / 2 - 80, WIN_HEIGHT / 2 + 80, Center, Top);
	sprintf(title, "%d", score);
	drawText(title, WIN_WIDTH / 2 - 80, WIN_HEIGHT / 2 + 130, Center, Top);
	sprintf(title, "%d", score);
	drawText(title, WIN_WIDTH / 2, WIN_HEIGHT / 2 + 80, Center, Top);
	sprintf(title, "%d", score);
	drawText(title, WIN_WIDTH / 2, WIN_HEIGHT / 2 + 130, Center, Top);
	sprintf(title, "%d", score);
	drawText(title, WIN_WIDTH / 2 + 90, WIN_HEIGHT / 2 + 80, Center, Top);
	sprintf(title, "%d", timer);
	drawText(title, WIN_WIDTH / 2 + 90, WIN_HEIGHT / 2 + 130, Center, Top);
	showWindow();
}

//sauvegarde le score
void sauvegarder()
{
}

//Affiche le score en fin de partie
void printresultat()
{
	char title[100];
	// Efface le contenu de la fenêtre
	clearWindow();
	sprintf(title, "Votre score est : ");
	drawText(title, WIN_WIDTH / 2, WIN_HEIGHT/2, Center, Top);
	sprintf(title, "%d", score);
	drawText(title, WIN_WIDTH / 2, WIN_HEIGHT/2+25, Center, Top);
	sprintf(title, "Bravo!");
	drawText(title, WIN_WIDTH / 2, WIN_HEIGHT/2+50, Center, Top);
	sprintf(title, "Cliquez pour retourner au menu");
	drawText(title, WIN_WIDTH / 2,WIN_HEIGHT/2+ 70, Center, Top);
	showWindow();
}

//Boucle principale
void menuLoop()
{
	int quit = 0;
	int quit2 = 0;
	SDL_Event event;
	char *parametres[4] = { "Jouer", "Options", "Statistiques", "Quitter" };
	char *parametres2[3] = { "Facile", "Normal", "Difficile" };
	initMenu(parametres, 4);
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
				while (!quit2) {
					SDL_WaitEvent(&event);
					if (event.type == SDL_MOUSEBUTTONDOWN) {
						quit2 = 1;
					}
				}
				quit2 = 0;
				renderMenu();
				break;
			case 1:
				initMenu(parametres2, 3);
				while (!quit2) {
					SDL_WaitEvent(&event);
					switch (event.type) {
					case SDL_MOUSEMOTION:
						onMouseMoveMenu(event.motion.x,
								event.motion.y);
						break;
					case SDL_MOUSEBUTTONDOWN:
						if (positionactuelle != -1) {
							difficulte =
							    positionactuelle;
						}
						quit2 = 1;
						break;
					case SDL_WINDOWEVENT:
						renderMenu();
						break;
					case SDL_QUIT:
						printf
						    ("Merci d'avoir joué!\n");
						quit2 = 1;
						quit = 1;
						break;
					}
				}
				quit2 = 0;
				initMenu(parametres, 4);
				renderMenu();
				break;
			case 2:
				printstat();
				while (!quit2) {
					SDL_WaitEvent(&event);
					if (event.type == SDL_MOUSEBUTTONDOWN) {
						quit2 = 1;
					}
				}
				quit2 = 0;
				renderMenu();
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
			quit2 = 1;
			quit = 1;
			break;
		}

	}
}


void audioCallBack(void *udata, Uint8 * stream, int len)
{
	// On ne lit que s'il y a des données à jouer
	if (audioBufferLen == 0)
		return;

	// Remise à zéro du tampon de sortie
	memset(stream, 0, len);
	// Lecture du buffer audio
	if (audioPos < audioBufferLen) {
		if (audioPos + len > audioBufferLen)
			len = audioLen = audioBufferLen;
		SDL_MixAudio(stream, audioBuffer + audioPos,
			     len, SDL_MIX_MAXVOLUME);
		audioPos += len;
	}
	// Décrémentation de ce qu'il reste à lire
	audioLen -= len;
}

int audio_Init(void)
{
	// Définition des propriétés audio
	audioSortie.freq = 48000;
	audioSortie.format = AUDIO_S16;
	audioSortie.channels = 2;
	audioSortie.samples = 1024;
	audioSortie.callback = audioCallBack;
	audioSortie.userdata = NULL;

	// Initialisation de la couche audio
	if (SDL_OpenAudio(&audioSortie, NULL) < 0) {
		fprintf(stderr, "Erreur d'ouverture audio: %s\n",
			SDL_GetError());
		return (-1);
	}

	return 0;
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
	SDL_Surface *image = IMG_Load("../logo.png");
	if (!image) {
		printf("Erreur de chargement de l'image : %s", SDL_GetError());
		return -1;
	}
	TextureImage = CreateTexture(image);
	SDL_Init(SDL_INIT_AUDIO);
	if (audio_Init() == -1) {
		return -1;
	}
	if (!SDL_LoadWAV("../dobble.wav", &audioBufferSpec,
			 &audioBuffer, &audioBufferLen)) {
		printf("Erreur lors du chargement du fichier WAV.\n");
		return 1;
	}
	char title[100];
	sprintf(title, DATA_DIRECTORY "/%s", argv[1]);
	FILE *f = fopen(title, "r");	// ouvre le fichier “fichier.txt” en lecture
	if (f == NULL) {
// erreur d’ouverture
	}
	SDL_PauseAudio(0);
	menuLoop();
	freeGraphics();
	SDL_FreeWAV(audioBuffer);
	return 0;
}
