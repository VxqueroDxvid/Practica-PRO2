/** @file Cluster.hh
    @brief Especificación de la clase Cluster
*/

#ifndef _CLUSTER_HH_
#define _CLUSTER_HH_

#include "Procesador.hh"
#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include "BinTree.hh"
#include <string>
#include <map>
#endif

using namespace std;


/** @class Cluster
    @brief Representa un conjunto de procesadores

*/
class Cluster
{
public:

  //Constructoras

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un cluster.
      \pre <em>cierto</em>
      \post El resultado es un cluster vacío
  */  
  Cluster();

  //Consultoras

    /** @brief Consulta si existe un procesador o no.

      \pre <em>cierto</em>
      \post Devuelve cierto si existe el procesador
  */
  bool existe_procesador(const string& p) const;

   /** @brief Consulta si existe un proceso o no.

      \pre Existe un procesador con ese identificador
      \post Devuelve cierto si existe un proceso con ese identificador
  */
  bool existe_proceso(const string& idprocesador, int idproceso) const;

  /** @brief Consulta si el procesador tiene procesos en su memoria (no está vacía).

      \pre Existe un procesador con ese identificador
      \post Devuelve cierto si el procesador tiene procesos en ejecución (en su memoria)
  */
  bool tiene_procesos_ejec(const string& p) const;

  /** @brief Consulta si el procesador tiene hijos.

      \pre Existe un procesador con ese identificador y no tiene procesos en ejecución
      \post Devuelve cierto si el procesador tiene hijos
  */
  bool tiene_hijos(const string& p) const;

  //Modificadoras

  /** @brief Lee un identificador, si está en el cluster original, añade un cluster en su lugar.

      \pre Existe un procesador con ese identificador, y este no tiene procesos en ejecución ni tiene hijos
      \post Añade el nuevo cluster en el lugar donde estaba el procesador
  */
  void modificar_cluster(const string& p, const Cluster& c1);

  /** @brief Retorna el identificador del procesador más adecuado donde se ha metido el proceso.

      \pre Existe un proceso con ese identificador y por lo menos una prioridad
      \post Añade el proceso en el procesador más adecuado y retorna su identificador
  */
  pair<bool,string> cabe_proceso(const Proceso& p);

  /** @brief Avanza el tiempo del circuito.

      \pre <em>cierto</em>
      \post Avanza el tiempo de todos los procesos en ejecución (si se han acabado se eliminan)
  */
  void avanzar_tiempo(int t);

  /** @brief Mueve todos los procesos de todos los procesadores al principio de la memoria, sin dejar huecos, sin solaparse y respetando el orden inicial.

      \pre <em>cierto</em>
      \post Se han movido todos los procesos de todos los procesadores al principio de la memoria, sin solaparse, sin dejar huecos y respetando el orden inicial
  */
  void compactar_memoria_cluster();

  /** @brief Mueve todos los procesos del procesador al principio de la memoria, sin dejar huecos, sin solaparse y respetando el orden inicial.

      \pre Existe un procesador con ese identificador
      \post Mueve todos los procesos del procesador al principio de la memoria, sin dejar huecos, sin solaparse y respetando el orden inicial
  */
  void compactar_memoria_procesador(const string& idprocesador);

   /** @brief Determina si un proceso puede pasar a ejecución en ese procesador, ocupando la memoria que necesite este, en la posición de memoria más pequeña y con el tamaño más ajustado.

      \pre Exsiten un procesador y un proceso con ese identificador
      \post True si se ha podido pasar el proceso a ejecución (si ha cabido), false en caso contrario
  */
  bool alta_proceso_procesador(const string& idprocesador, const Proceso& p);

  /** @brief Si existe un procesador con ese identificador y existe un proceso en ejecución con ese identificador, elimina el proceso.

      \pre Existen un procesador y un proceso con ese identificador
      \post Se ha eliminado el proceso del procesador
  */
  void baja_proceso_procesador(const string& idprocesador, int idproceso);

  // Lectura de un cluster

  /** @brief Operación de lectura.

      \pre <em>cierto</em>
      \post Cluster después de leer los procesadores
  */
  void configurar_cluster();

  // Escritura de un cluster

  /** @brief Operación de escritura.

      \pre <em>cierto</em>
      \post Escribe el contenido del cluster por orden creciente de identificador
  */
  void imprimir_procesadores_cluster()const;

   /** @brief Operación de escritura.

      \pre <em>cierto</em>
      \post Escribe la estructura de procesadores del cluster
  */
  void imprimir_estructura_cluster() const;

   /** @brief Operación de escritura.

      \pre Existe un procesador con ese identificador
      \post Escribe la estructura de procesadores del cluster
  */
  void imprimir_procesador(const string& idprocesador) const;


private:
  
  /** @brief Árbol con los identificadores de los procesadores.
  */
  BinTree <string> a;

  /** @brief Mapa con los identificadores de los procesadores como clave y los procesadores como valor.
  */
  map <string, Procesador> m;

  /** @brief Operación de escritura.

      \pre <em>cierto</em>
      \post Imprime la estructura del árbol
  */
  static void escribir_arbol (const BinTree <string> &a);

    /** @brief Operación de lectura.

      \pre <em>cierto</em>
      \post Lee el árbol del cluster
  */
  void leer_arbol(BinTree <string> &a);
  
  /** @brief Retorna cierto si el procesador con ese id tiene hijos, en caso contrario, retorna false.

      \pre <em>cierto</em>
      \post True si el procesador con ese id tiene hijos, false si no los tiene
  */
  static bool hay_hijos(const BinTree <string>& a, const string& p);

  /** @brief Pone el nuevo cluster en el lugar del procesador con el id p.

      \pre Existe un procesador con ese id y no tiene procesos en ejecución ni procesadores auxiliares
      \post Se ha añadido el cluster c1 al cluster original
  */
  static bool modificar_arbol(const string& p, BinTree <string>& a, const BinTree <string>& a1);

  /** @brief Retorna el identificador del procesador más adecuado donde se puede meter el proceso.

      \pre Existe un proceso con ese identificador
      \post Añade el proceso en el procesador más adecuado y retorna su identificador
  */
  void cabe_proceso_arbol(string& procadecuado, int& huecomin, int& memlibremin, int& minimaProf, int profactual, const BinTree<string>& a, int tam_proc, int idproceso);


};
#endif