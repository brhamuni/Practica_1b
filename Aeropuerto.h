#include <string>
#include "UTM.h"
#include "stdexcept"
#include "algorithm"


#ifndef PRACTICA_1B_AEROPUERTO_H
#define PRACTICA_1B_AEROPUERTO_H




class Aeropuerto {
private:
    std::string id;
    std::string ident;
    std::string tipo;
    std::string nombre;
    std::string continente;
    std::string iso_pais;
    UTM posicion;

public:

    UTM getUtm() const;

    void setUtm(UTM &utm);

    const std::string &getId() const;

    void setId(const std::string &id);

    const std::string &getIdent() const;

    void setIdent(const std::string &ident);

    const std::string &getTipo() const;

    void setTipo(const std::string &tipo);

    const std::string &getNombre() const;

    void setNombre(const std::string &nombre);

    const std::string &getContinente() const;

    void setContinente(const std::string &continente);

    const std::string &getIsoPais() const;

    void setIsoPais(const std::string &isoPais);

    Aeropuerto(std::string id, std::string ident, std::string tipo,
               std::string nombre,  std::string continente,  std::string isoPais,const UTM &pos);

    Aeropuerto(const Aeropuerto& orig);

    Aeropuerto &operator=(const Aeropuerto &orig);

    Aeropuerto();

    bool operator==(const Aeropuerto &orig)const ;

    bool operator<(const Aeropuerto &orig)const;

    bool operator>(const Aeropuerto &orig)const;

    virtual ~Aeropuerto();
};

#endif //PRACTICA_1B_AEROPUERTO_H
