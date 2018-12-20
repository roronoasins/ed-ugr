/**
  * @file vectorD.h
  * @brief Fichero cabecera del TDA vectorD
  */

#ifndef __VECTORDISPERSO_H
#define __VECTORDISPERSO_H

#include <list>     // tipo list STL
#include <utility>  // clase pair


using namespace std;

/**
  *  @brief T.D.A. vectorD
  *
  * Una instancia @e c del tipo de datos abstracto @c vectorD es un objeto,
  * el cual es un conjunto de elementos ordenados. El vector vendra dado
  * por un valor nulo, quedando asi el contenido del vector "dividido"
  * en dos, podiendo iterar sobre el vector de dos formas:
  * Sobre su contenido no nulo, y sobre todo su contenido.
  *
  * Lo representamos:
  *
  * v[n_ele] = {elem, elem, elem... (n_ele)...}
  *
  *
  * Un ejemplo de su uso:
  * @include ejemplo_vectorD.cpp
  * @include frecuencias.cpp
  *
  * @author Pablo Pérez Méndez
  * @author Luis González
  * @date Noviembre 2017
  */

template <typename  T >
class vectorD
{
public:
  /**
    * @brief Iterador sobre los elementos no nulos del vector
    */
  class stored_iterator;
  /**
    * @brief Iterador sobre todos los elementos que componen al vector disperso
    */
  class iterator;

  typedef unsigned int size_type;

  /**
    * @brief Constructor por defecto de la clase.
    */
  vectorD<T>( const  T  & t=  T () );

/**
  * @brief Constructor de copia de la clase
  * @param v vector del tipo vector disperso a construir
  */
  vectorD<T>(  const vectorD< T > & v);
/**
  * @brief Constructor de la clase
  * @param numcomp numero de elementos del vector disperso a construir
  * @param t valor por defecto del vector disperso a constuir
  * @pre numcomp debe ser un natural positivo
  */
  vectorD<T>( int numcomp, const  T  & t =  T () );


/**
  * @brief desctructor
  */
  ~vectorD<T>();


/**
  * @brief size
  * @return Devuelve el tamaño del vector disperso
  */
  size_type size() const;

/**
  * @brief default_value
  * @return Devuelve el valor por defecto del vector disperso
  */
  T  default_value( ) const;

/**
  * @brief Comprueba si esta vacio el vector disperso
  * @return Devuelve si esta vacio
  */
  bool empty();

  list< pair <int, T> > getList();

/**
  * @brief Inserta un elemento en una posicion del vector disperso
  * @param p posicion a insertar
  * @param t valor a insertar
  * @pre p p >= 0
  */
  void set(int p, const  T  & t);

/**
  * @brief Inserta un elemento al final del vector disperso
  * @param t valor a insertar
  */
  void push_back( const  T  & t);

/**
  * @brief Elimina un elemento del vector disperso
  * @param t valor a insertar
  */
  void pop_back(  );

/**
  * @brief Elimina los elemento del vector disperso
  */
  void clear();
  // elimina todos los elementos del vectorD. Tamanio es 0

/**
  * @brief Cambia el tamaño del vector
  * @param s valor a insertar
  * @pre s debe ser un natural positivo
  */
  void resize(int s);
  // cambia el tama~no del vector a "s" elementos. Si s es menor que el tama~no actual, elimina los restantes. Si es mayor,
  // aumenta la capacidad del vector asignando a todos los nuevos elementos el valor nulo.

/**
  * @brief Sobrecarga del operador =
  * @param  x un objeto de tipo vectorD que se copiara en el objeto impl�cito
  */
  vectorD<T> & operator= (const vectorD<T> & x);
  // operador de asignacion

/**
  * @brief Sobrecarga del operador []
  * @param  c posicion sobre la que indexar
  * @pre c c >= 0 && c < size
  */
  const  T  & operator[](int c);

/**
  * @brief Sobrecarga del operador ==
  * @param  x un objeto de tipo vectorD que se copiara en el objeto implícito
  */
  bool operator==( const vectorD<T> & x);

/**
  * @brief Sobrecarga del operador !=
  * @param  x un objeto de tipo vectorD que se copiara en el objeto implícito
  */
  bool operator!=( const vectorD<T> & x);



/**
  * @brief begin del vector disperso
  * @return Devuelve un iterador del vectorD al inicio de todos los elementos de este
  */
  iterator begin();

