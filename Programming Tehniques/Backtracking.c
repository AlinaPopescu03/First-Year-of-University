#include <stdio.h>
#include <stdlib.h>


int s[100], ap[100], N;
FILE *in;
FILE *out;

void afis()
{
    int i;
    for (i=1; i<=3; i++)
        fprintf(out, "%d ", s[i]);
    fprintf(out, "\n");
}

int valid(int k)
{
    if (ap[s[k]]!=0)
        return 0;
    // verificam daca culoare din mijloc are indice par
    if (k==2 &&s[k]%2==0)
        return 0;
    return 1;
}

void bkt(int k)

{
    int i;
    if(k==4)
        afis();
    else
    {

        for(i=1; i<=N; i++)
        {
            s[k]=i;
            if(valid(k))
            {
                ap[i]=1;
                bkt(k+1);
                ap[i]=0;
            }
        }
    }
}
int main()
{

    in=fopen("date.in", "r");
    out=fopen("date.out", "w");
    // Citire N
    fscanf(in,"%d", &N);
    // Apelam functia bt
    if (N==2)
        fprintf(out, "Nu sunt suficiente culori");
    else
        bkt(1);
    fclose(in);
    fclose(out);
    return 0;

}
