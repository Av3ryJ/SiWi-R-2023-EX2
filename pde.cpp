#include <omp.h>
#include <math.h>
#include <iostream>
#include <fstream>

void print_matrix(int nx, int ny, double *v) {
    for(int y=0; y<=ny; y++){
        for(int x=0; x<=nx; x++){
            std::cout << v[y*(nx+1)+x] << " ";
            }
        std::cout << std::endl;
    }
}


void initialize(int nx, int ny, double *v, double hx){
double sinhyb = sinh(2*M_PI);
#pragma omp parallel for
for(int y=0; y<=ny; ++y){
    for(int x=0; x<=nx; ++x){
        if(y==ny){
            v[y*(nx+1)+x]= sin(2*M_PI*x*hx)*sinhyb;
        }else{
            v[y*(nx+1)+x]= 0;
        }       
    }
}
print_matrix(nx, ny, v);
}


int main(int argc, char* argv[]){

if (argc < 4) {
        std::cout << "Usage: rgbs nx ny c" << std::endl;
        return -1;
    }
int nx = atoi(argv[1]); // number of intervalls in x-directon
int ny = atoi(argv[2]); // number of intervalls in y-directon
int c = atoi(argv[3]); // number of iterations

/*if (argc > 4) {
    int threads = atoi(argv[4]); // number of threads omp shall use
    //omp_set_num_threads(threads);
}

*/

double *values = new double[(nx+1)*(ny+1)];
// nx und ny gibt Anzahl der Intervalle an, die entstehen -> es gibt nx+1 & ny+1 Punkte in jede Richtung
double hx = 2.0/nx; // lenght of one intervall in x-direction
double hy = 1.0/ny; // lenght of one intervall in y-direction


initialize(nx, ny, values, hx);


// LGS mit Hilfe von red-black Gauss-Seidel loesen, dazu erstmal normal Gauss-Seidel zum laufen bringen, danach red-black
// Gauss-Seidel verwendet neue und alte Werte --> man rechnet alles auf der gleichen Matrix

double hx_squared = hx*hx;
double hy_squared = hy*hy;
double pi_squared = M_PI*M_PI;
double factor = 1*(2/hx_squared + 2/hy_squared + 4*pi_squared);
double xFactor = -1*hx_squared;
double yFactor = -1*hy_squared;

double f_xy;

for (int iteration = 0; iteration < c; ++iteration) {
    int rowlength = nx+1;
    //#pragma omp parallel for
    for (int row = 1; row < ny; ++row) { // row is y col is x
        f_xy = 4*pi_squared*sinh(2*M_PI*row*hy);
        for (int col = 1; col < nx; ++col) {    // nicht ueber Rand iterieren
            if ((row+col)%2  == 0) {
                // RED
                //std::cout << "RED" << std::endl;
                values[col + row*rowlength] = 1.0/4 * ((hx*hy*f_xy*sin(2*M_PI*col*hx))+
                        (values[(col-1) + row*rowlength]+values[(col+1) + row*rowlength]+values[col + (row-1)*rowlength]+values[col + (row+1)*rowlength]));
            }
        }
    }

    //pragma omp parallel for
    for (int row = 1; row < ny; ++row) { // row is y col is x
        f_xy = 4*pi_squared*sinh(2*M_PI*row*hy);
        for (int col = 1; col < nx; ++col) {    // nicht ueber Rand iterieren
            if ((row+col)%2  == 1) {
                // BLACK
                //std::cout << "BLACK" << std::endl;
                //std::cout << col+row*rowlength << std::endl;
                values[col + row*rowlength] = 1.0/4 * ((hx*hy*f_xy*sin(2*M_PI*col*hx))+
                                                       (values[(col-1) + row*rowlength]+values[(col+1) + row*rowlength]+values[col + (row-1)*rowlength]+values[col + (row+1)*rowlength]));
            }
        }
    }
}
std::cout << std::endl << "Solution:" << std::endl;
print_matrix(nx, ny, values);

std::ofstream fileO ("solution.txt");
    for(int i = 0; i<((nx+1)*(ny+1)); ++i) {
        fileO << values[i] << "\n";
    }
    fileO.close();

}    