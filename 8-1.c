#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

void saisyou2zyou(const char *filepath,int data,int N){
    double x[data],y[data],F[N+1][N+2],q,b,c;
    int i,j,n,k;
    FILE *fp;

    if( (fp=fopen(filepath,"r"))==NULL ) {
        printf("cannot open file.\n");
        exit(0);
    }
    for(i=0;i<data;i++){
        fscanf(fp,"%lf",&x[i]);
        fscanf(fp,"%lf",&y[i]);
    }
    
    fclose(fp);
    for(i=0;i<(N+1);i++)
        for(j=0;j<(N+1);j++)
                F[i][j]=0.0;

    for(i=0;i<(N+1);i++){
        for(j=0;j<(N+1);j++)
            for(n=0;n<data;n++)
                F[i][j]+=pow(x[n],j+i);
                
        for(n=0;n<data;n++)
            F[i][N+1]+=y[n]*pow(x[n],i);
    }
    
    for(i=0;i<N+1;i++){
        for(j=0;j<N+2;j++)
            printf(" %7.5lf",F[i][j]);
        printf("\n");
    }
    //cholesky(N+1,F);
    for(i=0;i<N+1;i++) {
        if(F[i][i]==0.0){
            for(j=i;j<N+2;j++){
                b=F[i][j];
                F[i][j]=F[i+1][j];
                F[i+1][j]=b;}
        }
        q=F[i][i];

        for(j=i;j<N+2;j++) F[i][j]/=q;

        for(k=0;k<N+1;k++) {
            if(k!=i) {
                q=F[k][i];
                for(j=i;j<N+2;j++) F[k][j]-=q*F[i][j];
            }
        }
    }
    for(i=0;i<N+1;i++) {
        for(j=0;j<N+2;j++) printf("%6.2f",F[i][j]);
        printf("\n");
    }
    printf("\n");
    printf("%6.2f",F[0][N+1]);
    
    for(i=1;i<N+1;i++) printf("+%6.2fx^(%d)",F[i][N+1],i);
    printf("\n\n");

    c=0;

    for(i=0;i<data;i++){
        printf("f(%f)=",x[i]);
        for(j=0;j<N+1;j++)
            c+=F[j][N+1]*pow(x[i],j);
        
        printf("%5.2f(%f)\n",c,y[i]);
        c=0;
    }

}

int main(){
    int N,data;
    N=4;
    data=9;
    saisyou2zyou("text2.txt",data,N);
}


/*
結果
9.00000 18.00000 51.00000 162.00000 548.25000 14.25000
 18.00000 51.00000 162.00000 548.25000 1930.50000 28.50000
 51.00000 162.00000 548.25000 1930.50000 6983.81250 121.31450
 162.00000 548.25000 1930.50000 6983.81250 25761.37500 499.88700
 548.25000 1930.50000 6983.81250 25761.37500 96424.26563 2031.19362
  1.00  0.00  0.00  0.00  0.00  8.00
  0.00  1.00  0.00  0.00  0.00-24.00
  0.00  0.00  1.00  0.00  0.00 22.00
  0.00  0.00  0.00  1.00  0.00 -8.00
  0.00  0.00  0.00  0.00  1.00  1.00

  8.00+-24.00x^(1)+ 22.00x^(2)+ -8.00x^(3)+  1.00x^(4)

f(0.000000)= 8.00(8.000000)
f(0.500000)= 0.56(0.563000)
f(1.000000)=-1.00(-1.000000)
f(1.500000)=-0.44(-0.438000)
f(2.000000)=-0.00(0.000000)
f(2.500000)=-0.44(-0.438000)
f(3.000000)=-1.00(-1.000000)
f(3.500000)= 0.56(0.563000)
f(4.000000)= 8.00(8.000000)
*/