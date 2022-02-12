#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

 
void saisyou2zyou(const char *filepath,int data){
    double x[data],y[data],F[2][3],q,b,c;
    int i,j,n,k,N;
    N=1;
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
        for(j=0;j<(N+2);j++)
                F[i][j]=0.0;

    for(i=0;i<(N+1);i++){
        for(j=0;j<(N+1);j++)
            for(n=0;n<data;n++)
                F[i][j]+=pow(x[n],j+i);
                
        for(n=0;n<data;n++)
            F[i][N+1]+=log(y[n])*pow(x[n],i);
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
    F[0][2]=exp(F[0][2]);
    for(i=1;i<N+1;i++)printf("y=%.4fe^(%.4fx)",F[0][2],F[1][2]);
    printf("\n\n");

    c=0;

    for(i=0;i<data;i++){
        printf("f(%f)=",x[i]);
        c=F[0][2]*exp(F[1][2]*x[i]);        
        printf("%5.2f(%f)\n",c,y[i]);
    }

}

int main(){
    int N,data;
    data=6;
    saisyou2zyou("text3.txt",data);
}

/*
結果
6.00000 21.00000 10.32792
21.00000 91.00000 43.34501
  1.00  0.00  0.28
  0.00  1.00  0.41

y=1.3256e^(0.4113x)

f(1.000000)= 2.00(1.500000)
f(2.000000)= 3.02(3.446000)
f(3.000000)= 4.55(5.606000)
f(4.000000)= 6.87(7.917000)
f(5.000000)=10.36(10.348000)
f(6.000000)=15.63(12.879000)
*/