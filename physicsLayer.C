#include <stdio.h>
#include <math.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "constantes.c"

/* La fonction RungeKutta applique une itération de la méthode de Runge-Kutta d'ordre 4 à la fonction spécifiée */
void RungeKutta(void Fonction(double,double*,double*),double*,double*);

/* La fonction RFD retourne le vecteur vitesse-accélération calculée en */
/* fonction du vecteur position-vitesse et de la date t donnée          */
void RFD(double,double*,double*);

/* La fonction Somme_Vecteur somme deux vecteurs donnés en argument en appliquant un facteur multiplicatif */
void Somme_Vecteur(double*,double*,double,int,double*);

/************************************************************/

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

    if (sqrt(ModuleAS) < SOLEIL_RAYON/JUPITER_RAYON)
    {
        printf("CRASH SOLEIL \n");
        u[0] = ASTERO_INIT_X;
        u[1] = ASTERO_INIT_Y;
        u[2] = ASTERO_INIT_VX;
        u[3] = ASTERO_INIT_VY;
        pause();
    }
    else if (sqrt(ModuleAJ) < JUPITER_TAILLE/JUPITER_RAYON)
    {
        printf("CRASH JUPITER \n");
        u[0] = ASTERO_INIT_X;
        u[1] = ASTERO_INIT_Y;
        u[2] = ASTERO_INIT_VX;
        u[3] = ASTERO_INIT_VY;
        pause();
    }
    else
    {
        ModuleAJ = pow(ModuleAJ,1.5); /* On obtient finalement les modules AJ et AS puissance 3 */
        ModuleAS = pow(ModuleAS,1.5);

        uprim[0] = u[2];
        uprim[1] = u[3];
        uprim[2] = FACTEUR * ( u[0] / ModuleAS + JUPITER_MASSE * (u[0] - Jupiter[0]) / ModuleAJ);
        uprim[3] = FACTEUR * ( u[1] / ModuleAS + JUPITER_MASSE * (u[1] - Jupiter[1]) / ModuleAJ);
	}
}

void Somme_Vecteur(double* a, double* b, double facteur, int n, double* res) {

    int i = 0;
    while (i < n) {
        res[i] = a[i] + facteur * b[i];
        i++;
    }

}
