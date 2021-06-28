#include <stdio.h>
#include <stdlib.h>


// Structul in care vom memora datele
struct Programari
{
    int nr_crt;
    int ora_inceput;
    int ora_final;
};

// Citirea datelor din fisier si memorarea lor in struct
void citire(struct Programari *programari, int nrProgramari,FILE *fIntrare)
{
    int i;
    for(i=0; i<nrProgramari; i++)
    {
        fscanf(fIntrare,"%d", &programari[i].nr_crt);
        fscanf(fIntrare,"%d", &programari[i].ora_inceput);
        fscanf(fIntrare,"%d", &programari[i].ora_final);
    }
}
//Functie necesara pentru sortare
int cmp(const void *a, const void *b)
{

    int a1 = ((struct Programari *) a)->ora_final;
    int b1 = ((struct Programari *) b)->ora_final;
    if(a1 < b1)
        return -1;
    if(a1 > b1)
        return 1;
    return 0;

}
//Greedy
void greedy(struct Programari *programari, int nrProgramari, FILE *fIesire)
{

    //Sortam in ordine crescatoare dupa oraFinal
    qsort(programari, nrProgramari, sizeof(struct Programari), cmp);

    //Luam o variabila auxiliara care retine ultimul spectacol din lista
    struct Programari ultimaProgramare = programari[0];

    //Afisam prima programare dupa sortare
    fprintf(fIesire, "%d\n", programari[0].nr_crt);

    //Verificam ce spectacol are oraInceput mai mare sau egala cu oraFinal a ultimelei programri din lista si il afisam
    int i;
    for ( i = 1; i < nrProgramari; i++)
    {
        if (programari[i].ora_inceput >= ultimaProgramare.ora_final)
        {
            fprintf(fIesire, "%d\n", programari[i].nr_crt);
            ultimaProgramare = programari[i];
        }
    }
}


    int main()
    {
        // Decarare fisiere si deschidere
        FILE *fIntrare=fopen("date.in", "r");
        FILE *fIesire=fopen("date.out", "w");


        int nrProgramari;
        fscanf(fIntrare, "%d", &nrProgramari);

        // Alocarea dinamica a memoriei
        struct Programari *programari=malloc(nrProgramari*sizeof(struct Programari));

        // Functia de citire a prograamrilor
        citire(programari, nrProgramari, fIntrare);


        //Apelez functia de Greedy
        greedy(programari, nrProgramari, fIesire);

        //Inchid fisierele de Iesire si Intrare
        fclose(fIesire);
        fclose(fIntrare);

        //Eliberez memoria alocata dinamic array-ului de spectacole
        free(programari);
    }



