/** @file Cluster.cc
    @brief Implementación de la clase Cluster
*/

#include "Cluster.hh"

Cluster:: Cluster(){}

bool Cluster:: existe_procesador(const string& p) const{
    map <string, Procesador>::const_iterator it = m.find(p);
    if (it == m.end()) return false;
    else return true;
}

bool Cluster:: existe_proceso(const string& idprocesador, int idproceso) const{
    map <string, Procesador>:: const_iterator it = m.find(idprocesador);
    return (*it).second.existe_proceso(idproceso);
}

bool Cluster:: tiene_procesos_ejec(const string& p) const{
    map <string, Procesador>::const_iterator it = m.find(p);
    return (*it).second.tiene_procesos_ejec();
}

bool Cluster:: tiene_hijos(const string& p) const{
   return hay_hijos(a, p);
}
bool Cluster:: hay_hijos(const BinTree <string>& a, const string& p){
    if ((not a.empty()) and (a.value()== p) and (not a.left().empty() or not a.right().empty())) return true;
    else if (not a.empty() and a.value() != p){
        return hay_hijos (a.left(), p) or hay_hijos (a.right(), p);
    }
    else {
        return false;
    }
}

bool Cluster:: modificar_arbol(const string& p, BinTree <string>& a, const BinTree <string>& a1){
    if (not a.empty() and a.value() == p){
        a = a1;
        return true;
    }
    else if (not a.empty() and a.value() != p){
        BinTree<string> aizq = a.left();
        BinTree<string> ader = a.right();
        bool b = modificar_arbol(p, aizq, a1) or modificar_arbol(p, ader, a1);
        a = BinTree<string>(a.value(),aizq,ader);
        return b;

    }
    return false;
}

void Cluster:: cabe_proceso_arbol(string& procadecuado, int& huecomin, int& memlibremin, int& minimaProf, int profactual, const BinTree<string>& a, int tam_proc, int idproceso){
    if (not a.empty()){
        map<string, Procesador>:: iterator it = m.find(a.value());
        if (it != m.end()){
            bool cabe = (*it).second.cabe_proceso(tam_proc, idproceso);
            if (cabe){
                int hueco = (*it).second.consultar_hueco_min(tam_proc);
                if(procadecuado == " " or hueco < huecomin){ // caso donde no hay empate en el hueco más ajustado
                    huecomin = hueco;
                    procadecuado = a.value();
                    memlibremin = (*it).second.consultar_mem_libre();
                    minimaProf = profactual;
                }
                else if (hueco == huecomin){ // caso de empate en los huecos
                    if ((*it).second.consultar_mem_libre() > memlibremin){ // caso donde no hay empate en memoria libre
                        memlibremin = (*it).second.consultar_mem_libre();
                        procadecuado = a.value();
                        minimaProf = profactual;
                    }
                    else if ((*it).second.consultar_mem_libre() == memlibremin){ // caso de empate en memoria libre
                        if (profactual < minimaProf){ // no hay empate en profundidad, si hubiera empate se queda automáticamente con el de la izquierda, es el que va antes
                            minimaProf = profactual;
                            procadecuado = a.value();
                        }
                    }
                } 
                ++profactual;
                cabe_proceso_arbol(procadecuado, huecomin, memlibremin, minimaProf, profactual, a.left(), tam_proc, idproceso);
                cabe_proceso_arbol(procadecuado, huecomin, memlibremin, minimaProf, profactual, a.right(), tam_proc, idproceso);
            }
            else{
                ++profactual;
                cabe_proceso_arbol(procadecuado, huecomin, memlibremin, minimaProf, profactual, a.left(), tam_proc, idproceso);
                cabe_proceso_arbol(procadecuado, huecomin, memlibremin, minimaProf, profactual, a.right(), tam_proc, idproceso);
            }
        }
    }
}

pair<bool,string> Cluster:: cabe_proceso(const Proceso& p){
    string procadecuado = " ";
    int minimaProf;
    int huecomin;
    int memlibremin;
    int tam_proc = p.consultar_cant_mem();
    int idproceso = p.consultar_idproceso();
    cabe_proceso_arbol(procadecuado, huecomin, memlibremin, minimaProf, 0, a, tam_proc, idproceso);
    if(procadecuado != " ") return make_pair(true,procadecuado);
    return make_pair(false,procadecuado);
}

void Cluster:: modificar_cluster(const string& p, const Cluster& c1){
    modificar_arbol(p, a, c1.a);
    map <string, Procesador>:: iterator it = m.find(p);
    m.erase(it);    
    map <string, Procesador>::const_iterator it1 = c1.m.begin();
    while (it1 != c1.m.end()){
        m.insert(*it1);
        ++it1;
    }
}

void Cluster:: avanzar_tiempo(int t){
    map <string, Procesador>:: iterator it = m.begin();
    while (it != m.end()){
        (*it).second.avanzar_tiempo(t);
        ++it;
    }
}

void Cluster:: compactar_memoria_cluster(){
    map <string, Procesador>:: iterator it = m.begin();
    while (it != m.end()){
        (*it).second.compactar_memoria_procesador();
        ++it;
    }
}

void Cluster:: compactar_memoria_procesador(const string& idprocesador){
    map <string, Procesador>:: iterator it = m.find(idprocesador);
    (*it).second.compactar_memoria_procesador();
}

bool Cluster:: alta_proceso_procesador(const string& idprocesador, const Proceso& proc){
    map <string, Procesador>:: iterator it = m.find(idprocesador);
    return (*it).second.alta_proceso_procesador(proc);
}

void Cluster:: baja_proceso_procesador(const string& idprocesador, int idproceso){
    map <string, Procesador>:: iterator it = m.find(idprocesador);
    (*it).second.baja_proceso_procesador(idproceso);
}

void Cluster:: configurar_cluster(){
    m.clear();
    leer_arbol(a);
}

void Cluster:: leer_arbol (BinTree <string> &a){
    string s;
    cin >> s;
    if (s != "*"){
        Procesador p;
        int n;
        cin >> n;
        p.modificar_capacidad(n);
        m.insert(make_pair(s, p));
        BinTree <string> e, d;
        leer_arbol(e);
        leer_arbol(d);
        a = BinTree <string> (s, e, d);
    }
}

void Cluster:: imprimir_procesadores_cluster() const{
    map<string, Procesador>::const_iterator it = m.begin();
    while (it != m.end()){
        cout << (*it).first << endl;
        (*it).second.imprimir_procesador();
        ++it;
    }
}

void Cluster:: escribir_arbol (const BinTree <string> &a){
    if (not a.empty()){
        cout << '(' << a.value();
        escribir_arbol(a.left());
        escribir_arbol(a.right());
        cout << ')';
    }
    else cout << ' '; 
}

void Cluster:: imprimir_estructura_cluster() const{
    escribir_arbol(a);
    cout << endl;
}

void Cluster:: imprimir_procesador(const string& idprocesador) const{
    map<string, Procesador>::const_iterator it = m.find(idprocesador);
    (*it).second.imprimir_procesador();
}