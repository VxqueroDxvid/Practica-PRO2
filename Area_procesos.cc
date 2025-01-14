/** @file Area_procesos.cc
    @brief Implementación de la clase Area_procesos
*/

#include "Area_procesos.hh"

Area_procesos:: Area_procesos(){}

void Area_procesos:: alta_prioridad(const string& p){
    Prioridad pr;
    m.insert(make_pair(p, pr));
}

void Area_procesos:: baja_prioridad(const string& p){
    map <string, Prioridad>:: iterator it = m.find(p);
    it = m.erase(it);
}

void Area_procesos:: alta_proceso_espera(const string& idprioridad, Proceso& p){
    map<string, Prioridad>:: iterator it = m.find(idprioridad);
    (*it).second.alta_proceso_espera(p);
}

void Area_procesos:: enviar_procesos_cluster(Cluster& c, int n){
    map <string, Prioridad>:: iterator it = m.begin();
    while (n > 0 and it != m.end()){
        (*it).second.enviar_procesos_cluster(c, n);
        ++it;
    }
}

bool Area_procesos:: existe_prioridad(const string& p) const{
    map<string, Prioridad>::const_iterator it = m.find(p);
    return it != m.end();
}

bool Area_procesos:: existe_proceso_ae(const string& idprioridad, int p) const{
    map <string, Prioridad>::const_iterator it = m.find(idprioridad);
    return (*it).second.existe_proceso_ae(p);
}

bool Area_procesos:: tiene_proc_pendientes(const string& p) const{
    map <string, Prioridad>::const_iterator it = m.find(p);
    return (*it).second.tiene_proc_pendientes();   
}

void Area_procesos:: leer_area_procesos(){
    string idprioridad;
    Prioridad p;
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
        cin >> idprioridad;
        m.insert(make_pair(idprioridad, p));
    }
}

void Area_procesos:: imprimir_area_espera() const{
    map <string, Prioridad>::const_iterator it = m.begin();
    while (it != m.end()){
        cout << (*it).first << endl;
        (*it).second.imprimir_prioridad();
        ++it;
    }
}

void Area_procesos:: imprimir_prioridad(const string& idprioridad) const{
    map <string, Prioridad>::const_iterator it = m.find(idprioridad);
    (*it).second.imprimir_prioridad();
}