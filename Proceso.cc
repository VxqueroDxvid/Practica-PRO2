/** @file Proceso.cc
    @brief Implementación de la clase Proceso
*/

#include "Proceso.hh"

Proceso:: Proceso(){
}

int Proceso:: consultar_idproceso() const{
    return idproceso;
}

int Proceso:: consultar_cant_mem() const{
    return cant_mem;
}

int Proceso:: avanzar_tiempo(int t){
    tiempo = tiempo - t;
    return tiempo;
}

void Proceso:: leer_proceso(){
    cin >> idproceso >> cant_mem >> tiempo;
}

void Proceso:: imprimir_proceso() const{
    cout << idproceso << " " << cant_mem << " " << tiempo << endl;
}