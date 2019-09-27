#include <cstdio>
#include <ctype.h>
#include <map>
#include <string>
#include <cstring>
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

bool isx(char c) {
    switch (c)
    {
        case 'x':
        case 'X':
            return true;
        break;
    }
    return false;
}

bool isexponent(char c) {
    switch (c)
    {
        case 'E':
        case 'e':
            return true;
        break;
    }
    return false;
}

bool issign(char c) {
    switch (c)
    {
        case '+':
        case '-':
            return true;
        break;
    }
    return false;
}

bool isdelimitation(char c) {
    switch (c)
    {
        case '(':
        case ')':
        case '[':
        case ']':
            return true;
        break;
    }
    return false;
}

bool isarithmetic(char c) {
    switch (c)
    {
        case '+':
        case '-':
        case '*':
        case '/':
            return true;
        break;
    }
    return false;
}

bool ispunctuation(char c) {
    switch (c)
    {
        case ',':
        case ';':
            return true;
        break;
    }
    return false;
}

std::map<std::string, token> reserved_words = {
    { "identity", _identity },
    { "transpose", _transpose },
    { "throw", _throw }
};

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

token hex() {
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
                if(c == 'x' || c == 'X') actual = 2;
                else actual = udef;
                break;
            case 2:
                if(isxdigit(c)) actual = 3;
                else actual = udef;
                break;
            case 3:
                if(isxdigit(c)) actual = 4;
                else actual = udef;
                break;
            case 4:
                if(isxdigit(c)) actual = 3;
                else actual = udef; 
                break;
            default: break;
        }

        if (actual != udef) {
            match[i] = c;
            i += 1;
        }
    }

    if (prior == 4) {
        printf("%s: ", match);
        fallback();
        success();
        return _hex;
    }

    fail();
    return _err;
}

token real() {
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
                else if (isdigit(c)) actual = 2;
                else actual = udef;
                break;
            case 1:
                if(c == '.') actual = 3;
                else actual = udef;
                break;
            case 2:
                if(isdigit(c));
                else if (c == '.') actual = 3;
                else if (c == 'e' || c == 'E') actual = 5;
                else actual = udef;
                break;
            case 3:
                if(isdigit(c)) actual = 4;
                else actual = udef;
                break;
            case 4:
                if(isdigit(c)) actual = 4;
                else if(c == 'e' || c == 'E') actual = 5;
                else actual = udef;
                break;
            case 5:
                if(c == '+' || c == '-') actual = 6;
                else if (isdigit(c)) actual = 7;
                else actual = udef; 
                break;
            case 6:
                if(isdigit(c)) actual = 7;
                else actual = udef; 
                break;
            case 7:
                if(isdigit(c));
                else actual = udef; 
                break;
            default: break;
        }

        if (actual != udef) {
            match[i] = c;
            i += 1;
        }
    }

    if (prior == 2 || prior == 4 || prior == 7) {
        printf("%s: ", match);
        fallback();
        success();
        return _real;
    }

    fail();
    return _err;
}

std::pair<token, char*> ids() {
    printf("Ids\n");
    int actual = 0;
    int prior = 0;
    char match[100] = "";
    int i = 0;    

    while(actual != udef) {
        prior = actual;
        char c = read();
        // printf("ids:char = %c %d\n", c, isalnum(c));

        switch (actual) {
            case 0:            
                if(isalpha(c)) actual = 1;
                else if (c == '_') actual = 2;
                else actual = udef;
                break;
            case 1:
                if(isalnum(c) || c == '_');
                else if (c == '\'') actual = 4;
                else actual = udef;
                break;
            case 2:
                if(isdigit(c) || c == '_');
                else if(isalpha(c)) actual = 1;
                else actual = udef;
                break;
            case 3:
                actual = udef;
                break;
            case 4:
                if (c == '\'');
                else actual = udef;  
                break;
            default: break;
        }

        if (actual != udef) {
            match[i] = c;
            i += 1;
        }
    }
    // printf("ids:prior = %d\n", prior);
    bool isReservedWord = reserved_words.count(match) > 0;
    if (prior == 1 || prior == 4 || isReservedWord) {
        fallback();
        success();
        if (isReservedWord) return std::make_pair(reserved_words[match], match);
        return std::make_pair(_id, match);
    }
  
    fail();
    return std::make_pair(_err, match);
}

