#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.h"
#include "displayLayer.C"

/* La fonction RungeKutta applique une itération de la méthode de Runge-Kutta d'ordre 4 à la fonction spécifiée */
void RungeKutta(void Fonction(double,double*,double*),double*,double*);

/* La fonction RFD retourne le vecteur vitesse-accélération calculée en */
/* fonction du vecteur position-vitesse et de la date t donnée          */
void RFD(double,double*,double*);

/* La fonction Somme_Vecteur somme deux vecteurs donnés en argument en appliquant un facteur multiplicatif */
void Somme_Vecteur(double*,double*,double,int,double*);

/* La fonction UpdateDisplay permet d'afficher graphiquement la situation passée en argument */
//void UpdateDisplay(SDL_Surface*,SDL_Surface*[3],double[6],int[2*L_TRAINEE + 1],TTF_Font*);

/* La fonction Init sert simplement a initialiser les positions avec les conditions initiales */
//void Init(SDL_Surface*,SDL_Surface*[3],double[6],int[2*L_TRAINEE + 1],TTF_Font*,double[6]);

void pause();

/************************************************************/
/************************************************************/
/************************************************************/

int main(int argc, char** argv) {

    int i, continuer = 1, mouv;
    double t=0;
	double temp[6];
    double Angle;
    double tab[6];
    double save[7];
    int trainee[2*L_TRAINEE+1] = {1};
    SDL_Surface* ecran = NULL;
    TTF_Font *police = NULL;
    SDL_Surface* tiles[3] =
    {
        IMG_Load("assets/etoile.png"),
        IMG_Load("assets/planete.png"),
        IMG_Load("assets/astero.png")
    };
    SDL_Surface* vides[3];
    SDL_Event event;

    if (BLANC == 0)
    {
        vides[0] = IMG_Load("assets/vide_b.png");
        vides[1] = IMG_Load("assets/vide_b.png");
        vides[2] = IMG_Load("assets/vide_b.png");
    }
    else
    {
        vides[0] = IMG_Load("assets/vide_n.png");
        vides[1] = IMG_Load("assets/vide_n.png");
        vides[2] = IMG_Load("assets/vide_n.png");
    }

    /* Initialisation de la SDL et de la fenêtre */
    SDL_Init(SDL_INIT_VIDEO);
	ecran = SDL_SetVideoMode(WINDOW_LARG,WINDOW_LARG+20, 32, SDL_HWSURFACE);
	SDL_WM_SetCaption("Mouvement chaotique d'un asteroide", NULL);

	TTF_Init();
	police = TTF_OpenFont("assets/DejaVuSans.ttf", 11);

    /* Initialisation des positions */
	InitDisplay(ecran,tiles,tab,trainee,police,temp);
	save[0] = 0.0; save[1] = tab[0]; save[2] = tab[1]; save[3] = tab[2]; save[4] = tab[3];save[5] = tab[4]; save[6] = tab[5];
	UpdateDisplay(ecran,tiles,tab,trainee,police);
	SDL_Flip(ecran);

	while (continuer) {
		mouv = 0;
		SDL_WaitEvent(&event);

		/* While event */
		switch(event.type) {
			case SDL_KEYDOWN: {
				if (event.key.keysym.sym == SDLK_ESCAPE) { continuer = 0; break; } /* Touche quitter */
				if (event.key.keysym.sym == SDLK_RETURN) { mouv = 1; break; } /* Touche continuer la simu */
				if (event.key.keysym.sym == SDLK_c) { /* Touche clear */
						t = 0.0;
					    InitDisplay(ecran,tiles,tab,trainee,police,temp);
					    UpdateDisplay(ecran,tiles,tab,trainee,police);
						SDL_Flip(ecran);
						break;
				}
				if (event.key.keysym.sym == SDLK_s) { /* Touche save */
					save[0] = t; save[1] = tab[0]; save[2] = tab[1]; save[3] = tab[2]; save[4] = tab[3];save[5] = tab[4]; save[6] = tab[5];
					break;
				}
				if (event.key.keysym.sym == SDLK_r) { /* Touche reload (la save) */
					    InitDisplay(ecran,tiles,tab,trainee,police,temp);
					    t = save[0]; tab[0] = save[1]; tab[1] = save[2]; tab[2] = save[3]; tab[3] = save[4]; tab[4] = save[5]; tab[5] = save[6];
					    UpdateDisplay(ecran,tiles,tab,trainee,police);
						SDL_Flip(ecran);
						break;
				}
			}
			case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) { /* Positionnement de l'astéroïde */
					UpdateDisplay(ecran,vides,tab,trainee,police);
					tab[2] = LARG * (2 * ((double)event.button.x)/WINDOW_LARG - 1);
					tab[3] = -LARG * (2 * ((double)event.button.y)/WINDOW_LARG - 1);
					temp[0] = tab[0]; temp[1] = tab[1]; temp[2] = tab[2]; temp[3] = tab[3];  temp[4] = tab[4];  temp[5] = tab[5];
					save[0] = t; save[1] = tab[0]; save[2] = tab[1]; save[3] = tab[2]; save[4] = tab[3];save[5] = tab[4]; save[6] = tab[5];
					UpdateDisplay(ecran,tiles,tab,trainee,police);
					SDL_Flip(ecran);
				}
                if (event.button.button == SDL_BUTTON_RIGHT) { /* Position du vecteur vitesse */
					tab[4] = 4 * PI *(LARG * (2 * ((double)event.button.x)/WINDOW_LARG - 1) - tab[2]);
					tab[5] = 4 * PI *(-LARG * (2 * ((double)event.button.y)/WINDOW_LARG - 1) - tab[3]);
					save[0] = t; save[1] = tab[0]; save[2] = tab[1]; save[3] = tab[2]; save[4] = tab[3];save[5] = tab[4]; save[6] = tab[5];
					UpdateDisplay(ecran,tiles,tab,trainee,police);
					SDL_Flip(ecran);
				}
                break;
			case SDL_QUIT: { continuer = 0; break; } /* Si on quitte, on quitte.. */
			default: { break; }
		}
		/* End While event */

		/* While Mouvement */
		if (mouv) {
			i = 0;
			while (i < ITER) {
				RungeKutta(RFD,&t,tab + 2);
				if (i % FREQ == 0) {
					if ((SDL_PollEvent(&event)) && ((event.type == SDL_KEYDOWN) || (event.type == SDL_QUIT))) { i = ITER; }
					UpdateDisplay(ecran,vides,temp,trainee,police);
					Angle = 2 * PI * t;
					tab[0] = cos(Angle); tab[1] = sin(Angle);
					temp[0] = tab[0]; temp[1] = tab[1]; temp[2] = tab[2]; temp[3] = tab[3];  temp[4] = tab[4];  temp[5] = tab[5];
					UpdateDisplay(ecran,tiles,tab,trainee,police);
					SDL_Flip(ecran);
				}
				i++;
			}
		}
		/* End while mouvement */
    }

    /* Libération des surfaces et de la SDL */
	SDL_FreeSurface(ecran);
	SDL_FreeSurface(tiles[0]); SDL_FreeSurface(tiles[1]); SDL_FreeSurface(tiles[2]);
	SDL_FreeSurface(vides[0]); SDL_FreeSurface(vides[1]); SDL_FreeSurface(vides[2]);
	TTF_Quit();
    SDL_Quit();
}

