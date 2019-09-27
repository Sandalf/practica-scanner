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

## 2. Palabras reservadas
Sólo se contemplan las siguientes: identity, transpose y throw.

## 3. Números octales
Un número octal es una secuencia de símbolos octales que comienza con 0 (cero). Ningún símbolo alfabético o el guión bajo puede aparecer inmediatamente después de esta secuencia.

Por ejemplo 034, 0, y 01 son números octales, pero 098 no lo es.

## 4. Números hexadecimales
Un número hexadecimal es una secuencia de longitud par pero no vacía de símbolos hexadecimales que es precedida por la secuencia 0x o 0X. Ningún símbolo alfabético o el guión bajo puede aparecer inmediatamente después de esta secuencia.

Por ejemplo 0x34, 0xA4f5, y 0XABCD son números hexadecimales, pero 0x, 0x98e y F3AE no lo son.

## 5. Números reales
Un número real consiste de dos partes: la primera es llamada la mantisa y la segunda el exponente.
1. La mantisa, a su vez, consiste de dos partes: la parte entera y la parte decimal. La mantisa inicia con la parte entera, la cual consiste de 1) una secuencia no vacía de símbolos numéricos no inicializada en 0 (cero), o bien 2) de un solo 0. En el primer caso, la parte decimal es opcional. En el segundo caso la parte decimal es obligatoria.
2. La parte decimal consiste de un punto (.) seguido de una secuencia no vacía de al menos un símbolo numérico.
3. El exponente es opcional.
4. El exponente inicia con la letra e (o E), seguida de un símbolo más (+) o menos (–), el cual es opcional.
5. El exponente finaliza con una secuencia no vacía de caracteres numéricos.
Ningún símbolo alfabético o el guión bajo puede aparecer inmediatamente después de un número real.

Por ejemplo, 24, 0.3, 315.7, 0.4e+5, 83e-4 y 0.7E10 son números reales.

## Comandos
compilacion
```
g++ -std=c++11 main.cpp scanner.cpp -o main.o
```

## MC Alejandro Aguilar Cornejo

