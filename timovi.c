#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timovi.h"

int beskonacniMeni() {
    int opcija;

    printf("0. Kraj programa.\n");
    printf("1. Ucitavanje timova iz fajla.\n");
    printf("2. Cuvanje timova u fajl.\n");
    printf("3. Dodavanje novog tima.\n");
    printf("4. Brisanje tima.\n");
    printf("5. Ispisivanje svih timova.\n");
    printf("6. Sortiranje timova po broju poena.\n");
    printf("7. Sortiranje timova po nazivu.\n");
    printf("8. Ispisivanje pobednika po divizijama.\n");

    scanf("%d", &opcija);
    return opcija;
}
int ucitajFajl(Tim timovi[]) {
    FILE* fajl = fopen("liga.txt", "r");
    int i = 0;
    char konDiv[20];

    while (!feof(fajl)) {
        int j = 0, k = 0;

        fgets(timovi[i].imeKluba, 50, fajl);
        strtok(timovi[i].imeKluba, "\n");
        fgets(timovi[i].grad, 50, fajl);
        strtok(timovi[i].grad, "\n");
        fscanf(fajl, "%d", &timovi[i].brojPoena);fgetc(fajl);
        fgets(konDiv, 20, fajl);
        strtok(konDiv, "\n");
        fgetc(fajl);

        while (konDiv[j] != ' '){
            timovi[i].konDiv.konferencija[k++] = konDiv[j++];
        }
        j++;
        timovi[i].konDiv.konferencija[k] = '\0';

        k=0;

        while (konDiv[j] != '\0'){
           timovi[i].konDiv.divizija[k++] = konDiv[j++];
        }
        timovi[i].konDiv.divizija[k] = '\0';

        i++;
    }
    fclose(fajl);

    return i;
}

void ispisiSvakiTim(Tim timovi[], int brTimova){
    int i;

    printf("\n");

    for (i=0; i<brTimova; i++){
        printf("%s\n", timovi[i].imeKluba);
        printf("%s\n", timovi[i].grad);
        printf("%d\n", timovi[i].brojPoena);
        printf("%s %s\n", timovi[i].konDiv.konferencija, timovi[i].konDiv.divizija);
        printf("\n");
    }
}

void cuvanjeUFajl(Tim timovi[], int brTimova){
    int i;
    FILE* fajl = fopen("liga.txt", "w");

    for (i=0; i<brTimova; i++){
        fprintf(fajl, "%s\n", timovi[i].imeKluba);
        fprintf(fajl, "%s\n", timovi[i].grad);
        fprintf(fajl, "%d\n", timovi[i].brojPoena);
        fprintf(fajl, "%s %s\n", timovi[i].konDiv.konferencija, timovi[i].konDiv.divizija);
        if (i != brTimova-1)fprintf(fajl, "\n");

    }

    fclose(fajl);

}

int dodajNoviTim (Tim timovi[], int brTimova){
    char c;
    int i = 0;

    fflush(stdin);
    printf("Unesite naziv tima:\n");
    gets(timovi[brTimova].imeKluba);
    printf("Unesite naziv grada:\n");
    gets(timovi[brTimova].grad);
    printf("Unesite broj poena:\n");
    scanf("%d", &timovi[brTimova].brojPoena);
    getchar();
    printf("Unesite konferenciju i diviziju:\n");

    while((c = getchar()) != ' '){
        timovi[brTimova].konDiv.konferencija[i++] = c;
    }
    timovi[brTimova].konDiv.konferencija[i] = '\0';

    i = 0;

    while ((c = getchar()) != '\n'){
        timovi[brTimova].konDiv.divizija[i++] = c;
    }
    timovi[brTimova].konDiv.divizija[i] = '\0';

    return brTimova + 1;
}

int brisiTim(Tim timovi[], int brTimova){
    char tim[50], grad[50];
    int i, j = brTimova+1;

    printf("Unesite naziv tima koji zelite da izbrisete:\n");
    fflush(stdin);
    gets(tim);
    strtok(tim, "\n");

    printf("Unesite naziv grada iz koga tim potice:\n");
    fflush(stdin);
    gets(grad);
    strtok(grad, "\n");

    for (i = 0; i < brTimova; i++){
        if (strcmp(timovi[i].imeKluba,tim) == 0)
            if (strcmp(timovi[i].grad, grad) == 0) j=i;
    }

    if (j == brTimova+1){
        printf("Tim koji ste hteli da izbrisete ne postoji!\n");
        return brTimova;
    }

    for (i = j; i < brTimova; i++){
        timovi[i] = timovi[i+1];
        printf("\n");
        return brTimova - 1;
    }

}

void sortirajPoBrPoena(Tim timovi[], int brTimova){
    int i, j;
    Tim temp;

    for (i = 0; i < brTimova - 1; i++)
        for (j = i+1; j < brTimova; j++)
            if (timovi[i].brojPoena > timovi[j].brojPoena){
                temp = timovi[i];
                timovi[i] = timovi[j];
                timovi[j] = temp;
            }
}

