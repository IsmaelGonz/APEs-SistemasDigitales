// AP2 - Codigo 1: secuencia de 4 LEDs sin delay()
// Placa: ESP32 Dev Module | core Espressif 3.x | sin librerias
// Pines: LEDs en GPIO16, 17, 18 y 19 (cada uno con 330 ohm)
constexpr uint8_t LEDS[] = {16, 17, 18, 19};
constexpr uint8_t N_LEDS = sizeof(LEDS) / sizeof(LEDS[0]);
constexpr uint32_t PERIODO = 300; // ms entre un paso y el siguiente
uint8_t posicion = 0; // LED encendido (0 a 3)
uint32_t tPaso = 0; // instante del ultimo paso
void setup() {
 for (uint8_t i = 0; i < N_LEDS; i++) {
 pinMode(LEDS[i], OUTPUT);
 }
}
void loop() {
 uint32_t ahora = millis();
 if (ahora - tPaso >= PERIODO) { // ya pasaron PERIODO ms?
 tPaso = ahora; // anotar la hora
 posicion = (posicion + 1) % N_LEDS; // avanzar al siguiente LED
 }
 for (uint8_t i = 0; i < N_LEDS; i++) {
 digitalWrite(LEDS[i], i == posicion); // solo el LED "posicion" encendido
  }
}
