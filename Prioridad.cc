/** @file Prioridad.cc
    @brief Implementación de la clase Prioridad
*/

#include "Prioridad.hh"

Prioridad:: Prioridad(){
    aceptados = 0;
    no_aceptados = 0;
}

void Prioridad:: alta_proceso_espera(Proceso& p){
    l.insert(l.end(), p);
    ids.insert(p.consultar_idproceso());
}

void Prioridad:: enviar_procesos_cluster(Cluster& c, int& n){
    list<Proceso>:: iterator it = l.begin();
    list<Proceso> l1;
    while (it != l.end() and n > 0){ // recorre la lista mientras no se hayan aceptado n procesos
        pair<bool,string> r = c.cabe_proceso(*it);
        if (r.first){
            string idprocesador = r.second;
            c.alta_proceso_procesador(idprocesador,*it);
            ++aceptados;
            --n;
            ids.erase((*it).consultar_idproceso());
            it = l.erase(it);
        }
        else {
            ++no_aceptados;
            l1.insert(l1.end(), *it);
            it = l.erase(it);
        }
    }
    l.insert(l.end(),l1.begin(),l1.end());
    
    
}

bool Prioridad:: existe_proceso_ae(int p) const{
    set<int>::const_iterator it = ids.find(p);
    return it != ids.end();
}

int Prioridad:: consultar_aceptados() const{
    return aceptados;
}

bool Prioridad:: tiene_proc_pendientes() const{
    return ids.size() > 0;
}

void Prioridad:: imprimir_prioridad() const{
    list <Proceso>:: const_iterator it = l.begin();
    while (it != l.end()){
        (*it).imprimir_proceso();
        ++it;
    }
    cout << aceptados << " " << no_aceptados << endl;
}