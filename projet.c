
#include "Outil.h"
#define N 2
#define M 6


int deplacement_droite (int Mat[N][M], int j, int joueur, int nb);
int deplacement_gauche (int Mat[N][M], int j, int joueur, int nb);
int Compte_Graine(int Mat[N][M]);
int bChaineEgale(char *sTexte1, char *sTexte2); //Toujours utile au cas où (surtout pour des mots de passe);
int main2();

void init_Mat(int Mat[N][M]){ //Initialisation de l'Awélé
	int i, j;
	
	for(i = 0 ; i < N ; i++){
		for(j = 0 ; j < M ; j++){
			Mat[i][j] = 4;
		}
	}
}

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

int Choix_case(char typeJ){ //Sélection de la case à déplacer selon le type de joueur
	int j;
	char c;
	printf("\nDéplacer quelle case ? \n");
	if(typeJ == 'J'){ //Joueur 'réel'
		scanf("%i",&j);
		while((j >= 7) || (j < 0)){ //Limites de la matrice prises en compte
			printf("Hors Limite !\nRecommencez : ");
			scanf("%i", &j);
		}
		if(j == 0){
			printf("Voulez-vous terminer le jeu ? (Attention, à 2 joueur vous passez votre tour)\n(y or n)\n");
			scanf("%*c%c", &c);
			if(c == 'n'){
				printf("Reprenons alors...\n");
				j = Choix_case(typeJ);
			} else if(c == 'y'){
				j = 0;
			} else {
				printf("Mal écrit, on reprend : \n");
				j = Choix_case(typeJ);
			}
		}
	} else if (typeJ == 'O'){ //Joueur 'Ordinateur', choisi sa case au hasard
		j = uHasard(6);
		printf("\nOrdi déplace case %i", j);

		if( j == 0 ){ //Prévision en cas de j nul
			j = 1;
		}
	} else { //On prévoit l'erreur sur 'typeJ'
		printf("ERREUR, 'typeJ' erronné : %c\nArrêt forcé\n", typeJ);
		j = -1;
	}
	return j;
}

int Case_Vide(int Mat[N][M], int joueur, int j, int nb, char TypeJ){ //On prend en compte les cases vides et on force le joueur à en changer
	while(nb == 0){
		printf("Erreur, Case vide\n");
		j = Choix_case(TypeJ);
		if(j > 0){
			j--;
		}
		nb = Mat[joueur][j];
		printf("\nnb points : %i\n", nb);
		AfficherMat(Mat);
	}
	return j;
}

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

