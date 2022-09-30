#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "timovi.h"

int main(){

    int opcija, brTimova = 0;
    Tim timovi[50];

    while (1) {

        opcija = beskonacniMeni();

        switch (opcija) {
            case 0:
                printf("Kraj programa!\n");
                return 0;
            case 1:
                brTimova = ucitajFajl(timovi);
                break;
            case 2:
                cuvanjeUFajl(timovi, brTimova);
                break;
            case 3:
                brTimova = dodajNoviTim(timovi, brTimova);
                cuvanjeUFajl(timovi, brTimova);
                break;
            case 4:
                brTimova = brisiTim(timovi, brTimova);
                cuvanjeUFajl(timovi,brTimova);
                break;
            case 5:
                ispisiSvakiTim(timovi, brTimova);
                break;
            case 6:
                sortirajPoBrPoena(timovi, brTimova);
                ispisiSvakiTim(timovi, brTimova);
                break;
            case 7:
                sortirajPoNazivu(timovi, brTimova);
                ispisiSvakiTim(timovi, brTimova);
                break;
            case 8:
                ispisiPobednikeDivizija(timovi, brTimova);
                break;
            default:
                printf("Neispravan unos!Pokusajte ponovo:\n");
                break;
        }
    }


    return 0;
}
