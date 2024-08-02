#pragma once

#ifndef ENTITY_H
#define ENTITY_H

// Klasa po której dziedzyczą obiekty mogące być indeksowane: Produkty, Klienci, Zamówienia

class Entity{
private:
    inline static unsigned int idCounter = 0;
protected:
    unsigned int id;
public:
    Entity() : id(idCounter){++idCounter;}
    virtual ~Entity() {}
    unsigned int GetId() const {return id;}
};

#endif // ENTITY_H
