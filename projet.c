
#include "Outil.h"
#define N 2
#define M 6

/**
*\file
*\brief Programme permettant de jouer une partie d'Awélé
*\author Jolliet Corentin
*\date Jeudi 1 Décembre 2016
*\fn void init_Mat(int Mat[N][M])
*\fn void AfficherMat(int Mat[N][M])
*\fn int Choix_case(int Mat[N][M], int joueur)
*\fn int Case_Vide(int Mat[N][M], int joueur, int j, int nb)
*\fn int Compte_Graine(int Mat[N][M])
*\fn int CapturePoints(int Mat[N][M], int joueur, int j, int nb)
*\fn int deplacement_gauche (int Mat[N][M], int j, int joueur, int nb)
*\fn int deplacement_droite (int Mat[N][M], int j, int joueur, int nb)
*\fn int deplacement(int Mat[N][M], int j, int joueur, int nb)
*\fn int JouerTourCapture(int Mat[N][M], int j, int joueur, int nb, int total, int fin)
*\fn void JouerTour(int Mat[N][M], int j, int joueur, int nb, int fin)
*\fn int ArretJeu(int j1, int j2, char c, int fin, int arret)
*\fn int Test(int comptest)
*\fn void Partie_Solo(void)
*\fn void Partie_A2(void)
*\fn int Highscores(FILE * fic, int compt)
*\fn int main2(void)
*\fn void ModuleAmorceR(void)
*\fn int main(void)
*/


int deplacement_droite (int Mat[N][M], int j, int joueur, int nb);
int deplacement_gauche (int Mat[N][M], int j, int joueur, int nb);
int Compte_Graine(int Mat[N][M]);
int bChaineEgale(char *sTexte1, char *sTexte2); //Toujours utile au cas où (surtout pour des mots de passe);
int main2();

/**\brief Initialise les valeurs de l'Awélé à 4*/
void init_Mat(int Mat[N][M]){ //Initialisation de l'Awélé
	int i, j;
	
	for(i = 0 ; i < N ; i++){
		for(j = 0 ; j < M ; j++){
			Mat[i][j] = 4;
		}
	}
}

/**\brief Affiche les valeurs courantes de l'Awélé*/
void AfficherMat(int Mat[N][M]){ //Affichage de l'Awélé et du reste des graines
	int i, j, reste;
	printf("\n   1 2 3 4 5 6\n");
	for(i = 0; i < N; i++){
		printf("J%i ", i+1);
		for(j = 0; j < M ; j++){
			printf("%i ",Mat[i][j]);
		}
		printf("\n");
	}
	reste = Compte_Graine(Mat);
	printf("\nIl reste %i points à prendre\n", reste);
	
}



/**\brief Sélection d'une case de l'Awélé*/
int Choix_case(int Mat[N][M]){ //Sélection de la case à déplacer selon le type de joueur
	int j;
	printf("\nDéplacer quelle case ? \n");
		scanf("%i",&j);
		/*while((j >= 7) || (j < 0)){ //Limites de la matrice prises en compte
			printf("Hors Limite !\nRecommencez : ");
			scanf("%i", &j);
		}	*/					
	return j;
}

/**\brief Test de Case vide avec correction imposée*/
int Case_Vide(int Mat[N][M], int joueur, int j, int nb){ //On prend en compte les cases vides et on force le joueur à en changer
	while(nb == 0){
		printf("\nErreur, Case vide\n");
		j = Choix_case(Mat);
		if(j > 0){
			j--;
		}
		nb = Mat[joueur][j];
		printf("\nnb points : %i\n", nb);
		AfficherMat(Mat);
	}
	return j;
}

/**\brief Compte le total de la somme des valeurs de l'Awélé*/
int Compte_Graine(int Mat[N][M]){ //Pour garder l'oeil sur le nombre de billes/graines restantes, aussi bien durant les tests que durant la partie
	int i, j;
	int comptG = 0;
	for (i = 0 ; i < N ; i++){
		for(j = 0 ; j < M ; j++){
			comptG = comptG + Mat[i][j];
		}
	}
	return comptG;
}


