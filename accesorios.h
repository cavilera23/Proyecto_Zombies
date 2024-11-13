#include <soldados.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory> // Para punteros inteligentes (unique_ptr)
#include <algorithm>
#pragma once

using namespace std;

// 1) Estructura para accesorios
struct Accesorios
{
    string nombre_accesorio;
    string tipo;
    int valor;
    int municiones;
    int duracion;
    bool mun_especial;

    Accesorios(string nombre, string tipo, int val, int mun, int dur, bool m_esp) // Constructor
        : nombre_accesorio(nombre), tipo(tipo), valor(val), municiones(mun), duracion(dur), mun_especial(m_esp)
    {
    }
};

vector<unique_ptr<Accesorios>> accesorios;

// Estructura para la mochila
struct Mochila
{
    string propietario;
    vector<unique_ptr<Accesorios>> accesorios; // Hasta 3 accesorios

    Mochila(string d) : propietario(d) {}

    // Método para agregar accesorios a la mochila
    bool agregarAccesorio(unique_ptr<Accesorios> accesorio)
    {
        if (accesorios.size() < 3)
        {
            accesorios.push_back(move(accesorio));
            return true;
        }
        else
        {
            cout << "Mochila llena, no se puede agregar mas accesorios.\n";
            return false;
        }
    }

    // Método para mostrar los accesorios en la mochila
    void mostrarAccesorios() const
    {
        cout << "Mochila de " << propietario << " contiene:\n";
        for (const auto &accesorio : accesorios)
        {
            cout << "- " << accesorio->nombre_accesorio << " (Tipo: " << accesorio->tipo
                 << ", Valor: " << accesorio->valor
                 << ", Municiones: " << accesorio->municiones
                 << ", Duracion: " << accesorio->duracion
                 << ", Municion Especial: " << (accesorio->mun_especial ? "Si" : "No") << ")\n";
        }
    }
};

// Función para agregar un accesorio (arma) al soldado
unique_ptr<Accesorios> agregarAccesorio()
{
    int categoria;
    cout << "Seleccione la categoria de armas:\n";
    cout << "1. Armas a distancia\n";
    cout << "2. Armas cuerpo a cuerpo\n";
    cout << "3. Armas improvisadas\n";
    cout << "----> ";
    cin >> categoria;

    int subcategoria, opcion;
    string nombre_accesorio, tipo;
    int valor, municiones, duracion;
    bool mun_especial;

    switch (categoria)
    {
    case 1:
        cout << "Seleccione el tipo de arma a distancia:\n";
        cout << "1. Armas de fuego\n";
        cout << "2. Armas arrojadizas\n";
        cout << "3. Armas de proyectiles\n";
        cout << "----> ";
        cin >> subcategoria;

        if (subcategoria == 1) // Armas de fuego
        {
            cout << "1. Pistolas\n2. Escopetas\n3. Fusiles de asalto\n4. Rifles de francotirador\n";
            cout << "----> ";
            cin >> opcion;
            system("cls");

            switch (opcion)
            {
            case 1:
                nombre_accesorio = "Pistola";
                valor = 30;
                municiones = 15;
                duracion = 100;
                tipo = "Arma de fuego";
                mun_especial = false;
                break;
            case 2:
                nombre_accesorio = "Escopeta";
                valor = 50;
                municiones = 8;
                duracion = 80;
                tipo = "Arma de fuego";
                mun_especial = false;
                break;
            case 3:
                nombre_accesorio = "Fusil de asalto";
                valor = 70;
                municiones = 30;
                duracion = 60;
                tipo = "Arma de fuego";
                mun_especial = false;
                break;
            case 4:
                nombre_accesorio = "Rifle de francotirador";
                valor = 90;
                municiones = 5;
                duracion = 50;
                tipo = "Arma de fuego";
                mun_especial = false;
                break;
            }
        }
        else if (subcategoria == 2) // Armas arrojadizas
        {
            cout << "1. Granadas\n2. Cocteles Molotov\n";
            cout << "----> ";
            cin >> opcion;
            system("cls");

            switch (opcion)
            {
            case 1:
                nombre_accesorio = "Granada";
                valor = 40;
                municiones = 3;
                duracion = 1;
                tipo = "Arma arrojadiza";
                mun_especial = false;
                break;
            case 2:
                nombre_accesorio = "Coctel Molotov";
                valor = 45;
                municiones = 2;
                duracion = 1;
                tipo = "Arma arrojadiza";
                mun_especial = false;
                break;
            }
        }
        else if (subcategoria == 3) // Armas de proyectiles
        {
            cout << "1. Ballestas\n2. Tirachinas\n";
            cout << "----> ";
            cin >> opcion;
            system("cls");

            switch (opcion)
            {
            case 1:
                nombre_accesorio = "Ballesta";
                valor = 60;
                municiones = 10;
                duracion = 70;
                tipo = "Arma de proyectiles";
                mun_especial = true;
                break;
            case 2:
                nombre_accesorio = "Tirachinas";
                valor = 20;
                municiones = 20;
                duracion = 100;
                tipo = "Arma de proyectiles";
                mun_especial = true;
                break;
            }
        }
        break;

    case 2:
        cout << "Seleccione el tipo de arma cuerpo a cuerpo:\n";
        cout << "1. Armas blancas\n2. Armas contundentes\n";
        cout << "----> ";
        cin >> subcategoria;

        if (subcategoria == 1) // Armas blancas
        {
            cout << "1. Cuchillo\n2. Machete\n3. Espada\n";
            cout << "----> ";
            cin >> opcion;
            system("cls");

            switch (opcion)
            {
            case 1:
                nombre_accesorio = "Cuchillo";
                valor = 25;
                municiones = 0;
                duracion = 100;
                tipo = "Arma blanca";
                break;
            case 2:
                nombre_accesorio = "Machete";
                valor = 40;
                municiones = 0;
                duracion = 80;
                tipo = "Arma blanca";
                break;
            case 3:
                nombre_accesorio = "Espada";
                valor = 60;
                municiones = 0;
                duracion = 70;
                tipo = "Arma blanca";
                break;
            }
        }
        else if (subcategoria == 2) // Armas contundentes
        {
            cout << "1. Bate de beisbol\n2. Martillo\n3. Tubería\n";
            cout << "----> ";
            cin >> opcion;
            system("cls");

            switch (opcion)
            {
            case 1:
                nombre_accesorio = "Bate de beisbol";
                valor = 35;
                municiones = 0;
                duracion = 90;
                tipo = "Arma contundente";
                mun_especial = false;
                break;
            case 2:
                nombre_accesorio = "Martillo";
                valor = 50;
                municiones = 0;
                duracion = 75;
                tipo = "Arma contundente";
                mun_especial = false;
                break;
            case 3:
                nombre_accesorio = "Tuberia";
                valor = 45;
                municiones = 0;
                duracion = 60;
                tipo = "Arma contundente";
                mun_especial = false;
                break;
            }
        }
        break;

    case 3:
        cout << "Seleccione el tipo de arma improvisada:\n";
        cout << "1. Objetos punzantes\n2. Objetos contundentes\n3. Armas incendiarias\n4. Trampas\n";
        cout << "----> ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            nombre_accesorio = "Objetos punzantes (clavos, tijeras, destornilladores)";
            valor = 20;
            municiones = 0;
            duracion = 50;
            tipo = "Arma improvisada";
            mun_especial = false;
            break;
        case 2:
            nombre_accesorio = "Objetos contundentes (ladrillos, rocas, palos)";
            valor = 15;
            municiones = 0;
            duracion = 40;
            tipo = "Arma improvisada";
            mun_especial = false;
            break;
        case 3:
            nombre_accesorio = "Armas incendiarias (fósforos, líquido inflamable)";
            valor = 35;
            municiones = 0;
            duracion = 30;
            tipo = "Arma improvisada";
            mun_especial = false;
            break;
        case 4:
            nombre_accesorio = "Trampas";
            valor = 50;
            municiones = 0;
            duracion = 60;
            tipo = "Arma improvisada";
            mun_especial = false;
            break;
        }
        break;

    default:
        cout << "Opcion invalida.\n";
        return nullptr;
    }
    return make_unique<Accesorios>(nombre_accesorio, tipo, valor, municiones, duracion, mun_especial);
}

