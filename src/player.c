#include "../include/player.h"

joueurs demarrerjoueur(int numero, int meeple){
	joueurs P;

	P.id = numero;
	P.meeple_color = meeple;
	P.meeple_numero = 7;
	P.score = 0;

	P.main = pile_initialisation();

	return P;
}




/*
void afficher_joueurs(joueurs P){
	printf("joueurs %s%d%s\nmeeples : ", BOLD, P.id, END_FORMAT);
	
	switch (P.meeple_color)
		{
		case 0:
			printf(YELLOW);
			break;
		
		case 1:
			printf(RED);
			break;
		
		case 2:
			printf(GREEN);
			break;
		
		case 3:
			printf(BLUE);
			break;
		
		case 4:
			printf(CYAN);
			break;
		
		case 5:
			printf(MAGENTA);
			break;
		
		default:
			printf("\033[37m");          //white
			break;
		}

	printf(" %d%s\n", P.meeple_numero, END_FORMAT);

	printf("score : %d\n", P.score);
	printf("%d tuiles en main\n", P.main.nombretuiles);

}
*/
void afficher_joueurs(joueurs P) {
    // Début du cadre supérieur
    printf("%s+--------------------------------------+%s\n", CYAN, END_FORMAT);
    printf("%s|%s               %sJoueur %d%s               %s|%s\n", CYAN, END_FORMAT, BOLD, P.id, END_FORMAT, CYAN, END_FORMAT);
    printf("%s+--------------------------------------+%s\n", CYAN, END_FORMAT);

    // Afficher les meeples avec la couleur appropriée
    printf("%s|%s Meeples: ", CYAN, END_FORMAT);
    switch (P.meeple_color) {
        case 0:
            printf("%s", YELLOW);
            break;
        case 1:
            printf("%s", RED);
            break;
        case 2:
            printf("%s", GREEN);
            break;
        case 3:
            printf("%s", BLUE);
            break;
        case 4:
            printf("%s", CYAN);
            break;
        case 5:
            printf("%s", MAGENTA);
            break;
        default:
            printf("\033[37m"); // Blanc par défaut
            break;
    }
    printf(" %d %s%s                         |\n", P.meeple_numero, END_FORMAT, CYAN, END_FORMAT);

    // Afficher le score
    printf("%s|%s Score: %s%d%s                             %s|\n", CYAN, END_FORMAT, BOLD, P.score, END_FORMAT, CYAN, END_FORMAT);

    // Afficher le nombre de tuiles en main
    printf("%s|%s Tuiles en main: %s%d%s             %s      |\n", CYAN, END_FORMAT, BOLD, P.main.nombretuiles, END_FORMAT, CYAN, END_FORMAT);

    // Fin du cadre inférieur
    printf("%s+--------------------------------------+%s\n", CYAN, END_FORMAT);
}

void affichermainjoueurs(joueurs P){
	printf("Joueur %d\n", P.id);
	printf("%d Tuiles en main\n", P.main.nombretuiles);
	afficherpile(P.main);
}


int placermeeplesurtuile(tile* T, int side, joueurs * P){
	//returns 0 if was unable to place a meeple
	if (T->cote[side].meeple != NONDEFINI || P->meeple_numero <= 0){
		return 0;
	} 
	
	T->cote[side].meeple = P->meeple_color;
	P->meeple_numero--;


	return 1;
}