int deplacement_gauche (int Mat[N][M], int j, int joueur, int nb){ //Déplacement vers la gauche ou de 5 à 0
	
	while((nb > 0) && (j >= 0)){
	//Ajoute 1 aux valeurs de la Matrice tant que le nombre de billes n'est pas 0
		j--;
		if (j >= 0){
			Mat[joueur][j]++;
			nb--;
		}
	}
	if(nb > 0){ //Lorsqu'on dépasse les limites de la matrice et qu'ils restent des billes à déposer
		joueur++;
		deplacement_droite(Mat, j, joueur, nb);
	}
	return joueur;
}

int deplacement_droite (int Mat[N][M], int j, int joueur, int nb){ //Déplacement vers la droite ou de 0 à 5
	
	while((nb > 0) && (j < M)){
	//Ajoute 1 aux valeurs de la Matrice tant que le nombre de billes n'est pas 0
		j++;
		if (j < 6){
			Mat[joueur][j]++;
			nb--;
		}
	}
	if(nb > 0){ //Lorsqu'on dépasse les limites de la matrice et qu'ils restent des billes à déposer
		joueur--;
		deplacement_gauche(Mat, j, joueur, nb);
	}
	return joueur;
}

/**\brief Gère les déplacements à gauche et à droite de l'Awélé*/
int deplacement(int Mat[N][M], int j, int joueur, int nb){
	//Une fonction pour deux déplacements;
	if(joueur == 0){
		joueur = deplacement_gauche(Mat, j, joueur, nb);
	} else if(joueur == 1){
		joueur = deplacement_droite(Mat, j, joueur, nb);
	} else {
		printf("\nErreur dans la numérotation des joueurs\n");
	}
	return joueur;
}

/**\brief Ajoute les points des cases concernées au joueur concerné*/
int CapturePoints(int Mat[N][M], int joueur, int j, int nb,int score[N]){
	//Capture des points; on s'assure d'être sur la bonne ligne pour commencer
	int totalpris = 0;
	printf("on rentre\n");
	if (joueur == 0){
		printf("j= %i",j);
		j=(6-(nb-(5-j)));
		printf("case du nvjoueur1= %i",j);
	}	
	else{
		j=((nb-j)-1);
		printf("case du nvjoueur= %i",j);
	}	
	if( (Mat[joueur][j]==3) || (Mat[joueur][j]==2) ){
		if (joueur==0)
			while(j<6 && ( Mat[joueur][j]==2 || Mat[joueur][j]==3)){
				score[1]=score[1]+Mat[joueur][j];
				Mat[joueur][j]=0;
				j++;
			}
		else
			while(j>(-1) && ( Mat[joueur][j]==2 || Mat[joueur][j]==3)){
				score[0]=score[0]+Mat[joueur][j];
				Mat[joueur][j]=0;
				j--;
			}
	}
}


/**\brief Un tour se déroule et on prend des points*/
void JouerTourCapture(int Mat[N][M], int j, int joueur, int nb, int score[N]){
	//joueur joue son tour ; rend le total de point gagnés
	int nvJoueur;
	j--;
	nb = Mat[joueur][j];
	//j = Case_Vide(Mat, joueur, j, nb);
	nb = Mat[joueur][j];
	Mat[joueur][j] = 0;
	if (joueur==0)
		nvJoueur=1;
	else 
		nvJoueur=0;
	deplacement(Mat, j, joueur, nb);
	printf("nvJoueur = %i\n", nvJoueur);
	CapturePoints(Mat,nvJoueur,j,nb,score);
	j++;
}

/**\brief On arrête le jeu lorsqu'on a certaines valeurs*/
/*int ArretJeu(int j1, int j2, char c, int arret){
	if((j1 == 0) || (j2 == 0)){
		while ((c != 'y') && (c != 'n')){
			printf("Voulez-vous arrêter le jeu ? (y or n)\n");
			scanf("%*c%c", &c);
			if(c == 'y'){
				j1 = fin;
				j2 = fin;
			} else if(c == 'n') {
				j1 = 0;
				j2 = 0;
			} else {
				printf("Erreur caractère\n");
			}
		}
	}
	if ((j1 == fin) || (j2 == fin)){
		arret = 1;
	} else {
		arret = 0;
	}
	return arret;
}



*/
void init_score(int score[N])
{
	score[0]=0;
	score[1]=0;
}

