#include "header.h"






void kreirajZaposlenika(void) {

    FILE * fp = NULL;
    ZAPOSLENIK * zap = NULL;
    zap = (ZAPOSLENIK * ) calloc(1, sizeof(ZAPOSLENIK));
    if (zap == NULL) {
        perror("greska");
    }
    fp = fopen("datoteka.txt", "a");
    if (fp == NULL) {
        perror("error");
        exit(EXIT_FAILURE);
    }
    int provjeraKor;
    int provjeraID1;
    int k=brojZap();
    printf("Upisite korisnicko ime: ");
    do{
    fgets(zap -> korisnickoIme, 15, stdin);
    zap->korisnickoIme[strcspn(zap->korisnickoIme, "\n")] = 0;
    provjeraKor=provjeraKorisnika(k, zap->korisnickoIme);
    if(provjeraKor==1){
        printf("Ovo korisnicko ime se vec koristi, pokusajte ponovo: ");
    }
    }while(provjeraKor!=0);
    char * sifra1;
    printf("Upisite sifru: ");
    sifra1 = sifra();
    strcpy(zap -> sifra, sifra1);
    printf("Upisite ime: ");
    fgets(zap->ime, 20, stdin);
    if(zap->ime[0]>=97&&zap->ime[0]<=122){
        zap->ime[0]=(zap->ime[0])-32;
    }
    printf("Upisite prezime: ");
    fgets(zap->prezime, 30, stdin);
    if(zap->prezime[0]>=97&&zap->prezime[0]<=122){
        zap->prezime[0]=(zap->prezime[0])-32;
    }
    printf("Upisite ID: ");
    do{
    scanf("%d", & zap -> ID);
    provjeraID1=provjeraID(k, zap->ID);
    if(provjeraID1==1){
        printf("Ovaj ID je zauzet, pokusajte ponovo: ");
    }
    }while(provjeraID1!=0);
    printf("Upisite placu: ");
    scanf("%f", & zap -> placa);

    fprintf(fp, "%s\n%s\n%s%s%d\n%.2f\n", zap -> korisnickoIme, zap -> sifra, zap -> ime, zap -> prezime, zap -> ID, zap -> placa);
    printf("Uspjesna registracija zaposlenika.\n");
    free(sifra1);
    free(zap);
    fclose(fp);

}





char * sifra(void) {

    const int max = 15;
    char * password;
    password = calloc(max + 1, sizeof(char));
    if (password == NULL) {
        return 0;
    }
    char ch;
    int pozicija = 0;
    while (1) {
        ch = getch();
        if (ch == 10) {
            break;
        } else if (ch == 32 || ch == 9 || ch == 8) {
            continue;
        } else {
            if (pozicija < max) {
                password[pozicija] = ch;
                pozicija++;
                printf("*");
            } else {
                printf("\nPreskocili ste maksimalan broj karaktera sifre koji iznosi:%d, sifra je postavljena.", max);
                break;
            }
        }
    }
    password[pozicija] = '\0';
    printf("\n");
    if (strlen(password) == 0) {
        printf("\nNije unesena sifra.\n ");
    } else if (strlen(password) < 6) {
        printf("Sifra mora biti barem 6 karaktera, pokusajte ponovo: ");
        free(password);
        password = sifra();
    } else {
        return password;
    }

}





int getch(void) {
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, & oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, & newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, & oldattr);
    return ch;
}




int brojZap(void) {

    FILE * fp = NULL;
    if((fp=fopen("datoteka.txt","r"))==NULL){
            
    }else{
    int i = 0;
    char citac[100];
    do {
        fgets(citac, 100, fp);
        if (feof(fp)) break;
        i++;

    } while (1);
    i = i / 6;
    fclose(fp);
    return i;
}
}






void ispisZap(int z) {
     FILE * fp = NULL;
    if (z == 0||(fp = fopen("datoteka.txt", "r"))==NULL) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n\n");

    } else {
        FILE * fp = NULL;
        fp = fopen("datoteka.txt", "r");
        if (fp == NULL) {
            perror("greska u otvaranju");
            exit(EXIT_FAILURE);
        }
        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("greska");
            exit(EXIT_FAILURE);

        }
         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < z; i++) {

            fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
            fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
            fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);
            
            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
        

        free(zaposlenici);
        fclose(fp);
    }
}