  /**
    * @brief end del vector disperso
    * @return Devuelve un iterador del vectorD al final(siguiente al ultimo) de todos los elementos de este
    */
  iterator end();

/**
  * @brief sbegin del vector disperso(solo del storage)
  * @return Devuelve un iterador(de los elementos almacenados) del vectorD al inicio(siguiente al ultimo) de todos los elementos de este
  */
  stored_iterator sbegin();

/**
  * @brief send del vector disperso(solo del storage)
  * @return Devuelve un iterador(de los elementos almacenados) del vectorD al final(siguiente al ultimo) de todos los elementos de este
  */
  stored_iterator send();


private:
/**
  * @page repConjunto Rep del TDA vectorD
  *
  * @section invConjunto Invariante de la representación
  *
  * El invariante es \e (vd,n_ele,v_nulo) :
  *   0 <= vd.size() < n_ele;  //Fallo tipo 1
  *   vd[i].second != v_nulo, para todo i = 0, ..., vd.size()-1; // Fallo tipo 2
  *   vd[i].first >=0, para todo i = 0, ..., vd.size()-1; // Fallo tipo 3
  *   vd[i].first < vd[j].first si i<j // Fallo tipo 4
  *
  * @section faConjunto Función de abstracción
  *
  * Un objeto válido @e rep del TDA FechaHistorica representa a
  *
  * FA(rep): rep -- > vector
  * (vd=[ (a,v1), (b,v2), ..., (n,vn) ]
  *  n_ele = M                           -------->   pos: 0 1 2 ... a-1 a ... x .... b....  ... n-1 n  n+1 ..... M-1
  *                                                  val: t t t ....t  v1 ... t .... v2 ..  ... t   vn  t  ...... t
  *  v_nulo = t
  *
  */

  list< pair<int, T > > vd;
  size_type n_ele;
  T   v_nulo;

/**
  * @brief Comprueba si el IR del TDA es cumplido
  * @return devuelve el tipo de fallo segun indica el IR. En caso de cumplir el IR se devuelve 0
  */
  int checkRepFails();

public:
  class stored_iterator{
    public:
      friend class vectorD<T>;

      stored_iterator() {}
      stored_iterator(const stored_iterator & d) : ite(d.ite) {}
      const pair<int, T > & operator *(  ) { return (*ite);}
      stored_iterator & operator++( ) {++ite; return *this;}
      stored_iterator operator++(int ) {stored_iterator tmp(*this); ++ite; return tmp;}
      bool operator == (const stored_iterator & d) {return ite == d.ite;}
      bool operator != (const stored_iterator & d) {return ite != d.ite; }

    private:
      typename list<pair<int, T > >::iterator ite;
  };

  class iterator{
    public:
      friend class vectorD<T>;
      iterator(){};
      iterator(const iterator & d) {*this = d;}
      const  T  & operator *(  ){
    	  stored_iterator st_it = el_vect->sbegin();
    		bool condition = true;

    		while (condition) {

    			if (st_it != el_vect->send()) {

    				if ((*st_it).first < i_vect)
    					++st_it;

    				else
    					condition = false;
    			}

    			else
    				condition = false;

  		}

		if (st_it != el_vect->send()) {

			if ((*st_it).first == i_vect)
				return (*st_it).second;

		}


		return el_vect->v_nulo;

	  }


    iterator & operator++( ){
	  	++i_vect;

		if (i_vect > (*ite_rep).first)
			++ite_rep;

		return *this;
	  }						     // operador ++ prefijo (invocado con ++it)


      iterator operator++(int )
	  {
		iterator tmp(*this);
		++i_vect;

		if (i_vect > (*ite_rep).first)
			++ite_rep;

		return tmp;
	  }							// operador ++ posfijo (invocado con it++)

	  iterator operator+=(const int inc)
	  {
		for (int i = 0; i < inc; i++){
			++i_vect;

			if (i_vect > (*ite_rep).first)
				++ite_rep;
		}

		return *this;
	  }

      bool operator == (const iterator & d) {return ((i_vect == d.i_vect) && (ite_rep == d.ite_rep) && (el_vect == d.el_vect));}
      bool operator != (const iterator & d) {return (!(*this == d));}
      iterator & operator=(const iterator & d) {i_vect = d.i_vect; ite_rep = d.ite_rep; el_vect = d.el_vect; return (*this);}

    private:
      int i_vect; // indice sobre el vector abstracto
      typename list<pair<int, T > >::iterator ite_rep; //iterador a la representacion
      vectorD<T> *el_vect; // ptro al vector para obtener el valor nulo del vector
      /* FA e IR*/
      /* FA(rep): rep -- > iterador sobre vector abstracto
        (i_vect, ite_rep, el_vec):
        i_vect = k
        ite_rep = p
        el_vect = v
         --------->
        iterador a la posicion k-esima del vector abstracto con valor nulo (*v).v_nulo
         */

        /* IR :
         IR(rep): rep ---> bool
        (i_vect, ite_rep):
         --------->
         0 <= i_vect <=n_ele
         i_vect <= (*ite_rep).first
         */

  };


};

// guardar pos del storeb_obj y comparar con stored_iterator(asi saber si devolver v_nulo o v_stored),

#include "vectorD.hxx"

#endif
