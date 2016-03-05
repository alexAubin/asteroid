#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"

#define L_track 10000

void UpdateDisplay(SDL_Surface*,SDL_Surface*[3],double[6],int[2*L_track + 1],TTF_Font*);
void InitDisplay(SDL_Surface* ecran, SDL_Surface* tiles[3],double tab[6], int* track, TTF_Font *police, double temp[6]);

// ##########################################################################################################################

void UpdateDisplay(SDL_Surface* ecran, SDL_Surface* tiles[3],double tab[6], int* track, TTF_Font *police) {

    int i;
    SDL_Rect Etoile, Planete, Astero, postext, track_pos;
    SDL_Surface *texte, *track_surf;
    char s[150];
    SDL_Color b = {NOIR, NOIR, NOIR}, n = {BLANC, BLANC, BLANC};

    // ####################
    // # Track management #
    // ####################

    track_surf = SDL_CreateRGBSurface(SDL_HWSURFACE, 1, 1, 32, 0, 0, 0, 0);
    if (tiles[0] != tiles[1]) SDL_FillRect(track_surf, NULL, SDL_MapRGB(ecran->format, BLANC, BLANC,BLANC));
    else SDL_FillRect(track_surf, NULL, SDL_MapRGB(ecran->format, NOIR, NOIR, NOIR));
    i = 1;
    while (i < L_track) {
        track_pos.x = track[2 * i - 1];
        track_pos.y = track[2 * i];
        SDL_BlitSurface(track_surf,NULL,ecran,&track_pos);
        i++;
    }
    SDL_FillRect(track_surf, NULL, SDL_MapRGB(ecran->format, NOIR, NOIR, NOIR));
    track_pos.x = track[2 * track[0] - 1];
    track_pos.y = track[2 * track[0]];
    SDL_BlitSurface(track_surf,NULL,ecran,&track_pos);
    track[2 * track[0] - 1] = (int) (WINDOW_LARG/2) * (tab[2] / LARG + 1);
    track[2 * track[0]] = (int) (WINDOW_LARG/2) * (-tab[3] / LARG + 1);
    track[0]++;
    if (track[0] > L_track) track[0] = 1;

    // ######################
    // # Objects management #
    // ######################

    Etoile.x = (int) (WINDOW_LARG/2) - H_E/2;
    Etoile.y = (int) (WINDOW_LARG/2) - H_E/2;
    Planete.x = (int) (WINDOW_LARG/2) * (tab[0] / LARG + 1) - H_P/2;
    Planete.y = (int) (WINDOW_LARG/2) * (-tab[1] / LARG + 1) - H_P/2;
    Astero.x = (int) (WINDOW_LARG/2) * (tab[2] / LARG + 1) - H_A/2;
    Astero.y = (int) (WINDOW_LARG/2) * (-tab[3] / LARG + 1) - H_A/2;

    SDL_BlitSurface(tiles[2],NULL,ecran,&Astero);
    SDL_BlitSurface(tiles[0],NULL,ecran,&Etoile);
    SDL_BlitSurface(tiles[1],NULL,ecran,&Planete);

    // ###################
    // # Text management #
    // ###################

    sprintf(s," # Asteroide # x = %f y = %f v_x = %f v_y = %f # # Jupiter # x = %f y = %f #     ",tab[2],tab[3],tab[4],tab[5],tab[0],tab[1]);
    texte = TTF_RenderText_Shaded(police,s,n,b);
    postext.x = 0; postext.y = WINDOW_LARG;
    SDL_BlitSurface(texte,NULL,ecran,&postext);

    // ##############
    // # Free stuff #
    // ##############

    SDL_FreeSurface(texte);
    SDL_FreeSurface(track_surf);
}

void InitDisplay(SDL_Surface* ecran, SDL_Surface* tiles[3],double tab[6], int track[2*L_track + 1], TTF_Font *police, double temp[6]) {

    SDL_Rect pos;
    SDL_Surface *rect;

    // ####################
    // # Clean the screen #
    // ####################

    rect = SDL_CreateRGBSurface(SDL_HWSURFACE, 2*WINDOW_LARG, 2*WINDOW_LARG, 32, 0, 0, 0, 0);
    SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, NOIR, NOIR, NOIR));
    pos.x = 0;
    pos.y = 0;
    SDL_BlitSurface(rect,NULL,ecran,&pos);

    // ######################
    // # Init the variables #
    // ######################

    tab[0] = 1.0; tab[1] = 0.0; tab[2] = ASTERO_INIT_X; tab[3] = ASTERO_INIT_Y; tab[4] = ASTERO_INIT_VX; tab[5] = ASTERO_INIT_VY;
    temp[0] = tab[0]; temp[1] = tab[1]; temp[2] = tab[2]; temp[3] = tab[3];  temp[4] = tab[4];  temp[5] = tab[5];
    for (int i = 1 ; i < 2 * L_track + 1 ; i++) track[i] = 0;

    SDL_FreeSurface(rect);
}