void login(int k) {
     FILE * fp = NULL;
    if (k == 0||(fp=fopen("datoteka.txt","r"))==NULL) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n\n");

    } else {

        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(k, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("greska");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < k; i++) {

            fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
            fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
            fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);
        }
        fclose(fp);

        char korisnik[15];
        printf("korisnicko ime: ");
        scanf("%s", korisnik);
        int provj = 0;
        int i = 0;
        do {
            if ((strcmp(korisnik, (zaposlenici + i) -> korisnickoIme)) == 0) {
                provj = 1;
                break;
            }

            i++;
        } while (k > i);
        char * sifra1;
        int pokusaj = 0;
        if (provj == 1) {
            printf("Korisnicko ime nadeno, upisite sifru, ");
            getchar();
            do {
                pokusaj++;
                if (pokusaj < 5) {
                    printf("imate jos %d pokusaj/a: ", 5 - pokusaj);

                }
                sifra1 = sifra();
                if (strcmp(sifra1, (zaposlenici + i) -> sifra) == 0) {
                    printf("Sifra pronadena.\n ");
                    free(sifra1);
                    free(zaposlenici);
                    int uvijet = 1;
                    while (uvijet) {
                        uvijet = izbornikZaposlenik(i);
                    }
                    break;
                }
            } while (pokusaj < 4);

        } else {
            printf("Korisnicko ime nije nadeno! pokusajte ponovo upisat ");
            login(k);
        }
        if (pokusaj == 4) {
            free(sifra1);
            free(zaposlenici);
            printf("Sifra netocna, vracam na izbornik.\n");
        }
    }
}





void promjenaSifre(int s, int z) {
    FILE * fp = NULL;
    fp = fopen("datoteka.txt", "r");
    if (fp == NULL) {
        perror("greska u otvaranju");
        exit(EXIT_FAILURE);
    }
    ZAPOSLENIK * zaposlenici = NULL;
    zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
    if (zaposlenici == NULL) {
        perror("greska");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < z; i++) {

        fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
        fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
        fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);
    }

    printf("Upisite novu sifru: ");
    char * novasifra;
    getchar();
    novasifra = sifra();
    strcpy((zaposlenici + s) -> sifra, novasifra);
    fclose(fp);
    fp = fopen("datoteka.txt", "w");
    for (int i = 0; i < z; i++) {
        fprintf(fp, "%s\n%s\n%s\n%s\n%d\n%.2f\n", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> ID, (zaposlenici + i) -> placa);
    }
    free(zaposlenici);
    fclose(fp);
    free(novasifra);
}


void stvoriBiljesku(char *ime){
    FILE *fp=NULL;
    fp=fopen(ime, "a");
    if (fp == NULL) {
            perror("greska u otvaranju");
            exit(EXIT_FAILURE);
        }
    char p;
    printf("\nUpisite biljesku: ");
    while((p=getchar())!=10){
        putc(p, fp);
    }
    fprintf(fp, "\n");
    
    fclose(fp);
    
}



void citajBiljesku(char *ime){
    FILE *fp=NULL;
    if((fp=fopen(ime,"r"))==NULL){
        printf("\nNema biljeske!\n.");
    }else{
    fp=fopen(ime, "r");
    printf("\nVasa biljeska:\n");
    char p;
	while ((p = getc(fp)) != EOF) {
		printf("%c", p);
	}
    
    fclose(fp);
    }
}








void obirisiZaposlenika(int z) {
   FILE * fp = NULL;

    if ((fp = fopen("datoteka.txt", "r"))==NULL||z==0) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n\n");
    }else{
        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("greska");
            exit(EXIT_FAILURE);

        }
         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < z; i++) {

            fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
            fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
            fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);

            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
        fclose(fp);
        printf("\nUnesite ID zaposlenika koji zelite obrisat: ");
        int zapID;
        int provjera=0;
        do{
        scanf("%d", &zapID);
        for(int i=0; i<z; i++){
        if((zaposlenici+i)->ID==zapID){
            provjera=1;
            break;
        }
        }
        
        if(provjera==1){
            break;
        }
        printf("\nNe postoji zaposlenik s tim ID-om, pokusajte ponovo: ");
        }while(1);
        fp = fopen("datoteka.txt", "w");
        for (int i = 0; i < z; i++) {
            if (zapID == (zaposlenici+i)->ID) {
                continue;
            }
            fprintf(fp, "%s\n%s\n%s\n%s\n%d\n%.2f\n", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> ID, (zaposlenici + i) -> placa);
        }
        printf("\nZaposlenik uspjesno obrisan!\n");
        fclose(fp);
        free(zaposlenici);
    }
}





void sortirajPlacaVeca(int z) {
    FILE * fp = NULL;

    if ((fp = fopen("datoteka.txt", "r"))==NULL||z==0) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n");
    }else{
        
    int i, j;
    ZAPOSLENIK * zaposlenici = NULL;
    zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
    if (zaposlenici == NULL) {
        perror("greska");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < z; i++) {

        fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
        fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
        fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);
    }

    fclose(fp);

    int min = -1;
    for (i = 0; i < z - 1; i++) {
        min = i;
        for (j = i + 1; j < z; j++) {
            if ((zaposlenici + j) -> placa > (zaposlenici + min) -> placa) {
                min = j;
            }
        }
        zamjena((zaposlenici + i), (zaposlenici + min));
    }

         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < z; i++) {

            
            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
    free(zaposlenici);

}
}



