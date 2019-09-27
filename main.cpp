#include <cstdio>
#include <ctype.h>
#include "scanner.hpp"

using namespace std;

int main()
{    
    // TODO: Allow user to specify the file
    open("test.txt");
    token t;

    do {
        t = next();

        // TODO: Print the string matched
        switch (t) {
            case _id: printf("Identificador\n"); break;
            case _identity:
            case _transpose:
            case _throw: printf("Palabra reservada\n"); break;
            case _oct: printf("Octal\n"); break;
            case _hex: printf("Hexadecimal\n"); break;
            case _real: printf("Real\n"); break;
            case _del: printf("Delimante\n"); break;
            case _arit: printf("Aritmetico\n"); break;
            case _punct: printf("Puntuación\n"); break;
            case _asign: printf("Asignación\n"); break;
            case _eof: printf("EOF\n"); break;
            case _err: printf("Error\n"); break;
            default: break;
        }
    } while(t != _eof && t != _err);

    close();
    return 0;
}
