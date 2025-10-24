//
// Created by Paolo on 22-10-2025.
//

#include "Sistema.h"

#include <fstream>
#include <iostream>
#include <sstream>

/**
 * Metodo constructor para la clase sistema
 * @param filas
 * @param columnas
 * @param f posicion de ladron
 * @param c posicion de ladron
 * @param botin
 * @param movimientos
 * @param visitadas
 * @param noche
 * @param hard
 * @param mpp
 */
Sistema::Sistema(int filas, int columnas, int f, int c, int botin,
                 int movimientos, int visitadas, bool noche, bool hard,
                 MPP<Casa>* mpp)
{
    posLadronFila = f;
    posLadronCol = c;
    this->botin = botin;
    numMovimientos = movimientos;
    casasVisitadas = visitadas;
    esNoche = noche;
    modoConAlarmas = hard;
    casas = mpp;
}
/**
 * @return Monto del votin acumulado actualmente
 */
int Sistema::getBotin() {
    return botin;
}


/**
 * @return Numero de casas visitadas actualmente por el ladron
 */
int Sistema::getCasasVisitadas() {
    return casasVisitadas;
}

/**
 * @return Numero de movimientos restantes para el ladron
 */
int Sistema::getNumMovimientos() {
    return numMovimientos;
}

/**
 * @return Posicion actual en fila del ladron
 */
int Sistema::getPosLadronFila() {
    return posLadronFila;
}

/**
 * @return Posicion actual en columna del ladron
 */
int Sistema::getPosLadronCol() {
    return posLadronCol;
}


/**
 * Metodo para leer el archivo ciudad.txt y guardar sus datos dentro de una matriz
 * @param nombreArchivo
 */
void Sistema::leerArchivo(string nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo" << endl;
        return;
    }

    string linea;
    getline(archivo, linea); // Se ignora la primera linea que tiene el encabezado
    int lineaNum = 1;

    while (getline(archivo, linea)) {
        lineaNum++;
        if (linea.empty()) continue;

        stringstream ss(linea);
        string token;
        int fila, columna, perro, alarma, valor;

        try {
            getline(ss, token, ','); fila = stoi(token);
            getline(ss, token, ','); columna = stoi(token);
            getline(ss, token, ','); perro = stoi(token);
            getline(ss, token, ','); alarma = stoi(token);
            getline(ss, token, ','); valor = stoi(token);
        } catch (...) {
            cerr << "Error: valor invalido en la linea " << lineaNum << ": " << linea << endl;
            continue;
        }

        // Sumamos 1 a fila y columna porque la MPP ignora el 0 (nodos cabecera)
        int fMPP = fila + 1;
        int cMPP = columna + 1;

        if (fMPP > 0 && fMPP <= FILAS && cMPP > 0 && cMPP <= COLUMNAS) {
            Casa casa(valor, perro == 1, alarma == 1);
            casas->insertar(fMPP, cMPP, casa);
        } else {
            cerr << "Fuera de rango en la linea " << lineaNum << ": " << fila << "," << columna << endl;
        }
    }

    archivo.close();
}

/**
 * Metodo que cargara los elementos de la matriz normal hacia la matriz poco poblada
 * @param casas matriz poco poblada de casas
 */
void Sistema::cargarMPP(MPP<Casa>* casas) {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (matrizNormal[i][j].valor > 0) {
                casas->insertar(i,j,matrizNormal[i][j]);
            }
        }
    }
}



/**
 * @return true si es noche, false si es dia
 */
bool Sistema::getEsNoche() {
    return esNoche;
}

bool Sistema::getModoConAlarmas() {
    return modoConAlarmas;
}

/**
 * Metodo que mostrara el mapa de la ciudad entero, contando las casas con alarmas y perros
 */
void Sistema::mostrarMapaTotal(MPP<Casa>* casas) {
    casas->mostrarMatrizEntera(posLadronFila, posLadronCol);
}