int CapturePoints(int Mat[N][M], int joueur, int j, int nb){
	int totalpris = 0;

	if( ((j - 6) > 0) && (nb < 12)){
		j = j - 6;
		printf("j = %i\n", j);
	} else if( nb >= 12 ){
		while((j - 6) > 0){
			j = j - 6;
		}
	}
	
	While(7);
	while(bWhile("pourquoiçafaitça?(CapturePoints)", (j < 6) && (j >= 0)) ){
		if((Mat[joueur][j] < 4) && (Mat[joueur][j] > 1)) {
			totalpris = totalpris + Mat[joueur][j];
			Mat[joueur][j] = 0;
		}
		if(joueur == 0){
			j--;
		} else if(joueur == 1){
			j++;
		}
	}
	return totalpris;
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
int deplacement(int Mat[N][M], int j, int joueur, int nb){
	
	if(joueur == 0){
		joueur = deplacement_gauche(Mat, j, joueur, nb);
	} else if(joueur == 1){
		joueur = deplacement_droite(Mat, j, joueur, nb);
	} else {
		printf("\nErreur dans la numérotation des joueurs\n");
	}
	return joueur;
}
int JouerTourCapture(int Mat[N][M], int j, int joueur, int nb, int total, char typeJ, int fin){
	//joueur joue son tour ;
	int nvJoueur;
	j--;
	nb = Mat[joueur][j];
	j = Case_Vide(Mat, joueur, j, nb, typeJ);
	nb = Mat[joueur][j];
	Mat[joueur][j] = 0;
	nvJoueur = deplacement(Mat, j, joueur, nb);
	if (nvJoueur != joueur){
		total = total + CapturePoints(Mat, nvJoueur, (j + nb), nb);
	}
	j++;
	return total;
}

void JouerTour(int Mat[N][M], int j, int joueur, int nb, char typeJ, int fin){
	int nvJoueur;
	j--;
	nb = j--;
	nb = Mat[joueur][j];
	j = Case_Vide(Mat, joueur, j, nb, typeJ);
	nb = Mat[joueur][j];
	Mat[joueur][j] = 0;
	nvJoueur = deplacement(Mat, j, joueur, nb);
	j++;
}

int ArretJeu(int j1, int j2, char c, int fin, int arret){
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


void TestA2() {

	int Mat[N][M];
	int fin = -1;
	char c, typeJ;
	int j1, j2, totalj1, totalj2, nb, arret;
	totalj1 = 0;
	totalj2 = 0;
	j1 = 1;
	j2 = 1;
	init_Mat(Mat); //Initialisation OBLIGATOIRE !

	AfficherMat(Mat);
	typeJ = 'J';
	do{
		printf("\n'Testeur 1' as J1\n");

		j1 = Choix_case(typeJ);

		if((j1 != 0) && (j1 != -1)){
			JouerTour(Mat, j1, 0, nb, typeJ, fin);
		} else if(j1 == -1) {
			j1 = fin;
		}
		AfficherMat(Mat);

		printf("\n'Testeur 2' as J2\n");

		j2 = Choix_case(typeJ);

		if((j2 != 0) && (j2 != -1)){
			JouerTour(Mat, j2, 1, nb, typeJ, fin);
		} else if(j2 == -1) {
			j2 = fin;
		}
		AfficherMat(Mat);

		arret = ArretJeu(j1, j2, c, fin, arret);
	}while(arret != 1);
	
}

void TestOrdi(){

	int Mat[N][M];
	int fin = -1;
	int compt;
	char c, typeJ;
	int j1, j2, totalj1, totalj2, nb, arret;
	totalj1 = 0;
	totalj2 = 0;
	j1 = 1;
	j2 = 1;
	typeJ = 'O';

	init_Mat(Mat); //Initialisation OBLIGATOIRE !

	AfficherMat(Mat);

	do{
		printf("\nTour 'OrdiTest1' as J1 :\n");
		j1 = Choix_case(typeJ);

		if((j1 != 0) && (j1 != -1)){
			JouerTour(Mat, j1, 0, nb, typeJ, fin);
		} else if(j1 == -1) {
			j1 = fin;
		}
		AfficherMat(Mat);

		printf("\nTour 'OrdiTest2' as J2 :\n");
		j2 = Choix_case(typeJ);

		if((j2 != 0) && (j2 != -1)){
			JouerTour(Mat, j2, 1, nb, typeJ, fin);
		} else if(j2 == -1) {
			j2 = fin;
		}
		AfficherMat(Mat);

		compt++;

	}while(compt < 1);
	printf("\nFait\n");
}

void TestErrTJoueur() {

	int Mat[N][M];
	int fin = -1;
	char c, typeJ;
	int j1, j2, totalj1, totalj2, nb, arret;
	totalj1 = 0;
	totalj2 = 0;
	j1 = 1;
	j2 = 1;
	init_Mat(Mat); //Initialisation OBLIGATOIRE !

	AfficherMat(Mat);

	printf("Test : Entrez un type de joueur erronné ('A','B', ...)\n");
	scanf("%*c%c", &typeJ);
	do{
		printf("\n'Testeur' as J1\n");
		

		j1 = Choix_case(typeJ);

		if((j1 != 0) && (j1 != -1)){
			JouerTour(Mat, j1, 0, nb, typeJ, fin);
		} else if(j1 == -1) {
			j1 = fin;
		}
		AfficherMat(Mat);

		arret = ArretJeu(j1, j2, c, fin, arret);
	}while(arret != 1);
	
}

void TestErrNumJoueur() {

	int Mat[N][M];
	int fin = -1;
	int joueur;
	char c;
	int j1, j2, totalj1, totalj2, nb, arret;
	int typeJ = 'J';
	totalj1 = 0;
	totalj2 = 0;
	j1 = 1;
	j2 = 1;
	init_Mat(Mat); //Initialisation OBLIGATOIRE !

	AfficherMat(Mat);

	printf("Test : Entrez un numéro de joueur erronné (entier > 1 ou < 0 de préférence...)\n");
	scanf("%i", &joueur);
	do{
		printf("\n'Testeur' as J1\n");
		
		if((joueur != 0) || (joueur != 1)){
			j1 = fin;
			j2 = fin;
			printf("\nTest effectué : ERREUR sur 'joueur'\n");
		} else {
			j1 = Choix_case(typeJ);

			if((j1 != 0) && (j1 != -1)){
				JouerTour(Mat, j1, 0, nb, typeJ, fin);
			} else if(j1 == -1) {
				j1 = fin;
			}
			AfficherMat(Mat);
			printf("\nTest effectué : Pas d'ERREUR sur 'joueur'\n");
		}		

		arret = ArretJeu(j1, j2, c, fin, arret);
	}while(arret != 1);
	
	
}

void TestCapture(){

	int Mat[N][M];
	int fin = -1;
	char c, typeJ;
	int j1, j2, totalj1, totalj2, nb, arret;
	totalj1 = 0;
	totalj2 = 0;
	j1 = 1;
	j2 = 1;
	init_Mat(Mat); //Initialisation OBLIGATOIRE !

	AfficherMat(Mat);
	typeJ = 'J';
	do{
		printf("\n'Testeur 1' as J1\n");
		

		j1 = Choix_case(typeJ);
		if((j1 != 0) && (j1 != -1)){
			totalj1 = JouerTourCapture(Mat, j1, 0, nb, totalj1, typeJ, fin);
		} else if(j1 == -1) {
			j1 = fin;
		}
		AfficherMat(Mat);

		printf("\n'Testeur 2' as J2\n");

		j2 = Choix_case(typeJ);
		if((j2 != 0) && (j2 != -1)){
			totalj2 = JouerTourCapture(Mat, j2, 1, nb, totalj2, typeJ, fin);
		} else if(j2 == -1) {
			j2 = fin;
		}
		AfficherMat(Mat);
	
		arret = ArretJeu(j1, j2, c, fin, arret);
	}while(arret != 1);

}

int Test(int comptest){

	int arret, choix;
	int chance = 5;
	char passe[1+20] = "Courgette";
	char essai[20];
	
	
	if(comptest < 1){
		printf("\nBesoin d'un mot de passe pour les tests :\n");
		do{
			printf("Essai %i\n", (6-chance));
			scanf("%s", essai);
			if(strcmp(essai, passe)!=0){
				chance--;
				printf("\nRaté ! Encore %i essai(s) !\n", chance);
			}
		}while((strcmp(essai, passe)!=0) && (chance > 0));

		if(chance == 0){
			printf("\nDésolé, plus d'essais possibles, à plus !\nP.S. : Cherchez dans vos Highscores !\n");
			comptest = 1;
			return comptest;
		} else do{
			printf("\nQuel test ?\n");
			printf(" 1 - Test A 2\n");
			printf(" 2 - Ordi\n");
			printf(" 3 - Capture Points\n");
			printf(" 4 - Erreur type joueur\n");
			printf(" 5 - Erreur numérotation\n");
			printf(" 6 - Arrêter\n");
			printf("Votre choix : ");
			scanf("%i", &choix);
		
			switch(choix){
				case 1: TestA2(); break;
				case 2: TestOrdi(); break;
				case 3: TestCapture(); break;
				case 4: TestErrTJoueur(); break;
				case 5: TestErrNumJoueur(); break;
				case 6: arret = -1; break;
				default: printf("Erreur, le choix ne peut être compris qu'entre 1 et 6, merci !");
				//On prévoit pour choix < 1 et choix > 6
			}
		}while( arret != -1 );
	} else {
		printf("\nInutilisable pour l'instant\n");
	}
}
void Partie_Solo(){
	int Mat[N][M];
	int fin = -1;
	int joue;
	char c, typeJ;
	int j1, j2, totalj1, totalj2, nb, arret;
	totalj1 = 0;
	totalj2 = 0;
	j1 = 1;
	j2 = 1;
	init_Mat(Mat); //Initialisation OBLIGATOIRE !
	AfficherMat(Mat);
	
	printf("Voulez-vous jouer en '1'er ou en '2'éme ?\n");
	scanf("%i", &joue);
	
	while((joue <= 0) || (joue > 2)){ //On prévoit l'erreur sur la saisie de l'entier
		printf("Entrez juste 1 ou 2...\n");
		scanf("%i", &joue);
	}
	if(joue == 2){
		printf("\nJ1 = Ordi ; J2 = Joueur\n");
	} else {
		printf("\nJ1 = Joueur ; J2 = Ordi\n");
	}
	//On précise qui joue à quelle place
	do{
	//Boucle qui fonctionne tant qu'il n'y a pas d'erreur et qu'aucun des joueurs n'a atteint au moins 24 points

		if(joue == 1){ //On précise que le joueur joue en 1er ou en 2éme

			printf("\nTour 'Joueur' as J1 :\n");
			typeJ = 'J'; //A préciser pour la sélection de la case.

			j1 = Choix_case(typeJ);

			if((j1 != 0) && (j1 != -1)){
				JouerTour(Mat, j1, 0, nb, typeJ, fin);
			} else if(j1 == -1) {
				j1 = fin;
			}
			AfficherMat(Mat); //Pour garder un oeil sur le jeu...

			printf("\nTour 'Ordinateur' as J2 :\n");
			typeJ = 'O';

			j2 = Choix_case(typeJ);

			if((j1 != -1) && (j1 != 0)){
				JouerTour(Mat, j2, 1, nb, typeJ, fin);
			} else if(j1 == -1) {
				j2 = fin;
			} else if(j1 == 0){
				j2 = 0;
			}

			AfficherMat(Mat);
	
			arret = ArretJeu(j1, j2, c, fin, arret);
		}
		else if(joue == 2){
			printf("\nTour 'Ordinateur' as J1 :\n");
			typeJ = 'O';

			j1 = Choix_case(typeJ);

			if(j2 != 0){
			//Passe si l'ordinateur n'a pas rencontré d'erreur ou si le joueur réel souhaite continuer
				JouerTour(Mat, j1, 0, nb, typeJ, fin);

			} else if (j2 == 0) { //Prend en compte la volonté d'arrêter du joueur
				j1 = 0;
			}
			
			AfficherMat(Mat);

			printf("\nTour 'Joueur' as J2 :\n");
			typeJ = 'J';

			j2 = Choix_case(typeJ);

			if((j2 != 0) && (j2 != -1)){
				JouerTour(Mat, j2, 1, nb, typeJ, fin);
			} else if(j2 == -1) {
				j2 = fin;
			}
			AfficherMat(Mat);

			arret = ArretJeu(j1, j2, c, fin, arret);
		}
	

		if(joue == 1){
			printf("Total Joueur : %i\nTotal Ordi : %i\n", totalj1, totalj2);
		} else {
			printf("Total Joueur : %i\nTotal Ordi : %i\n", totalj2, totalj1);
		}
	}while( arret != 1 );
}

void Partie_A2(){
	int Mat[N][M];
	int fin = -1;
	char c;
	char typeJ = 'J';
	int j1, j2, totalj1, totalj2, nb, arret;
	totalj1 = 0;
	totalj2 = 0;
	j1 = 1;
	j2 = 1;
	typeJ = 'J';

	init_Mat(Mat); //Initialisation OBLIGATOIRE !
	AfficherMat(Mat);
	
	do{

	printf("\n'Joueur 1' as J1\n");
	

	j1 = Choix_case(typeJ);

	if((j1 != 0) && (j1 != -1)){
		JouerTour(Mat, j1, 0, nb, typeJ, fin);
	} else if(j1 == -1) {
		j1 = fin;
	}
	AfficherMat(Mat);

	printf("\n'Joueur 2' as J2\n");

	j2 = Choix_case(typeJ);

	if((j2 != 0) && (j2 != -1)){
		JouerTour(Mat, j2, 1, nb, typeJ, fin);
	} else if(j2 == -1) {
		j2 = fin;
	}
	AfficherMat(Mat);
	
	arret = ArretJeu(j1, j2, c, fin, arret);
	}while( arret != 1 );

	printf("\nTotal J1 : %i\nTotal J2 : %i\n", totalj1, totalj2);
}

int Highscores(FILE * fic, int compt){ //Affichage du contenu d'un fichier 'Highscores'
	
	int rang, score, n;
	char c;
	if(compt < 1){ //On ne souhaite pas l'afficher deux fois d'affilé...
		printf("\nMeilleurs scores : \n");
		While(13);
		while(bWhile("pourquoiçafaitça?",!feof(fic))){//On affiche toutes les infos du fichier
			fscanf(fic,"%i %i %c",&rang,&score,&c);
			n++;
			if(n <= rang){ //On s'assure que l'on n'affiche pas un doublon
				printf("Rang : %i - %c Score : %i\n", rang, c, score);
			}
		}
		printf("Fin\n");
		compt = 1;
		return compt; //On précise qu'il a été utilisé
	} else {
		printf("\nDéjà utilisé précédemment\n");
	}
}

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
		fprintf(fic,"5 24 G\n");
		fprintf(fic,"6 24 E\n");
		fprintf(fic,"7 24 T\n");
		fprintf(fic,"8 24 T\n");
		fprintf(fic,"9 24 E\n");
	}
	fclose(fic);
	do { //Menu de Sélection
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
	while(choix!=5);
	printf("\nA plus !\n"); //Fin
	return EXIT_SUCCESS;
}

void ModuleAmorceR(){
	//amorce tous les modules (code à exécuter une fois pour toutes AVANT d'utiliser un quelconque module depuis le main)
	OutilAMORCER();//NE PAS DECLASSER:doit toujours être appelé en premier
	//amorcer TOUS les modules autres que Outil mentionnés dans les include de main.c
		//TasAMORCER();
}//ModuleAmorceR

int main (int argc, const char * argv[]) {
	Appel0("");//NE PAS TOUCHER; ce code doit toujours être placé au début du main
		ModuleAmorceR();//NE PAS TOUCHER; ce code doit toujours suivre immédiatement Appel0("")
te("dtxsxsd",54);
		main2();
	Appel1("");//NE PAS TOUCHER; ce code doit toujours être placé à la fin du main, juste avant le return()
    return 0;
}
