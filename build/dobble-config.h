#ifndef DOBBLE_CONFIG_H
#define DOBBLE_CONFIG_H

/**
 * Ce fichier définit les paramètres de configuration du programme Dobble.
 * Il est généré automatiquement à partir du modèle include/dobble-config.h.in
 * vers build/dobble-config.h par CMake lors de la génération des fichiers
 * Makefile.
 *
 * Cela permet d'écrire du code qui s'adapte à la configuration de la machine
 * sur laquelle le projet est compilé.
 */

/* Chemin d'accès au dossier de données du projet (data) */
#define DATA_DIRECTORY "/home/sebastian/dobble/data"

/* Echelle de la fenêtre de rendu, à ajuster en fonction de la taille de l'écran */
#define WIN_SCALE 1.0

/* Largeur de la fenêtre de rendu */
#define WIN_WIDTH ((int)(400 * WIN_SCALE))

/* Hauteur de la fenêtre de rendu */
#define WIN_HEIGHT ((int)(768 * WIN_SCALE))

/* Taille de la police en pixels */
#define FONT_SIZE ((int)(20 * WIN_SCALE))

/* Taille des icônes utilisées dans les matrices d'icônes */
#define ICON_SIZE 90

/* Taille des icônes lors du dessin à l'écran */
#define DRAW_ICON_SIZE 70

/* Taille des icônes dans la fenêtre de rendu */
#define WIN_ICON_SIZE ((int)(DRAW_ICON_SIZE * WIN_SCALE))

/* Taille des cartes */
#define CARD_RADIUS (WIN_WIDTH / 2 - 2 * FONT_SIZE)

#endif /*DOBBLE_CONFIG_H*/
