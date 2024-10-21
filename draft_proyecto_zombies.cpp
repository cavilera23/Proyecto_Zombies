#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>    // Para punteros inteligentes (unique_ptr)
#include <algorithm> // Para std::find_if

/* HECHO POR:
    CHRISTIAN VILERA
    ISAAC RODRIGUEZ
    ARNALDO VELASQUEZ
*/

using namespace std;

/* COMPONENTES */
// 1) Estructura para accesorios
struct Accesorios
{
    std::string nombre_accesorio;
    std::string tipo;
    int valor;
    int municiones;
    int duracion;

    Accesorios(std::string nombre, std::string tipo, int val, int mun, int dur) // Constructor
        : nombre_accesorio(nombre), tipo(tipo), valor(val), municiones(mun), duracion(dur)
    {
    }
};

// 2) Estructura para zombies
struct Zombies
{
    std::string nombre_zombie;
    int ataque;
    int velocidad;
    int durabilidad;
    bool poder_especial;

    Zombies(std::string nombre, int atk, int vcd, int dur, bool pwr) // Constructor
        : nombre_zombie(nombre), ataque(atk), velocidad(vcd), durabilidad(dur), poder_especial(pwr)
    {
    }
};

// 3) Estructura para la mochila
struct Mochila
{
    std::string propietario;
    std::vector<std::unique_ptr<Accesorios>> accesorios; // Hasta 3 accesorios

    Mochila(std::string d) : propietario(d) {}

    // Método para agregar accesorios a la mochila
    bool agregarAccesorio(std::unique_ptr<Accesorios> accesorio)
    {
        if (accesorios.size() < 3)
        {
            accesorios.push_back(std::move(accesorio));
            return true;
        }
        else
        {
            std::cout << "Mochila llena, no se puede agregar mas accesorios.\n";
            return false;
        }
    }

    // Método para mostrar los accesorios en la mochila
    void mostrarAccesorios() const
    {
        std::cout << "Mochila de " << propietario << " contiene:\n";
        for (const auto &accesorio : accesorios)
        {
            std::cout << "- " << accesorio->nombre_accesorio << " (Tipo: " << accesorio->tipo
                      << ", Valor: " << accesorio->valor
                      << ", Municiones: " << accesorio->municiones
                      << ", Duracion: " << accesorio->duracion << ")\n";
        }
    }
};

// 4) Estructura para soldados
struct Soldado
{
    std::string nombre_soldado;
    const int salud = 100; // Salud constante
    Mochila mochila;

    Soldado(std::string nombre)
        : nombre_soldado(nombre), mochila(nombre) {} // Constructor inicializa mochila

    // Método para asignar un accesorio a la mochila
    void agregarAccesorioMochila(std::unique_ptr<Accesorios> accesorio)
    {
        if (!mochila.agregarAccesorio(std::move(accesorio)))
        {
            std::cout << "No se pudo agregar el accesorio a la mochila.\n";
        }
    }

    // Método para mostrar el soldado y su mochila
    void mostrarSoldado() const
    {
        std::cout << "Soldado: " << nombre_soldado << "\nSalud: " << salud << std::endl;
        mochila.mostrarAccesorios();
    }
};

/* FUNCIONES PARA GESTIONAR SOLDADOS, ZOMBIES, Y ACCESORIOS */

// Vectores para almacenar soldados, zombies, y accesorios
std::vector<std::shared_ptr<Soldado>> soldados;
std::vector<std::unique_ptr<Zombies>> zombies;
std::vector<std::unique_ptr<Accesorios>> accesorios;

// Función para agregar soldado
void agregarSoldado()
{
    std::string nombre;
    std::cout << "Ingrese el nombre del soldado: ";
    std::cin >> nombre;
    soldados.push_back(std::make_shared<Soldado>(nombre));
    std::cout << "Soldado " << nombre << " agregado.\n";
}

