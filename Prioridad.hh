/** @file Prioridad.hh
    @brief Especificación de la clase Prioridad
*/

#ifndef _PRIORIDAD_HH_
#define _PRIORIDAD_HH_

#include "Proceso.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <list>
#include <set>
#endif

using namespace std;

/** @class Prioridad
    @brief Representa un conjunto de procesos ordenados por antigüedad

*/
class Prioridad
{
public:
  //Constructoras

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar una prioridad.
      \pre <em>cierto</em>
      \post El resultado es una prioridad vacía
  */  
  Prioridad();
  
  //Modificadoras

 /** @brief Añade el proceso p en la prioridad

      \pre Existen una prioridad (parámetro implícito) y un proceso con ese identificador
      \post Inserta el proceso p en la prioridad
  */
  void alta_proceso_espera(Proceso& p);

  /** @brief Envía n procesos en espera al cluster por orden de prioridad.

      \pre Existe la prioridad del parámetro implícito, por lo menos
      \post Se han enviado n procesos en espera al cluster por orden de prioridad
  */
  void enviar_procesos_cluster(Cluster& c, int& n);
  
  //Consultoras

   /** @brief Consulta si existe un proceso con el identificador p.

      \pre Existe una prioridad por lo menos (parámetro implícito)
      \post Devuelve cierto si existe un proceso con el identificador p
  */
  bool existe_proceso_ae(int p) const;

  /** @brief Consulta los procesos aceptados de la prioridad.

      \pre Existe una prioridad por lo menos (parámetro implícito)
      \post Devuelve el número de procesos aceptados
  */
  int consultar_aceptados() const;

   /** @brief Consulta si la prioridad tiene procesos pendientes (si la lista no está vacía).

      \pre Existe una prioridad por lo menos (parámetro implícito)
      \post Devuelve cierto si la prioridad tiene procesos pendientes
  */
  bool tiene_proc_pendientes() const;

  // Escritura de una prioridad

  /** @brief Operación de escritura. 

      \pre Existe una prioridad por lo menos (parámetro implícito)
      \post Escribe el contenido de la lista de la prioridad, sus procesos aceptados y los rechazados
  */
  void imprimir_prioridad() const;


private:
  
  /** @brief Lista de procesos que estarán ordenados por antigüedad.
  */
  list<Proceso> l;

  /** @brief Set con los identificadores de los procesos ordenados crecientemente.
  */
  set<int> ids;

  /** @brief Entero con el número de procesos aceptados por el clúster.
  */
  int aceptados;

  /** @brief Entero con el número de procesos rechazados por el clúster.
  */
  int no_aceptados;
};
#endif