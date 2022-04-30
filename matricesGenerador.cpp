#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <math.h>

using namespace std;

int main()
{
    int n_lim = 12;  // Cantidad de dimensiones a probar para las matrices. 2^1, 2^2, ..., 2^n_lim.
    int tot = 20; // Total de pares de matrices que se usarán para medir el tiempo por cada dimensión

    for(int n=1;n<n_lim+1;n++){
        int dim = pow(2,n);
        string filename = "Matrices20//Matrices_n"+to_string(n)+"_tot"+to_string(tot)+".txt";

        ofstream fw(filename, std::ofstream::out);
        if(fw.is_open()){
            fw << dim << "\n" << tot << "\n";
            // 2*tot matrices para poder hacer tot multiplicaciones.
            for(int t=0;t<2*tot;t++){
                for(int i=0;i<dim;i++){
                    for(int j=0;j<dim;j++){
                        fw << rand() % 19 + -9 << " ";
                    }
                    fw << "\n";
                }
            }
        }
        fw.close();
    cout << "Progreso: " << n << "/" << n_lim << endl;
    }

    // Tardó 212 segundos
}