// Función para agregar un zombie
void agregarZombie()
{
    int opcion;
    std::cout << "Seleccione el tipo de zombie a agregar:\n";
    std::cout << "1. Zombies rapidos y agiles\n";
    std::cout << "2. Zombies tanques\n";
    std::cout << "3. Zombies inteligentes\n";
    std::cout << "4. Zombies infectados por hongos\n";
    std::cout << "5. Zombies bioluminiscentes\n";
    std::cin >> opcion;

    std::unique_ptr<Zombies> nuevoZombie;

    switch (opcion)
    {
    case 1:
        nuevoZombie = std::make_unique<Zombies>("Zombie rapido y agil", 20, 90, 30, false);
        std::cout << "Zombie rapido y agil agregado.\n";
        break;
    case 2:
        nuevoZombie = std::make_unique<Zombies>("Zombie tanque", 70, 20, 100, false);
        std::cout << "Zombie tanque agregado.\n";
        break;
    case 3:
        nuevoZombie = std::make_unique<Zombies>("Zombie inteligente", 40, 50, 50, true);
        std::cout << "Zombie inteligente agregado.\n";
        break;
    case 4:
        nuevoZombie = std::make_unique<Zombies>("Zombie infectado por hongos", 60, 30, 80, true);
        std::cout << "Zombie infectado por hongos agregado.\n";
        break;
    case 5:
        nuevoZombie = std::make_unique<Zombies>("Zombie bioluminiscente", 50, 60, 70, true);
        std::cout << "Zombie bioluminiscente agregado.\n";
        break;
    default:
        std::cout << "Opcion invalida. No se agrego ningun zombie.\n";
        return;
    }

    zombies.push_back(std::move(nuevoZombie)); // Agregar el zombie a la lista
}

// Función para agregar un accesorio
void agregarAccesorio()
{
    std::string nombre, tipo;
    int valor, municiones, duracion;
    std::cout << "Ingrese el nombre del accesorio: ";
    std::cin >> nombre;
    std::cout << "Ingrese tipo, valor, municiones y Duracion: ";
    std::cin >> tipo >> valor >> municiones >> duracion;
    accesorios.push_back(std::make_unique<Accesorios>(nombre, tipo, valor, municiones, duracion));
    std::cout << "Accesorio " << nombre << " agregado.\n";
}

// Función para mostrar soldado
void mostrarSoldados()
{
    std::cout << "Soldados disponibles:\n";
    for (const auto &soldado : soldados)
    {
        soldado->mostrarSoldado();
    }
}

// Función para mostrar zombies
void mostrarZombies()
{
    std::cout << "Zombies disponibles:\n";
    for (const auto &zombie : zombies)
    {
        std::cout << "Zombie: " << zombie->nombre_zombie << ", Ataque: " << zombie->ataque << "\n";
    }
}

// Función para mostrar accesorios
void mostrarAccesorios()
{
    std::cout << "Accesorios disponibles:\n";
    for (const auto &accesorio : accesorios)
    {
        std::cout << "Accesorio: " << accesorio->nombre_accesorio << ", Tipo: " << accesorio->tipo << "\n";
    }
}

// Función para eliminar un soldado
void eliminarSoldado()
{
    std::string nombre;
    std::cout << "Ingrese el nombre del soldado a eliminar: ";
    std::cin >> nombre;

    auto it = std::find_if(soldados.begin(), soldados.end(),
                           [&nombre](const std::shared_ptr<Soldado> &soldado)
                           { return soldado->nombre_soldado == nombre; });

    if (it != soldados.end())
    {
        soldados.erase(it);
        std::cout << "Soldado " << nombre << " eliminado.\n";
    }
    else
    {
        std::cout << "Soldado no encontrado.\n";
    }
}

// Función para eliminar un zombie
void eliminarZombie()
{
    if (zombies.empty())
    {
        std::cout << "No hay zombies para eliminar.\n";
        return;
    }

    int opcion;
    std::cout << "Seleccione el tipo de zombie que desea eliminar:\n";
    std::cout << "1. Zombies rapidos y agiles\n";
    std::cout << "2. Zombies tanques\n";
    std::cout << "3. Zombies inteligentes\n";
    std::cout << "4. Zombies infectados por hongos\n";
    std::cout << "5. Zombies bioluminiscentes\n";
    std::cout << "----> ";
    std::cin >> opcion;

    std::string tipoZombie;
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
        std::cout << "Opción invalida.\n";
        return;
    }

    std::cout << "Seleccione una opcion:\n";
    std::cout << "1. Eliminar numero especifico de zombies de este tipo\n";
    std::cout << "2. Eliminar todos los zombies de este tipo\n";
    int subopcion;
    std::cout << "----> ";
    std::cin >> subopcion;

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
            std::cout << "No hay zombies de este tipo para eliminar.\n";
            return;
        }

        std::cout << "Hay " << count << " zombies de tipo " << tipoZombie << ".\n";
        std::cout << "¿Cuantos desea eliminar? ";
        std::cout << "----> ";
        std::cin >> cantidadEliminar;

        if (cantidadEliminar > count)
        {
            std::cout << "No puede eliminar mas de los existentes. Eliminando " << count << " zombies.\n";
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
        std::cout << eliminados << " zombies de tipo " << tipoZombie << " eliminados.\n";
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
        std::cout << "Se eliminaron " << eliminados << " zombies de tipo " << tipoZombie << ".\n";
    }
    else
    {
        std::cout << "Opcion invalida.\n";
    }
}

