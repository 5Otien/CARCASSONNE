#include "../include/game.h"
jeu miseajeu(char* filename, int nombrejoueurs) {
    jeu G;

    G.nombrejoueurs = nombrejoueurs;
    G.arene = grille_initialisation();
    G.pioche = recupererfichier(filename);

    for (int i = 0; i < nombrejoueurs; i++) {
        G.joueurs[i] = demarrerjoueur(i+1, NONDEFINI);
    }

    return G;
}


void donnertuiles(jeu* G){
	int i = 0;
	while (G->pioche.nombretuiles > 0){
		empiler(&G->joueurs[i].main, depiler(&G->pioche));
		i++;
		if (i == G->nombrejoueurs) i=0;
	}
};

int tuilesvisites[TAILLE] = {NONDEFINI}; 
int estdedans(int *tab, int value){
	int i = 0;
	while (tab[i] != NONDEFINI && i < TAILLE){
		if (tab[i] == value) return 1;
		i++;
	}
	return 0;
}

void ajoutertuilesvisites(int value){
	int i = 0 ;
	while (tuilesvisites[i] != NONDEFINI && i < TAILLE){
		i++;
	}
	if (tuilesvisites[i] == NONDEFINI)tuilesvisites[i] = value;
}

void affichertuilesvisites(){
	int i = 0;
	printf("Tuiles visités = (");
	while (tuilesvisites[i] != NONDEFINI && i < TAILLE){
		printf("%d ; ",tuilesvisites[i]);
		i++;
	}
	printf(")\n");
}

int pcount(jeu Jeu, int x, int y, int s, int start, int meeples[6], int final_evaluation){
    // Fonction principale pour compter les points
    // Retourne le nombre total de points

    int total_points = 0; // Initialise le nombre total de points à 0

    // Vérifie si la zone est fermée
    
    
    // Si la zone est fermée, calcule les points de la zone fermée
    

    // Calcule les points des tuiles adjacentes

    return total_points; // Retourne le nombre total de points
}



int recuperermeeplejoueurs(jeu G, int meeple){
	for (int i = 0 ; i < G.nombrejoueurs ; i++){
		// if (G.joueurs[i].meeple_color == meeple) return i;
		if (G.joueurs[i].meeple_color == meeple){
			return i;
		}
	}
	return NONDEFINI;
}

void enlever_meeples_de_zone(jeu* G, int meeples[6], int x, int y, int s){
	
	char type = G->arene.tab[x][y].cote[s].type;
	int empty[6] = {0};
	int i;

	if (type == 'a' || type == 'v'){
		meeples[G->arene.tab[x][y].cote[4].meeple]--;
		G->arene.tab[x][y].cote[4].meeple = NONDEFINI;
		return;
	}

	int X = x, Y = y, S = s;
	int tuilesvisites[TAILLE] = {NONDEFINI};
	if (s == 4){
		for (i = 0 ; i < 4 ; i++){
			if (comptype(type, G->arene.tab[x][y].cote[i].type)){
				S = i;
				tuilesadjacentes(&X, &Y, &S);
				break;
			}
		}
	}

	int j = 0;
	int estdanslatuilevisite = 0;
	while (memcmp(meeples, empty, 6*sizeof(int)) != 0){

		//on verifie si la tuile courante a des meeples
		if (comptype(type, G->arene.tab[X][Y].cote[4].type)){
			for (i = 0 ; i < 5 ; i++){
				if (comptype(type, G->arene.tab[X][Y].cote[i].type) && G->arene.tab[X][Y].cote[i].meeple !=NONDEFINI){
					meeples[G->arene.tab[X][Y].cote[i].meeple]--;
					int ind = recuperermeeplejoueurs(*G, G->arene.tab[X][Y].cote[i].meeple);
					G->joueurs[ind].meeple_numero++;
					G->arene.tab[X][Y].cote[i].meeple = NONDEFINI;
				}
			}
		}
		else{
			if (G->arene.tab[X][Y].cote[S].meeple != NONDEFINI){
				meeples[G->arene.tab[X][Y].cote[S].meeple]--;
				int ind = recuperermeeplejoueurs(*G, G->arene.tab[X][Y].cote[S].meeple);
				G->joueurs[ind].meeple_numero++;
				G->arene.tab[X][Y].cote[S].meeple = NONDEFINI;
			}
		}

		j = 0;
		while (tuilesvisites[j] != NONDEFINI && tuilesvisites[j] != 0 && j < TAILLE) j++;
		tuilesvisites[j] = G->arene.tab[X][Y].id;


		// on définit les nouveaux X, Y et S pour le parcours
		if (comptype(type, G->arene.tab[X][Y].cote[4].type)){
			for (i = 0 ; i < 4 ; i++){
				if (comptype(type, G->arene.tab[X][Y].cote[i].type)){
					S = i;
					tuilesadjacentes(&X, &Y, &S);

					// on vérifie que la tuile existe
					if (G->arene.tab[X][Y].id == NONDEFINI){
						if (i==3) 
							return;
						else
							continue;
					}

					// on break que si la tuile n'est pas danstuilesvisites
					j = 0;
					estdanslatuilevisite = 0;
					while (tuilesvisites[j] != NONDEFINI && tuilesvisites[j] != 0 && j < TAILLE){
						if (tuilesvisites[j] == G->arene.tab[X][Y].id)
							estdanslatuilevisite = 1;
						j++;
					}
					if (!estdanslatuilevisite)
						break;
				}


				if (i == 3) return;
			}
		}
		else{
			tuilesadjacentes(&X, &Y, &S);
			// on vérifie que la tuile existe
			if (G->arene.tab[X][Y].id == NONDEFINI)
				return;

			// si danstuilesvisites . on return
			j = 0;
			estdanslatuilevisite = 0;
			while (tuilesvisites[j] != NONDEFINI && tuilesvisites[j] != 0 && j < TAILLE){
				if (tuilesvisites[j] == G->arene.tab[X][Y].id)
					return;
				j++;
			}
		}


	}

	return;

}


