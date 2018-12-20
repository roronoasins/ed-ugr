#include <list>     // tipo list STL
#include <utility>  // clase pair
#include "vectorD.h"

using namespace std;

//////////// constructores //////////////

vectorD<T>( const  T  & t=  T () ) {}
// constructor por defecto. t hace referencia al valor por defecto del vector

vectorD<T>(  const vectorD< T > & b){

}
/** constructor primitivo que hace una copia del vector disperso b. */

vectorD<T>( int numcomp, const  T  & t =  T () ) {

}
/** constructor primitivo que crea un vectorD con numcomp componentes, todas ellas iguales a t. numcomp debe ser mayor que cero.
t hace referencia al valor por defecto
 */

 ////////////// destructor ////////////
 ~vectorD<T>(){
   vd.clear();
 }

 /////////// Consultores ////////////
 size_type size() const{
   return n_ele;
 }
 // Devuelve el tamaño del vectorD

 T  default_value( ) const{
   
 }
 // Devuelve el valor por defecto de vectorD

 bool empty();
 // el vectorD esta vacio?
