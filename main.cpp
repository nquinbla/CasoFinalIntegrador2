/*CARGA DE SCRIPTS (50 puntos)
//
//Se proporciona una implementación correcta de load_script(const char* filename, bool show_script = false) que carga correctamente el archivo dado y muestra su contenido si show_script es verdadero. (25 puntos)
//Se proporciona una implementación correcta de load_script() que solicita al usuario un nombre de archivo, llama a la función load_script(const char* filename, bool show_script = false) y maneja cualquier error de manera apropiada. (25 puntos)
//
//MANEJO DE ERRORES (50 puntos)
//El código tiene un manejo de errores sólido y completo para el caso de que el nombre del archivo proporcionado no exista. (15 puntos)
//El código tiene un manejo de errores sólido y completo para el caso de que el archivo proporcionado no se pueda abrir por alguna razón. (15 puntos)
//El código tiene un manejo de errores sólido y completo para el caso de que se produzca un error de lectura durante la lectura del archivo. (20 puntos)
*/

#include <iostream>
#include <string>
#include <cstdio>
#include <vector>

using namespace std;

struct ColorConsole // no se puede modificar
{
    static constexpr auto fg_blue = "\033[34m";
    static constexpr auto bg_white = "\033[47m";
};

struct ConsoleBox
{
    void new_text() {/*...*/}
    void set_text(const string &text) { cout << text << endl; }
};

ConsoleBox *consoleBox = new ConsoleBox; // suponemos que ya está inicializado

void load_script(const char* filename, bool show_script = false) // función de carga de script con el nombre que indica el ejercicio
{
    string script;
    FILE* f = nullptr;
    try
    {
        f = fopen(filename, "rb");
        if (!f)
        {
            perror("error de apertura de archivo"); // error de apertura de archivo
            cerr << "error de apertura de " << filename << endl; // error de apertura de archivo
            return;
        }

        int c;
        char buf[4001]; // buffer de lectura
        while ((c = fread(buf, 1, 4000, f)) > 0) // lectura de archivo
        {
            buf[c] = 0; // terminador de cadena
            script.append(buf); // concatenación de cadena
        }
        fclose(f); // cierre de archivo
        f = nullptr; // puntero nulo

        if (show_script)
        {
            cout << ColorConsole::fg_blue << ColorConsole::bg_white; // color de consola
            cout << script << endl; // impresión de script
        }
        consoleBox->new_text(); // nueva línea
        consoleBox->set_text(script); // impresión de script
    }
    catch (...) // excepción
    {
        cerr << "error durante la lectura del archivo" << endl; // error de lectura
        if(f)
            fclose(f); // cierre de archivo

    }  cerr << "Error desconocido durante la lectura del archivo" << endl;
        if (f)
            fclose(f); // cierre de archivo
}

void load_script() // función de carga de script
{
    string filename; // nombre de archivo
    cout << "Ingrese el nombre del archivo: "; // mensaje
    cin >> filename;   // lectura de nombre de archivo
    load_script(filename.c_str(), true); // llamada a función de carga de script
}

int main()
{
    load_script();
    return 0;
}


