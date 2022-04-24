#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <bits/stdc++.h>
#include <math.h>
#include <string>
#include <fstream>

using namespace std;

void generateRandomArray(int *arr, int n){
    for(int i=0;i<n;i++){
        arr[i] = rand() % n + -n;
    }
}

void generateDecArray(int *arr, int n){
    for(int i=0;i<n;i++){
        arr[i] = n-i;
    }
}

void generateCreArray(int *arr, int n){
    for(int i=0;i<n;i++){
        arr[i] = i;
    }
}

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
    int mediciones;
    cout << "Ingrese cantidad de mediciones: ";
    cin >> mediciones;

    int repeticiones;
    cout << "Ingrese repeticiones por medición: ";
    cin >> repeticiones;

    cout << "---- Comienzan las mediciones con algoritmos de ordenamiento ----\n";

    // Vectores que almacenearán los tiempos
    double time_rss[mediciones];
    double time_rqs[mediciones];
    double time_rms[mediciones];
    double time_rs[mediciones];

    double time_dss[mediciones];
    double time_dqs[mediciones];
    double time_dms[mediciones];
    double time_ds[mediciones];

    for(int i=0;i<mediciones;i++){
        cout << "Medición " << i << endl;
        int n = pow(2,i);    //Tamaño del arreglo

        // Orden Aleatorio:
        int arr_ran[n];
        generateRandomArray(arr_ran, n);

        // QuickSort
        clock_t start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            auto arr_4_quickSort = arr_ran;
            quickSort(arr_4_quickSort, n);
        }
        time_rqs[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        // MergeSort
        start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            auto arr_4_mergeSort = arr_ran;
            int *mergesort = mergeSort(arr_4_mergeSort, n);
        }
        time_rms[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        // SelectionSort
        start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            auto arr_4_selectionSort = arr_ran;
            selectionSort(arr_4_selectionSort, n);
        }
        time_rss[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        // sort C++
        start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            auto arr_4_cppSort = arr_ran;
            std::sort(arr_4_cppSort, arr_4_cppSort+n);
        }
        time_rs[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        cout << "Orden aleatorio terminado \n";

        // Orden Decreciente:
        int arr_dec[n];
        generateDecArray(arr_dec, n);

        // QuickSort
        start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            auto arr_4_quickSort = arr_dec;
            quickSort(arr_4_quickSort, n);
        }
        time_dqs[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        // MergeSort
        start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            auto arr_4_mergeSort = arr_dec;
            int *mergesort = mergeSort(arr_4_mergeSort, n);
        }
        time_dms[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        // SelectionSort
        start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            auto arr_4_selectionSort = arr_dec;
            selectionSort(arr_4_selectionSort, n);
        }
        time_dss[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        // sort C++
        start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            auto arr_4_cppSort = arr_dec;
            std::sort(arr_4_cppSort, arr_4_cppSort+n);
        }
        time_ds[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        cout << "Orden decreciente terminado \n";
    }

    // Guardamos los tiempos en archivos .txt

    ofstream fw_ran("Tiempos_arreglo_aleatorio.txt", std::ofstream::out);
    if(fw_ran.is_open()){
        for(int i=0;i<mediciones;i++){
            fw_ran << time_rss[i] << " ";
        }
        fw_ran << "\n";
        for(int i=0;i<mediciones;i++){
            fw_ran << time_rqs[i] << " ";
        }
        fw_ran << "\n";
        for(int i=0;i<mediciones;i++){
            fw_ran << time_rms[i] << " ";
        }
        fw_ran << "\n";
        for(int i=0;i<mediciones;i++){
            fw_ran << time_rs[i] << " ";
        }
    }

    ofstream fw_dec("Tiempos_arreglo_decreciente.txt", std::ofstream::out);
    if(fw_dec.is_open()){
        for(int i=0;i<mediciones;i++){
            fw_dec << time_dss[i] << " ";
        }
        fw_dec << "\n";
        for(int i=0;i<mediciones;i++){
            fw_dec << time_dqs[i] << " ";
        }
        fw_dec << "\n";
        for(int i=0;i<mediciones;i++){
            fw_dec << time_dms[i] << " ";
        }
        fw_dec << "\n";
        for(int i=0;i<mediciones;i++){
            fw_dec << time_ds[i] << " ";
        }
    }
    return 0;
}

