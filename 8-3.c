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
                F[i][j]+=pow(log(x[n]),j+i);
                
        for(n=0;n<data;n++)
            F[i][N+1]+=log(y[n])*pow(log(x[n]),i);
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
    for(i=1;i<N+1;i++)printf("y=%.4fx^(%.4f)",F[0][2],F[1][2]);
    printf("\n\n");

    c=0;

    for(i=0;i<data;i++){
        printf("f(%f)=",x[i]);
        c=F[0][2]*pow(x[i],F[1][2]);        
        printf("%5.2f(%f)\n",c,y[i]);
    }

}

int main(){
    int N,data;
    data=5;
    saisyou2zyou("text4.txt",data);
}

/*
 5.00000 0.20604 0.02917
 0.20604 1.62398 4.36332
  1.00  0.00 -0.11
  0.00  1.00  2.70

y=0.8999x^(2.7002)

f(0.400000)= 0.08(0.075800)
f(0.800000)= 0.49(0.492700)
f(1.200000)= 1.47(1.472400)
f(1.600000)= 3.20(3.201600)
f(2.000000)= 5.85(5.848200)
*/