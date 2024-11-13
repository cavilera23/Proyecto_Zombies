#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <accesorios.h>
#pragma once

// Estructura para soldados
struct Soldado
{
    string nombre_soldado;
    const int salud = 100; // Salud constante
    Mochila mochila;

    Soldado(string nombre)
        : nombre_soldado(nombre), mochila(nombre) {} // Constructor inicializa mochila

    // Método para asignar un accesorio a la mochila
    void agregarAccesorioMochila(unique_ptr<Accesorios> accesorio)
    {
        if (!mochila.agregarAccesorio(move(accesorio)))
        {
            cout << "No se pudo agregar el accesorio a la mochila.\n";
        }
    }

    // Método para mostrar el soldado y su mochila
    void mostrarSoldado() const
    {
        cout << "Soldado: " << nombre_soldado << "\nSalud: " << salud << "\n"
             << endl;
        mochila.mostrarAccesorios();
    }
};

vector<shared_ptr<Soldado>> soldados;

// Estructura para los equipos
struct Equipo
{
    string nombre_equipo;
    vector<shared_ptr<Soldado>> soldados; // Lista de soldados en el equipo

    Equipo(string nombre) : nombre_equipo(nombre) {}

    // Método para mostrar los soldados en el equipo
    void mostrarSoldados() const
    {
        cout << "Equipo: " << nombre_equipo << "\n";
        if (soldados.empty())
        {
            cout << "No hay soldados en este equipo.\n";
            return;
        }
        for (const auto &soldado : soldados)
        {
            cout << "- " << soldado->nombre_soldado << "\n";
        }
    }
};

vector<unique_ptr<Equipo>> equipos;

// Funcion crear equipo
void crearEquipo()
{
    string nombre;
    while (true)
    {
        cout << "Ingrese el nombre del equipo (minimo 10 caracteres): ";
        cin.ignore();
        getline(cin, nombre);

        if (nombre.length() <= 10)
        {
            equipos.push_back(make_unique<Equipo>(nombre));
            cout << "Equipo " << nombre << " creado.\n";
            break;
        }
        else
        {
            cout << "Error: El nombre del equipo debe tener al menos 10 caracteres. Inténtelo de nuevo.\n";
        }
    }
}

// Funcion agregar soldado a equipo
void asignarSoldadoAEquipo()
{
    if (soldados.empty())
    {
        cout << "No hay soldados disponibles para asignar.\n";
        return;
    }

    if (equipos.empty())
    {
        cout << "No hay equipos creados. Primero crea un equipo.\n";
        return;
    }

    cout << "Seleccione un soldado para asignar:\n";
    for (int i = 0; i < soldados.size(); ++i)
    {
        cout << i + 1 << ") " << soldados[i]->nombre_soldado << "\n";
    }

    int opcionSoldado;
    cin >> opcionSoldado;

    if (opcionSoldado < 1 || opcionSoldado > soldados.size())
    {
        cout << "Opción no válida.\n";
        return;
    }

    cout << "Seleccione un equipo al que desea asignar el soldado:\n";
    for (int i = 0; i < equipos.size(); ++i)
    {
        cout << i + 1 << ") " << equipos[i]->nombre_equipo << "\n";
    }

    int opcionEquipo;
    cin >> opcionEquipo;

    if (opcionEquipo < 1 || opcionEquipo > equipos.size())
    {
        cout << "Opción no válida.\n";
        return;
    }

    // Asignar el soldado al equipo seleccionado
    equipos[opcionEquipo - 1]->soldados.push_back(soldados[opcionSoldado - 1]);
    cout << "Soldado " << soldados[opcionSoldado - 1]->nombre_soldado << " asignado al equipo " << equipos[opcionEquipo - 1]->nombre_equipo << ".\n";
}

// Mostras equipos
void mostrarEquipos()
{
    if (equipos.empty())
    {
        cout << "No hay equipos creados.\n";
        return;
    }

    for (const auto &equipo : equipos)
    {
        equipo->mostrarSoldados();
    }
}

// Función para agregar soldado
void agregarSoldado()
{
    string nombre;
    cout << "Ingrese el nombre del soldado: ";
    cin >> nombre;
    soldados.push_back(make_shared<Soldado>(nombre));
    cout << "Soldado " << nombre << " agregado.\n";
}

// Función para mostrar soldado
void mostrarSoldados()
{
    cout << "Soldados disponibles:\n";
    for (const auto &soldado : soldados)
    {
        soldado->mostrarSoldado();
    }
}

// Función para asignar un accesorio creado a un soldado
void asignarAccesorioSoldado()
{
    if (soldados.empty())
    {
        cout << "No hay soldados para asignar accesorios.\n";
        return;
    }

    if (accesorios.empty())
    {
        cout << "No hay accesorios disponibles para asignar.\n";
        return;
    }

    cout << "Seleccione el soldado al que desea asignar un accesorio:\n";
    for (int i = 0; i < soldados.size(); ++i)
    {
        cout << i + 1 << ") " << soldados[i]->nombre_soldado << "\n";
    }

    int opcion;
    cin >> opcion;

    if (opcion < 1 || opcion > soldados.size())
    {
        cout << "Opcion no valida.\n";
        return;
    }

    soldados[opcion - 1]->agregarAccesorioMochila(move(accesorios[0]));

    accesorios.erase(accesorios.begin());

    cout << "Accesorio asignado exitosamente al soldado.\n";
}

// Función para eliminar un soldado
void eliminarSoldado()
{
    string nombre;
    cout << "Ingrese el nombre del soldado a eliminar: ";
    cin >> nombre;

    auto it = find_if(soldados.begin(), soldados.end(),
                      [&nombre](const shared_ptr<Soldado> &soldado)
                      { return soldado->nombre_soldado == nombre; });

    if (it != soldados.end())
    {
        soldados.erase(it);
        cout << "Soldado " << nombre << " eliminado.\n";
    }
    else
    {
        cout << "Soldado no encontrado.\n";
    }
}