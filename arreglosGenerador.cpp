#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

int main()
{
    int n_lim = 40;  // Cantidad de largos a probar para los arreglos. Desde 1000 y de 1000 en 1000 hasta 1000*n_lim.
    int tot = 20; // Total de arreglos que se usarán para medir el tiempo por cada largo

    for(int n=1;n<n_lim+1;n++){
        int largo = 1000*n;
        string filename = "Arreglos20//Arreglo_n"+to_string(n)+"_tot"+to_string(tot)+".txt";

        ofstream fw(filename, std::ofstream::out);
        if(fw.is_open()){
            fw << largo << "\n" << tot << "\n";
            for(int t=0;t<tot;t++){
                for(int i=0;i<largo;i++){
                    fw << rand() % 19 + -9 << " ";
                }
                fw << "\n";
            }
        }
        fw.close();
    cout << "Progreso: " << n << "/" << n_lim << endl;
    }    
}
