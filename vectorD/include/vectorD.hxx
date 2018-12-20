#include <assert.h>
#include <algorithm>
#include <list>

using namespace std;

template <class T>
vectorD<T>::vectorD(const  T  & t){
  n_ele = 0;
  v_nulo = t;
}

template <class T>
vectorD<T>::vectorD(const vectorD<T> & b){
  this->vd = b.getList();
  this->n_ele = b.size();
  this->v_nulo = b.default_value();
}

template <class T>
vectorD<T>::vectorD(int numcomp, const  T  & t ){
  assert(numcomp >= 0);
  n_ele = numcomp;
  v_nulo = t;
}

template <class T>
vectorD<T>::~vectorD<T>(){
  this->clear();
  }

template <class T>
list< pair <int, T> > vectorD<T>::getList(){
  return vd;
}

template <class T>
typename vectorD<T>::size_type vectorD<T>::size() const{
  return n_ele;
}

template <class T>
T vectorD<T>::default_value( ) const{
  return v_nulo;
}

template <class T>
bool vectorD<T>::empty(){
  return n_ele == 0;
}

template <class T>
void vectorD<T>::set(int p, const  T  & t){
  typename list<pair<int,T > >::iterator it = vd.begin();
  int i = 0;

  while( i < p  && it != vd.end()) {
	if ((*it).first == i)
		++it;

	++i;
  }

  if ( p > this->size() )  resize(p);

  if ( t != v_nulo ){
    if ( (*it).first == p && !vd.empty() )
        (*it).second = t;
    else {
      	pair <int, T> par(p, t);
        vd.insert(it, par);
    }
  }else
		vd.erase(it);

}

template <class T>
void vectorD<T>::push_back( const  T  & t){
  if ( t != v_nulo ){
    pair <int, T> par(n_ele, t);
    vd.push_back(par);
  }

  n_ele++;
}

template <class T>
void vectorD<T>::pop_back(  ){

  n_ele--;

  typename list<pair<int,T > >::iterator it = vd.end()--;

  if ((*it).first != size())
  	vd.pop_back();

}

template <class T>
void vectorD<T>::clear(){
  n_ele = 0;
  vd.clear();
}

template <class T>
void vectorD<T>::resize(int s){
  if ( s < n_ele ){
  typename list<pair<int,T> >::iterator it = vd.begin();
    bool size = false;
    for (; it != vd.end() && !size; ++it){
      if ( (*it).first > s )
        size = true;
    }
    vd.erase(it,vd.end());
  }
  n_ele = s;
}

template <class T>
vectorD<T> & vectorD<T>::operator=(const vectorD<T> & x){
    this->clear();
    vd = x.getList();
    n_ele = x.size();
}

template <class T>
const  T  & vectorD<T>::operator[](int c) {
  assert ( c >= 0 && c < n_ele );
  vectorD<T>::iterator it = (*this).begin();
  it += c;
  return *it;
}

template <class T>
bool vectorD<T>::operator==( const vectorD<T> & x){
  list< pair<int, T > > list(x.getList());
  bool igual = true;
  vectorD<T>::iterator it = vd.begin(), second_it = list.begin();
  igual = this->size() != x.size() ? false : true;

  for (; it != vd.end() && igual ; it++)
    igual = *it != *second_it ? false : true; //if ( *it != *second_it )  igual = false;

  return igual;
}

template <class T>
bool vectorD<T>::operator!=( const vectorD<T> & x){
  return !( *this == x);
}

template <class T>
typename vectorD<T>::iterator vectorD<T>::begin(){
  vectorD<T>::iterator tmp_it;

  tmp_it.i_vect = 0;
  tmp_it.ite_rep = vd.begin();
  tmp_it.el_vect = this;

   return tmp_it;
}

template <class T>
typename vectorD<T>::iterator vectorD<T>::end(){
  vectorD<T>::iterator tmp_it;

  tmp_it.i_vect = n_ele;
  tmp_it.ite_rep = vd.end();
  tmp_it.el_vect = this;

  return tmp_it;
}

template <class T>
typename vectorD<T>::stored_iterator vectorD<T>::sbegin(){
  vectorD<T>::stored_iterator tmp_it;

  tmp_it.ite = vd.begin();

  return tmp_it;
}

template <class T>
typename vectorD<T>::stored_iterator vectorD<T>::send(){
  vectorD<T>::stored_iterator tmp_it;

  tmp_it.ite = vd.end();

  return tmp_it;
}
