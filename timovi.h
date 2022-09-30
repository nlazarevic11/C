#ifndef TIMOVI_H_INCLUDED
#define TIMOVI_H_INCLUDED

typedef struct {
    char konferencija[5];
    char divizija[10];
} KonDiv;

typedef struct {
    char imeKluba[100];
    char grad[100];
    int brojPoena;
    KonDiv konDiv;
} Tim;

int beskonacniMeni();
int ucitajFajl(Tim timovi[]);
void ispisiSvakiTim(Tim timovi[], int brTimova);
void cuvanjeUFajl(Tim timovi[], int brTimova);
int dodajNoviTim(Tim timovi[], int brTimova);
int brisiTim(Tim timovi[], int brTimova);
void sortirajPoBrPoena(Tim timovi[], int brTimova);
void sortirajPoNazivu(Tim timovi[], int brTimova);
void ispisiPobednikeDivizija(Tim timovi[], int brTimova);

#endif // TIMOVI_H_INCLUDED
