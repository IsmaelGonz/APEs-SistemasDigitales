# 🚀 APE 3: Temporizador de hardware y generación de señal con ESP32

## 📖 1. Descripción del proyecto

### ¿Qué hace?
Este proyecto implementa el uso de temporizadores de hardware del ESP32 utilizando la API del core 3.x. Utiliza interrupciones (ISR) para hacer parpadear un LED y generar ondas cuadradas de frecuencias específicas (100 Hz, 1000 Hz, 5000 Hz), verificando las señales con un analizador lógico virtual y un multímetro físico.

### ¿Qué problema resuelve?
Demuestra cómo gestionar el tiempo a nivel de hardware con altísima precisión, evitando funciones bloqueantes como `delay()`. Además, implementa buenas prácticas en programación de sistemas embebidos, como el "patrón bandera", manteniendo las rutinas de servicio de interrupción (ISR) lo más cortas y eficientes posibles.

### ✨ Principales funcionalidades
* **Código 1 - Parpadeo con patrón bandera:** El temporizador genera una alarma, la ISR levanta una bandera (`volatile`) y el ciclo principal (`loop`) se encarga de encender/apagar el LED (GPIO19) e imprimir los tiempos en milisegundos usando `millis()`.
* **Código 2 - Generación y medición de onda cuadrada:** Calcula automáticamente el valor de la alarma aplicando el "factor 2" según la frecuencia deseada. Invierte el estado del pin (GPIO18) directamente en la ISR para exactitud temporal nanométrica y cuenta los ciclos para validar la frecuencia generada.

---

## 🛠️ 2. Tecnologías utilizadas

| Tipo | Tecnología | Uso |
| :--- | :--- | :--- |
| **Lenguaje** | Arduino C/C++ | Desarrollo nativo para ESP32 |
| **Plataforma** | Espressif ESP32 | Microcontrolador (DevKit V1 de 30 pines) |
| **Simulación** | Wokwi | Circuito y Analizador Lógico (archivo `diagram.json`) |
| **Análisis Lógico** | PulseView / GTKWave | Lectura del archivo de captura digital `.vcd` |
| **Herramientas** | Arduino IDE | Carga y depuración (Core Espressif v3.x) |

---

## ⚙️ 3. Instalación y configuración

### 📋 Requisitos previos
* Placa **ESP32 DevKit V1** y Protoboard.
* 1 LED rojo y 1 Resistencia de 330 Ω.
* **Arduino IDE** con el Core de Espressif **3.x** instalado. *(Ojo: Los códigos de esta práctica son incompatibles con el core v2.x).*
* Software **PulseView** instalado en el computador para leer gráficos digitales.

### 🚀 Instalación paso a paso
1. **Instalar el core ESP32 (Arduino IDE):**
   * Ir a `Archivo` > `Preferencias` y en URLs Adicionales pegar: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   * Ir a `Herramientas` > `Placa` > `Gestor de tarjetas` e instalar "esp32 by Espressif Systems".
2. **Clonar el repositorio:**
   ```bash
   git clone [https://github.com/IsmaelGonz/AP2-Sistemas%20Digitales](https://github.com/IsmaelGonz/AP2-Sistemas%20Digitales)
   cd "AP2-Sistemas Digitales"
   
1. ** Seleccionar la placa y puerto:**

  * En Arduino IDE: Herramientas > Placa > ESP32 Dev Module.

🔧 Configuración de Hardware
LED Principal: Ánodo al pin GPIO19 mediante resistencia de 330 Ω, cátodo a GND.

Onda Cuadrada: Pin GPIO18 directo a la punta del analizador/osciloscopio.

Monitor Serie: Configurado a 115200 baudios.

🎮 4. Uso del proyecto
💡 Código 1: LED con temporizador y patrón bandera
Cargar el codigo1.ino a la placa ESP32.

Abrir el Monitor Serie (115200 baudios).

Modificar la variable ALARMA_US a valores como 1000000, 250000 y 50000 para observar las variaciones en el tiempo de impresión y velocidad de parpadeo del LED.

🎛️ Código 2: Generar y medir onda cuadrada
Cargar el codigo2.ino configurando la variable FREC_SENAL (ej. 100, 1000, 5000).

En el Monitor Serie, verificar el cálculo interno del valor de la alarma y los "cambios de pin por segundo".

Medición Física: Conectar un multímetro en modo Hz (o un osciloscopio) entre GND y GPIO18 para comprobar que la frecuencia real entregada por la placa coincida con la programada en el código.

💻 Análisis con Wokwi y PulseView
Importar el archivo diagram.json en wokwi.com. Iniciar la simulación y detenerla a los 3 segundos.

Permitir la descarga del archivo generado wokwi-logic.vcd.

Abrir PulseView → Import Value Change Dump data. Medir el periodo exacto de la onda analizando el tiempo entre los flancos de subida del canal logic.D0.

---
📂 5. Estructura del repositorio
APE3/
├── capturas/
│   ├── medicion.jpg           # Evidencia física de medición 1
│   └── medicion1.jpg          # Evidencia física de medición 2
├── codigo1/codigo1/
│   └── codigo1.ino            # Temporizador con patrón bandera
├── codigo2/codigo2/
│   └── codigo2.ino            # Generación de onda cuadrada y factor 2
├── wokwi/
│   ├── diagram.json           # Circuito para Wokwi (ESP32 + LED + Analizador)
│   └── wokwi-logic.vcd        # Captura de datos del analizador lógico (.vcd)
└── Readme.md                  # Documentación principal
---

✅ 6. Verificación técnica y justificaciones
🔍 Detalles técnicos aplicados
El Patrón Bandera (Código 1): La variable bandera (hayAlarma) se declara con el modificador volatile para forzar al compilador a leerla directamente desde la RAM y evitar cuelgues u optimizaciones no deseadas. La impresión de texto pesada (Serial.printf) queda fuera de la ISR y es manejada por el loop().

Priorización en ISR (Código 2): Se omite el patrón bandera y se invierte el pin (digitalWrite) directamente dentro de la ISR para asegurar que la señal cuadrada sea matemáticamente perfecta y no sufra retardos de procesamiento.

El Factor 2: Se programa aplicando la fórmula ALARMA_US = 1000000 / (2 * FREC_SENAL). Dado que una onda cuadrada completa requiere un flanco de subida (encendido) y uno de bajada (apagado), el temporizador debe alarmar al doble de la velocidad de la frecuencia objetivo.

Autorrecarga Continua: Se emplea la instrucción timerAlarm(timer, ALARMA_US, true, 0); donde el parámetro true evita desbordamientos reseteando infinitamente el hardware.
