#include <cstdio>
#include <ctype.h>
#include <iostream>
#include "scanner.hpp"

using namespace std;

int main(int argc, char** argv)
{    
    char file[100] = "";
    cout << "Ingresa una ruta de archivo: ";
    cin >> file;

    open(file);
    token t;
    int i = 5;

    do {
        i++;
        pair<token, char *> t = next();
        
        switch (t.first) {
            case _id: printf("Identificador: %s\n", t.second); break;
            case _identity:
            case _transpose:
            case _throw: printf("Palabra reservada: %s\n", t.second); break;
            case _oct: printf("Octal: %s\n", t.second); break;
            case _hex: printf("Hexadecimal: %s\n", t.second); break;
            case _real: printf("Real: %s\n", t.second); break;
            case _del: printf("Delimante: %s\n", t.second); break;
            case _arit: printf("Aritmetico: %s\n", t.second); break;
            case _punct: printf("Puntuación: %s\n", t.second); break;
            case _asign: printf("Asignación: %s\n", t.second); break;
            case _eof: printf("EOF: %s\n", t.second); break;
            case _err: printf("Error: %s\n", t.second); break;
            default: break;
        }
    } while(t != _eof && t != _err && i < 50);

    close();
    return 0;
}
