//
// Created by Paolo on 22-10-2025.
//
#include "Sistema.h"
#include "Interfaz.h"

/**
 * Constructor de la clase interfaz
 */
Interfaz::Interfaz()  {
    casas = new MPP<Casa>(21,21);
    cout << "======== Bienvenido a la simulacion de ladron ========"<<endl;
    cout << "........"<<endl;
    cout << "........"<<endl;
    cout<<endl;
    cout<<endl;
    int mode;
    bool hard;

    while (1) {
        cout << "====== Desea considerar las casas con perros y alarmas?"<<endl;
        cout << "1. Si"<<endl;
        cout << "2. No"<<endl;
        cin >> mode;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Por favor ingrese una opcion valida"<<endl;
            continue;
        }
        switch (mode) {
            case 1: {
                hard = true;
                mainMenu(hard);
                return;
            }
            case 2: {
                hard = false;
                mainMenu(hard);
                return;
            }
            default: {
                cout << "Ingrese una opcion valida"<<endl;
                break;
            }

        }
    }

}

/**
 *  Menu "Principal" el cual nos derivara a los otros menus para la simulacion
 * @param hard booleano que sera true si es que se consideran los perros y alarmas, y false si no
 */
void Interfaz::mainMenu(bool hard) {
    int time;
    bool night;

    while (1) {
        cout << "====== Desea que sea de noche?"<<endl;
        cout << "1. Si"<<endl;
        cout << "2. No"<<endl;
        cin >> time;
        if (cin.fail()) {
            cin.clear();
            cin.ignore();
            cout << "Por favor ingrese una opcion valida"<<endl;
            continue;
        }
        switch (time) {
            case 1: {
                night = true;
                positionMenu(hard, night);
                return;
            }
            case 2: {
                night = false;
                positionMenu(hard, night);
                return;
            } default: {
                cout << "Ingrese una opcion valida"<<endl;
                break;
            }
        }
    }
}

/**
 * Menu para obtener la posicion inicial del ladron para la simulacion
 * @param hard
 * @param night booleano que sera true si es que el usuario decidio que fuera noche, y false si el usuario escogio de dia
 */
void Interfaz::positionMenu(bool hard, bool night) {
    int posF;
    int posC;
    int numMov;
    while (true) {
        cout << "Ingrese la posicion en fila del ladron (Desde el 1 hasta el 20):";
        if (cin >> posF && posF >= 1 && posF <= 20) break;
        cout << "Entrada invalida. Intente de nuevo"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
    }
    while (true) {
        cout << "Ingrese la posicion en columna del ladron (Desde el 1 hasta el 20):";
        if (cin >> posC && posC >= 1 && posC <= 20) break;
        cout << "Entrada invalida. Intente de nuevo"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
    }
    while (true) {
        cout << "Ingrese el numero de movimientos del ladron (Desde el 5 hasta el 10):";
        if (cin >> numMov && numMov >= 5 && numMov <= 10) break;
        cout << "Entrada invalida. Intente de nuevo"<<endl;
        cin.clear();
        cin.ignore(1000,'\n');
    }

    Sistema * sistema = new Sistema(20, 20,posF, posC, 0, numMov,0,night,hard,casas);

    sistema->leerArchivo("ciudad.txt");
    sistema->cargarMPP(casas);
    simulationMenu(sistema, casas);


}

/**
 * Ultimo menu que dara paso a la simulacion del ladron tomara todas las configuraciones anteriores para que la simulacion se haga bajo esas mismas
 * @param sistema
 * @param casas Matriz poco poblada de casas
 */
void Interfaz::simulationMenu(Sistema *sistema, MPP<Casa>* casas) {
    if (sistema->getModoConAlarmas()) {
        sistema->mostrarMapaTotal(casas);

    } else {
        sistema->mostrarMapaReducido(casas);
    }
    cout <<"Numero de movimientos restantes: "<< sistema->getNumMovimientos() << endl;
    sistema->simularLadron();
}




