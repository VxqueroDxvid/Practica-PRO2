/** @file Proceso.hh
    @brief Especificación de la clase Proceso
*/

#ifndef _PROCESO_HH_
#define _PROCESO_HH_

#ifndef NO_DIAGRAM
#include <iostream>
#endif

using namespace std;

/** @class Proceso
    @brief Es un proceso, puede estar en espera o en ejecución

*/
class Proceso
{
public:
  //Constructoras

  /** @brief Creadora por defecto. 

      Se ejecuta automáticamente al declarar un proceso.
      \pre <em>cierto</em>
      \post El resultado es un proceso vacío
  */  
  Proceso();

  //Consultoras

  /** @brief Devuelve el identificador del proceso.

      \pre Existe por lo menos el proceso del parámetro implícito
      \post Retorna el identificador del proceso
  */
  int consultar_idproceso() const;

  /** @brief Devuelve la cantidad de memoria que ocuopa el proceso.

      \pre Existe por lo menos el proceso del parámetro implícito
      \post Retorna la cantidad de memoria que ocupa
  */
  int consultar_cant_mem() const;

  //Modificadoras

   /** @brief Avanza el tiempo del circuito.
  
      \pre Existe por lo menos el proceso del parámetro implícito
      \post Retorna el tiempo ya avanzado
  */
  int avanzar_tiempo(int t);
  
  // Lectura de un proceso

  /** @brief Operación de lectura.

      \pre Existe por lo menos el proceso del parámetro implícito (aunque puede que sea vacío)
      \post Proceso después de leer sus atributos
  */
  void leer_proceso();

  // Escritura de un proceso

  /** @brief Operación de escritura.

      \pre Existe por lo menos el proceso del parámetro implícito
      \post Se escribe el proceso
  */
  void imprimir_proceso() const;


private:
  
  /** @brief Entero que contiene el identificador del proceso.
  */
  int idproceso;

  /** @brief Entero que contiene la cantidad de memoria que ocupa el proceso.
  */
  int cant_mem;

  /** @brief Entero con el tiempo que tarda en ejecutarse el proceso.
  */
  int tiempo;
};
#endif