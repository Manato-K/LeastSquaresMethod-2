/*LeastSquaresMethod2*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yacobi(float A[3][3], float X[3], float B[3])
{
    int i, j;
    float tmp, err;
    do
    {
        err=0.0;
        for(i=0; i<3; i++){
            tmp=B[i];
            for(j=0; j<3; j++)
                if(i!=j) tmp-=A[i][j]*X[j];
            tmp/=A[i][j];
            err+=fabs(tmp-X[i]);
        }
    } while (err>1.0e-6);
}

int main(void)
{
    int i, j, m;
    float sx[5], sy[5], tx, ty, t;
    float A[3][3], X[3], B[3];
    float x[100], y[100];
    FILE *fp;

    if((fp=fopen("2011125-2.dat","r"))==NULL){
        printf("cannot open file/n");
        exit(0);
    }
    i=0;
    while (fscanf(fp, "%f %f", &x[i], &y[i])!=EOF)
        i++;
    m=i;
    fclose(fp);

    for(i=0; i<5; i++) sx[i]=sy[i]=0.0;
    for(i=0; i<m; i++){
        for(j=0; j<5; j++){
            if(j==0) tx=1.0; else tx*=x[i];
            sx[j]+=tx;
        }
        for(j=0; j<3; j++){
            if(j==0) ty=y[i]; else ty*=x[i];
            sy[j]+=ty;
        }
        for(j=0; j<3; j++) A[i][j]=sx[i+j];
        X[i]=1.0;
        B[i]=sy[i];
    }
    yacobi(A, X, B);
    for(i=0; i<3; i++){
        if(i==0) printf("y=%.4f",X[0]);
        else{
            if(X[i]>0.0) printf("+");
            printf("%.4f", X[i]);
        }
        if(i>1) printf("^%d",i);
    }
    printf("/n");
    for(i=0; i<m; i++){
        t=X[2];
        for(j=1; j>=0; j--) t=t*x[i]+X[j];
        printf("%7.4f %7.4f(%7.4f)/n",x[i], y[i], t);
    }
}