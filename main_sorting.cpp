#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <math.h>
#include <string>
#include <fstream>

using namespace std;

void swap(int *x, int *y){
    int aux = *x;
    *x = *y;
    *y = aux;
}


void selectionSort(int *arr, int n){
    for (int i=0;i<n;i++){
        int min_index = i;
        for (int j=i;j<n;j++){
            if (arr[j]<arr[min_index]){
                min_index = j;
            }
        }
        swap(&arr[i], &arr[min_index]);
    }
}

int *merge(int *arr_izq, int *arr_der, int n_izq, int n_der){
    int n_merged = n_izq+n_der;
    int *merged = new int[n_merged];
    int i=0, j=0, k=0;
    while(i<n_izq && j<n_der){
        if(arr_izq[i]<arr_der[j]){
            merged[k] = arr_izq[i];
            i++;
        }else{
            merged[k] = arr_der[j];
            j++;
        }
        k++;
    }

    // Vacíar en merged los elementos restantes.
    if(i<n_izq){
        // Vaciar arr_izq en merged
        for(int i_aux=i;i_aux<n_izq;i_aux++){
            merged[k] = arr_izq[i_aux];
            k++;
        }
    }
    if(j<n_der){
        // Vaciar arr_izq en merged
        for(int j_aux=j;j_aux<n_der;j_aux++){
            merged[k] = arr_der[j_aux];
            k++;
        }
    }
    return merged;
}

int *mergeSort(int *arr, int n){
    if (n<=1) return arr;
    int mitad = n/2;
    int n_izq = mitad;
    int n_der = n-mitad;
    int *arr_izq = mergeSort(arr, n_izq);
    int *arr_der = mergeSort(arr+n_izq, n_der);
    return merge(arr_izq, arr_der, n_izq, n_der);
}

int partition(int *arr, int n){
    int p = arr[0];
    int i = 1;
    for (int j=1;j<n;j++){
        if(arr[j]<p){
            swap(&arr[j],&arr[i]);
            i++;
        }
    }
    swap(&arr[0],&arr[i-1]);
    return i-1;
}

void quickSort(int *arr, int n){
    if (n<=1) return;
    int pivot_index = partition(arr, n); // Obtener el pivot
    quickSort(&arr[0], pivot_index);  // Ordenar lado izquierdo
    quickSort(&arr[pivot_index+1], n-pivot_index-1);  //Ordenar lado derecho
}

int main()
{
    double *time_ss = new double[40];
    double *time_qs = new double[40];
    double *time_ms = new double[40];
    double *time_s = new double[40];

    for(int n=1;n<41;n++){
        string filename = "Arreglos20//Arreglo_n"+to_string(n)+"_tot20.txt";
        ifstream fr(filename, ifstream::in);

        if(fr.is_open()){
            int largo, tot_rep;
            fr >> largo;
            fr >> tot_rep;
            int inicio_stream = fr.tellg();

            {
            // Creamos una matriz cuyas filas son los tot_rep arreglos guardados en el archivo a leer
            int **arreglos = new int*[tot_rep];
            for(int rep=0;rep<tot_rep;rep++){
                arreglos[rep] = new int[largo];
                for(int i=0;i<largo;i++){
                    fr >> arreglos[rep][i];
                }
            }

            // Ahora, en arreglos[i] tenemos el i-ésimo arreglo del archivo .txt
            // Midamos el tiempo de cada método:

            // SelectionSort

            clock_t start = clock();
            for(int i=0;i<tot_rep;i++){
                selectionSort(arreglos[i], largo);
            }
            delete(arreglos);
            // Guardamos el tiempo promedio de cada quickSort
            time_ss[n] = (((double)clock() - (double)start) / CLOCKS_PER_SEC) / tot_rep;
            }

            // Volvemos a leer el archivo (pues la matriz "arreglos" había quedado ordenada y repetimos el proceso para los demás métodos.

            {
            // mergeSort:
            fr.clear();
            fr.seekg(inicio_stream, ios::beg);

            int **arreglos = new int*[tot_rep];
            for(int rep=0;rep<tot_rep;rep++){
                arreglos[rep] = new int[largo];
                for(int i=0;i<largo;i++){
                    fr >> arreglos[rep][i];
                }
            }

            clock_t start = clock();
            for(int i=0;i<tot_rep;i++){
                auto arreglo_aux = mergeSort(arreglos[i], largo);
            }
            delete(arreglos);

            time_ms[n] = (((double)clock() - (double)start) / CLOCKS_PER_SEC) / tot_rep;
            }

            {
            // quickSort:
            fr.clear();
            fr.seekg(inicio_stream, ios::beg);

            int **arreglos = new int*[tot_rep];
            for(int rep=0;rep<tot_rep;rep++){
                arreglos[rep] = new int[largo];
                for(int i=0;i<largo;i++){
                    fr >> arreglos[rep][i];
                }
            }

            clock_t start = clock();
            for(int i=0;i<tot_rep;i++){
                quickSort(arreglos[i], largo);
            }
            delete(arreglos);

            time_qs[n] = (((double)clock() - (double)start) / CLOCKS_PER_SEC) / tot_rep;
            }

            {
            // Sort de C++:
            fr.clear();
            fr.seekg(inicio_stream, ios::beg);

            int **arreglos = new int*[tot_rep];
            for(int rep=0;rep<tot_rep;rep++){
                arreglos[rep] = new int[largo];
                for(int i=0;i<largo;i++){
                    fr >> arreglos[rep][i];
                }
            }

            clock_t start = clock();
            for(int i=0;i<tot_rep;i++){
                sort(arreglos[i], arreglos[i]+largo);
            }
            delete(arreglos);

            time_s[n] = (((double)clock() - (double)start) / CLOCKS_PER_SEC) / tot_rep;
            }
        }
        fr.close();

        cout << filename << ": \n";
    }

    string selectionSortfile = "TiemposArreglos20//selectionSort_tot20.txt";
    string mergeSortfile = "TiemposArreglos20//mergeSort_tot20.txt";
    string quickSortfile = "TiemposArreglos20//quickSort_tot20.txt";
    string cppSortfile = "TiemposArreglos20//cppSort_tot20.txt";

    ofstream fw_ss(selectionSortfile, ofstream::out);
    if(fw_ss.is_open()){
        for(int i=0;i<40;i++){
            fw_ss << time_ss[i] << ", ";
        }
    }
    fw_ss.close();

    ofstream fw_ms(mergeSortfile, ofstream::out);
    if(fw_ms.is_open()){
        for(int i=0;i<40;i++){
            fw_ms << time_ms[i] << ", ";
        }
    }
    fw_ms.close();

    ofstream fw_qs(quickSortfile, ofstream::out);
    if(fw_qs.is_open()){
        for(int i=0;i<40;i++){
            fw_qs << time_qs[i] << ", ";
        }
    }
    fw_qs.close();

    ofstream fw_s(cppSortfile, ofstream::out);
    if(fw_s.is_open()){
        for(int i=0;i<40;i++){
            fw_s << time_s[i] << ", ";
        }
    }
    fw_s.close();


    // Tarda 1121 s en correr.
    return 0;
}