int classement(jeu G){
	//returns the index of the gagnant 

	int i;
	int indice_joueurs[G.nombrejoueurs];
	for (i = 0 ; i < G.nombrejoueurs ; i++){
		indice_joueurs[i] = i;
	}

	int sorted = 0, tmp;

	// tri 
	do {
		sorted = 1;
		for (i = 0 ; i < G.nombrejoueurs-1 ; i++){
			if (G.joueurs[indice_joueurs[i+1]].score <= G.joueurs[indice_joueurs[i]].score)
				continue;
			sorted = 0;
			tmp = indice_joueurs[i+1];
			indice_joueurs[i+1] = indice_joueurs[i];
			indice_joueurs[i] = tmp;
		}
	} while (!sorted);

	printf("classement\n\n");
	for (i = 0 ; i < G.nombrejoueurs ; i++){
		usleep(500000);
		printf("#%d: Joueur %s%d%s\n", i+1, BOLD, G.joueurs[indice_joueurs[i]].id, END_FORMAT);
		printf("\t%d points\n\n", G.joueurs[indice_joueurs[i]].score);
	}

	sleep(SLEEPTIME);

	int gagnant = indice_joueurs[0];



	return gagnant;
}

void afficher(){
 printf("\n");        
                                                            
 printf("\n");        
                                                            
 printf("\n");        
printf("                                         &&&&&&&&.    &&&     &&&&&&&&&   ,&&&&&&&&    &&&&     &&&&&&&&    &&&&&&&.  #&&&&&&&   &&&&  &&*  &&&&  &&&  &&&&&&&&&     //\\                 \n");
 printf("                                        &&&    ..    &&&&&    &&&   #&&  .&&&    #    #&&&&     &&    &    &&&   &   .&&   *&&#  &&#&  &&*  && &  &&&  &&           < () >               \n");
 printf("                                        &&           && &&,   &&&   .&&, &&&          &&#&&&    &&&        &&&       &&&    &&&  && &/ &&*  &&.&& &&&  &&            \\//                \n");
 printf("                                        &&          #&& #&&   &&&..*&&&  &&          *&& ,&&     &&&&,      &&&&     &&&     &&  && && &&*  &&.&& &&&  &&&&&&&.  ,   \\//           {|}     \n");
 printf("                                        &&          &&   &&   &&&&&&&&   &&          &&&  &&/     .&&&&       &&&&*  &&&     &&  && *& &&*  &&. &.&&&  &&&&&&&.  // \\,| ,          .--.   \n");            
 printf("                                        &&&         &&&&&&&&  &&&  &&&   &&&        .&&&&&&&&        #&&        *&&  &&&    &&&  &&  &/&&*  &&. &&&&&  &&        |    =|= >       //.--.\\ \n");
 printf("   ^                                    &&&&    ,  &&&&&&&&&  &&&   &&&  .&&&.      &&&&&&&&&,       &&&  .      &&. .&&#  &&#  &&  &&&&*  &&.  &&&&&  &&         \\//`| `         |====|  \n");  
 printf(" //\\                                     &&&&&&& ,&&.    &&  &&&    &&.   &&&&&&&. &&*    &&& *&&&&&&&*  *&&&&&&&#   &&&&&&&   &&  *&&&*  &&. . &&&&  &&&&&&&&& `     |           |`::`|   \n");            
 printf("  | |                                                                                                                                                                  |      .-;`\\..../`;_.-^-._ \n");
 printf("  |.|                                                                                                                                                               //\\\\/  //  |...::..|`   :   `|\n");
 printf("  |:|      __                                                                                                                                                        |:'\\ |   //'' ::'' |   .:.   |\n");
 printf(",_|:|_,  //  |                                                                                                                                                        \\ /\\;-,/\\  ::   |..:::::..|\n");
 printf("  |Oo   // _I_                                                                                                                                                        |\\ <` >  >._::_.  | ':::::' |\n");  
 printf("   +\\  || __|                                                                                                                                                        | \\ \\ `/   ^^    |   ':'   |\n");
 printf("       \\||___|                                                                                                                                                       |       |         \\    :   //\n");
 printf("       \\ //.:.\\                                                                                                                                                     |       |          \\   :  // \n");
 printf("         |.:.//-----\\                                                                                                                                                |       |__//\\___|`-.:.-`  \n");
 printf("         |___|::oOo::|                                                                                                                                                |        \\_ || _//    `     \n");
 printf("        //   |:<_T_>:|                                                                                                                                                |         <_ >< _>         \n");
 printf("        |____\\ ::: //                                                                                                                                                |         |  ||  |         \n");
 printf("         | |  \\ ://                                                                                                                                                  |         |  ||  |         \n");
 printf("         | |   | |                                                                                                                                                    |       _\\.:||:.//_       \n");
 printf("        \\ //  | \\___                                                                                                                                                |      //___//\\____\\      \n");  
 printf("        // |   |_____\\                                                                                                                                                           FAIT PAR AMRANI RAYAN\n");
 printf("                                                                                                                                                                                      MOSTEFI BILAL\n");
 printf("                                                                                                                                                                                                    \n");
 printf("                                                                                                                                                                     supervisé par M. LOUETSI KENELM\n");
 printf("                                                                                                                                                                                                    \n");
    }
