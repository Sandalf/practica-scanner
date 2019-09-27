#ifndef scanner_hpp
#define scanner_hpp

typedef enum { _id, _res, _identity, _transpose, _throw, _nat, _real, _oct, _hex, _del, _arit, _punct, _asign, _eof, _err } token;

extern void open(const char *fname);
extern void close();
extern token next();

#endif