/**\brief Jeu entre 2 *joueurs*/
void Partie_A2(){
	int Mat[N][M];
	char c;
	int j1, j2,score[N], nb, arret;
	init_score(score);
	j1 = 0;
	j2 = 1;
	init_Mat(Mat); //Initialisation OBLIGATOIRE !
	AfficherMat(Mat);
	
	while( score[0]<24 && score[1]<24){

		printf("\n'Joueur 1' joue \n");
		j1 = Choix_case(Mat);
		JouerTourCapture(Mat, j1, 0, nb, score);
		AfficherMat(Mat);
		printf("total point J1 : %i\n", score[0]);
		printf("total point J2 : %i\n", score[1]);
		
		printf("\n'Joueur 2' joue \n");
		j2 = Choix_case(Mat);
		JouerTourCapture(Mat, j2, 1, nb, score);
		AfficherMat(Mat);
		printf("total point J1 : %i\n", score[0]);
		printf("total point J2 : %i\n", score[1]);
	}

	printf("\nTotal J1 : %i\nTotal J2 : %i\n", score[0],score[1]);
}

/**\brief 'Menu' de sélection des modes de jeux et des autres fonctions*/
int main2(){
	int choix;
	int compt = 0;
	int comptest = 0;
	FILE * fic;
	fic = fopen("highscoresA.txt","r");
	if(fic == NULL){ //On initialise un fichier Highscores pour les tests
		fic = fopen("highscoresA.txt","w");
		fprintf(fic,"1 24 C\n");
		fprintf(fic,"2 24 O\n");
		fprintf(fic,"3 24 U\n");
		fprintf(fic,"4 24 R\n");
		fprintf(fic,"5 24 G\nJouerTourCap");
		fprintf(fic,"6 24 E\n");
		fprintf(fic,"7 24 T\n");
		fprintf(fic,"8 24 T\n");
		fprintf(fic,"9 24 E\n");
	}
	fclose(fic);
	Partie_A2();
	/*do { //Menu de Sélection
		fic = fopen("highscoresA.txt","r");
			printf("\n	Bienvenue,\n\nComment voulez jouer à l'Awélé ?\n");
			printf(" 1 - Contre l'ordi\n");
			printf(" 2 - A deux\n");
			printf(" 3 - Afficher highscores\n");
			printf(" 4 - Test\n");
			printf(" 5 - Quitter le jeu\n");
			printf("Votre choix : ");
		
			scanf("%i", &choix);
		
			switch(choix){
				case 1: Partie_Solo(); break;
				case 2: Partie_A2(); break;
				case 3: compt = Highscores(fic, compt); break;
				case 4: comptest = Test(comptest); break;
				case 5: break;
				default: printf("Erreur, le choix ne peut être compris qu'entre 1 et 5, merci !");
				//On prévoit pour choix < 1 et choix > 5
			}
			if((choix != 3) && (compt > 0) && (choix != 5)){//Car l'afficher une fois suffit pour l'instant
				compt = 0;
				printf("\nFonction Highscore réutilisable\n");
			}
			if((choix != 4) && (comptest > 0) && (choix != 5)){//Car l'afficher une fois suffit pour l'instant
				comptest = 0;
				printf("\nFonction Test réutilisable\n");
			}
		fclose(fic); //Permet de relire le fichier à partir du début de ce dernier
	}
	while(choix!=5);*/
	printf("\nA plus !\n"); //Fin
	return EXIT_SUCCESS;
}

/**\brief Celle-là j'ai pas compris...*/
void ModuleAmorceR(){
	//amorce tous les modules (code à exécuter une fois pour toutes AVANT d'utiliser un quelconque module depuis le main)
	OutilAMORCER();//NE PAS DECLASSER:doit toujours être appelé en premier
	//amorcer TOUS les modules autres que Outil mentionnés dans les include de main.c
		//TasAMORCER();
}//ModuleAmorceR

/**\brief Fonction principale appelant les autres*/
int main (int argc, const char * argv[]) {
	Appel0("");//NE PAS TOUCHER; ce code doit toujours être placé au début du main
		ModuleAmorceR();//NE PAS TOUCHER; ce code doit toujours suivre immédiatement Appel0("")
te("dtxsxsd",54);
		main2();
	Appel1("");//NE PAS TOUCHER; ce code doit toujours être placé à la fin du main, juste avant le return()
    return 0;
}

