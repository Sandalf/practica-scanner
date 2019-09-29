#include <cstdio>
#include <ctype.h>
#include <iostream>
#include "scanner.hpp"

using namespace std;

int main(int argc, char** argv)
{    
    printf("SCANNER\n");
    // char file[100] = "";
    // cout << "Ingresa una ruta de archivo: ";
    // cin >> file;

    open("test.txt");
    token t;
    char* match;

    do {
        pair<token, char *> res = next();
        t = res.first;
        match = res.second;
        
        switch (t) {
            case _id: printf("Identificador: %s\n", match); break;
            case _identity:
            case _transpose:
            case _throw: printf("Palabra reservada: %s\n", match); break;
            case _oct: printf("Octal: %s\n", match); break;
            case _hex: printf("Hexadecimal: %s\n", match); break;
            case _real: printf("Real: %s\n", match); break;
            case _del: printf("Delimante: %s\n", match); break;
            case _arit: printf("Aritmetico: %s\n", match); break;
            case _punct: printf("Puntuación: %s\n", match); break;
            case _asign: printf("Asignación: %s\n", match); break;
            case _eof: printf("EOF: %s\n", match); break;
            case _err: printf("Error: %s\n", match); break;
            default: break;
        }
    } while(t != _eof && t != _err);

    close();
    return 0;
}
