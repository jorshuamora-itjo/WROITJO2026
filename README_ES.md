<div align="center">

# WRO 2026 — Futuros Ingenieros
### **Equipo:** The Pits JO &nbsp;|&nbsp; **Robot:** Meteoro
**Instituto Técnico Jesús Obrero (ITJO)**

[![C++](https://img.shields.io/badge/Language-C%2B%2B17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![WRO 2026](https://img.shields.io/badge/WRO-Future_Engineers_2026-orange?style=for-the-badge)](https://wro-association.org/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg?style=for-the-badge)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Arduino_Nano-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)

---

> 🇬🇧 **Note for international judges:** You can read the official main documentation in English at [`README.md`](README.md).

---

</div>

## Materiales de Ingeniería

Este repositorio contiene todos los materiales de ingeniería, modelos CAD, diagramas esquemáticos, código fuente y documentación técnica del vehículo autónomo **Meteoro**, desarrollado por el equipo **The Pits JO** del **Instituto Técnico Jesús Obrero (ITJO)** para la competencia **WRO Future Engineers 2026**.

### Contenido del Repositorio

* **`README.md`**: Documentación técnica principal en inglés.
* **`README_ES.md`**: Documentación técnica completa en español.
* **`LICENSE`**: Licencia de código abierto MIT correspondiente al equipo The Pits JO.
* **`.gitignore`**: Archivo de configuración para ignorar temporales y binarios de compilación.
* **`src/`**: Diferentes códigos del software de control para todos los componentes que fueron programados para participar en la competencia.
* **`models/`**: Archivos de los modelos utilizados por impresoras 3D, máquinas de corte láser y máquinas CNC para fabricar los elementos del vehículo.
* **`photos/`**: Galería fotográfica unificada que contiene tanto fotos oficiales del equipo, vistas del carro y registros del proceso de armado y programación.
* **`video/`**: Archivo con el enlace directo al video de demostración de manejo en pista.
* **`schematics/`**: Diagramas esquemáticos de los componentes electromecánicos, ilustrando todos los elementos (componentes electrónicos y motores) utilizados en el vehículo y cómo se conectan entre sí.
* **`docs/`**: Documentación adicional, hojas de datos, tablas de pines y listas de verificación en foso.

---

> **Aclaración Técnica de Nomenclatura**
> 
> Para evitar redundancias o confusiones a lo largo de este documento y de todo el repositorio técnico:
> 1. Se denominará **"Pit Dinoco"** (o versión 1.1) a la primera plataforma experimental construida por el equipo para nuestra primera competencia WRO.
> 2. Se denominará **"Meteoro"** (o versión 2.0) al prototipo actual de competencias, fruto del rediseño integral electromecánico y de software.

---

## Introducción

El equipo **The Pits JO** está integrado por estudiantes del 6.º año de Educación Media Técnica del **Instituto Técnico Jesús Obrero (ITJO)**. Nuestra formación abarca las especialidades de Electrónica y Telemática, lo que nos ha permitido abordar el desarrollo del vehículo desde una perspectiva integral de ingeniería mecatrónica.

Aunque en la práctica real del taller todos los integrantes colaboramos de forma transversal en el armado, cableado, programación y resolución de imprevistos (*"todos hacemos todo"*), hemos definido una estructura de responsabilidades alineada a las áreas de especialización académica de cada miembro:

| Integrante | Mención Académica | Roles Principales | Contribuciones Clave y Trabajos Cruzados |
| :--- | :--- | :--- | :--- |
| **Samuel Castillo** | Técnico Profesional Industrial en Electrónica | Diseñador Mecánico 3D, Mantenimiento e Integración Electromecánica | Modelado CAD de los chasis v1.1 y v2.0, calibración mecánica de la dirección, fabricación 3D de engranajes customizados y desarrollo de rutinas de código para actuadores. |
| **Jorshua Mora** | Técnico Profesional Industrial en Telemática | Programador Principal de Software, Especialista en Visión y Pits | Desarrollo del firmware base, calibración del sistema PixyCam2, mantenimiento correctivo en foso y apoyo directo en el ruteo e integración de conexiones eléctricas. |
| **Winston Garrido** | Técnico Profesional Industrial en Electrónica | Algoritmos de Control PID, Diseñador de Esquemas y Gestión de Repositorio | Ajuste del control PID adaptativo, diseño de la distribución de potencia, elaboración del pinout/esquemas eléctricos y estructuración técnica del repositorio GitHub. |

Por recomendación y petición expresa de nuestro mentor técnico, la estructura arquitectónica del firmware y la selección de la geometría de viraje fueron evaluadas bajo estrictas pruebas de repetición antes de su implementación definitiva en el prototipo v2.0.

---

## Análisis Crítico y Lecciones Aprendidas (Pit Dinoco v1.1)

Tras concluir nuestra primera experiencia en la World Robot Olympiad (WRO), realizamos un análisis crítico y riguroso sobre el desempeño en pista de **Pit Dinoco**. Aquella primera iteración nos permitió identificar fallas de ingeniería que condicionaban el rendimiento general:

* **Ruteo de Cableado Deficiente:** La ausencia de canaletas integradas derivó en conductores doblados o expuestos a rozamiento con elementos móviles, ocasionando falsos contactos durante las pruebas.
* **Distribución de Peso Inadecuado:** La concentración del peso (baterías de litio) en el voladizo posterior desplazó el centro de gravedad (CG), privando de adherencia al eje delantero. Esto provocaba que el robot subvirara (*"se fuera de frente"*) en las esquinas de 90º.
* **Interferencia Física de Sensores:** Los sensores ultrasónicos se encontraban en posiciones contiguas a las ruedas delanteras, llegando a colisionar mecánicamente durante los virajes máximos.
* **Acoples Mecánicos Improvisados:** El mecanismo de dirección utilizaba un brazo de servo adaptado manualmente que, bajo carga continua, sufría deformación por fricción térmica (llegando a derretirse o barrerse el estriado del motor).

### Pilares de Diseño para Meteoro v2.0

Con base en las lecciones extraídas de Pit Dinoco, establecimos cuatro pilares de diseño para el prototipo **Meteoro**:

1. **Accesibilidad y Mantenibilidad:** Acceso rápido a las baterías y módulos lógicos sin necesidad de desmontar la estructura principal en foso.
2. **Gestión Térmica y Eléctrica de Cables:** Canaletas de ruteo internas y pasacables dedicados para aislar líneas de potencia de líneas de señal.
3. **Robustez Mecánica:** Piezas impresas con perfiles de alta resistencia (5 perímetros de pared y relleno Giroide al 20%) en áreas sometidas a impacto o vibración.
4. **Cinemática Corregida:** Integración de dirección estilo F1 basada en geometría Ackermann y acoplamiento de Yugo Escocés.

Mantuvimos la combinación que demostró eficiencia operacional en el prototipo anterior: elementos lógicos en impresión 3D, electrónica estandarizada y componentes mecánicos complementarios de LEGO Technic (ejes estriados, cojinetes de precisión y ruedas de 40mm de diámetro por 20mm de grosor).

---

## Componentes y Sensores

Reemplazamos los módulos tradicionales HC-SR04 por sensores **RCWL-1601**. A pesar de mantener la misma interfaz física de 4 pines (`VCC`, `TRIG`, `ECHO`, `GND`), estos presentan mejoras sustanciales en inmunidad al ruido acústico y tiempos de refresco:

| Parámetro Técnico | Módulo Anterior: HC-SR04 | Módulo Actual: RCWL-1601 | Impacto en el Vehículo "Meteoro" |
| :--- | :--- | :--- | :--- |
| **Factor de Forma** | Estándar (45 x 20 mm) | Compacto (21 x 18 mm) | Permite su integración interna en el alerón delantero. |
| **Tensión de Operación** | 5.0V DC rígido | 3.0V - 5.5V DC | Inmunidad ante ligeras fluctuaciones de la línea de control. |
| **Ángulo de Apertura** | aprox. 15º (Propenso a ecos) | < 12º (Haz concentrado) | Reduce falsas lecturas con paredes acrílicas en diagonal. |
| **Precisión de Rango** | ±3 mm | ±1 mm | Estabilidad en el cálculo de error para el bucle PID. |

Para la optimización del tiempo de respuesta del centrado PID, analizamos soluciones aplicadas por equipos internacionales de alto rendimiento en la WRO, tomando como referencia técnica la disposición de sensores del equipo **GammaVersion** (campeones de España WRO 2022/2025 en su análisis *"Gamma Version's Car Review"*).

* **Ventaja Cinemática:** Al adelantar los sensores respecto al eje de viraje delantero, el controlador procesa las variaciones de pared con mayor anticipación espacial, iniciando la corrección antes de ingresar a la curva.
* **Protección Estructural Anticolisión:** Para evitar daños por impacto en caso de colisión, se diseñaron carcasas rígidas personalizadas que encastran los transductores ultrasónicos con una tolerancia de ajuste de 0.1mm.
* **Orientación Espacial:** Para no exceder los límites dimensionales reglamentarios, los sensores laterales (izquierdo y derecho) se montaron verticalmente, mientras que el frontal se mantuvo en disposición horizontal.

---

## Especificaciones Mecánicas y Cinemática de Dirección

El diseño dimensional de Meteoro se esquematizó previamente sobre papel milimetrado para garantizar el cumplimiento de la norma WRO (máximo 30cm de largo x 20cm de ancho):

* **Largo Total:** 26 cm
* **Ancho Total:** 13 cm
* **Diámetro de Ruedas:** 40 mm (Grosor: 20 mm)

Al reubicar las baterías en el centro del chasis inferior, el motor DC de tracción tuvo que orientarse de forma paralela al eje trasero. Debido a que los engranajes rectos convencionales operan únicamente de forma coplanar y los engranajes doble biselados comercializados por LEGO no ofrecían la relación exacta deseada sin alterar las cotas del vehículo, diseñamos e imprimimos en 3D un juego de **engranajes biselados a 90º a medida**.

Esta relación **(1:1.5)** mantiene el balance óptimo para nuestra masa total de **660 g**, proporcionando velocidad lineal sin comprometer el par de arranque (torque).

### Geometría de Dirección Ackermann

Para eliminar el arrastre de los neumáticos delanteros en virajes de 90º implementamos una geometría de dirección Ackermann impulsada por un servomotor **MG90S** alojado en el chasis mediante un mecanismo de guía ranurada y pasador (basado cinemáticamente en el Yugo Escocés).

$$\cot(\theta_{\text{ext}}) - \cot(\theta_{\text{int}}) = \frac{w}{L}$$

Donde $w = 128\text{ mm}$ (ancho de vía) y $L = 165\text{ mm}$ (distancia entre ejes).

Tras evaluar comportamientos geométricos (Ackermann al 100%, Paralelo y Agresivo >100%), se ajustó la línea de convergencia desplazando el punto de cruce 2.5 cm por detrás del centro del eje trasero. Esto otorga un comportamiento equilibrado:

* **En Recta:** Evita oscilaciones o hipersensibilidad en correcciones PID pequeñas.
* **En Curva:** Permite que la rueda interior ($\theta_{\text{int}}$) abra un ángulo mayor que la exterior ($\theta_{\text{ext}}$), evitando que el vehículo arrastre el tren delantero.

---

## Distribución de Chasis (Estructura de Dos Plantas)

* **Planta Inferior (Chasis Base):** Aloja el paquete de baterías Li-ion 3S dispuesto de forma longitudinal centrado, el motor DC con su caja reductora biselada, el servomotor de dirección y el alerón con los 3 sensores RCWL-1601. Posee una ventana inferior para el reemplazo de baterías sin desmontar el nivel superior.
* **Planta Superior (Carcasa Superior F1):** Soporta el driver de potencia L298N, la cámara de visión PixyCam2 y las tarjetas Arduino Nano (Maestro/Esclavo). Su geometría aerodinámica actúa como cubierta del servo y enruta los conductores hacia la parte posterior.

---

## Módulos y Enlaces Directos

* **Firmware del Prototipo:** [`src/`](src/)
* **Tabla de Conexiones (Pinout):** [`schematics/`](schematics/)
* **Lista de Verificación de Foso:** [`docs/`](docs/)

---

<div align="center">

© 2026 **The Pits JO** — Instituto Técnico Jesús Obrero.  
Todos los derechos reservados. Distribuido bajo la [Licencia MIT](LICENSE).

</div>
