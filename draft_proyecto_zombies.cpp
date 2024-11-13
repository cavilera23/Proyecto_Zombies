#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <memory>    // Para punteros inteligentes (unique_ptr)
#include <algorithm> // Para std::find_if
#include <zombies.h>
#include <soldados.h>
#include <mapas.h>
#include <accesorios.h>

/* HECHO POR:
    CHRISTIAN VILERA
    ISAAC RODRIGUEZ
    ARNALDO VELASQUEZ
*/

using namespace std;

/* COMPONENTES */
/* FUNCIONES PARA GESTIONAR SOLDADOS, ZOMBIES, Y ACCESORIOS */

// Menú para gestionar el mapa
void menuMapa(MapaMetro &mapa)
{
    int opcion = 0;
    string nombre;
    bool hayZombies;
    bool hayAccesorios;

    while (opcion != 5)
    {
        cout << "\n--- Menu de Manejo de Mapa ---\n";
        cout << "1. Agregar Seccion\n";
        cout << "2. Eliminar Seccion\n";
        cout << "3. Editar Seccion\n";
        cout << "4. Mostrar Mapa\n";
        cout << "5. Volver al Menu Principal\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        system("cls");

        switch (opcion)
        {
        case 1:
            cout << "Ingrese el nombre de la seccion: ";
            cin.ignore();
            getline(cin, nombre);
            cout << "Hay zombies en esta seccion? (1 = Si, 0 = No): ";
            cin >> hayZombies;
            cout << "Hay accesorios en esta seccion? (1 = Si, 0 = No): ";
            cin >> hayAccesorios;
            mapa.agregarSeccion(nombre, hayZombies, hayAccesorios);
            cout << "Seccion agregada correctamente.\n";
            break;
        case 2:
            cout << "Ingrese el nombre de la seccion a eliminar: ";
            cin.ignore();
            getline(cin, nombre);
            if (mapa.eliminarSeccion(nombre))
            {
                cout << "Seccion eliminada correctamente.\n";
            }
            else
            {
                cout << "Seccion no encontrada.\n";
            }
            break;
        case 3:
            cout << "Ingrese el nombre de la seccion a editar: ";
            cin.ignore();
            getline(cin, nombre);
            if (mapa.editarSeccion(nombre))
            {
                cout << "Seccion editada correctamente.\n";
            }
            else
            {
                cout << "Seccion no encontrada.\n";
            }
            break;
        case 4:
            mapa.mostrarMapa();
            break;
        case 5:
            cout << "Volviendo al menu principal...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
            break;
        }
    }
}

// Menu equipos
void menuEquipos()
{
    int opcion;
    do
    {
        cout << "\n--- Menu de Equipos ---\n";
        cout << "1. Crear Equipo\n";
        cout << "2. Asignar Soldado a Equipo\n";
        cout << "3. Mostrar Equipos\n";
        cout << "4. Volver\n";
        cout << "----> ";
        cin >> opcion;
        system("cls");

        switch (opcion)
        {
        case 1:
            crearEquipo();
            break;
        case 2:
            asignarSoldadoAEquipo();
            break;
        case 3:
            mostrarEquipos();
            break;
        case 4:
            return;
        default:
            cout << "Opción inválida.\n";
            break;
        }
    } while (opcion != 4);
}

/* MENÚS INTERACTIVOS */
void menuSoldados()
{
    int opcion;
    do
    {
        cout << "\n--- Menu de Soldados ---\n";
        cout << "1. Agregar Soldado\n";
        cout << "2. Mostrar Soldados\n";
        cout << "3. Eliminar Soldado\n";
        cout << "4. Volver\n";
        cout << "----> ";
        cin >> opcion;
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
            cout << "Opción inválida.\n";
            break;
        }
    } while (opcion != 4);
}

void menuZombies()
{
    int opcion;
    do
    {
        cout << "\n--- Menu de Zombies ---\n";
        cout << "1. Agregar Zombie\n";
        cout << "2. Mostrar Zombies\n";
        cout << "3. Eliminar Zombie\n";
        cout << "4. Volver\n";
        cout << "----> ";
        cin >> opcion;
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
            cout << "Opcion invalida.\n";
            break;
        }
    } while (opcion != 4);
}

void menuAccesorios()
{
    int opcion;
    do
    {
        cout << "\n--- Menu de Accesorios ---\n";
        cout << "1. Agregar Accesorio\n";
        cout << "2. Mostrar Accesorios\n";
        cout << "3. Eliminar Accesorio\n";
        cout << "4. Asignar Accesorio a Soldado\n";
        cout << "5. Volver\n";
        cout << "----> ";
        cin >> opcion;
        system("cls");

        switch (opcion)
        {
        case 1:
            crearAccesorio();
            break;
        case 2:
            mostrarAccesorios();
            break;
        case 3:
            eliminarAccesorio();
            break;
        case 4:
            asignarAccesorioSoldado();
            break;
        case 5:
            return;
        default:
            cout << "Opcion invalida.\n";
            break;
        }
    } while (opcion != 5);
}

void menuPrincipal()
{
    MapaMetro mapa;
    int opcion;

    do
    {
        cout << "\n--- Menu Principal ---\n";
        cout << "1. Gestionar Soldados\n";
        cout << "2. Gestionar Zombies\n";
        cout << "3. Gestionar Accesorios\n";
        cout << "4. Gestionar Equipos\n";
        cout << "5. Gestionar Mapas\n";
        cout << "6. Salir\n";
        cout << "Ingrese una opcion: ";
        cin >> opcion;
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
            menuEquipos();
            break;
        case 5:
            menuMapa(mapa);
        case 6:
            cout << "Saliendo del programa.\n";
            break;
        default:
            cout << "Opcion invalida.\n";
            break;
        }
    } while (opcion != 6);
}

// Bienvenida al programa
void Bienvenida(const string &fileName)
{
    ifstream inputFile(fileName); // Abrir el archivo

    if (!inputFile)
    {
        cerr << "Error: No se pudo abrir el archivo " << fileName << endl;
        return;
    }

    string linea;
    while (getline(inputFile, linea)) // Leer cada línea del archivo
    {
        cout << linea << endl; // Imprimir cada línea en el terminal
    }

    inputFile.close(); // Cerrar el archivo
}

int main()
{
    char continuar;
    while (continuar != 'X' && continuar != 'x')
    {
        string filename = "ucab_z.txt";
        Bienvenida(filename);
        cout << "PRESIONA X PARA CONTINUAR --> ";
        cin >> continuar;
        system("cls"); // Limpia la consola
    }

    menuPrincipal(); // Iniciar el menu principal
    return 0;
}

/*Funcion de juego
1.Manejo de todo lo necesario del juego
2.Mostrar el mapa
3.Menu de opciones del juego dentro de cada estacion
4.Posibilades
5.Siguiente estacion
*/