/**
 * Metodo que mostrara el mapa de la ciudad, pero solo mostrara disponibles las casas sin alarmas y perros
 */
void Sistema::mostrarMapaReducido(MPP<Casa>* casas) {
    casas->mostrarMatrizReducida(posLadronFila, posLadronCol);
}

/**
 *
 * @param nuevaFila
 * @param nuevaColumna
 */
void Sistema::moverLadron(int nuevaFila, int nuevaColumna) {
    if (nuevaFila < 0 || nuevaFila > 20 || nuevaColumna < 0 || nuevaColumna > 20) return;
    if (numMovimientos == 0) return;

    Casa casa = casas->get(nuevaFila, nuevaColumna);

    //Modo sin alarmas y perros
    if (!modoConAlarmas && (casa.alarma || casa.perro)) {
        cout << "Casa protegida" <<endl;
        posLadronFila = nuevaFila;
        posLadronCol = nuevaColumna;
        numMovimientos--;
        casas->mostrarMatrizReducida(posLadronFila, posLadronCol);
        cout << "Movimientos restantes: "<< numMovimientos << endl;
        cout << "Botin acumulado: "<<botin << endl;
        return;
    }
    // Modo con alarmas
    bool fallo = false;
    if (modoConAlarmas) {
        srand(time(0));

        if (casa.perro) {
            if ((rand()%100) < 30) fallo = true;
        }
        if (casa.alarma) {
            if ((rand()%100) <(esNoche ? 100 : 30)) fallo = true;
        }
    }
    if (!fallo && casa.valor > 0) {
        botin += casa.valor;
        casas->insertar(nuevaFila, nuevaColumna, Casa());
        casasVisitadas++;
        cout << "Casa robada por un valor de: "<< casa.valor << endl;

    } else if (fallo) {
        cout << "Has sido descubierto!!"<<endl;
        numMovimientos = 0;
        return;
    } else {
        cout << "Casa vacia"<<endl;
    }

    posLadronFila = nuevaFila;
    posLadronCol = nuevaColumna;
    numMovimientos--;

    casas->mostrarMatrizEntera(posLadronFila, posLadronCol);
    cout << "Movimientos restantes: "<<numMovimientos << endl;
    cout << "Botin acumulado: "<<botin << endl;

}
void Sistema::simularLadron() {
    int dx[8] = {-1,-1,-1,0,0,1,1,1};
    int dy[8] = {-1,0,1,-1,1,-1,0,1};

    while (numMovimientos > 0) {
        int mejorFila = -1;
        int mejorCol = -1;
        double mayorValorEsperado = 0;


        //Se revisan los 8 movimientos posibles
        for (int k = 0; k < 8; k++) {
            int newFila = posLadronFila + dx[k];
            int newCol = posLadronCol + dy[k];

            if (newFila < 0 || newFila > 20 || newCol < 0 || newCol > 20) return;
            Casa c = casas->get(newFila, newCol);

            // Si esta en el modo sin alarmas y hay una casa con alarmas se descarta
            if (!modoConAlarmas && (c.perro || c.alarma)) continue;

            // Calculamos la mejor opcion teniendo en cuenta las probabilidades
            double probFallar = 0;
            if (modoConAlarmas) {
                if (c.perro) probFallar += 0.3;
                if (c.alarma) probFallar += esNoche ? 1.0 : 0.3;
                if (probFallar > 1.0) probFallar = 1.0;
            }

            double valorEsperado = c.valor* (1.0 - probFallar);
            if (valorEsperado > mayorValorEsperado) {
                mayorValorEsperado = valorEsperado;
                mejorFila = newFila;
                mejorCol = newCol;
            }
        }
        // En caso de que el ladron quede entre casas sin un valor real
        if (mejorFila == -1) {
            cout << "No hay movimientos buenos posibles"<<endl;
            break;
        }
        //Mover al ladron
        moverLadron(mejorFila, mejorCol);
    }
    cout << "Simulacion terminada, botin total: "<< botin << endl;
}










