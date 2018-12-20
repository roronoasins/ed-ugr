/**
  * @file Cronologia.h
  * @brief Fichero cabecera del TDA Cronologia
  *
  */

#ifndef __CRONOLOGIA
#define __CRONOLOGIA

#include <iostream>
#include <map>
#include "FechaHistorica.h"

using namespace std;

typedef map<int, FechaHistorica > MapaFH;
/**
  *  @brief T.D.A. Cronologia
  *
  * Una instancia @e c del tipo de datos abstracto @c Cronologia es un objeto,
  * el cual es un conjunto de fechas histÃ³ricas ordenadas por aÃ±o.
  * Lo representamos:
  *
  * anio#acontecimientosautor
  * anio#acontecimientosautor
  *
  * Un ejemplo de su uso:
  * @include pruebacronologia.cpp
  *
  * @author Luis González Romero
  * @author Pablo Pérez Méndez
  * @date Diciembre 2017
  */

  class Cronologia {

   private:
  /**
    * @page repConjunto Rep del TDA Cronologia
    *
    * @section invConjunto Invariante de la representacion
    *
    * El invariante es \e rep.den!=0
    *
    * @section faConjunto Funcion de abstraccion
    *
    * Un objeto valido @e rep del TDA Racional representa al valor
    *
    * (rep.num,rep.den)
    *
    */




    MapaFH crono; /**< conjunto de las fechas historicas > */

   public:
 		typedef typename map <int, FechaHistorica>::iterator iterator;
  	typedef typename map <int, FechaHistorica>::const_iterator const_iterator;


  /**
    * @brief Constructor por defecto de la clase. Crea el conjunto de fechas histÃ³ricas formado por la fecha histÃ³rica por defecto
    */
    Cronologia();

  /**
    * @brief Constructor de la clase
    * @param  crono mapa de la cronologia a crear
    * @return Crea la cronologia
    */
    Cronologia(MapaFH crono);

  /**
    * @brief Constructor de copias de la clase
    * @param crono  conjunto de fechas historicas a construir
    */
    Cronologia (const Cronologia& crono);

  /**
    * @brief anio
    * @return Devuelve el aÃ±o de un acontecimiento dado
    */
    int anio (string acontecimiento);

  /**
    * @brief Acontecimientos
    * @param anio anio de los acontecimientos solicitados
    * @return Devuelve los acontecimientos dados en un aÃ±o
    */
    set<string> acontecimientos (int anio);

  /**
    * @brief Eventos del tipo FechaHistorica
    * @param anio anio de los acontecimientos solicitados
    * @return Devuelve los acontecimientos dados en un aÃ±o
    */
    FechaHistorica getEventos ( int anio );

  /**
    * @brief inserta una cronologia
    * @param c cronologia a añadir
    * @return Devuelve los acontecimientos dados en un año
    */
    void setCrono (const Cronologia c);

  /**
    * @brief getCrono
    * @return Devuelve un mapa de crono
    */
    MapaFH getCrono() const;

    string acontecimientoconcreto (int anio, int contador);

  /**
    * @brief desctructor
    */
    ~Cronologia ();

  /**
    * @brief añade una fecha
    * @param f FechaHistorica a añadir
    */
    void AniadeFecha (const FechaHistorica & f);

    Cronologia & operator= (const Cronologia & otro);

  /**
    * @brief Concatena un mapa
    * @param otro MapaFH a concatenar con el objeto implicito
    */
    Cronologia operator + (const MapaFH & otro);

  /**
    * @brief Concatena el objeto implicito con un objeto del tipo FechaHistorica
    * @param otro FechaHistorica a concatenar con el objeto implicito
    */
    Cronologia operator + (const FechaHistorica & otro);

  /**
    * @brief Sobrecarga del operador +=
    * @param f FechaHistorica a concatenar con el objeto implicito
    */
    Cronologia & operator += (const FechaHistorica & otro);

  /**
    * @brief Sobrecarga del operador +=
    * @param otro Cronologia a concatenar con el objeto implicito
    */
    Cronologia & operator += (const Cronologia & otro);

    /**
      * @brief Salida de una Cronologia a ostream
      * @param os stream de salida
      * @param c Cronologia a escribir
      */
    friend ostream& operator<< (ostream& os, const Cronologia &c);

    /**
      * @brief Entrada de una FechaHistorica desde istream
      * @param is stream de entrada
      * @param c Cronologia que recibe el valor
      */
    friend istream& operator>> (istream& is, Cronologia &c);

    /**
      * @brief Recuento estadistico de una cronologia
      * @param c Cronologia a estudiar
      * @post Se imprime el estudio por pantalla
      */
    friend void recuentoEventos(const Cronologia & c);

  /**
    * @brief obtencion de un conjunto de FechaHistorica dentro de un intervalo
    * @param inicio año de comienzo
    * @param fin año final
    * @return Devuelve una Cronologia con los acontecimientos dados en un intervalo
    * @pre debe especificarse tanto una fecha de inicio como de final
    */
    Cronologia intervalo (int inicio, int fin);

  /**
    * @brief obtencion de la union de dos Cronologias
    * @param inicio año de comienzo
    * @param fin año final
    * @return Devuelve una Cronologia con los acontecimientos dados en un intervalo
    */
    void Union(const Cronologia & c1, const Cronologia & c2);

  /**
    * @brief obtencion de un conjunto de FechaHistorica con apariciones de la palabra clave
    * @param buscar palabra clave a buscar
    * @return Devuelve una Cronologia con los acontecimientos donde haya apariciones de la palabra clave especificada
    */
    MapaFH PalabraClave (string buscar);

  /**
  	* @brief Declaración de los begin y end de ambos iterators.
  	*/

  	Cronologia::iterator begin ();

  	Cronologia::iterator end ();

  	Cronologia::const_iterator cbegin () const;

  	Cronologia::const_iterator cend () const;

};
#endif
