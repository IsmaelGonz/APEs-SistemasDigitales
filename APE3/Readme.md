Práctica 3: Temporizador de hardware y generación de señal con ESP32



Asignatura: Sistemas Digitales (5to Ciclo)



Institución: Universidad Nacional de Loja - Carrera de Computación



Fecha: 30 de octubre de 2026



Integrantes del Equipo



Richard Cajas



Ismael Gonzalez



Jostin Vasquez



Miguel Veintimilla



Gyna Yupanqui



Objetivo de la Práctica



Configurar un temporizador de hardware del ESP32 utilizando la API del core 3.x. El propósito es utilizar su interrupción (ISR) para hacer parpadear un LED, generar una onda cuadrada con frecuencias calculadas (100 Hz, 1000 Hz, 5000 Hz) y medir dicha señal con un analizador lógico virtual y un multímetro físico.



Herramientas y Materiales



Software:



Wokwi: Simulador online de circuitos.



Arduino IDE: Con el paquete esp32 by Espressif Systems (core v3.x).



PulseView / GTKWave: Para abrir y analizar archivos .vcd del analizador lógico.



Hardware:



1x Placa ESP32 DevKit V1 de 30 pines



1x Protoboard



1x LED rojo de 5 mm



1x Resistencia de 330 Ω



Cables jumper macho-macho



Multímetro u osciloscopio



Resumen de Procedimientos y Resultados



Simulación de Temporizador y Patrón Bandera: Se configuró el temporizador para levantar una bandera en intervalos de 1000 ms, 250 ms y 50 ms. La función loop() procesó estos cambios para hacer parpadear el LED, logrando un periodo exacto sin atascar la CPU.



Generación de Onda Cuadrada: Se aplicó la fórmula del factor 2 (Alarma\_us = 1000000 / (2 \* Frecuencia)). Para 1000 Hz, la alarma se configuró en 500 ticks, generando exitosamente una señal medida a 1 ms por periodo en PulseView.



Prueba Física: Se cargó el código al ESP32 real. Al medir con el multímetro, los resultados fueron sumamente precisos (ej. midiendo 99.99 Hz para una señal solicitada de 100 Hz), verificando el comportamiento del software en hardware real.



Conclusiones Destacadas



Precisión: La temporización por hardware ofrece una precisión determinista a nivel de microsegundos, eliminando la incertidumbre de los retardos por software (como delay()).



Factor 2: Para la generación de ondas, es crucial aplicar el "factor 2" en los cálculos del temporizador, ya que cada alarma solo representa un flanco (un cambio de estado, medio periodo).



Eficiencia (ISR): Es vital mantener las Rutinas de Servicio de Interrupción (ISR) lo más veloces posible. Tareas lentas como impresiones seriales deben delegarse a la función principal utilizando el "patrón bandera" con variables de tipo volatile.

