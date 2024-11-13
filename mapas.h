#include <soldados.h>
#include <zombies.h>
#include <accesorios.h>
#include <string>
#include <iostream>
#pragma once

// Estructura para las selecciones del metro en el mapa del juego
struct SeccionMetro
{
    string nombre;
    bool hayZombies;
    bool hayAccesorios;
    SeccionMetro *siguiente;

    SeccionMetro(const string &nombre, bool zombies, bool accesorios)
        : nombre(nombre), hayZombies(zombies), hayAccesorios(accesorios), siguiente(nullptr) {}
};

class MapaMetro
{
private:
    SeccionMetro *inicio;

public:
    MapaMetro() : inicio(nullptr) {}

    void agregarSeccion(const string &nombre, bool hayZombies, bool hayAccesorios)
    {
        SeccionMetro *nuevaSeccion = new SeccionMetro(nombre, hayZombies, hayAccesorios);
        if (!inicio)
        {
            inicio = nuevaSeccion;
        }
        else
        {
            SeccionMetro *temp = inicio;
            while (temp->siguiente)
            {
                temp = temp->siguiente;
            }
            temp->siguiente = nuevaSeccion;
        }
    }

    bool eliminarSeccion(const string &nombre)
    {
        if (!inicio)
            return false;

        if (inicio->nombre == nombre)
        {
            SeccionMetro *temp = inicio;
            inicio = inicio->siguiente;
            delete temp;
            return true;
        }

        SeccionMetro *actual = inicio;
        while (actual->siguiente && actual->siguiente->nombre != nombre)
        {
            actual = actual->siguiente;
        }

        if (actual->siguiente)
        {
            SeccionMetro *temp = actual->siguiente;
            actual->siguiente = temp->siguiente;
            delete temp;
            return true;
        }

        return false; // No se encontró la sección
    }

    bool editarSeccion(const string &nombre)
    {
        SeccionMetro *actual = inicio;
        while (actual)
        {
            if (actual->nombre == nombre)
            {
                cout << "Ingrese el nuevo nombre de la seccion: ";
                cin.ignore();
                getline(cin, actual->nombre);
                cout << "¿Hay zombies en esta seccion? (1 = Si, 0 = No): ";
                cin >> actual->hayZombies;
                cout << "¿Hay accesorios en esta seccion? (1 = Si, 0 = No): ";
                cin >> actual->hayAccesorios;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    void mostrarMapa()
    {
        SeccionMetro *temp = inicio;
        while (temp)
        {
            cout << "Seccion: " << temp->nombre
                 << (temp->hayZombies ? " - Cuidado! Zombies presentes" : " - Seguro")
                 << (temp->hayAccesorios ? " - Hay accesorios aqui" : "") << endl;
            temp = temp->siguiente;
        }
    }

    ~MapaMetro()
    {
        while (inicio)
        {
            SeccionMetro *temp = inicio;
            inicio = inicio->siguiente;
            delete temp;
        }
    }
};