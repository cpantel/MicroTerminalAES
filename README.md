# MicroTerminalAES

El objetivo de este proyecto es ejercitar y seguir aprendiendo sobre los conceptos y prácticas de los cursos de programación de sistemas embebidos de [CAPSE](http://www.proyecto-ciaa.com.ar/devwiki/doku.php?id=educacion:cursos:cursos_programacion_ciaa) del [Proyecto CIAA](http://www.proyecto-ciaa.com.ar] y un curso de Udemy [Microcontrollers and the C Programming Language](https://www.udemy.com/mcu_msp430/).

* Implementar el cifrado AES utilizando las operaciones AES nativas del procesador MSP430-FR6989 de la placa MSP-EXP430FR6989 utilizada en el curso de Udemy.
* Usar una [EDU-CIAA-NXP]() + [Poncho PLC]() como dispositivo de entrada y salida con comunicación serial hacia MSP-EXP430FR6989 y serial USB hacia una computadora.
* Utilizar los displays, leds y switches de ambas placas para monitorearlas y controlarlas. 
* Conectar un teclado de [TI99-4A](https://en.wikipedia.org/wiki/Texas_Instruments_TI-99/4A) a la EDU-CIAA-NXP

==Toolchains==
* LaunchPad MSP-EXP430FR6989
  * CSS v7
* EDU-CIAA-NXP + Poncho PLC
  * algo parecido a [http://www.proyecto-ciaa.com.ar/devwiki/doku.php?id=borradores:install_linux]
  * sAPI del Firmware V2 [https://github.com/ciaa/firmware_v2.git]


<!-- language: lang-none -->

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
 
==Elección de componentes==

EDU-CIAA-NXP: Una elección natural.

Poncho PLC: por el display. ¿Por qué no el [Poncho Educativo]()? Por que el puerto serial del Poncho Educativo está a niveles ....

MSP-EXP430FR6989: por haberlo usado en el curso de Udemy, haber visto que tenía AES y haber quedado moralmente en deuda con un trabajo práctico final.

Teclado matricial TI99 4A: por haberlo guardado por décadas.