//GAME

	void menu() {
    // Début du cadre supérieur
    printf("%s+-------------------------------------------------+%s\n", CYAN, END_FORMAT);
    printf("%s|%s                   %sMENU%s                          %s|%s\n", CYAN, END_FORMAT, BOLD, END_FORMAT, CYAN, END_FORMAT);
    printf("%s+-------------------------------------------------+%s\n", CYAN, END_FORMAT);

    // Options du menu avec différentes couleurs
    printf("%s|%s %sD%s%s Pour tourner à %sDroite%s                         %s|%s\n", CYAN, END_FORMAT, BOLD, END_FORMAT, CYAN, GREEN, END_FORMAT, CYAN, END_FORMAT);
    printf("%s|%s %sG%s%s Pour tourner à %sGauche%s                         %s|%s\n", CYAN, END_FORMAT, BOLD, END_FORMAT, CYAN, GREEN, END_FORMAT, CYAN, END_FORMAT);
    printf("%s|%s %sP%s%s Redessiner si la tuile ne peut pas être placée%s|%s\n", CYAN, END_FORMAT, BOLD, END_FORMAT, CYAN, CYAN, END_FORMAT);
    printf("%s|%s %sY%s%s Pour %sValider%s                                  %s|%s\n", CYAN, END_FORMAT, BOLD, END_FORMAT, CYAN, GREEN, END_FORMAT, CYAN, END_FORMAT);
    printf("%s|%s %sC%s%s Pour voir le %sclassement%s                       %s|%s\n", CYAN, END_FORMAT, BOLD, END_FORMAT, CYAN, MAGENTA, END_FORMAT, CYAN, END_FORMAT);

    // Fin du cadre inférieur
    printf("%s+-------------------------------------------------+%s\n", CYAN, END_FORMAT);
}


