#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <fstream>

using namespace std;

void printMatriz(int **mat, int n){
	for(int i=0;i<n;i++){
		for(int j=0; j<n;j++){
			cout << mat[i][j] << " ";
		}
		cout << endl;
	}
}

int **crearMatriz(int n){
	int **mat = new int*[n];
	for(int i=0;i<n;i++){
		mat[i]=new int[n];
	}
	return mat;
}

int **generarMatriz(int n){
    int **mat = crearMatriz(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            mat[i][j] = rand() % 100 + -50;
        }
    }
    return mat;
}

int **multCubicaMatriz(int **mat1, int **mat2, int n){
	int **mat3 = crearMatriz(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			// Se calcula el elemento mat3[i][j]:
			int sum = 0;
			for(int k=0;k<n;k++){
				sum = sum +mat1[i][k]*mat2[k][j];
			}
			mat3[i][j] = sum;
		}
	}
	return mat3;
}

int **multTranspMatriz(int **mat1, int **mat2, int n){
    // Primero transponemos mat2:
    int **mat2T = crearMatriz(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            mat2T[i][j] = mat2[j][i];
        }
    }
    // Multiplicamos "normalmente" utilizando la localidad de los datos
    int **mat3 = crearMatriz(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int sum = 0;
			for(int k=0;k<n;k++){
				sum = sum +mat1[i][k]*mat2T[j][k];
			}
			mat3[i][j] = sum;
		}
	}
	return mat3;
}

int **getQ1(int **mat, int n){
    // Para obtener la "esquina superior izquierda" de una matriz.
    int **Q1 = crearMatriz(n/2);
    for(int i=0;i<n/2;i++){
        for(int j=0;j<n/2;j++){
            Q1[i][j] = mat[i][j];
        }
    }
    return Q1;
}

int **getQ2(int **mat, int n){
    // Para obtener la "esquina superior derecha" de una matriz.
    int **Q2 = crearMatriz(n/2);
    for(int i=0;i<n/2;i++){
        for(int j=n/2;j<n;j++){
            Q2[i][j-n/2] = mat[i][j];
        }
    }
    return Q2;
}

int **getQ3(int **mat, int n){
    // Para obtener la "esquina inferior izquierda" de una matriz.
    int **Q3 = crearMatriz(n/2);
    for(int i=n/2;i<n;i++){
        for(int j=0;j<n/2;j++){
            Q3[i-n/2][j] = mat[i][j];
        }
    }
    return Q3;
}

int **getQ4(int **mat, int n){
    // Para obtener la "esquina inferior derecha" de una matriz.
    int **Q4 = crearMatriz(n/2);
    for(int i=n/2;i<n;i++){
        for(int j=n/2;j<n;j++){
            Q4[i-n/2][j-n/2] = mat[i][j];
        }
    }
    return Q4;
}

int **matSuma(int **mat1, int **mat2, int n){
    int **mat_suma = crearMatriz(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            mat_suma[i][j] = mat1[i][j] + mat2[i][j];
        }
    }
    return mat_suma;
}

int **matResta(int **mat1, int **mat2, int n){
    int **mat_resta = crearMatriz(n);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            mat_resta[i][j] = mat1[i][j] - mat2[i][j];
        }
    }
    return mat_resta;
}

