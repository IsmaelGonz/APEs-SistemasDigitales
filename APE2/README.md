# AP2 Sistemas Digitales

## 1. Descripción del proyecto

### ¿Qué hace?
Este proyecto implementa dos ejemplos prácticos para la placa **ESP32 Dev Module** con el objetivo de trabajar con salidas digitales (LEDs) y entradas (pulsador), utilizando temporización basada en `millis()` sin el uso de `delay()`.

### ¿Qué problema resuelve?
Demuestra cómo realizar secuencias temporizadas y controladas por eventos en sistemas embebidos, evitando el bloqueo del microcontrolador que genera el uso de `delay()`, y aplicando técnicas básicas como el antirrebote por software.

### Principales funcionalidades

- **Código 1 - Secuencia circular de LEDs:** Enciende un LED a la vez (GPIO16, GPIO17, GPIO18, GPIO19) en ciclo, avanzando cada 300 ms.
- **Código 2 - Juego de luces interactivo:** Igual que el código 1, pero permite cambiar la velocidad de la secuencia (lento → medio → rápido → lento) al presionar un pulsador conectado a GPIO21, con antirrebote por software (30 ms) y registro de cambios por el monitor serie.

## 2. Tecnologías utilizadas

| Tipo | Tecnología | Uso |
|---|---|---|
| Lenguaje | [Arduino C/C++ (Arduino framework)](https://www.arduino.cc/reference/en/) | Desarrollo para ESP32 |
| Plataforma objetivo | [Espressif ESP32](https://www.espressif.com/es/products/socs/esp32) | Microcontrolador (ESP32 Dev Module) |
| Simulación | [Wokwi](https://wokwi.com/) | Simulación del circuito (archivo `diagram.json`) |
| Herramientas | [Arduino IDE](https://www.arduino.cc/en/software) / [PlatformIO](https://platformio.org/) | Carga y depuración de los sketchs |

*No se utilizan librerías externas; todo el código es nativo del framework Arduino para ESP32.*

## 3. Instalación y configuración

### Requisitos previos

- Placa **ESP32 Dev Module** (o compatible)
- Arduino IDE con el [Core de Espressif para ESP32](https://docs.espressif.com/projects/arduino-esp32/en/latest/) instalado, o PlatformIO
- Cable USB para conectar la placa
- (Opcional) Cuenta en [Wokwi](https://wokwi.com/) para simular con `wokwi/diagram.json`

### Instalación paso a paso

1. **Instalar el core ESP32** (Arduino IDE):
   - Abrir Arduino IDE → `Archivo > Preferencias`
   - En "Gestor de URLs Adicionales de Tarjetas", agregar: `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
   - Ir a `Herramientas > Placa > Gestor de tarjetas`, buscar `esp32` e instalar el paquete de Espressif

2. **Clonar o descargar el repositorio**
   ```bash
   git clone https://github.com/Richard9302/AP2-SistemasDigitales.git
   cd AP2-SistemasDigitales
   ```

3. **Seleccionar la placa y puerto**
   - En Arduino IDE: `Herramientas > Placa > ESP32 Arduino > ESP32 Dev Module`
   - `Herramientas > Puerto` → seleccionar el puerto correspondiente a la placa

### Configuración

- **Código 1:** No requiere configuración adicional. Usa pines 16, 17, 18, 19.
- **Código 2:** Requiere pulsador en GPIO21 con resistencia interna `INPUT_PULLUP`. El monitor serie a 115200 baudios se usa para mostrar los cambios de velocidad.
- **Sin variables de entorno** ni credenciales requeridas para este proyecto.

## 4. Uso del proyecto

### Código 1: Secuencia de 4 LEDs sin `delay()`
1. Abrir `codigo1/AP2_Codigo1.ino.ino` en Arduino IDE
2. Verificar y cargar el sketch a la placa ESP32
3. Observar la secuencia: los LEDs conectados a GPIO16-19 se encienden uno tras otro cada 300 ms en ciclo continuo

### Código 2: Juego de luces interactivo
1. Abrir `codigo2/Codigo2.ino` en Arduino IDE
2. Verificar y cargar el sketch a la placa ESP32
3. Abrir el Monitor Serie a **115200 baudios**
4. Presionar el pulsador conectado a GPIO21 para alternar entre las velocidades: 400 ms (lento), 150 ms (medio), 60 ms (rápido)
5. El monitor serie mostrará: `Periodo: X ms` al cambiar de velocidad

### Simulación con Wokwi
- Abrir [Wokwi](https://wokwi.com/) e importar el archivo `wokwi/diagram.json` para simular el circuito tal como está definido.

## 5. Estructura del proyecto

```text
AP2-SistemasDigitales/
├── codigo1/
│   └── AP2_Codigo1.ino.ino    # Secuencia circular de 4 LEDs a 300 ms
├── codigo2/
│   └── Codigo2.ino            # Secuencia con cambio de velocidad por pulsador + antirrebote
├── evidencias/
│   └── IMG_0809.mov           # Evidencia fotográfica/video del montaje/funcionamiento
├── informe/
│   └── APE2.pdf               # Informe de la práctica
├── wokwi/
│   └── diagram.json           # Diagrama de circuito para Wokwi (ESP32 + 4 LEDs + pulsador)
├── README.md                  # Documentación del proyecto
└── .git/                      # Control de versiones
```

**Descripción de elementos principales:**
- `codigo1/`: Implementación básica de temporización con `millis()`
- `codigo2/`: Implementación con entrada por pulsador, máquina de estados de velocidad, antirrebote por software y salida por monitor serie
- `wokwi/diagram.json`: Conexiones (LEDs a GPIO16-19 con resistencias 330Ω, pulsador a GPIO21 con GND, usando `INPUT_PULLUP`)
- `informe/`: Documentación escrita de la práctica
- `evidencias/`: Material de evidencia del funcionamiento

## 6. Verificación del funcionamiento

### Verificaciones realizadas (inspección del código)
- **Temporización correcta:** Ambos códigos utilizan `millis()` comparando `ahora - tPaso >= PERIODO/VELOCIDAD`, sin llamadas bloqueantes a `delay()`
- **Lógica de secuencia:** Se activa un único LED por iteración (`digitalWrite(LEDS[i], i == posicion)`) con avance cíclico `posicion = (posicion + 1) % N_LEDS`
- **Entrada con antirrebote:** Código 2 implementa filtrado por tiempo (`T_REBOTE = 30 ms`), detección de flanco de bajada (`estadoEstable == LOW`) y solo actúa en el instante de presionado
- **Configuración de E/S:** LEDs como `OUTPUT`, pulsador como `INPUT_PULLUP`
- **Feedback:** Código 2 reporta cambios por `Serial` a 115200 baudios

### Cómo verificar
1. Cargar `codigo1` y observar el ciclo de 4 LEDs a ritmo constante
2. Cargar `codigo2`, abrir monitor serie a 115200 y presionar el pulsador varias veces para confirmar el cambio de velocidad
3. (Opcional) Simular con `wokwi/diagram.json` para verificar conexiones antes de cargar a hardware

### Estado
- **Sin suite de pruebas automatizadas** en el repositorio (`.ino`/sketches para Arduino/ESP32). No se ejecutaron pruebas unitarias/integradas en este entorno.
- **Sin errores evidentes** detectados en la revisión del código fuente.

## Evidencia 

- [Evidencia de video (GitHub)](https://github.com/user-attachments/assets/9817ad55-25e1-4eda-92e6-f49e4c679b99)
