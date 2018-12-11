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
int difficulte = 1;
SDL_Rect rectangles[4];
SDL_Point Souris;
SDL_Texture *TextureImage;



void FileLoad(char* argfile)//méthode chargeant le fichier entré en parametre (mettre argv[1])
{
  FILE* file = fopen(DATA_DIRECTORY, "r");
if (argfile == NULL) {
printf("Echec d’ouverture du fichier.\n");
}
int Nb_cartes, Nb_icones, nbRead, lec;
nbRead = fscanf(argfile, "%d %d", &Nb_cartes, &Nb_icones);
if (nbRead != 2) {
printf("Erreur de lecture.\n");
}else {
  printf("nombre de cartes : %i\n",Nb_cartes);
  printf("nombre d'icones : %i\n",Nb_icones);
  int tabIcones[Nb_cartes][Nb_icones];
  for (int i=0;i<Nb_cartes;i++)
  {
    for(int j=0;j<Nb_icones;j++)
    {
      fscanf(argfile,"%d", &lec);
      tabIcones[i][j]=lec;
      printf("%d",tabIcones[i][j]);
    }
    printf("\n");
  }//contient toutes les cartes possibles
}

fclose(argfile);
}

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

//affiche les scores
void printstat()
{
	char title[100];
	// Efface le contenu de la fenêtre
	clearWindow();
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
	drawText(title, WIN_WIDTH / 2, 0, Center, Top);
	sprintf(title, "%d", score);
	drawText(title, WIN_WIDTH / 2, 25, Center, Top);
	sprintf(title, "Bravo!");
	drawText(title, WIN_WIDTH / 2, 50, Center, Top);
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

SDL_AudioSpec audioSortie;
Uint32 audioLen, audioPos;
SDL_AudioSpec audioBufferSpec;
Uint8 *audioBuffer;
Uint32 audioBufferLen;

void audioCallBack(void *udata, Uint8 * stream, int len)
{
	// On ne lit que s'il reste des données à jouer
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
	char ccf[100];//ccf=chemin complet du fichier
	sprintf(ccf,DATA_DIRECTORY "/%s",argv[1]);
	FileLoad(ccf);
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
	SDL_PauseAudio(0);
	menuLoop();
	freeGraphics();
	SDL_FreeWAV(audioBuffer);
	return 0;
}
