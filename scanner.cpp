#include <cstdio>
#include <ctype.h>
#include "scanner.hpp"

FILE *file;
long q;
long lastq = -1;
const int udef = -1;

void open(const char *fname) {
    file = fopen(fname, "r");
    q = 0;
}

void close() {
    fclose(file);
}

char read() {
    return fgetc(file);
}

void success() {
    lastq = q;
    q = ftell(file);
}

void fallback() {
    fseek(file, -1, SEEK_CUR);
}

void fail() {
    fseek(file, q, SEEK_SET);
}

bool isnatural(char c) {
    switch (c) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        return true;
        break;
    }

    return false;
}

bool isoctal(char c) {
    switch (c) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        return true;
        break;
    }

    return false;
}

token id() {
    int actual = 0;
    int prior = 0;
    char match[100] = "";
    int i = 0;

    while(actual != udef) {
        prior = actual;
        char c = read();        

        switch (actual) {
            case 0:
                if(isalpha(c)) actual = 1;
                else if (c == '_') actual = 3;
                else actual = udef;
                break;
            case 1:
                if(isalpha(c) || isdigit(c) || c == '_');
                else if(c == '\'') actual = 2;
                else actual = udef;
                break;
            case 2:
                if(c == '\'');
                else actual = udef;
                break;
            case 3:
                if(isdigit(c) || c == '_');
                else if (isalpha(c)) actual = 1;
                else actual = udef;
                break;
            default:
                break;
        }

        if (actual != udef) {
            match[i] = c;
            i += 1;
        }
    }

    if (prior == 1 || prior == 2) {
        printf("%s: ", match);
        fallback();
        success();
        return _id;
    }

    fail();    
    return _err;
}

token oct() {
    int actual = 0;
    int prior = 0;
    char match[100] = "";
    int i = 0;

    while(actual != udef) {
        prior = actual;
        char c = read();

        switch (actual) {
            case 0:
                if(c == '0') actual = 1;
                else actual = udef;
                break;
            case 1:
                if(isoctal(c));
                else actual = udef;
                break;
            default: break;
        }

        if (actual != udef) {
            match[i] = c;
            i += 1;
        }
    }

    if (prior == 1) {
        printf("%s: ", match);
        fallback();
        success();
        return _oct;
    }

    fail();
    return _err;
}

bool wsp() {
    while(isspace(read()));

    fallback();
    success();

    return true;
}

bool eof() {
    if (read() == EOF) {
        fallback();
        return true;
    }

    fallback();
    return false;
}

int line(long _q) {
    long q = 0;
    int line = 0;
    int c;
    while ((c = fgetc(file)) != EOF && q < _q) {
        q++;
        if (c == '\n') {
            ++line;
        }
    }
    ++line;
    return line;
}

token next() {
    wsp();
    if (lastq == q && q != 0) return _eof;
    
    token tid = id();
    if (tid != _err) return tid;

    token toct = oct();
    if (toct != _err) return toct;

    read();
    if (eof()) return _eof;

    lastq = q;
    q = 0;
    fail();
    printf("Error en posición %ld\n", lastq);
    printf("Linea %d\n", line(lastq));
    
    return _err;
}