void RungeKutta(void Fonction(double,double*,double*),double* t, double* Vecteur) {

    double k1[4], k2[4], k3[4], k4[4];
    double temp1[4], temp2[4], temp3[4];
    int i;

    Fonction(*t,Vecteur,k1);
    Somme_Vecteur(Vecteur,k1,H/2,4,temp1);
    *t+=H/2;
    Fonction(*t,temp1,k2);
    Somme_Vecteur(Vecteur,k2,H/2,4,temp2);
    Fonction(*t,temp2,k3);
    Somme_Vecteur(Vecteur,k3,H,4,temp3);
    *t+=H/2;
    Fonction(*t,temp3,k4);

    i = 0;
    while (i < 4) {
        Vecteur[i] += (H/6) * (k1[i] + 2*k2[i] + 2*k3[i] + k4[i]);
        i++;
    }
}

void RFD(double t, double* u, double* uprim) {

    double Angle;
    double Jupiter[2];
    double ModuleAS, ModuleAJ, Double_Produit;

    Angle = 2 * PI * t;
    Jupiter[0] = cos(Angle);
    Jupiter[1] = sin(Angle);

    ModuleAS = u[0] * u[0] + u[1] * u[1]; /* On calcule la somme des carrés des coordonnées de l'asteroide */
    ModuleAJ = 1; /* Et de celle de Jupiter */
    Double_Produit = 2 * (u[0] * Jupiter[0] + u[1] * Jupiter[1]); /* Et le double produit */

    ModuleAJ += ModuleAS - Double_Produit;

    if (sqrt(ModuleAS) < SOLEIL_RAYON/JUPITER_RAYON) { printf("CRASH SOLEIL \n"); u[0] = ASTERO_INIT_X; u[1] = ASTERO_INIT_Y; u[2] = ASTERO_INIT_VX; u[3] = ASTERO_INIT_VY; pause(); }
    else if (sqrt(ModuleAJ) < JUPITER_TAILLE/JUPITER_RAYON) { printf("CRASH JUPITER \n"); u[0] = ASTERO_INIT_X; u[1] = ASTERO_INIT_Y; u[2] = ASTERO_INIT_VX; u[3] = ASTERO_INIT_VY; pause(); }
    else {

    ModuleAJ = pow(ModuleAJ,1.5); /* On obtient finalement les modules AJ et AS puissance 3 */
    ModuleAS = pow(ModuleAS,1.5);


    uprim[0] = u[2];
    uprim[1] = u[3];
    uprim[2] = FACTEUR * ( u[0] / ModuleAS + JUPITER_MASSE * (u[0] - Jupiter[0]) / ModuleAJ);
    uprim[3] = FACTEUR * ( u[1] / ModuleAS + JUPITER_MASSE * (u[1] - Jupiter[1]) / ModuleAJ);

	}
}

void pause() {

    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        continuer = 0;
    }
}

void Somme_Vecteur(double* a, double* b, double facteur, int n, double* res) {

    int i = 0;
    while (i < n) {
        res[i] = a[i] + facteur * b[i];
        i++;
    }

}
