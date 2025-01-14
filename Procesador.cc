/** @file Procesador.cc
    @brief Implementación de la clase Procesador
*/

#include "Procesador.hh"

Procesador:: Procesador(){}

bool Procesador:: existe_proceso(int idproceso) const{
    map <int, int>::const_iterator it = posiciones.find(idproceso);
    if (it != posiciones.end()) return true;
    else return false;
}

bool Procesador:: tiene_procesos_ejec() const{
    if (not memoria.empty()) return true;
    else return false;
}

int Procesador:: consultar_mem_libre() const{
    return memlibre;
}

bool Procesador:: cabe_proceso(int tam_proc, int idproceso){
    map<int, set<int>>:: iterator it = huecos.lower_bound(tam_proc);
    if (it != huecos.end() and not existe_proceso(idproceso)){
        return true;
    }
    else return false;
}

int Procesador:: consultar_hueco_min(int tam_proc){
    map<int, set<int>>:: iterator it = huecos.lower_bound(tam_proc);
    return (*it).first;
}

void Procesador:: compactar_memoria_procesador(){
    if(not memoria.empty()){
        map <int, Proceso>:: iterator it = memoria.begin();
        if ((*it).first > 0){
            memoria.insert(make_pair(0, (*it).second));
            map<int,int>::iterator it2 = posiciones.find((*it).second.consultar_idproceso());
            (*it2).second = 0;
            memoria.erase(it);
        }
        it = memoria.begin();
        int posfinalproc = (*it).first + (*it).second.consultar_cant_mem();
        ++it;
        while (it != memoria.end()){
            pair<map<int,Proceso>::iterator, bool> p = memoria.insert(make_pair(posfinalproc, (*it).second));
            if(p.second){
                map<int,int>::iterator it2 = posiciones.find((*it).second.consultar_idproceso());
                (*it2).second = posfinalproc;
                memoria.erase(it);
                it = p.first;
            }
            posfinalproc = (*it).first + (*it).second.consultar_cant_mem();
            ++it;
        }
        map <int, set<int>>:: iterator it1 = huecos.begin();
        while (it1 != huecos.end()){
            it1 = huecos.erase(it1);
        }
        if(memlibre > 0){
            set <int> s;
            s.insert(posfinalproc);
            huecos.insert(make_pair(memlibre, s));
        }
    }
}

bool Procesador:: alta_proceso_procesador(const Proceso& p){
    int cantidad = p.consultar_cant_mem();
    map <int, set<int>>:: iterator it = huecos.lower_bound(cantidad); // busco el hueco de tamaño más ajustado donde cabe el proceso
    if (it == huecos.end()) return false; // el proceso no cabe
    else { // el proceso cabe
        memlibre -= cantidad;
        set<int>:: iterator it1 = (*it).second.begin(); // coge el hueco de ese tamaño que aparece primero en la memoria (primera posición)
        int nuevo = (*it1);
        int nuevapos = nuevo + cantidad;
        if ((*it).first > cantidad){ // si el tamaño del hueco es mayor que el del proceso, quedará hueco después de meter el proceso
            int hueconuevo = ((*it).first) - cantidad;
            map <int, set<int>>:: iterator it2 = huecos.find(hueconuevo); // busca si ya hay algún hueco del mismo tamaño
            if (it2 == huecos.end()) { // no hay hueco del mismo tamaño
                set <int> saux;
                saux.insert(nuevapos);
                huecos.insert(make_pair(hueconuevo, saux));
            }
            else (*it2).second.insert(nuevapos); // ya hay hueco del mismo tamaño
        }
        (*it).second.erase(it1); // borra el hueco del set de posiciones
        if ((*it).second.empty()) huecos.erase(it); // si no hay más posiciones en el set, borra el nodo del mapa de huecos porque significa que ya no hay huecos de ese tamaño
        memoria.insert(make_pair(nuevo, p));
        int nombre = p.consultar_idproceso();
        posiciones.insert(make_pair(nombre, nuevo)); // añade el proceso a los otros dos mapas
        return true;
    }
}

