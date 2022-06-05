#include "header.h"

int izbornik(void) {
    printf("*********************************************************************************************\n");
    printf("*                                                                                           *\n");
    printf("*----------------------------------EVIDENCIJA ZAPOSLENIKA-----------------------------------*\n");
    printf("*                                                                                           *\n");
    printf("*********************************************************************************************\n");
	printf("*                             Odaberite jednu od ponudenih opcija:                          *\n");
	printf("*                                                                                           *\n");
	printf("*\t\t\t    Opcija 1: Registracija zaposlenika.\t\t\t            *\n");
	printf("*\t\t\t    Opcija 2: Prijava zaposlenika.   \t\t\t            *\n");
	printf("*\t\t\t    Opcija 3: Ispisivanje podataka o svim zaposlenicima.\t    *\n");
	printf("*\t\t\t    Opcija 4: Sortiranje zaposlenih.     \t\t\t    *\n");
	printf("*\t\t\t    Opcija 5: Brisanje zaposlenog.       \t\t\t    *\n");
	printf("*\t\t\t    Opcija 6: Trazenje po ID-u.          \t\t\t    *\n");
	printf("*\t\t\t    Opcija 7: Zavrsetak programa.        \t\t\t    *\n");
	printf("*\t\t\t    Upisite opciju 1-7: ");
	int uvijet, uvijetSortiraj=1;
    do{
		    
		scanf("%d", &uvijet);
		if(uvijet<=0 || uvijet >7)
		    printf("Broj izvan ogranicenja, pokusajte ponovo: ");
		}while(uvijet<=0 || uvijet >7);
	int k;
	switch (uvijet) {

	case 1:
	getchar();
	kreirajZaposlenika();
		break;
	case 2:
		k=brojZap();
		login(k);
		break;
	case 3:
	    k=brojZap();
		ispisZap(k);
		break;
	case 4:
		k=brojZap();
		while(uvijetSortiraj){
		uvijetSortiraj=sortiraj(k);
		}
		break;
	case 5:
	    k=brojZap();
		obirisiZaposlenika(k);
		break;
	case 6:
	    k=brojZap();
		trazenjeID(k);
		break;
	case 7:
	    uvijet=0;
	    break;
	default:
	uvijet=1;
	}

	return uvijet;
}






int izbornikZaposlenik(int z){
        FILE *fp=NULL;
    fp=fopen("datoteka.txt", "r");
    if(fp==NULL){
        perror("greska u otvaranju");
        exit(EXIT_FAILURE);
    }
    ZAPOSLENIK *zaposlenik=NULL;
    zaposlenik=(ZAPOSLENIK*)calloc(1, sizeof(ZAPOSLENIK));
    if(zaposlenik==NULL){
        perror("greska");
        exit(EXIT_FAILURE);
    }
    for(int i=0; i<z+1; i++){
        
        fscanf(fp, "%s %s", zaposlenik->korisnickoIme, zaposlenik->sifra);
        fscanf(fp, "%s %s ",zaposlenik->ime, zaposlenik->prezime);
        fscanf(fp, "%d %f",&zaposlenik->ID,&zaposlenik->placa);
    }
    int uvijet=1;
    
    fclose(fp);
    printf("\n*********************************************************************************************\n");
    printf("*                                                                                           *\n");
    printf("  ----------------------------------Dobro dosli, %s!-----------------------------------\n", zaposlenik->ime );
    printf("*                                                                                           *\n");
    printf("*********************************************************************************************\n");
	printf("*                             Odaberite jednu od ponudenih opcija:                          *\n");
	printf("*                                                                                           *\n");
	printf("*\t\t\t    Opcija 1: Promjena sifre.        \t\t\t            *\n");
	printf("*\t\t\t    Opcija 2: Upisite biljeske.      \t\t\t            *\n");
	printf("*\t\t\t    Opcija 3: Ispisite vase biljeske. \t\t\t            *\n");
	printf("*\t\t\t    Opcija 4: Povratak na izbornik.  \t\t\t            *\n");
    printf("*\t\t\t    Upisite opciju 1-4: ");
	free(zaposlenik);
	
	do{
		 scanf("%d", &uvijet);
		if(uvijet<=0 || uvijet >4)
		    printf("Broj izvan ogranicenja, pokusajte ponovo: ");
		}while(uvijet<=0 || uvijet >4);   
	int k;
		switch (uvijet) {
    
	case 1:
	k=brojZap();
	promjenaSifre(z, k);
		break;
	case 2:
	    getchar();
		stvoriBiljesku(zaposlenik->ime);
		break;
	case 3:
     	citajBiljesku(zaposlenik->ime);
		break;
	case 4:
	uvijet=0;
	    break;
	default:
	uvijet=1;
	
	}

    return uvijet;
		
}




int sortiraj(int z){
    printf("\n\n*********************************************************************************************\n");
    printf("*                                                                                           *\n");
    printf("*----------------------------------------SORTIRANJE-----------------------------------------*\n");
    printf("*                                                                                           *\n");
    printf("*********************************************************************************************\n");
	printf("*                                                                                           *\n");
	printf("*\t\t\t    Opcija 1: Sortiranje po imenu.       \t\t\t    *\n");
	printf("*\t\t\t    Opcija 2: Sortiranje po placi od najvece. \t\t\t    *\n");
	printf("*\t\t\t    Opcija 3: Sortiranje po placi od najmanje.\t\t\t    *\n");
	printf("*\t\t\t    Opcija 4: Vracanje na izbornik.      \t\t\t    *\n");
	printf("*\t\t\t    Upisite opciju 1-4: ");
	int uvijet;
	do{
		 scanf("%d", &uvijet);
		if(uvijet<=0 || uvijet >4)
		    printf("Broj izvan ogranicenja, pokusajte ponovo: ");
		}while(uvijet<=0 || uvijet >4); 
		int k;
	
	switch (uvijet) {

	case 1:
     	k=brojZap();
	    sortirajIme(k);
		break;
	case 2:
	    k=brojZap();
		sortirajPlacaVeca(k);
		break;
	case 3:
	    k=brojZap();
		sortirajPlacaManja(k);
		break;
	case 4:
	    uvijet=0;
		break;
	default:
		uvijet=1;
	}
	
	return uvijet;
	
	
}
