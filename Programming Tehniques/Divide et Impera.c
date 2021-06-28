#include <stdio.h>
#include <stdlib.h>
int verificare(int nr)
{

    if (nr ==0 || nr<0 )
        return 0;
    if(nr==1)
        return 1;
    while(nr!=1)
    {
        if (nr%2==1)
            return -1;
        nr/=2;

    }
    return 1;
}

int divide_matrice(int left, int right, int lineUp, int lineDown, int **matrix)
{
    int line, colum, middle, lineMiddle;
    if (left==right)
    {
        if(right%2==1 && lineUp%2==0)
            matrix[lineUp][left]=1;
        return 1;
    }
    else
    {
        middle=(left+right)/2;
        lineMiddle=(lineUp+lineDown)/2;
        // if(verificare(right+1) &&   verificare(left) && verificare(lineUp+1) && verificare(lineDown+1) )
        if( (verificare(left) && verificare(right+1) && verificare(lineUp+1)&& verificare(lineDown+1)  && lineDown<left)||(lineUp/2%2==0 && left/2%2==1))
        {


            divide_matrice(left, middle, lineUp, lineMiddle, matrix);
            divide_matrice(left, middle, lineMiddle+1, lineDown, matrix);
            divide_matrice(middle+1, right, lineMiddle+1,lineDown, matrix);
            for(line=lineUp; line<=lineDown; line++)
                for(colum=left; colum<=right; colum++)
                    matrix [line][ colum] =1;

        }
        else
        {
            divide_matrice(left, middle, lineUp, lineMiddle, matrix);
            divide_matrice(middle+1, right, lineUp, lineMiddle, matrix);
            divide_matrice(left, middle, lineMiddle+1, lineDown, matrix);
            divide_matrice(middle+1, right, lineMiddle+1,lineDown, matrix);
        }
    }
}
int main()
{
    FILE *fIntrare=fopen("date.in", "r");
    FILE *fIesire=fopen("date.out", "w");

    int n;
    if (fIntrare==NULL)
        printf ("Eroare!");
    fscanf(fIntrare,"%d",&n);
    printf("%d \n",n);
    int size=1<<n;
    //printf("%d",dim);
    int i,j;

    int **matrix=(int**)calloc(size,sizeof(int*));
    for(i=0; i<size; i++)
        matrix[i]=(int*)calloc(size, sizeof(int));

    int left=0, right=size-1;
    //printf("%d %d ", left, right);
    int lineUp=left, lineDown=size-1;
    //printf("%d %d",lineUp, lineDown);
    int middle=size/2;


    divide_matrice(left, right, lineUp, lineDown, matrix);

    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            fprintf(fIesire,"%d ", matrix[i][j]);

        }
        fprintf(fIesire, "%s","\n");
    }

    fclose(fIntrare);
    fclose(fIesire);

}
