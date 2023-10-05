#ifndef PRACTICA_1B_UTM_H
#define PRACTICA_1B_UTM_H


class UTM {
private:
    float latitud=0;

    float longitud=0;
public:
    virtual ~UTM();

    UTM()=default;

    UTM(const float  &latitud,const float &longitud);

    float getLatitud() const;

    void setLatitud(float latitud);

    float getLongitud() const;

    void setLongitud(float longitud);

};


#endif //PRACTICA_1B_UTM_H
