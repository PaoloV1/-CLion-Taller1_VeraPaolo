//
// Created by Paolo on 22-10-2025.
//

#ifndef SISTEMA_H
#define SISTEMA_H
#include <string>
#include "Casa.h"
#include "MPP.h"
using namespace std;


class Sistema {
private:
    int filas;
    int columnas;
    int posLadronFila;
    int posLadronCol;
    int botin;
    int numMovimientos;
    int casasVisitadas;
    bool esNoche;
    bool modoConAlarmas;
    MPP<Casa>* casas;


public:
    Sistema(int filas, int columnas, int posLadronFila, int posLadronCol,int botin, int numMovimientos, int casasVisitadas, bool esNoche, bool  modoConAlarmas, MPP<Casa>* mpp);
    int getPosLadronFila();
    int getPosLadronCol();
    int getBotin();
    int getNumMovimientos();
    int getCasasVisitadas();
    bool getModoConAlarmas();
    void leerArchivo(string nombreArchivo);
    void mostrarMapaTotal(MPP <Casa>* mpp);
    void mostrarMapaReducido(MPP <Casa>* mpp);
    bool getEsNoche();
    void moverLadron(int nuevaFila, int nuevaColumna);
    void simularLadron();

    bool robar(Casa casa);
    void cargarMPP(MPP<Casa>* mpp);
};



#endif //SISTEMA_H
