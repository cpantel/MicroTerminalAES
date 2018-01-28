# MicroTerminalAES

El objetivo de este proyecto es ejercitar y seguir aprendiendo sobre los conceptos y prácticas de los cursos de programación de sistemas embebidos de CAPSE [1] del Proyecto CIAA [2] y un curso de Udemy [3].

* Implementar el cifrado AES utilizando las operaciones AES nativas del procesador MSP430-FR6989 de la placa MSP-EXP430FR6989 utilizada en el curso de Udemy.
* Usar una EDU-CIAA-NXP + Poncho PLC como dispositivo de entrada y salida con comunicación serial hacia MSP-EXP430FR6989 y serial USB hacia una computadora.
* Utilizar los displays, leds y switches de ambas placas para controlas 
* Conectar un teclado de TI99 4A a la EDU-CIAA-NXP


                        +---------+ 
                        | Teclado |
                        +---------+ 
                             | 
                             v
    +---------+       +--------------+          +------------------+
    |    PC   |       | EDU-CIAA-NXP |          | MSP-EXP430FR6989 |
    |         |<----->|              |<-------->|       AES        | 
    |  Tests  |       |              |          |     Display      |
    +---------+       +--------------+          +------------------+
                             |
                             v
                       +------------+ 
                       | Poncho PLC |
                       |   Display  |
                       +------------+ 
 
[1] 
[2] 
[3] 
