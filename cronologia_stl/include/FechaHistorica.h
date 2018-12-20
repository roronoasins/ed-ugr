/**
  * @file FechaHistorica.h
  * @brief Fichero cabecera del TDA FechaHistorica
  *
  */

#ifndef __FECHAHISTORICA
#define __FECHAHISTORICA

#include <iostream>
#include  <vector>
#include <string>
#include <set>

using namespace std;

/**
  *  @brief T.D.A. FechaHistorica
  *
  * Una instancia @e c del tipo de datos abstracto @c FechaHistorica es un objeto
  * el cual se compone de una fecha y uno o más eventos sucedidos en dicha fecha.
  * La fecha representará únicamente el año en el que tuvieron lugar los
  * acontecimientos en forma de número natural, y cada uno de los acontecimientos
  * podrán contener más de una palabra. Lo representamos:
  *
  *
  * anio#acontecimientos
  *
  *
  * @author Luis González
  * @author Pablo Pérez
  * @date Diciembre 017
  */


  class FechaHistorica {

   private:
  /**
    * @page repConjunto Rep del TDA FechaHistorica
    *
    * @section invConjunto Invariante de la representacion
    *
    * El invariante es \e rep.acontecimientos.size()!=0
    *
    * @section faConjunto Funcion de abstraccion
    *
    * Un objeto valido @e rep del TDA FechaHistorica representa a
    *
    * (rep.anio,rep.acontecimientos)
    *
    */

    typedef   pair<int, set<string> > Fecha;
    Fecha fecha;


    /**
      * @brief Metodo privado de copia, añade acontecimientos y palabras clave
      * @param f FechaHistorica a copiar al objeto implicito
      */
      void copia(const FechaHistorica &f);

   public:
     using const_iterator = set<string>::const_iterator;
     using iterator = set<string>::iterator;

  /**
    * @brief Constructor por defecto de la clase. Crea un objeto sin acontecimientos, año -1
    */
     FechaHistorica();

  /**
    * @brief Constructor de la clase
    * @param anio año de la fecha histórica a construir
    * @param a conjunto de acontecimientos de la fecha histórica a construir
    * @return Crea la fecha histórica anio#acontecimiento
    * @pre anio debe ser un natural positivo
    */
      FechaHistorica(int anio, set<string> acontecimientos);

    /**
      * @brief Constructor de copias de la clase
      * @param f FechaHistorica que se copiara en el objeto implicito
      */
      FechaHistorica (const FechaHistorica &f);

      FechaHistorica( int anio, string acontecimientos);

      /**
        * @brief desctructor
        */
      ~FechaHistorica();

      /**
        * @brief Anio
        * @return Devuelve el año de la fecha histórica
        */
        int getAnio () const;

    /**
      * @brief acontecimientos
      * @return Devuelve los acontecimientos dados en el año
      */
        set<string> getAcontecimientos () const;

        string getAcontecimientoConcreto(int contador);

      /**
        * @brief Asignacion del año
        * @param an año para asignar
        * @pre an debe ser un entero
        */
        void setAnio(int an);

        /**
          * @brief Asignacion de acontecimientos
          * @param ac acontecimientos para asignar
          * @pre ac debe de ser un acontecimiento diferente a alguno ya existente
          */
        void setAcontecimientos(set<string> an);



        FechaHistorica::iterator begin ();

        FechaHistorica::iterator end ();

        FechaHistorica::const_iterator cbegin ();

        FechaHistorica::const_iterator cend ();

    /**
      * @brief Concatena objetos del tipo FechaHistorica
      * @param f FechaHistorica a concatenar con el objeto implicito
      */
        FechaHistorica operator+(const FechaHistorica &f);

      /**
        * @brief Sobrecarga del operador =
        * @param  FechaHistorica que se copiara en el objeto implicito
        */
        FechaHistorica& operator=(const FechaHistorica &f);

    /**
      * @brief Sobrecarga del operador +=
      * @param f FechaHistorica a concatenar con el objeto implicito
      */
        void operator+=(const FechaHistorica &f);

    /**
      * @brief Salida de una FechaHistorica a ostream
      * @param os stream de salida
      * @param f FechaHistorica a escribir
      * @post Se obtiene en \a os la cadena (anio#vector<acontecimientos>) con \e anio,vector<acontecimientos> los valores
      *   del año y acontecimientos de \a f
      */
        friend ostream& operator<< (ostream& os, const FechaHistorica &f);

    /**
      * @brief Entrada de una FechaHistorica desde istream
      * @param is stream de entrada
      * @param f FechaHistorica que recibe el valor
      * @retval La FechaHistorica le�da en f
      * @pre La entrada tiene el formato (anio#vector<acontecimientos>) con \e anio,\e vector<acontecimientos> los valores
      *   del año y acontecimientos
      */
        friend istream& operator>> (istream& is, FechaHistorica &f);

};
    #endif
