#include <omp.h>
#include <math.h>


void initialize(int nx, int ny, double *v, double hx){
#pragma omp parallel for

for(int y=0; y<=ny; y++){
    for(int x=0; x<=nx; x++){
        if(y==nx){
            v[y*(nx+1)+x]=sin(2*M_PI*hx)*sinh(2*M_PI);
        }else{
            v[y*(nx+1)+x]= 0;
        }       
    }
}

}


int main(int argc, char* argv[]){

if (argc < 5) {
        std::cout << "Usage: rgbs nx ny c" << std::endl;
        return -1;
    }
int nx = argv[1];
int ny = argv[2]; 
int c = argv[3];
int theads = argv[4];

double *values = new double[(nx+1)*(ny+1)];
// nx und ny gibt Anzahl der Intervalle an, die entstehen -> es gibt nx+1 & ny+1 Punkte in jede Richtung
double hx = 2.0/nx; 
double hy = 1.0/ny; 

omp_set_num_threads(threads);

initialize(nx, ny, values, hx);

// LGS mit Hilfe von red-black Gauss-Seidel lösen, dazu erstmal normal Gauss-Seidel zum laufen bringen, danach red-black
// Gauss-Seidel verwendet neue und alte Werte --> man rechnet alles auf der gleichen Matrix


}    