void sortirajPoNazivu(Tim timovi[], int brTimova){
    int i, j;
    Tim temp;


    for (i = 0; i < brTimova - 1; i++)
        for (j = i + 1; j < brTimova; j++)
            if (strcmp(timovi[i].imeKluba, timovi[j].imeKluba) > 0){
                temp = timovi[i];
                timovi[i] = timovi[j];
                timovi[j] = temp;
            }
    printf("\n");
}

void ispisiPobednikeDivizija(Tim timovi[], int brTimova){
    Tim pobednik;
    int i;

    // AFC South AFC South AFC South AFC South AFC South

    pobednik.brojPoena = 0;

    for (i = 0; i < brTimova; i++)
        if (timovi[i].konDiv.divizija[0] == 'S' && timovi[i].konDiv.konferencija[0] == 'A')
            if (timovi[i].brojPoena > pobednik.brojPoena)
                pobednik = timovi[i];

    printf("\nPobednici divizija:\nAFC South:\nime: %s\ngrad: %s\nbroj bodova:%d\n", pobednik.imeKluba, pobednik.grad, pobednik.brojPoena);

    // AFC West AFC West AFC West AFC West AFC West

    pobednik.brojPoena = 0;

    for (i = 0; i < brTimova; i++)
        if (timovi[i].konDiv.divizija[0] == 'W' && timovi[i].konDiv.konferencija[0] == 'A')
            if (timovi[i].brojPoena > pobednik.brojPoena)
                pobednik = timovi[i];

    printf("\nAFC West:\nime: %s\ngrad: %s\nbroj bodova: %d\n", pobednik.imeKluba, pobednik.grad, pobednik.brojPoena);

    // AFC North AFC North AFC North AFC North AFC North

    pobednik.brojPoena = 0;

    for (i = 0; i < brTimova; i++)
        if (timovi[i].konDiv.divizija[0] == 'N' && timovi[i].konDiv.konferencija[0] == 'A')
            if (timovi[i].brojPoena > pobednik.brojPoena)
                pobednik = timovi[i];

    printf("\nAFC North:\nime: %s\ngrad: %s\nbroj bodova: %d\n", pobednik.imeKluba, pobednik.grad, pobednik.brojPoena);

    // AFC East AFC East AFC East AFC East AFC East

    pobednik.brojPoena = 0;

    for (i = 0; i < brTimova; i++)
        if (timovi[i].konDiv.divizija[0] == 'E' && timovi[i].konDiv.konferencija[0] == 'A')
            if (timovi[i].brojPoena > pobednik.brojPoena)
                pobednik = timovi[i];

    printf("\nAFC East:\nime: %s\ngrad: %s\nbroj bodova: %d\n", pobednik.imeKluba, pobednik.grad, pobednik.brojPoena);

    // NFC South NFC South NFC South NFC South NFC South

    pobednik.brojPoena = 0;

    for (i = 0; i < brTimova; i++)
        if (timovi[i].konDiv.divizija[0] == 'S' && timovi[i].konDiv.konferencija[0] == 'N')
            if (timovi[i].brojPoena > pobednik.brojPoena)
                pobednik = timovi[i];

    printf("\nNFC South:\nime: %s\ngrad: %s\nbroj bodova: %d\n", pobednik.imeKluba, pobednik.grad, pobednik.brojPoena);

    // NFC West NFC West NFC West NFC West NFC West

    pobednik.brojPoena = 0;

    for (i = 0; i < brTimova; i++)
        if (timovi[i].konDiv.divizija[0] == 'W' && timovi[i].konDiv.konferencija[0] == 'N')
            if (timovi[i].brojPoena > pobednik.brojPoena)
                pobednik = timovi[i];

    printf("\nNFC West:\nime: %s\ngrad: %s\nbroj bodova: %d\n", pobednik.imeKluba, pobednik.grad, pobednik.brojPoena);

    // NFC North NFC North NFC North NFC North NFC North

    pobednik.brojPoena = 0;

    for (i = 0; i < brTimova; i++)
        if (timovi[i].konDiv.divizija[0] == 'N' && timovi[i].konDiv.konferencija[0] == 'N')
            if (timovi[i].brojPoena > pobednik.brojPoena)
                pobednik = timovi[i];

    printf("\nNFC North:\nime: %s\ngrad: %s\nbroj bodova: %d\n", pobednik.imeKluba, pobednik.grad, pobednik.brojPoena);

    // NFC East NFC East NFC East NFC East NFC East

    pobednik.brojPoena = 0;

    for (i = 0; i < brTimova; i++)
        if (timovi[i].konDiv.divizija[0] == 'E' && timovi[i].konDiv.konferencija[0] == 'N')
            if (timovi[i].brojPoena > pobednik.brojPoena)
                pobednik = timovi[i];

    printf("\nNFC East:\nime: %s\ngrad: %s\nbroj bodova: %d\n", pobednik.imeKluba, pobednik.grad, pobednik.brojPoena);

    printf("\n");
}