int **strassen(int **mat1, int **mat2, int n){
    // Supondremos que la dimensión de la matriz es n * n, con n potencia de 2.
    // Creamos A,B,C,D,E,F,G y H, matrices de n/2 * n/2:
    int **A = getQ1(mat1, n);
    int **B = getQ2(mat1, n);
    int **C = getQ3(mat1, n);
    int **D = getQ4(mat1, n);
    int **E = getQ1(mat2, n);
    int **F = getQ2(mat2, n);
    int **G = getQ3(mat2, n);
    int **H = getQ4(mat2, n);
    if(n==2){
        int **mat_producto = crearMatriz(2);
        mat_producto[0][0] = A[0][0]*E[0][0] + B[0][0]*G[0][0];
        mat_producto[0][1] = A[0][0]*F[0][0] + B[0][0]*H[0][0];
        mat_producto[1][0] = C[0][0]*E[0][0] + D[0][0]*G[0][0];
        mat_producto[1][1] = C[0][0]*F[0][0] + D[0][0]*H[0][0];
        return mat_producto;
    }
    int **p1 = strassen(A, matResta(F,H,n/2), n/2);
    int **p2 = strassen(matSuma(A,B,n/2), H, n/2);
    int **p3 = strassen(matSuma(C,D,n/2), E, n/2);
    int **p4 = strassen(D, matResta(G,E,n/2), n/2);
    int **p5 = strassen(matSuma(A,D,n/2), matSuma(E,H,n/2), n/2);
    int **p6 = strassen(matResta(B,D,n/2), matSuma(G,H,n/2), n/2);
    int **p7 = strassen(matResta(A,C,n/2), matSuma(E,F,n/2), n/2);

    // Armar Z
    int **Z1 = matSuma(matSuma(p5, matResta(p4,p2, n/2), n/2), p6, n/2);
    int **Z2 = matSuma(p1,p2,n/2);
    int **Z3 = matSuma(p3,p4,n/2);
    int **Z4 = matSuma(matResta(p5,p3,n/2),matResta(p1,p7,n/2), n/2);

    int **Z = crearMatriz(n);

    for(int i=0;i<n/2;i++){
        for(int j=0;j<n/2;j++){
            Z[i][j] = Z1[i][j];
            Z[i][j+n/2] = Z2[i][j];
            Z[i+n/2][j] = Z3[i][j];
            Z[i+n/2][j+n/2] = Z4[i][j];
        }
    }
    return Z;
}

int main()
{
    int mediciones;
    cout << "Ingrese cantidad de mediciones: ";
    cin >> mediciones;

    int repeticiones;
    cout << "Ingrese repeticiones por medición: ";
    cin >> repeticiones;

    cout << "---- Comienzan las mediciones con algoritmos de multiplicación de matrices ----\n";

    // Vectores que almacenearán los tiempos
    double time_clasic[mediciones];
    double time_mod[mediciones];
    double time_strassen[mediciones];

    for(int i=0;i<mediciones;i++){
        cout << "Medición " << i << endl;
        int n = pow(2,i);    //Tamaño del arreglo

        // Matrices Aleatorio:
        int **mat1 = generarMatriz(n);
        int **mat2 = generarMatriz(n);

        cout << "Clásico " << i << endl;
        // Algoritmo Clásico
        int **mat_pclasic = crearMatriz(n);
        clock_t start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            mat_pclasic = multCubicaMatriz(mat1, mat2, n);
        }
        time_clasic[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        cout << "Modificado " << i << endl;
        // Algoritmo Clásico modificado
        int **mat_pmod = crearMatriz(n);
        start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            mat_pmod = multTranspMatriz(mat1,mat2,n);
        }
        time_mod[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;

        cout << "Strassen " << i << endl;
        // Strassen
        int **mat_pstra = crearMatriz(n);
        start = clock();
        for (int rep=0;rep<repeticiones;rep++){
            mat_pstra = strassen(mat1, mat2, n);
        }
        time_strassen[i] = ((double)clock() - (double)start) / CLOCKS_PER_SEC;
    }

    // Guardamos los tiempos en archivos .txt

    ofstream fw("Tiempos.txt", std::ofstream::out);
    if(fw.is_open()){
        for(int i=0;i<mediciones;i++){
            fw << time_clasic[i] << " ";
        }
        fw << "\n";
        for(int i=0;i<mediciones;i++){
            fw << time_mod[i] << " ";
        }
        fw << "\n";
        for(int i=0;i<mediciones;i++){
            fw << time_strassen[i] << " ";
        }
    }
	return 0;
}
