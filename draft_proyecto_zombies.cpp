#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <codecvt>
#include <locale>
#include <memory> // Para punteros inteligentes

using namespace std;

/*  HECHO POR:
    1. Christian Vilera
    2. Isaac Rodriguez
    3. Arnaldo Velasquez
*/

/* Introduccion al lore:
    1.
*/

/* COMPONENTES */
// 1) Estrucutra para zombies
struct Zombies
{
    std::string nombre_zombie;
    int ataque;
    int durabilidad;

    Zombies(std::string nombre, int atk, int dur)
        : nombre_zombie(nombre), ataque(atk), durabilidad(dur) {}
};

// 2) Estructura para accesorios
struct Accesorios
{
    std::string nombre_accesorio;
    std::string tipo;
    int valor;
    int municiones;
    int duracion;

    Accesorios(std::string nombre, std::string tipo, int val, int mun, int dur)
        : nombre_accesorio(nombre), tipo(tipo), valor(val), municiones(mun), duracion(dur) {}
};

// 3) Estructura para soldados
struct Soldado
{
    std::string nombre_soldado;
    int salud;
    std::unique_ptr<Accesorios> accesorio; // Pointer to an accessory

    Soldado(std::string nombre, int hp)
        : nombre_soldado(nombre), salud(hp), accesorio(nullptr) {}

    void asignarAccesorio(std::unique_ptr<Accesorios> nuevoAccesorio)
    {
        accesorio = std::move(nuevoAccesorio);
    }
};

// 4) Estructura para mapas
struct Mapa
{
    std::string nombre_estacion;
    int cantidad_zombies;
    std::vector<std::unique_ptr<Zombies>> zombies; // Vector to store zombies dynamically

    Mapa(std::string nombre) : nombre_estacion(nombre), cantidad_zombies(0) {}

    void agregarZombie(std::unique_ptr<Zombies> nuevoZombie)
    {
        zombies.push_back(std::move(nuevoZombie));
        cantidad_zombies++;
    }
};

/* FUNCIONES: Declaracion */
void Bienvenida(const std::string &fileName);
int agregar_zombies(Zombies);
int agregar_accesorios(Accesorios);
int agregar_equipos(Soldado);
int agregar_estacion(Mapa);

// se repite todo con eliminar y modificar

/* PROGRAMA */

// Funcion para imprimir la bandera con fuente ASCII
void Bienvenida(const std::string &fileName)
{
    std::ifstream inputFile(fileName); // Abrir el archivo

    if (!inputFile)
    {
        std::cerr << "Error: Could not open file " << fileName << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(inputFile, linea)) // Leer cada linea del archivo
    {
        std::cout << linea << std::endl; // Imprimir cada linea en el terminal
    }

    inputFile.close(); // Cerrar el archivo
}

// Funcion para agregar un soldado
std::unique_ptr<Soldado> agregarSoldado(std::string nombre, int salud)
{
    return std::make_unique<Soldado>(nombre, salud);
}

// Funcion para agregar un accesorio
std::unique_ptr<Accesorios> agregarAccesorio(std::string nombre, std::string tipo, int valor, int municiones, int duracion)
{
    return std::make_unique<Accesorios>(nombre, tipo, valor, municiones, duracion);
}

// Funcion para agregar un zombie
std::unique_ptr<Zombies> agregarZombie(std::string nombre, int ataque, int durabilidad)
{
    return std::make_unique<Zombies>(nombre, ataque, durabilidad);
}

// Funcion para asignar un accesorio a un soldado
void asignarAccesorioSoldado(Soldado &soldado, std::unique_ptr<Accesorios> accesorio)
{
    soldado.asignarAccesorio(std::move(accesorio));
}

// Funcion para mostrar la informacion de un soldado
void mostrarSoldado(const Soldado &soldado)
{
    std::cout << "Soldado: " << soldado.nombre_soldado << "\nSalud: " << soldado.salud << std::endl;
    if (soldado.accesorio)
    {
        std::cout << "Accesorio: " << soldado.accesorio->nombre_accesorio
                  << " (Tipo: " << soldado.accesorio->tipo
                  << ", Valor: " << soldado.accesorio->valor
                  << ", Municiones: " << soldado.accesorio->municiones
                  << ", Duracion: " << soldado.accesorio->duracion << ")\n";
    }
    else
    {
        std::cout << "No se han asignado accesorios.\n";
    }
}

// Funcion para mostrar la informacion de un zombie
void mostrarZombie(const Zombies &zombie)
{
    std::cout << "Zombie: " << zombie.nombre_zombie << "\nAtaque: " << zombie.ataque
              << "\nDurabilidad: " << zombie.durabilidad << std::endl;
}

// Funcion para mostrar la informacion de un mapa
void mostrarMapa(const Mapa &mapa)
{
    std::cout << "Mapa: " << mapa.nombre_estacion << "\nCantidad de Zombies: " << mapa.cantidad_zombies << std::endl;
    for (const auto &zombie : mapa.zombies)
    {
        mostrarZombie(*zombie);
    }
}

int main()
{
    // Bienvenida, presiona X para continuar
    char continuar;
    while (continuar != 'X')
    {
        std::string filename = "ucab_z.txt";
        Bienvenida(filename);
        std::cout << "PRESIONA X PARA CONTINUAR --> ";
        std::cin >> continuar;
        std::system("cls");
    }

    // Crear algunos soldados
    auto soldado1 = agregarSoldado("Richtofen", 100);
    auto soldado2 = agregarSoldado("Nikolai", 90);

    // Crear algunos accesorios y asignarlos a los soldados
    auto accesorio1 = agregarAccesorio("Escudo", "Defensa", 50, 0, 100);
    auto accesorio2 = agregarAccesorio("Rifle", "Ataque", 75, 30, 80);
    asignarAccesorioSoldado(*soldado1, std::move(accesorio1));
    asignarAccesorioSoldado(*soldado2, std::move(accesorio2));

    // Mostrar la informacion de los soldados
    mostrarSoldado(*soldado1);
    mostrarSoldado(*soldado2);

    // Crear un mapa y agregar algunos zombies
    Mapa estacion("Estacion Central");
    auto zombie1 = agregarZombie("Zombie A", 30, 40);
    auto zombie2 = agregarZombie("Zombie B", 50, 60);
    estacion.agregarZombie(std::move(zombie1));
    estacion.agregarZombie(std::move(zombie2));
}
