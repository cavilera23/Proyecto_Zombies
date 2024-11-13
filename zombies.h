#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#pragma once

using namespace std;

// Estructura para zombies
struct Zombies
{
    string nombre_zombie;
    int ataque;
    int velocidad;
    int durabilidad;
    bool poder_especial;

    Zombies(string nombre, int atk, int vcd, int dur, bool pwr) // Constructor
        : nombre_zombie(nombre), ataque(atk), velocidad(vcd), durabilidad(dur), poder_especial(pwr)
    {
    }
};

vector<unique_ptr<Zombies>> zombies;

// Función para agregar un zombie
void agregarZombie()
{
    int opcion;
    cout << "Seleccione el tipo de zombie a agregar:\n";
    cout << "1. Zombies rapidos y agiles\n";
    cout << "2. Zombies tanques\n";
    cout << "3. Zombies inteligentes\n";
    cout << "4. Zombies infectados por hongos\n";
    cout << "5. Zombies bioluminiscentes\n";
    cout << "----> ";
    cin >> opcion;

    unique_ptr<Zombies> nuevoZombie;

    switch (opcion)
    {
    case 1:
        nuevoZombie = make_unique<Zombies>("Zombie rapido y agil", 20, 90, 30, false);
        cout << "Zombie rapido y agil agregado.\n";
        break;
    case 2:
        nuevoZombie = make_unique<Zombies>("Zombie tanque", 70, 20, 100, false);
        cout << "Zombie tanque agregado.\n";
        break;
    case 3:
        nuevoZombie = make_unique<Zombies>("Zombie inteligente", 40, 50, 50, true);
        cout << "Zombie inteligente agregado.\n";
        break;
    case 4:
        nuevoZombie = make_unique<Zombies>("Zombie infectado por hongos", 60, 30, 80, true);
        cout << "Zombie infectado por hongos agregado.\n";
        break;
    case 5:
        nuevoZombie = make_unique<Zombies>("Zombie bioluminiscente", 50, 60, 70, true);
        cout << "Zombie bioluminiscente agregado.\n";
        break;
    default:
        cout << "Opcion invalida. No se agrego ningun zombie.\n";
        return;
    }

    zombies.push_back(move(nuevoZombie)); // Agregar el zombie a la lista
}

// Función para mostrar zombies
void mostrarZombies()
{
    cout << "Zombies disponibles:\n";
    for (const auto &zombie : zombies)
    {
        cout << "Zombie: " << zombie->nombre_zombie << " || Ataque: " << zombie->ataque << " | Velocidad: " << zombie->velocidad << " | Durabilidad: " << zombie->durabilidad << "\n";
    }
}

// Función para eliminar un zombie
void eliminarZombie()
{
    if (zombies.empty())
    {
        cout << "No hay zombies para eliminar.\n";
        return;
    }

    int opcion;
    cout << "Seleccione el tipo de zombie que desea eliminar:\n";
    cout << "1. Zombies rapidos y agiles\n";
    cout << "2. Zombies tanques\n";
    cout << "3. Zombies inteligentes\n";
    cout << "4. Zombies infectados por hongos\n";
    cout << "5. Zombies bioluminiscentes\n";
    cout << "----> ";
    cin >> opcion;

    string tipoZombie;
    switch (opcion)
    {
    case 1:
        tipoZombie = "Zombie rapido y agil";
        break;
    case 2:
        tipoZombie = "Zombie tanque";
        break;
    case 3:
        tipoZombie = "Zombie inteligente";
        break;
    case 4:
        tipoZombie = "Zombie infectado por hongos";
        break;
    case 5:
        tipoZombie = "Zombie bioluminiscente";
        break;
    default:
        cout << "Opción invalida.\n";
        return;
    }

    cout << "Seleccione una opcion:\n";
    cout << "1. Eliminar numero especifico de zombies de este tipo\n";
    cout << "2. Eliminar todos los zombies de este tipo\n";
    int subopcion;
    cout << "----> ";
    cin >> subopcion;

    if (subopcion == 1)
    {
        int cantidadEliminar;
        int count = 0;
        for (const auto &zombie : zombies)
        {
            if (zombie->nombre_zombie == tipoZombie)
                count++;
        }

        if (count == 0)
        {
            cout << "No hay zombies de este tipo para eliminar.\n";
            return;
        }

        cout << "Hay " << count << " zombies de tipo " << tipoZombie << ".\n";
        cout << "¿Cuantos desea eliminar? ";
        cout << "----> ";
        cin >> cantidadEliminar;

        if (cantidadEliminar > count)
        {
            cout << "No puede eliminar mas de los existentes. Eliminando " << count << " zombies.\n";
            cantidadEliminar = count;
        }

        int eliminados = 0;
        for (auto it = zombies.begin(); it != zombies.end() && eliminados < cantidadEliminar;)
        {
            if ((*it)->nombre_zombie == tipoZombie)
            {
                it = zombies.erase(it); // Eliminar el zombie y avanzar el iterador
                eliminados++;
            }
            else
            {
                ++it; // Avanzar el iterador si no se elimina
            }
        }
        cout << eliminados << " zombies de tipo " << tipoZombie << " eliminados.\n";
    }
    else if (subopcion == 2)
    {
        int eliminados = 0;
        for (auto it = zombies.begin(); it != zombies.end();)
        {
            if ((*it)->nombre_zombie == tipoZombie)
            {
                it = zombies.erase(it); // Eliminar el zombie y avanzar el iterador
                eliminados++;
            }
            else
            {
                ++it; // Avanzar el iterador si no se elimina
            }
        }
        cout << "Se eliminaron " << eliminados << " zombies de tipo " << tipoZombie << ".\n";
    }
    else
    {
        cout << "Opcion invalida.\n";
    }
}