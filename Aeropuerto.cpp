#include "Aeropuerto.h"

#include <utility>

Aeropuerto::Aeropuerto() :id(""), ident(""), tipo(""), nombre(""), continente(""),
                          iso_pais(""),posicion( UTM()){
}


Aeropuerto::~Aeropuerto() {

}

Aeropuerto::Aeropuerto(std::string id, std::string ident, std::string tipo,
                        std::string nombre,  std::string continente,  std::string isoPais,const UTM &pos) : id(std::move(id)), ident(ident), tipo(tipo), nombre(nombre), continente(continente),
                                                                                                                              iso_pais(isoPais),posicion(pos) {

}
Aeropuerto& Aeropuerto::operator=(const Aeropuerto &orig){
    if(this!=&orig){
        id=orig.id;
        ident=orig.ident;
        tipo=orig.tipo;
        nombre=orig.nombre;
        continente=orig.continente;
        iso_pais=orig.iso_pais;
        posicion=orig.posicion;
    }
    return *this;
}




Aeropuerto::Aeropuerto(const Aeropuerto& orig) : id(orig.id), ident(orig.ident), tipo(orig.tipo), nombre(orig.nombre), continente(orig.continente),
                                                 iso_pais(orig.iso_pais){
}


const std::string &Aeropuerto::getId() const {
    return id;
}

void Aeropuerto::setId(const std::string &id) {
    Aeropuerto::id = id;
}

const std::string &Aeropuerto::getIdent() const {
    return ident;
}

void Aeropuerto::setIdent(const std::string &ident) {
    Aeropuerto::ident = ident;
}

const std::string &Aeropuerto::getTipo() const {
    return tipo;
}

void Aeropuerto::setTipo(const std::string &tipo) {
    Aeropuerto::tipo = tipo;
}

const std::string &Aeropuerto::getNombre() const {
    return nombre;
}

void Aeropuerto::setNombre(const std::string &nombre) {
    Aeropuerto::nombre = nombre;
}

const std::string &Aeropuerto::getContinente() const {
    return continente;
}

void Aeropuerto::setContinente(const std::string &continente) {
    Aeropuerto::continente = continente;
}

const std::string &Aeropuerto::getIsoPais() const {
    return iso_pais;
}

void Aeropuerto::setIsoPais(const std::string &isoPais) {
    iso_pais = isoPais;
}

UTM Aeropuerto::getUtm() const {
    return posicion;
}

void Aeropuerto::setUtm(UTM &utm) {
    Aeropuerto::posicion = utm;
}

bool Aeropuerto::operator==(const Aeropuerto &orig) const {
    return  (id==orig.id);
}

bool Aeropuerto::operator<(const Aeropuerto &orig) const {
    return  (stoi(id) < stoi(orig.id));
}

bool Aeropuerto::operator>(const Aeropuerto &orig) const  {
    return  (stoi(id) > stoi(orig.id));

}