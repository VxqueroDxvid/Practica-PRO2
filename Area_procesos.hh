/** @file Area_procesos.hh
    @brief Especificación de la clase Area_procesos
*/

#ifndef _AREA_PROCESOS_HH_
#define _AREA_PROCESOS_HH_

#include "Prioridad.hh"
#include "Cluster.hh"

#ifndef NO_DIAGRAM
#include <string>
#include <map>
#endif

using namespace std;

/** @class Area_procesos
    @brief Representa un conjunto de prioridades ordenadas por identificador

*/
class Area_procesos
{
public:
  //Constructoras

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un área de procesos.
      \pre <em>cierto</em>
      \post El resultado es un área de procesos vacía
  */  
  Area_procesos();

  //Modificadoras

  /** @brief Si no hay ninguna prioridad con ese identificador, se añade al área de procesos.

      \pre No existe una prioridad con ese identificador
      \post Se añade la prioridad al área de procesos
  */
  void alta_prioridad(const string& p);

  /** @brief Si hay una prioridad con ese identificador, se elimina del área de procesos.

      \pre Existe una prioridad con ese identificador
      \post Se elimina la prioridad del área de procesos de espera
  */
  void baja_prioridad(const string& p);

  /** @brief Si no hay ningún proceso con ese mismo identificador en la prioridad y existe esa prioridad en el área de procesos el proceso pasa al área de procesos.

      \pre Existe una prioridad con ese identificador y ningún proceso con ese mismo identificador
      \post Se añade el proceso al área de procesos de espera con dicha prioridad
  */
  void alta_proceso_espera(const string& idprioridad, Proceso& p);

  /** @brief Envía n procesos en espera al cluster por orden de prioridad.

      \pre <em>cierto</em>
      \post Se han enviado n procesos en espera al cluster por orden de prioridad
  */
  void enviar_procesos_cluster(Cluster& c, int n);

   //Consultoras

  /** @brief Consulta si existe una prioridad con ese identificador.

      \pre <em>cierto</em>
      \post Devuelve cierto si existe una prioridad con el identificador p
  */
  bool existe_prioridad(const string& p) const;

  /** @brief Consulta si existe un proceso con ese identificador.

      \pre Existe una prioridad con ese identificador
      \post Devuelve cierto si existe un proceso con el identificador p
  */
  bool existe_proceso_ae(const string& idprioridad, int p) const;

  /** @brief Consulta si la prioridad tiene procesos pendientes (si la lista no está vacía).

      \pre Existe una prioridad con ese identificador
      \post Devuelve cierto si la prioridad tiene procesos pendientes
  */
  bool tiene_proc_pendientes(const string& p) const;

   // Lectura de un área de procesos

  /** @brief Operación de lectura.

      \pre <em>cierto</em>
      \post Lee área de procesos
  */
  void leer_area_procesos();
  
  // Escritura de un área de procesos

  /** @brief Operación de escritura.

      \pre <em>cierto</em>
      \post Escribe los procesos pendientes de todas las prioridades del área de espera por orden creciente de prioridad
  */
  void imprimir_area_espera()const;

  /** @brief Operación de escritura.

      \pre Existe una prioridad con ese identificador
      \post Escribe los procesos pendientes de la prioridad con ese id y el número de procesos aceptados y rechazados
  */
  void imprimir_prioridad(const string& idprioridad)const;


private:

  /** @brief Mapa con los identificadores de las prioridades como clave y las prioridades como valor.
  */
  map <string, Prioridad> m;
};
#endif