//GAME
jeu demarrer_jeu(char * filename) {
    afficher();

    char choix[3];
    
    // Tant que l'utilisateur n'entre pas "GO", on continue à demander
    while (strcmp(choix, "GO") != 0) {
        printf("Voulez-vous lancer le JEU? (GO pour continuer) : ");
        scanf("%s", choix);

        // Vérifier si l'utilisateur veut continuer
        if (strcmp(choix, "GO") != 0) {
            printf("Veuillez entrer GO pour lancer le jeu.\n");
        }
    }
	printf("INFO: SI vous souhaitez quitter le jeu à tout moment cliquez!  %sQ%s.\n\n\n", BOLD, END_FORMAT);
	usleep(500000);
	int tmp=NONDEFINI, l = 0, i;
					// on utilise la variable l dans les boucles while pour éviter qu'elles bouclent à l'infini
	   printf("\n\n");
    printf("                       \033[41m          \033[0m  Blason (b)\n");
    printf("                       \033[42m          \033[0m  Prairie (p)\n");
    printf("                       \033[47m          \033[0m  Route (r)\n");
    printf("                       \033[43m          \033[0m  Village/Ville (v)\n");
    printf("                       \033[103m          \033[0m  Abbaye (a)\n");     // jaune foncé
    printf("                       \033[40m          \033[0m  Non défini (autre)\n");

	printf("Combien de joueurs etes-vous?\n");
	
	while (tmp <= 0 || tmp > 6){
		scanf("%d", &tmp);
		l++;
		
	}
	jeu G = miseajeu(filename, tmp);

	
	
	for (i = 0 ; i < G.nombrejoueurs ; i++){
	
		G.joueurs[i].id =  G.nombrejoueurs - i;
	}

	// les joueurs choisissent leur meeple
	for (i = 0 ; i < G.nombrejoueurs ; i++){
		printf("\n Joueur %s%d%s: \n\n", BOLD, G.joueurs[i].id, END_FORMAT);
		printf("Choisissez la couleur de votre pion/meeples:\n");
		tmp = NONDEFINI;
		
		while (tmp < 0 || tmp > 5){
			printf("%s JAUNE : 0\n %sROUGE : 1\n %sVERT : 2\n %sBLEU : 3\n %sCYAN : 4\n %sMAGENTA : 5 %s\n", YELLOW, RED, GREEN, BLUE, CYAN, MAGENTA, END_FORMAT);
			scanf("%d", &tmp);

			// on vérifie que cette couleur de meeple n'a pas déjà été choisie
			if (tmp >= 0 && tmp <= 5){
				for (int j = 0 ; j < G.nombrejoueurs ; j++){
					if (G.joueurs[j].meeple_color == tmp){
						tmp = NONDEFINI;
						break;
					}
				}
			}



		}
		G.joueurs[i].meeple_color = tmp;
	}

	
	//tuile de départ
	tournertuile(&G.pioche.tab[G.pioche.nombretuiles-1], 270);
	tile T = depiler(&G.pioche);
	placertuilesurgrille(&G.arene, T, 72, 72);
	
	
	melange(&G.pioche);
	donnertuiles(&G);

	usleep(500000);

	printf(CLEAR);
	
	printf("%s%d%s joueurs: \n\n",BOLD, G.nombrejoueurs, END_FORMAT);

	for (i = 0 ; i < G.nombrejoueurs ; i++){
		usleep(500000);
		afficher_joueurs(G.joueurs[i]);
		printf("\n");
	}
	sleep(SLEEPTIME);
	

	return G;
}



