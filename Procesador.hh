/** @file Procesador.hh
    @brief Especificación de la clase Procesador
*/

#ifndef _PROCESADOR_HH_
#define _PROCESADOR_HH_

#include "Proceso.hh"

#ifndef NO_DIAGRAM
#include <set>
#include <string>
#include <map>
#endif

using namespace std;


/** @class Procesador
    @brief Contiene una memoria en la que guardará y ejecutará los procesos

*/
class Procesador
{
public:
  //Constructoras

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un procesador.
      \pre <em>cierto</em>
      \post El resultado es un procesador vacío
  */  
  Procesador();

  //Consultoras

  /** @brief Retorna el hueco mínimo del procesador donde cabe el proceso.

      \pre Existe por lo menos el procesador del parámetro implícito
      \post Devuelve un entero con el hueco mínimo
  */
  int consultar_hueco_min(int tam_proc);

  /** @brief Determina si existe un proceso en la memoria del parámetro implícito o no.

      \pre Existe por lo menos el procesador del parámetro implícito
      \post Devuelve cierto si existe un proceso con el identificador p
  */
  bool existe_proceso(int idproceso) const;

   /** @brief Determina si el parámetro implícito tiene procesos en ejecución.

      \pre Existe por lo menos el procesador del parámetro implícito
      \post Devuelve cierto si existe algún proceso en ejecución en su memoria
  */
  bool tiene_procesos_ejec() const;

  /** @brief Retorna un entero con la memoria libre del procesador.

      \pre Existe por lo menos el procesador del parámetro implícito
      \post Devuelve un entero con la memoria libre del procesador
  */
  int consultar_mem_libre() const;

  //Modificadoras

   /** @brief Retorna true si el proceso cabe en el procesador.

      \pre Existen un procesador (parámetro implícito) y un proceso con ese identificador
      \post Devuelve true si el proceso cabe en el procesador
  */
  bool cabe_proceso(int tam_proc, int idproceso);
  
  /** @brief Modifica la capacidad del procesador.

      \pre Existe por lo menos el procesador del parámetro implícito
      \post La capacidad y la memoria libre ahora son iguales a n
  */
  void modificar_capacidad(int n);

  /** @brief Mueve todos los procesos del procesador al principio de la memoria, sin dejar huecos, sin solaparse y respetando el orden inicial.

      \pre Existe por lo menos el procesador del parámetro implícito
      \post Mueve todos los procesos del procesador al principio de la memoria, sin dejar huecos, sin solaparse y respetando el orden inicial
  */
  void compactar_memoria_procesador();

  /** @brief Añade el proceso en la memoria del procesador, si ha podido, devuelve true, false, en caso contrario.

      \pre Existen por lo menos un procesador (parámetro implícito) y un proceso con ese identificador
      \post Devuelve true si ha podido añadir el proceso a la memoria, false en caso contrario
  */
  bool alta_proceso_procesador(const Proceso& p);

  /** @brief Elimina el proceso de la memoria del procesador.

      \pre Existen por lo menos un procesador (parámetro implícito) y un proceso con ese identificador
      \post Se ha eliminado el proceso con ese id de la memoria del procesador
  */
  void baja_proceso_procesador(int idproceso);

  /** @brief Avanza el tiempo del circuito.

      \pre Existe por lo menos un procesador (parámetro implícito)
      \post Avanza el tiempo de todos los procesos en ejecución (si se han acabado se eliminan)
  */
  void avanzar_tiempo(int t);

  // Escritura de un procesador

  /** @brief Operación de escritura.

      \pre Existe un procesador por lo menos (parámetro implícito)
      \post Escribe los procesos de dicho procesador por orden creciente de primera posición de memoria
  */
  void imprimir_procesador()const;


private:
  
  /** @brief Map donde la clave es la posición donde empieza el proceso y el valor es el propio proceso.
  */
  map <int, Proceso> memoria;

  /** @brief Map donde la clave es el nombre del proceso y el valor es la posición donde empieza el proceso.
  */
  map <int, int> posiciones;

  /** @brief Map donde la clave es el tamaño del hueco y el valor el conjunto de las posiciones donde empiezan los huecos de ese tamaño.
  */
  map <int, set<int>> huecos;

  /** @brief Entero que contiene la capacidad del procesador.
  */
  int capacidad;

  /** @brief Entero que contiene la memoria libre del procesador.
  */
  int memlibre;
  
  /** @brief Elimina el proceso de la memoria del procesador y retorna un iterador apuntando al siguiente proceso de la memoria

      \pre Existen por lo menos un procesador (parámetro implícito) y un proceso con ese identificador
      \post Se ha eliminado el proceso con ese id de la memoria del procesador
  */
  map <int, Proceso>:: iterator baja_proceso(int idproceso);
};
#endif