// Función para eliminar un accesorio
void eliminarAccesorio()
{
    std::string nombre;
    std::cout << "Ingrese el nombre del accesorio a eliminar: ";
    std::cin >> nombre;

    auto it = std::find_if(accesorios.begin(), accesorios.end(),
                           [&nombre](const std::unique_ptr<Accesorios> &accesorio)
                           { return accesorio->nombre_accesorio == nombre; });

    if (it != accesorios.end())
    {
        accesorios.erase(it);
        std::cout << "Accesorio " << nombre << " eliminado.\n";
    }
    else
    {
        std::cout << "Accesorio no encontrado.\n";
    }
}

/* MENÚS INTERACTIVOS */
void menuSoldados()
{
    int opcion;
    do
    {
        std::cout << "\n--- Menu de Soldados ---\n";
        std::cout << "1. Agregar Soldado\n";
        std::cout << "2. Mostrar Soldados\n";
        std::cout << "3. Eliminar Soldado\n";
        std::cout << "4. Volver\n";
        std::cout << "----> ";
        std::cin >> opcion;
        system("cls");

        switch (opcion)
        {
        case 1:
            agregarSoldado();
            break;
        case 2:
            mostrarSoldados();
            break;
        case 3:
            eliminarSoldado();
            break;
        case 4:
            return;
        default:
            std::cout << "Opción inválida.\n";
            break;
        }
    } while (opcion != 4);
}

void menuZombies()
{
    int opcion;
    do
    {
        std::cout << "\n--- Menu de Zombies ---\n";
        std::cout << "1. Agregar Zombie\n";
        std::cout << "2. Mostrar Zombies\n";
        std::cout << "3. Eliminar Zombie\n";
        std::cout << "4. Volver\n";
        std::cout << "----> ";
        std::cin >> opcion;
        system("cls");

        switch (opcion)
        {
        case 1:
            agregarZombie();
            break;
        case 2:
            mostrarZombies();
            break;
        case 3:
            eliminarZombie();
            break;
        case 4:
            return;
        default:
            std::cout << "Opcion invalida.\n";
            break;
        }
    } while (opcion != 4);
}

void menuAccesorios()
{
    int opcion;
    do
    {
        std::cout << "\n--- Menu de Accesorios ---\n";
        std::cout << "1. Agregar Accesorio\n";
        std::cout << "2. Mostrar Accesorios\n";
        std::cout << "3. Eliminar Accesorio\n";
        std::cout << "4. Volver\n";
        std::cout << "----> ";
        std::cin >> opcion;
        system("cls");

        switch (opcion)
        {
        case 1:
            agregarAccesorio();
            break;
        case 2:
            mostrarAccesorios();
            break;
        case 3:
            eliminarAccesorio();
            break;
        case 4:
            return;
        default:
            std::cout << "Opcion invalida.\n";
            break;
        }
    } while (opcion != 4);
}

void menuPrincipal()
{
    int opcion;
    do
    {
        std::cout << "\n--- Menu Principal ---\n";
        std::cout << "1. Gestionar Soldados\n";
        std::cout << "2. Gestionar Zombies\n";
        std::cout << "3. Gestionar Accesorios\n";
        std::cout << "4. Salir\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        system("cls");

        switch (opcion)
        {
        case 1:
            menuSoldados();
            break;
        case 2:
            menuZombies();
            break;
        case 3:
            menuAccesorios();
            break;
        case 4:
            std::cout << "Saliendo del programa.\n";
            break;
        default:
            std::cout << "Opcion invalida.\n";
            break;
        }
    } while (opcion != 4);
}

// Bienvenida al programa
void Bienvenida(const std::string &fileName)
{
    std::ifstream inputFile(fileName); // Abrir el archivo

    if (!inputFile)
    {
        std::cerr << "Error: No se pudo abrir el archivo " << fileName << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(inputFile, linea)) // Leer cada línea del archivo
    {
        std::cout << linea << std::endl; // Imprimir cada línea en el terminal
    }

    inputFile.close(); // Cerrar el archivo
}

int main()
{
    char continuar;
    while (continuar != 'X')
    {
        std::string filename = "ucab_z.txt";
        Bienvenida(filename);
        std::cout << "PRESIONA X PARA CONTINUAR --> ";
        std::cin >> continuar;
        std::system("cls");
    }

    menuPrincipal(); // Iniciar el menú principal
    return 0;
}