// Funcion para crear accesorio y agregarlo al vector global
void crearAccesorio()
{
    auto accesorio = agregarAccesorio(); // Crea el accesorio usando la función agregarAccesorio
    if (accesorio)
    {                                          // Si el accesorio es válido (no es nulo)
        accesorios.push_back(move(accesorio)); // Se añade al vector global
        cout << "Accesorio creado y agregado exitosamente.\n";
    }
    else
    {
        cout << "No se pudo crear el accesorio.\n";
    }
}

// Función para mostrar accesorios
void mostrarAccesorios()
{
    if (accesorios.empty())
    { // Verifica si el vector de accesorios está vacío
        cout << "No hay accesorios creados.\n";
        return;
    }

    cout << "Accesorios disponibles:\n";
    for (size_t i = 0; i < accesorios.size(); ++i)
    {
        cout << i + 1 << ") " << accesorios[i]->nombre_accesorio
             << " (Tipo: " << accesorios[i]->tipo
             << ", Valor: " << accesorios[i]->valor
             << ", Municiones: " << accesorios[i]->municiones
             << ", Duracion: " << accesorios[i]->duracion
             << ", Municion Especial: " << (accesorios[i]->mun_especial ? "Si" : "No") << ")\n";
    }
}

// Función para eliminar un accesorio
void eliminarAccesorio()
{
    if (accesorios.size() == 0)
    {
        cout << "No hay accesorios para eliminar.\n";
        return;
    }

    // Mostrar accesorios disponibles para eliminar
    cout << "Seleccione un accesorio para eliminar:\n";
    for (int i = 0; i < accesorios.size(); ++i)
    {
        cout << i + 1 << ") " << accesorios[i]->nombre_accesorio
             << " (Tipo: " << accesorios[i]->tipo << ")\n";
    }

    int opcion;
    cin >> opcion;

    if (opcion < 1 || opcion > accesorios.size())
    {
        cout << "Opcion no valida.\n";
        return;
    }

    // Eliminar accesorio seleccionado
    accesorios.erase(accesorios.begin() + (opcion - 1));
    cout << "Accesorio eliminado exitosamente.\n";
}