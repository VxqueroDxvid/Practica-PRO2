/** @mainpage Simulación del rendimiento de procesadores interconectados
*/
/** @file program.cc
    @brief Código principal de la práctica "Simulación del rendimiento de procesadores interconectados"
*/
#include "Cluster.hh"
#include "Area_procesos.hh"
#include "Proceso.hh"
#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include "BinTree.hh"
#endif
using namespace std;

/** @brief El código principal de la práctica
*/ 
int main() {
    Cluster c;
    Area_procesos ae;
    c.configurar_cluster();
    ae.leer_area_procesos();
    string opcion;
    cin >> opcion;
    while (opcion != "fin"){
        if (opcion == "configurar_cluster" or opcion == "cc") {
            cout << "#" << opcion << endl;
            c.configurar_cluster(); 
        }
        else if (opcion == "modificar_cluster" or opcion == "mc") {
            string p;
            cin >> p;
            Cluster c1;
            c1.configurar_cluster();
            cout << "#" << opcion << " " << p << endl;
            if (not c.existe_procesador(p)) cout << "error: no existe procesador" << endl;
            else if (c.tiene_procesos_ejec(p)) cout << "error: procesador con procesos" << endl;
            else if (c.tiene_hijos(p)) cout << "error: procesador con auxiliares" << endl;
            else {
                c.modificar_cluster(p, c1);
            }
        }
        else if (opcion == "alta_prioridad" or opcion == "ap") {
            string idprioridad;
            cin >> idprioridad;
            cout << "#" << opcion << " " << idprioridad << endl;
            if (ae.existe_prioridad(idprioridad)) cout << "error: ya existe prioridad" << endl;
            else {
                ae.alta_prioridad(idprioridad);
            }
        }
        else if (opcion == "baja_prioridad" or opcion == "bp") {
            string idprioridad;
            cin >> idprioridad;
            cout << "#" << opcion << " " << idprioridad << endl;
            if (not ae.existe_prioridad(idprioridad)) cout << "error: no existe prioridad" << endl;
            else if (ae.tiene_proc_pendientes(idprioridad)) cout << "error: prioridad con procesos" << endl;
            else {
                ae.baja_prioridad(idprioridad);
            }
        }
        else if (opcion == "alta_proceso_espera" or opcion == "ape") {
            string idprioridad;
            cin >> idprioridad;
            Proceso p;
            p.leer_proceso();
            cout << "#" << opcion << " " << idprioridad << " " << p.consultar_idproceso() << endl;
            if (not ae.existe_prioridad(idprioridad)) cout << "error: no existe prioridad" << endl;
            else if (ae.existe_proceso_ae(idprioridad, p.consultar_idproceso())) cout << "error: ya existe proceso" << endl;
            else {
                ae.alta_proceso_espera(idprioridad, p);
            } 
        }
        else if (opcion == "alta_proceso_procesador" or opcion == "app") {
            string idprocesador;
            cin >> idprocesador;
            Proceso p;
            p.leer_proceso();
            cout << "#" << opcion << " " << idprocesador << " " << p.consultar_idproceso() << endl;
            if (not c.existe_procesador(idprocesador)) cout << "error: no existe procesador" << endl;
            else if (c.existe_proceso(idprocesador, p.consultar_idproceso())) cout << "error: ya existe proceso" << endl;
            else if (not c.alta_proceso_procesador(idprocesador, p)) cout << "error: no cabe proceso" << endl;
        }
        else if (opcion == "baja_proceso_procesador" or opcion == "bpp") {
            string idprocesador;
            int idproceso;
            cin >> idprocesador >> idproceso;
            cout << "#" << opcion << " " << idprocesador << " " << idproceso << endl;
            if (not c.existe_procesador(idprocesador)) cout << "error: no existe procesador" << endl;
            else if (not c.existe_proceso(idprocesador, idproceso)) cout << "error: no existe proceso" << endl;
            else {
                c.baja_proceso_procesador(idprocesador, idproceso);
            }
        }
        else if (opcion == "enviar_procesos_cluster" or opcion == "epc") {
            int n;
            cin >> n;
            cout << "#" << opcion << " " << n << endl;
            ae.enviar_procesos_cluster(c, n);
        }
        else if (opcion == "avanzar_tiempo" or opcion == "at") {
            int t;
            cin >> t;
            cout << "#" << opcion << " " << t << endl;
            c.avanzar_tiempo(t);
        }
        else if (opcion == "imprimir_prioridad" or opcion == "ipri") {
            string idprioridad;
            cin >> idprioridad;
            cout << "#" << opcion << " " << idprioridad << endl;
            if (not ae.existe_prioridad(idprioridad)) cout << "error: no existe prioridad" << endl;
            else {
                ae.imprimir_prioridad(idprioridad);
            }
        }
        else if (opcion == "imprimir_area_espera" or opcion == "iae") {
            cout << "#" << opcion << endl;
            ae.imprimir_area_espera();
        }
        else if (opcion == "imprimir_procesador" or opcion == "ipro") {
            string idprocesador;
            cin >> idprocesador;
            cout << "#" << opcion << " " << idprocesador << endl;
            if (not c.existe_procesador(idprocesador)) cout << "error: no existe procesador" << endl;
            else {
                c.imprimir_procesador(idprocesador);
            }
        }
        else if (opcion == "imprimir_procesadores_cluster" or opcion == "ipc") {
            cout << "#" << opcion << endl;
            c.imprimir_procesadores_cluster();
        }
        else if (opcion == "imprimir_estructura_cluster" or opcion == "iec") {
            cout << "#" << opcion << endl;
            c.imprimir_estructura_cluster();
        }
        else if (opcion == "compactar_memoria_procesador" or opcion == "cmp") {
            string idprocesador;
            cin >> idprocesador;
            cout << "#" << opcion << " " << idprocesador << endl;
            if (not c.existe_procesador(idprocesador)) cout << "error: no existe procesador" << endl;
            else {
               c.compactar_memoria_procesador(idprocesador);
            }
        }
        else if (opcion == "compactar_memoria_cluster" or opcion == "cmc") {
            cout << "#" << opcion << endl;
            c.compactar_memoria_cluster();
        }
        cin >> opcion;
    }
}