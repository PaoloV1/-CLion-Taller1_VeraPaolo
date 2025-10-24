//
// Created by Paolo on 22-10-2025.
//

#ifndef INTERFAZ_H
#define INTERFAZ_H
#include "Casa.h"
#include "MPP.h"
#include "Sistema.h"
class Interfaz {
private:
    MPP<Casa>* casas;
public:
    Interfaz();
    ~Interfaz();
    void mainMenu(bool hard);
    void positionMenu(bool hard, bool night);
    void simulationMenu(Sistema* sistema, MPP<Casa>*casas);
};



#endif //INTERFAZ_H
