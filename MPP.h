//
// Created by Paolo on 22-10-2025.
//

#ifndef MPP_H
#define MPP_H
#include <iomanip>
#include <iostream>
using namespace std;

template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* abajo;
    Nodo<T>* derecha;
    int fila;
    int columna;
    Nodo(): dato(T()), derecha(nullptr), abajo(nullptr), fila(0), columna(0) {}
    Nodo(T dato, int fila, int columna) {
        this->dato = dato;
        this->fila = fila;
        this->columna = columna;
        this->abajo = nullptr;
        this->derecha = nullptr;
    }
    T getData() {
        return dato;
    }
    void setData(T dato) {
        this->dato = dato;
    }
    Nodo<T> * getDown() {
        return abajo;
    }
    void setDown(Nodo<T>* down) {
        this->abajo = abajo;
    }
    Nodo<T>* getDerecha() {
        return derecha;
    }
    void setDerecha(Nodo<T>* derecha) {
        this->derecha = derecha;
    }
};


template <typename T>
class MPP {
    private:
    int filas;
    int columnas;
    Nodo<T> ** aRow;
    Nodo<T> ** aCol;
public:
    /**
     * Metodo constructor para la matriz
     * @param filas
     * @param columnas
     */
    MPP(int filas, int columnas) {
        this->filas = filas;
        this->columnas = columnas;

        aRow = new Nodo<T> *[filas + 1];
        aCol = new Nodo<T> *[columnas + 1];

        for (int i = 0; i < filas; i++) {
            aRow[i] = new Nodo<T> [T(),i,0];
            aRow[i]->derecha = aRow[i];
        }
        for (int j = 0; j < columnas; j++) {
            aCol[j] = new Nodo<T>[T(),0,j];
            aCol[j]->abajo = aCol[j];
        }
    }

    /**
     * @return numero de filas de la matriz
     */
    int getFilas() {
        return filas;
    }

    /**
     * @return numero de columnas de la matriz
     */
    int getColumnas() {
        return columnas;
    }

    /**
     * Setter de filas
     * @param filas
     */
    void setFilas(int filas) {
        this->filas = filas;
    }

    /**
     * Setter de columna
     * @param columnas
     */
    void setColumnas(int columnas) {
        this->columnas = columnas;
    }

    /**
     * Metodo para insertar un nuevo nodo dentro de la matriz
     * @param f fila
     * @param c columna
     * @param dato
     */
    void insertar(int f, int c, T dato) {
        // Caso de que la fila o columna sea menor o igual a 0, o que sea mayor que el tamaño de la matriz
        if (f <= 0 || f >= filas || c <= 0 || c >= columnas) {
            cout << "Fuera de rango" << endl;
            return;
        }

        Nodo<T>* nuevo = new Nodo<T>(dato, f, c);

        // Inserción en fila
        Nodo<T>* actualFila = aRow[f];
        while (actualFila->derecha != aRow[f] && actualFila->derecha->columna < c) {
            actualFila = actualFila->derecha;
        }

        if (actualFila->derecha != aRow[f] && actualFila->derecha->columna == c) {
            actualFila->derecha->dato = dato;
            delete nuevo;
            return;
        }

        nuevo->derecha = actualFila->derecha;
        actualFila->derecha = nuevo;

        // Inserción en columna
        Nodo<T>* actualCol = aCol[c];
        while (actualCol->abajo != aCol[c] && actualCol->abajo->fila < f) {
            actualCol = actualCol->abajo;
        }

        nuevo->abajo = actualCol->abajo;
        actualCol->abajo = nuevo;
    }

    /**
     * Metodo para obtener el valor de una casa
     * @param f fila
     * @param c columna
     */
    T get(int f, int c) {
        // Si es un nodo cabecera se retorna un puntero nulo
        if (f == 0 || c == 0) Casa();

        Nodo<T>* actual = aRow[f];
        // Se recorre hasta llegar a la posicion necesaria
        while (actual->derecha != aRow[f] && actual->derecha->columna < c) {
            actual = actual->derecha;
        }
        // Se retorna el valor de la posicion
        if (actual->derecha != aRow[f] && actual->derecha->columna == c) {
            return actual->dato;
        }
        return Casa(); // Si el nodo no existe se retorna un puntero nulo
    }

    void set(int f, int c, T dato) {
        // Si se intenta cambiar un nodo cabecera se retorna
        if (f == 0 || c == 0) return;

        Nodo<T>* actual = aRow[f];
        // Se recorre hasta llegar a la posicion necesaria
        while (actual->derecha != aRow[f] && actual->derecha->columna < c) {
            actual = actual->derecha;
        }
        // Se actualiza el valor
        if (actual->derecha != aRow[f] && actual->derecha->columna == c) {
            actual->derecha->dato = dato;
        // En caso de que el nodo no exista se crea
        } else {
            insertar(f, c, dato);
        }
    }
    void mostrarMatrizEntera(int posF, int posC) {
        const int ancho = 8; // ancho fijo por celda para alinear
        for (int i = 0; i < filas; i++) {
            Nodo<T>* actual = aRow[i]->derecha;

            for (int j = 0; j < columnas; j++) {
                string celda;

                if (i == posF && j == posC) {
                    celda = "L";
                }
                else if (actual != nullptr && actual != aRow[i] && actual->columna == j) {
                    celda = to_string(actual->dato.valor);
                    if (actual->dato.alarma) celda += "(A)";
                    if (actual->dato.perro) celda += "(P)";

                    actual = actual->derecha;
                    if (actual == aRow[i]) actual = nullptr;
                }
                else {
                    celda = "-";
                }

                // imprime la celda con ancho fijo
                cout << setw(ancho) << left << celda;
            }
            cout << endl;
        }
    }

    void mostrarMatrizReducida(int posF, int posC) {
        const int ancho = 8; // ancho fijo por celda

        for (int i = 0; i < filas; i++) {
            Nodo<T>* actual = aRow[i]->derecha;

            for (int j = 0; j < columnas; j++) {
                string celda;

                if (i == posF && j == posC) {
                    celda = "L";
                }
                else if (actual != nullptr && actual != aRow[i] && actual->columna == j) {
                    if (actual->dato.valor == 0 || actual->dato.alarma || actual->dato.perro)
                        celda = "X";
                    else
                        celda = to_string(actual->dato.valor);

                    actual = actual->derecha;
                    if (actual == aRow[i]) actual = nullptr;
                }
                else {
                    celda = "-";
                }

                cout << setw(ancho) << left << celda;
            }
            cout << endl;
        }
    }
};

#endif //MPP_H
