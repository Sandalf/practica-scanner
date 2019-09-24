# Lenguajes y Autómatas II
## Práctica No. 1: Diseño e Implementación de un Analizador Léxico

## Familias Léxicas
* Símbolos alfabéticos: Conjunto de los caracteres en los rangos a, b, …, z y A, B, …, Z.
* Símbolos numéricos: Conjunto de los caracteres comprendidos en el rango 0, 1, …, 9.
* Símbolos octales: Conjunto de los caracteres comprendidos en el rango 0, 1, …, 7.
* Símbolos hexadecimales: Conjunto de los caracteres comprendidos en los rangos 0, 1, …, 9
(caracteres numéricos), a, b, …, f y A, B, …, F.

## 1. Identificadores
Un identificador es una secuencia que consiste únicamente de símbolos alfabéticos, símbolos numéricos, el
guion bajo (_) y el apóstrofo ('):
1. No puede comenzar con un símbolo numérico.
2. Debe tener al menos un símbolo alfabético.
3. El apóstrofo solo puede aparecer al final. Un identificador pueden terminar con al menos un apóstrofo.
4. No son palabras reservadas.
Los siguientes son ejemplos de identificadores: x, _abc, x_4', _3x, cont''.

## Comandos
compilacion
```
g++ main.cpp scanner.cpp -o main.o
```
