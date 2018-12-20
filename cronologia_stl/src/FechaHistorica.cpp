#include<iostream>
#include "FechaHistorica.h"
#include <vector>
#include <string>
#include <set>

using namespace std;

//Constructor por defecto
FechaHistorica::FechaHistorica(){
  fecha.first = -1;
}

//Constructor
FechaHistorica::FechaHistorica( int anio, set<string> acontecimientos = {}){
  this->fecha.first = anio;
  this->fecha.second = acontecimientos;
}

//Constructor de copia
FechaHistorica::FechaHistorica (const FechaHistorica& f){
    this->fecha.first = f.getAnio();                         // se copia el año
    this->fecha.second = f.getAcontecimientos();   // se copian los acontecimientos de la fecha historica pasada como parametro
}

FechaHistorica::FechaHistorica( int anio, string acontecimientos = {}){
  this->fecha.first = anio;
  this->fecha.second.insert(acontecimientos);
}

//desctructor
FechaHistorica::~FechaHistorica(){
  fecha.first = -1;
  fecha.second.clear();
}

int FechaHistorica::getAnio() const{
  return fecha.first;
}

set<string> FechaHistorica::getAcontecimientos() const{
  return fecha.second;
}

string FechaHistorica::getAcontecimientoConcreto(int contador) {

	iterator it = begin();

	string evento = "";

	for (int i = 0; it != end () && i < contador; ++i, ++it) {
		if (i + 1 == contador)
			evento = *it;

	}

	return (evento);
}

void FechaHistorica::setAnio(int an){
  this->fecha.first = an;
}

void FechaHistorica::setAcontecimientos(set<string> ac){
  set<string>::iterator it = ac.begin();

  for (; it != ac.end(); it++)
    fecha.second.insert(*it);

}

FechaHistorica FechaHistorica::operator+(const FechaHistorica &f){
  FechaHistorica fecha;

  if ( f.getAnio() == this->getAnio() ){
    fecha = *this;
    fecha += f;
  }

  return fecha;
}

FechaHistorica& FechaHistorica::operator=(const FechaHistorica &f){
    if ( &f != this ){
      this->fecha.second.clear();
      this->fecha.first = f.getAnio();
      this->fecha.second = f.getAcontecimientos();
    }
    return *this;
}

void FechaHistorica::operator+=(const FechaHistorica &f){
  if ( f.getAnio() == this->getAnio() ){
    FechaHistorica::iterator it = this->begin();

    for ( it; it != this->end(); it++ )
      this->fecha.second.insert(*it);
  }
}


FechaHistorica::iterator FechaHistorica::begin () {

	iterator i = fecha.second.begin();

	return (i);


}

FechaHistorica::iterator FechaHistorica::end () {

	iterator i = fecha.second.end();

	return (i);


}

FechaHistorica::const_iterator FechaHistorica::cbegin ()
{

	const_iterator i = fecha.second.begin();

	return (i);


}

FechaHistorica::const_iterator FechaHistorica::cend ()
{

	const const_iterator i = fecha.second.end();

	return (i);


}