void gameplay(jeu G){
    
	if (G.joueurs[0].main.nombretuiles < 1){
		return;
	}

	int montrer_tuiles = 0;
	while (G.arene.nombretuiles < NB_DE_TUILES){
		for (int i = 0 ; i < G.nombrejoueurs ; i++){

			if (G.joueurs[i].main.nombretuiles == 0){
				printf(CLEAR);
				afficher_joueurs(G.joueurs[i]);
				printf("\n");
				afficher_grille(G.arene, montrer_tuiles, !montrer_tuiles, NONDEFINI, NONDEFINI,G.joueurs[i].id);
				printf("\n\nVous avez placé toutes vos tuiles, au tour du joueur suivant.\n");
				sleep(SLEEPTIME);

				continue;
			} 
			
			tile  T = depiler(&G.joueurs[i].main);
			char tmp = ' ';
			int j = 0;

			while((tmp != 'D' || tmp != 'G'|| tmp != 'Y' || tmp != 'P') && j<10){
				printf(CLEAR);
				afficher_joueurs(G.joueurs[i]);
				printf("\n");
				afficher_grille(G.arene, montrer_tuiles, !montrer_tuiles, NONDEFINI, NONDEFINI,G.joueurs[i].id);
				printf("\n\nTuile : \n");
				affichertuile(T, 0, 1);   
				menu();
				scanf(" %c", &tmp);
				printf("\n");

				if (tmp == 'Y'){
					break;
				} 
				else if (tmp == 'D' ){
					tournertuile(&T, 90);
					tmp = ' ';
				}
				else if (tmp == 'G'){
					tournertuile(&T, 270);
					tmp = ' ';
				}
				else if (tmp == 'P'){
					//on vérifie que la tuile ne peut pas être posée
					
					// on établit une fenêtre des tuiles placées pour ne pas avoir à parcourir tout le plateau
					int maxX = -1, maxY = -1;
					int minX = NB_DE_TUILES*2, minY = NB_DE_TUILES*2;
					int i, j;
					for (i = 0 ; i < NB_DE_TUILES*2-1 ; i++){
						for (j = 0 ; j < NB_DE_TUILES*2-1 ; j++){
							if (G.arene.tab[i][j].id != NONDEFINI){
								if (minX > i) minX = i;
								if (minY > j) minY = j;

								if (maxX < i) maxX = i;
								if (maxY < j) maxY = j;
							}
						}
					}
					if (minX > 0) minX--;
					if (minY > 0) minY--;
					if (maxX < NB_DE_TUILES*2-1) maxX++;
					if (maxY < NB_DE_TUILES*2-1) maxY++;

					int placable = 0;
					for (int degrees = 0 ; degrees < 360 ; degrees += 90){

						for (int x = minX ; x <= maxX ; x++){
							for (int y = minY ; y <= maxY ; y++){
								if (tuileposable(G.arene, T, x, y)){
									placable = 1;

									//on sort des boucles
									x = maxX;
									y = maxY;
									tournertuile(&T, -degrees-90);
									degrees = 360;
								}
							}
						}
						tournertuile(&T, 90);
					}
					if (placable){
						printf("\nTuile non posable ici .\n\n");
						sleep(SLEEPTIME);
						tmp = ' ';
					}
					else{
						placeralabasedelapile(&G.joueurs[i].main, T);
						if (G.joueurs[i].main.nombretuiles == 1){
							tmp = 'S';
							break;
						}
						T = depiler(&G.joueurs[i].main);
						tmp = ' ';
					}
				}
				else if (tmp == 'Q'){
					
					exit(1);
				}
				else if (tmp == 'C'){
					printf(CLEAR);
					classement(G);
					getchar();
					getchar();
					tmp = ' ';
				}
				else{
					tmp = ' ';
				}
				j++;
				
			}

			if (tmp == 'S'){		//skipping turn
				printf("\n\nVotre Tuile ne peut pas etre placée .Passez au joueur suivant.\n");
				sleep(SLEEPTIME);
				continue;
			}

			//placement
			int x = NONDEFINI, y = NONDEFINI;
			int t = 0;
			while (t == 0 || x == NONDEFINI || y == NONDEFINI){
				printf(CLEAR);
				afficher_joueurs(G.joueurs[i]);
				printf("\n");
				afficher_grille(G.arene, 0, 1, NONDEFINI, NONDEFINI,G.joueurs[i].id);
				printf("\n\nVotre tuile:\n");
				affichertuile(T, 0, 1);
				printf("\n\nEcrivez l'emplacement souhaité pour la tuile(x,y):\n");
				scanf("%d %d", &x, &y);
				t = placertuilesurgrille(&G.arene, T, x, y);                    
			
				
			}


			//meeple
			printf(CLEAR);
			afficher_joueurs(G.joueurs[i]);
			printf("\n");
			afficher_grille(G.arene, 0, 1, x, y,G.joueurs[i].id);
			sleep(SLEEPTIME/3);

			char temporaire = ' ';
			montrer_tuiles = 0;
			if (G.joueurs[i].meeple_numero <= 0){
				printf("Vous avez utilisé toutes les tuiles.\n\n");
				sleep(SLEEPTIME);
			}
			else{
				printf("Changer l'affichage en appuyant sur M %sM%s.\n\n", BOLD, END_FORMAT);
				while (temporaire != 'Y' && temporaire != 'N' && temporaire != 'Q'){
					printf("Place a meeple? (Y/N) ");
					scanf(" %c", &temporaire);

					if (temporaire == 'M'){
						montrer_tuiles = !montrer_tuiles;

						printf(CLEAR);
						afficher_joueurs(G.joueurs[i]);
						printf("\n");
						afficher_grille(G.arene, montrer_tuiles, !montrer_tuiles, x, y,G.joueurs[i].id);

					}
				}

				if (temporaire == 'Y'){
					int tmps = NONDEFINI;
					t = 0;
					while (t == 0){
						printf(CLEAR);
						afficher_joueurs(G.joueurs[i]);
						printf("\n");
						afficher_grille(G.arene, 1, 0, x, y,G.joueurs[i].id);
						printf("\nEntrez une valeur négative pour annuler.\n");
						printf("\nYour tile is at (%d ; %d).\n\n", x, y);
						printf("Quel coté?\n");
						printf("\t  0\n");
						printf("\t3 4 1\n");
						printf("\t  2\n\n");
						scanf("%d", &tmps);
						if (tmps < 0) break;        //if meeple cannot be placed: enter negative value
						if (!meeplesurlazone(G.arene, x, y, tmps, 1)){
							t = placermeeplesurtuile(&G.arene.tab[x][y], tmps, &G.joueurs[i]);
						}
					}
					printf(CLEAR);
					afficher_joueurs(G.joueurs[i]);
					printf("\n");
					afficher_grille(G.arene, 1, 0, x, y,G.joueurs[i].id);
					sleep(SLEEPTIME / (2.0/3.0));
				}
				else if (temporaire == 'Q'){
					
					
					exit(1);
				}
			}

			//évaluation
			int to[6] = {0};
			int nb_points;
			//abbayeestferme(G, x, y);
			for (j = 0 ; j < 4 ; j++){
				nb_points = pcount(G, x, y, j, 1, to, 0);
				if (nb_points > 0){
					//pointsmax(&G, to, nb_points);
					enlever_meeples_de_zone(&G, to, x, y, j);
					sleep(SLEEPTIME*2);
				}
				memset(to, 0, 6*sizeof(int));
			}


			
		}

	}

	// fin de partie

	printf(CLEAR);
	printf("Toutes les tuiles ont été posées, fin du jeu !\n\n");
	usleep(500000);
	printf("Derniere évaluation..");
	sleep(SLEEPTIME/1.5);
	
	// il faut parcourir la grille une fois de plus pour récupérer les points de chaque zone où il y a un ou des meeples, pour ensuite donner les points aux joueurs
	
	int ta[6] = {0};
	int tabl[6] = {0};			//sert seulement à la comparaison
	int nb_points, conteurdetuile = 0;
	for (int i = 0 ; i < NB_DE_TUILES*2-1 ; i++){
		for (int j = 0 ; j < NB_DE_TUILES*2-1 ; j++){
			if (G.arene.tab[i][j].id == NONDEFINI)
				continue;

			for (int k = 0 ; k < 5 ; k++){
				nb_points = pcount(G, i, j, k, 1, ta, 1);
				if (nb_points > 0 && memcmp(ta, tabl, 6*sizeof(int)) != 0){
					//pointsmax(&G, ta, nb_points);
				}
				memset(ta, 0, 6*sizeof(int));
			}

			conteurdetuile++;
			if (conteurdetuile >= NB_DE_TUILES){
				i = NB_DE_TUILES*2-1;
				j = NB_DE_TUILES*2-1;
			}
				
		}
	}

	sleep(SLEEPTIME/(2.0/3.0));

	printf(CLEAR);
	int gagnant = classement(G);

	sleep(SLEEPTIME/3.0);
	printf("\n\n\nBravo au Joueur %s%d%s Qui a gagné avec %d points!\n\n", BOLD, G.joueurs[gagnant].id, END_FORMAT, G.joueurs[gagnant].score);


	return;   
}