std::pair<token, char*> nums() {
    printf("Nums\n");
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
                else if (isnatural(c)) actual = 2;
                else actual = udef;
                break;
            case 1:
                if(isoctal(c)) actual = 3;
                else if (isx(c)) actual = 4;
                else if (c == '.') actual = 5;
                else actual = udef;
                break;
            case 2:
                if(isdigit(c));
                else if (isexponent(c)) actual = 6;
                else if (c == '.') actual = 5;
                else actual = udef;
                break;
            case 3:
                if(isoctal(c));
                else actual = udef;
                break;
            case 4:
                if(isxdigit(c)) actual = 7;
                else actual = udef;
                break;
            case 5:
                if(isdigit(c)) actual = 8;
                else actual = udef; 
                break;
            case 6:
                if(isdigit(c)) actual = 9;
                else if (issign(c)) actual = 10;
                else actual = udef; 
                break;
            case 7:
                if(isxdigit(c)) actual = 11;
                else actual = udef; 
                break;
            case 8:
                if(isdigit(c));
                else if (isexponent(c)) actual = 6;
                else actual = udef; 
                break;
            case 9:
                if(isdigit(c));
                else actual = udef; 
                break;
            case 10:
                if(isdigit(c)) actual = 9;
                else actual = udef; 
                break;
            case 11:
                if(isxdigit(c)) actual = 7;
                else actual = udef; 
                break;
            default: break;
        }

        if (actual != udef) {
            match[i] = c;
            i += 1;
        }
    }

    if (prior == 1 || prior == 2 || prior == 3 || prior == 8 || prior == 9 || prior == 11) {
        fallback();
        success();
        token t;
        if (prior == 1 || prior == 3) t = _oct;
        if (prior == 2 || prior == 8 || prior == 9) t = _real;
        if (prior == 11) t = _hex;
        return std::make_pair(t, match);
    }
    
    fail();
    return std::make_pair(_err, match);
}

std::pair<token, char*> signs() {
    printf("Signs\n");
    int actual = 0;
    int prior = 0;
    char match[100] = "";
    int i = 0;    

    while(actual != udef) {
        prior = actual;
        char c = read();
        printf("signs:char %c\n", c);

        switch (actual) {
            case 0:
                if(isdelimitation(c)) actual = 1;
                else if (isarithmetic(c)) actual = 2;
                else if (ispunctuation(c)) actual = 3;
                else if (c == ':') actual = 4;
                else actual = udef;
                break;
            case 1:
                actual = udef;
                break;
            case 2:
                actual = udef;
                break;
            case 3:
                actual = udef;
                break;
            case 4:
                actual = udef;
                break;
            default: break;
        }

        if (actual != udef) {
            match[i] = c;
            i += 1;
        }
    }

    if (prior == 1 || prior == 2 || prior == 3 || prior == 4) {
        fallback();
        success();
        token t;
        if (prior == 1) t = _del;
        if (prior == 2) t = _arit;
        if (prior == 3) t = _punct;
        if (prior == 4) t = _asign;
        return std::make_pair(t, match);
    }
  
    fail();
    return std::make_pair(_err, match);
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

std::pair<token, char*> next() {
    wsp();
    if (lastq == q && q != 0) return std::make_pair(_eof, (char*)"");
    
    std::pair<token, char*> tids = ids();
    if (tids.first != _err) return tids;

    std::pair<token, char*> tnums = nums();
    if (tnums.first != _err) return tnums;

    std::pair<token, char*> tsings = signs();
    if (tsings.first != _err) return tsings;
    printf("Is not sign\n");

    read();
    if (eof()) return std::make_pair(_eof, (char*)"");

    lastq = q;
    q = 0;
    fail();
    printf("Error en posición %ld\n", lastq);
    printf("Linea %d\n", line(lastq));
    
    return std::make_pair(_err, (char*)"");
}
