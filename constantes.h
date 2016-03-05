#ifndef DEF_CONSTANTES
#define DEF_CONSTANTES

    /*******************************************************************/
	/******* Constantes du problèmes (a priori, pas à modifier) ********/
	/*******************************************************************/

    #define H_E 12 /* Taille des tiles Etoile/Planete/Asteroide */
    #define H_P 10
    #define H_A 9

    #define NOIR 0 /* Pour inverser les couleurs, inverser le nom des variables */
    #define BLANC 255

    #define PI 3.141592653589
    #define CONSTANTE_GRAVITATION (6.67428 * pow(10,-11))

    #define SOLEIL_MASSE (2 * pow(10,30))
    #define SOLEIL_RAYON (1.4 * pow(10,9)) /* Rayon du soleil */

    #define JUPITER_MASSE 1 /* En fait, il s'agit du ratio Masse_Jupiter / Masse_Soleil */
    #define JUPITER_RAYON (8 * pow(10,11)) /* Rayon de l'orbite de jupiter */
    #define JUPITER_TAILLE (70 * pow(10,6)) /* Rayon de jupiter */

    #define JUPITER_PERIODE (2 * PI * pow(JUPITER_RAYON,1.5) / sqrt(CONSTANTE_GRAVITATION * SOLEIL_MASSE))
    #define FACTEUR -39.478417604 /* = 4 PI² */

	/*******************************************************************/
	/*** Conditions initiales et paramètres relatifs à la simulation ***/
	/*******************************************************************/

    #define LARG 1.4 /* Demi-largeur de la fenêtre en Rayon d'orbite */
    #define WINDOW_LARG 710 /* Largeur de la fenêtre en pixel */
    #define L_TRAINEE 20000 /* Nombre de points de la trainée */

    #define H (pow(10,-7)) /* Pas d'itération */
    #define ITER (2*pow(10,9)) /* Nombre d'itérations */
    #define FREQ 5000 /* Fréquence de prélévement de la position */

    #define ASTERO_INIT_X 4.0135
    #define ASTERO_INIT_Y 5
    #define ASTERO_INIT_VX -2*PI
    #define ASTERO_INIT_VY -2*PI

    //#define ASTERO_INIT_X 4.0135
    //#define ASTERO_INIT_Y 5
    //#define ASTERO_INIT_VX -2*PI
    //#define ASTERO_INIT_VY -2*PI



#endif

/*************************************************
 *
 *  Ci-dessous sont regroupées les conditions initiales utilisées pour le rapport
 *
 * Partie I.1
 *
 *  	Premier cas
 *  #define ASTERO_INIT_X (1 - 0.1/pow(3.0,0.3333333333333333333333333333333333333333333333333333333333333333))
    #define ASTERO_INIT_Y 0
    #define ASTERO_INIT_VX 0
    #define ASTERO_INIT_VY sqrt(CONSTANTE_GRAVITATION * SOLEIL_MASSE / (JUPITER_RAYON * ASTERO_INIT_X)) * JUPITER_PERIODE / JUPITER_RAYON - 0.587

 *
 *  	Deuxieme cas
 *  #define ASTERO_INIT_X (1 - 0.1/pow(3.0,0.3333333333333333333333333333333333333333333333333333333333333333))
    #define ASTERO_INIT_Y 0.00001
    #define ASTERO_INIT_VX 0
    #define ASTERO_INIT_VY sqrt(CONSTANTE_GRAVITATION * SOLEIL_MASSE / (JUPITER_RAYON * ASTERO_INIT_X)) * JUPITER_PERIODE / JUPITER_RAYON - 0.587

 *
 * Partie I.2
 *
 * #define invk 1.33333333333333333333333333333333333
    #define ASTERO_INIT_X (-pow(invk,-0.66666666666666666666666666666666666666666666666666666666666666666666666666666666666666666667))
    #define ASTERO_INIT_Y 0.000001
    #define ASTERO_INIT_VX 0
    #define ASTERO_INIT_VY 2*PI*ASTERO_INIT_X*invk
 *
 * Partie II.1
 *
 *  #define ASTERO_INIT_X 4.0135
    #define ASTERO_INIT_Y 5
    #define ASTERO_INIT_VX -2*PI
    #define ASTERO_INIT_VY -2*PI
 *
 * Partie II.2
 *
 *  #define ASTERO_INIT_X 2.479041
 *  ou 2.475041
    #define ASTERO_INIT_Y 2.140545
    #define ASTERO_INIT_VX -6.814159
    #define ASTERO_INIT_VY -1.946902
 *
 * Partie III. 1
 *
 * #define ASTERO_INIT_X -0.868116
   #define ASTERO_INIT_Y 1.481690
   #define ASTERO_INIT_VX 3.4945
   #define ASTERO_INIT_VY -7.7
 *
 *
 * Partie III.2
 *
 * Premier cas
 * #define ASTERO_INIT_X -2.755-0.0177026719
    #define ASTERO_INIT_Y -2.941
    #define ASTERO_INIT_VX 2.336
    #define ASTERO_INIT_VY 4.354013
 *
 * Deuxième cas
 * #define ASTERO_INIT_X -2.755-0.0177016719
    #define ASTERO_INIT_Y -2.941
    #define ASTERO_INIT_VX 2.336
    #define ASTERO_INIT_VY 4.354013
  *

 * *******/
