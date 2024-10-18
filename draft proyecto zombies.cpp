#include <iostream>

/*  HECHO POR:
    1, 2, 3.
*/

/* COMPONENTES */

struct draft_mapa
{
    std::string nombre_estacion;
    int cantidad_zombies;
};

struct draft_accesorios
{
    std::string nombre_accesorio;
    std::string tipo;
    int valor;
    int municiones;
    int duracion;
}Accesorio1, Accesorio2;

struct draft_soldado
{
    std::string nombre_soldado;
    int salud = 100;
    draft_accesorios accesorio;
    draft_accesorios valor;
}Soldado1, Soldado2;

struct draft_zombies
{
    std::string nombre_zombie;
    int ataque;
    int fortaleza;
};

/* FUNCIONES: Declaracion */

int agregar_zombies(draft_zombies);
int agregar_accesorios(draft_accesorios);
int agregar_equipos(draft_soldado);
int agregar_estacion(draft_mapa);

// se repite todo con eliminar y modificar

/* PROGRAMA */

int main()
{
    Soldado1.nombre_soldado = "Chris";
    Accesorio1.nombre_accesorio = "Pistola";
    std::cout << "Nombre de soldado: " << Soldado1.nombre_soldado
    << " Y usa: " << Accesorio1.nombre_accesorio;
}