void Procesador:: baja_proceso_procesador(int idproceso){
    baja_proceso(idproceso);
}
map <int, Proceso>:: iterator Procesador:: baja_proceso(int idproceso){
    map <int, int>:: iterator it = posiciones.find(idproceso);
    int pos = (*it).second;
    posiciones.erase(it); // borra el proceso del mapa de identificadores y posiciones
    map <int, Proceso>:: iterator it1 = memoria.find(pos);
    int tamtotal = (*it1).second.consultar_cant_mem();
    int cantidadproc = (*it1).second.consultar_cant_mem();
    int posproc = (*it1).first;
    int pos_total = posproc;
    memlibre += cantidadproc;
    if (it1 != memoria.begin()){ // caso donde el proceso que se va a eliminar no es el primero (tiene uno antes por lo menos)
        --it1;
        int cantidadant = (*it1).second.consultar_cant_mem();
        int poshuecoant = (*it1).first + cantidadant; // posición donde empieza el hueco entre procesos (puede ser que no haya hueco)
        int tamhuecoant = posproc - poshuecoant;
        if(tamhuecoant > 0){ // si hay hueco entre procesos
            map <int, set <int>>:: iterator it1bis = huecos.find(tamhuecoant); // busca el hueco de ese tamaño
            (*it1bis).second.erase(poshuecoant);
            if((*it1bis).second.empty()) huecos.erase(it1bis); // si el set está vacío borra el nodo del mapa de huecos
            tamtotal = tamtotal + tamhuecoant;
            pos_total = poshuecoant;
        }
        ++it1;
    }
    else if(posproc > 0){ // el proceso es el primero pero hay hueco en el principio de la memoria
        map <int, set <int>>:: iterator it1bis = huecos.find(posproc); // busca el hueco de ese tamaño (será la posición del proceso menos 0)
        (*it1bis).second.erase(0);
        if((*it1bis).second.empty()) huecos.erase(it1bis);
        tamtotal = tamtotal + posproc;
        pos_total = 0;
    }
    ++it1;
    if (it1 != memoria.end()){ // caso donde el proceso tiene otro proceso detrás, mismo procedimiento que en el primer if
        int posprocsig = (*it1).first;
        int poshuecosig = posproc + cantidadproc;
        int tamhuecosig = posprocsig - poshuecosig;
        if(tamhuecosig > 0){
            map <int, set <int>>:: iterator it1bis = huecos.find(tamhuecosig);
            (*it1bis).second.erase(poshuecosig);
            if((*it1bis).second.empty()) huecos.erase(it1bis);
            tamtotal = tamtotal + tamhuecosig;
        }

    }
    else if(posproc + cantidadproc < capacidad){ // caso donde el proceso es el último pero hay un hueco al final de la memoria, mismo procedimiento que el primer else if
        int poshuecosig = posproc + cantidadproc;
        int tamhuecosig = capacidad - poshuecosig;
        map <int, set <int>>:: iterator it1bis = huecos.find(tamhuecosig);
        (*it1bis).second.erase(poshuecosig);
        if((*it1bis).second.empty()) huecos.erase(it1bis);
        tamtotal = tamtotal + tamhuecosig;
    }
    --it1;
    map <int, set <int>>:: iterator it2 = huecos.find(tamtotal);
    if (it2 == huecos.end()){  // si no hay huecos del mismo tamaño que el tamaño resultante
        set<int> s;
        s.insert(pos_total);
        huecos.insert(make_pair(tamtotal,s));
    }
    else{ // si hay huecos del mismo tamaño que el tamaño resultante
        (*it2).second.insert(pos_total);
    }
    it1 = memoria.erase(it1); // borra el proceso del mapa de posiciones y proceso
    return it1;
}

void Procesador:: avanzar_tiempo(int t){
    map <int, Proceso>:: iterator it = memoria.begin();
    while (it != memoria.end()){
        int tiempook = (*it).second.avanzar_tiempo(t);
        if (tiempook <= 0){ // si se ha acabado el tiempo de ejecución del proceso
            int id = (*it).second.consultar_idproceso();
            it = baja_proceso(id); // la función baja_proceso retorna un iterador apuntando al siguiente elemento de memoria
        }
        else ++it;
    }
}

void Procesador:: modificar_capacidad(int n){
    capacidad = n;
    memlibre = n;
    set<int> s;
    s.insert(0);
    huecos.insert(make_pair(memlibre, s));
}

void Procesador:: imprimir_procesador() const{
    map<int, Proceso>::const_iterator it = memoria.begin();
    while (it != memoria.end()){
        cout << (*it).first << " ";
        (*it).second.imprimir_proceso();
        ++it;
    }
}