void sortirajPlacaManja(int z) {
    FILE * fp = NULL;

    if ((fp = fopen("datoteka.txt", "r"))==NULL||z==0) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n");
    }else{
        int i, j;
    ZAPOSLENIK * zaposlenici = NULL;
    zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
    if (zaposlenici == NULL) {
        perror("greska");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < z; i++) {

        fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
        fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
        fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);
    }

    fclose(fp);

    int min = -1;
    for (i = 0; i < z - 1; i++) {
        min = i;
        for (j = i + 1; j < z; j++) {
            if ((zaposlenici + j) -> placa < (zaposlenici + min) -> placa) {
                min = j;
            }
        }
        zamjena((zaposlenici + i), (zaposlenici + min));
    }

         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < z; i++) {
            
            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
    free(zaposlenici);

}
}




void sortirajIme(int z) {
    FILE * fp = NULL;

    if ((fp = fopen("datoteka.txt", "r"))==NULL||z==0) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n");
    }else{
    int i,j;
    ZAPOSLENIK * zaposlenici = NULL;
    zaposlenici = (ZAPOSLENIK * ) calloc(z, sizeof(ZAPOSLENIK));
    if (zaposlenici == NULL) {
        perror("greska");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < z; i++) {

        fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
        fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
        fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);
    }

    fclose(fp);

    int min = -1;
    for (i = 0; i < z - 1; i++) {
        min = i;
        for (j = i + 1; j < z; j++) {
            if ((zaposlenici + j) -> ime[0] < (zaposlenici + min) -> ime[0]) {
                min = j;
            }
        }
        zamjena((zaposlenici + i), (zaposlenici + min));
    }

         printf("\n---------------------------------------------------------------------------------------------\n");
         printf("ID\t\tIme\t\tPrezime\t\t\tPlaca");
         printf("\n---------------------------------------------------------------------------------------------\n");
        for (int i = 0; i < z; i++) {
            
            printf("%d\t\t%s\t\t%s\t\t\t%.2f\n", (zaposlenici + i) -> ID, (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> placa);
        }
    free(zaposlenici);
}
}




void zamjena(ZAPOSLENIK * veci, ZAPOSLENIK * manji) {
    ZAPOSLENIK temp;
    temp = * manji;
    * manji = * veci;
    * veci = temp;
}




void trazenjeID(int k){
         FILE * fp = NULL;
    if (k == 0||(fp=fopen("datoteka.txt","r"))==NULL) {
        printf("\nNema zaposlenika, registrirajte nekog prvo!\n\n");

    } else {

        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(k, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("greska");
            exit(EXIT_FAILURE);
        }
        int trazeniID;
        printf("\nUpisite ID koji trazite: ");
        scanf("%d", &trazeniID);
        int provjera=0;
        int i;
        for (i = 0; i < k; i++) {

            fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
            fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
            fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);
            if(trazeniID==(zaposlenici+i)->ID){
                provjera=1;
                break;
                
            }
        }
        fclose(fp);
        if(provjera==1){

             printf("\nZaposlenik naden!\n\nIme:%s\nPrezime:%s\nID:%d\nPlaca:%.2f\n\n",(zaposlenici + i) -> ime, (zaposlenici + i) -> prezime, (zaposlenici + i) -> ID, (zaposlenici + i) -> placa);
        }
        else{
            printf("\nTrazeni ID nije naden!\n");
        }
      free(zaposlenici);
        
    }
}




int provjeraKorisnika(int k, char *korisnik){
             FILE * fp = NULL;
    if (k == 0||(fp=fopen("datoteka.txt","r"))==NULL) {
    } else {

        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(k, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("greska");
            exit(EXIT_FAILURE);
        }
        int provjera=0;
        for (int i = 0; i < k; i++) {

            fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
            fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
            fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);
            if ((strcmp(korisnik, (zaposlenici + i) -> korisnickoIme)) == 0) {
                provjera = 1;
                break;
            }
                
            }
            fclose(fp);
            free(zaposlenici);
            return provjera;
        }
    
}




int provjeraID(int k, int ID){
             FILE * fp = NULL;
    if (k == 0||(fp=fopen("datoteka.txt","r"))==NULL) {
    } else {

        ZAPOSLENIK * zaposlenici = NULL;
        zaposlenici = (ZAPOSLENIK * ) calloc(k, sizeof(ZAPOSLENIK));
        if (zaposlenici == NULL) {
            perror("greska");
            exit(EXIT_FAILURE);
        }
        int provjera=0;
        for (int i = 0; i < k; i++) {

            fscanf(fp, "%s %s", (zaposlenici + i) -> korisnickoIme, (zaposlenici + i) -> sifra);
            fscanf(fp, "%s %s ", (zaposlenici + i) -> ime, (zaposlenici + i) -> prezime);
            fscanf(fp, "%d %f", & (zaposlenici + i) -> ID, & (zaposlenici + i) -> placa);
            if (ID==(zaposlenici+i)->ID) {
                provjera = 1;
                break;
            }
                
            }
            fclose(fp);
            free(zaposlenici);
            return provjera;
        }
}


