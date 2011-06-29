#ifndef PHYSICOBJECT_H
#define PHYSICOBJECT_H

#include <QObject>
#include <QElapsedTimer>
#include "PhysicSize.h"
#include "Point.h"
#include "Vector3.h"

const preal f_defaultMass = 0.01f;

class PhysicObject : public QObject
{
    Q_OBJECT
public:
    PhysicObject(preal mass = f_defaultMass);

    // Modifie toutes les conposantes des vecteurs et coordonnées de l'objet
    void processMove();

    // Applique un vecteur force avec ces composantes en NEWTON
    void applyForcev(Vector3 v3_force);

    inline preal getMass() const {return f_mass;}

public: // Public temporairement

    QElapsedTimer m_elapsedTimer;

    preal f_mass; // La masse de l'objet en KG

    Point pt_position; // La position de l'objet
    Vector3 v3_velocity, v3_acceleration; // Le vecteur vitesse et le vecteur accélération
    Vector3 v3_forces; // Somme des forces appliquées à l'objet
};

#endif // PHYSICOBJECT_H
