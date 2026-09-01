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

* **[`README.md/`](README.md/)**: Documentación técnica principal en inglés.
* **[`README_ES.md/`](README_ES.md/)**: Documentación técnica completa en español.
* **[`LICENSE`](LICENSE/)**: Licencia de código abierto MIT correspondiente al equipo The Pits JO.
* **[`.gitignored`](.gitignored/)**: Archivo de configuración para ignorar temporales y binarios de compilación.
* **[`src/`](src/)**: Diferentes códigos del software de control para todos los componentes que fueron programados para participar en la competencia.
* **[`models/`](models/)**: Archivos de los modelos utilizados por impresoras 3D, máquinas de corte láser y máquinas CNC para fabricar los elementos del vehículo.
* **[`photos/`](photos/)**: Galería fotográfica unificada que contiene tanto fotos oficiales del equipo, vistas del carro y registros del proceso de armado y programación.
* **[`video/`](video/)**: Archivo con el enlace directo al video de demostración de manejo en pista.
* **[`schematics/`](schematics/)**: Diagramas esquemáticos de los componentes electromecánicos, ilustrando todos los elementos (componentes electrónicos y motores) utilizados en el vehículo y cómo se conectan entre sí.
* **[`docs/`](docs/)**: Documentación adicional, hojas de datos, tablas de pines y listas de verificación en foso.

---

> **Aclaración Técnica de Nomenclatura**
> 
> Para facilitar la lectura de la documentación y evitar confusiones a lo largo de este proyecto, utilizamos la siguiente norma:
> 1. **Pit Dinoco (Versión 1.1):** Es nuestro primer auto experimental. Con él aprendimos las bases de la competencia y detectamos las principales fallas a corregir.
> 2. **Meteoro (Versión 2.0):** Es el vehículo definitivo de competencia. Nace del rediseño completo de la parte mecánica, los circuitos de potencia y el programa de control.

---

## Comparativa Visual de los Prototipos

| Criterio de Diseño | Pit Dinoco ($v1.1$) | Meteoro ($v2.0$) |
| :--- | :--- | :--- |
| **Estructura** | Piso único (monocapa) con cables expuestos. | Chasis modular de doble piso con canaletas internas. |
| **Dirección** | Giro simple con servo expuesto a desgaste. | Geometría Ackermann con mecanismo de Yugo Escocés. |
| **Tracción** | Engranajes planos visibles. | Motor longitudinal con engranajes biselados a 90°. |
| **Reparto de Peso** | Baterías atrás (provocaba subviraje). | Baterías al centro del chasis inferior (equilibrio 50/50). |
| **Sensores de Distancia** | Módulos HC-SR04 pegados al frente. | Sensores RCWL-1601 integrados dentro del alerón F1. |

---

## Introducción

El equipo **The Pits JO** está integrado por estudiantes del 6.º año de Educación Media Técnica del **Instituto Técnico Jesús Obrero (ITJO)**. Nuestra formación académica abarca las especialidades de Electrónica y Telemática, lo que nos brindó las herramientas necesarias para construir un auto autónomo desde cero.

Aunque en la práctica diaria en el taller aplicamos la filosofía de *"todos hacemos todo"* (armar, soldar, programar y probar en pista), distribuimos la responsabilidad principal según la especialidad de cada integrante:

| Integrante | Mención Académica | Roles Principales | Contribuciones Clave y Trabajos Cruzados |
| :--- | :--- | :--- | :--- |
| **Samuel Castillo** | Técnico Profesional Industrial en Electrónica | Diseñador Mecánico 3D, Mantenimiento e Integración Electromecánica | Diseñó en 3D las piezas y el chasis de los prototipos $v1.1$ y $v2.0$, calibró el sistema de dirección, fabricó los engranajes a medida y apoyó en las rutinas de prueba de los motores. |
| **Jorshua Mora** | Técnico Profesional Industrial en Telemática | Programador Principal de Software, Especialista en Visión y Pits | Desarrolló el código base, configuró el sensor de visión PixyCam2, atendió el mantenimiento rápido en la zona de competencia (pits) y ayudó a conectar la red de cables. |
| **Winston Garrido** | Técnico Profesional Industrial en Electrónica | Algoritmos de Control PID, Diseñador de Esquemas y Gestión de Repositorio | Calibró el sistema de control de trayectoria $PD$, diseñó la red de alimentación eléctrica, dibujó los esquemáticos y organizó toda la documentación técnica en GitHub. |

> **Nota sobre Orientación Técnica**  
> Por recomendación y petición expresa de nuestro mentor técnico, la estructura arquitectónica del código y la geometría de la dirección fueron sometidas a intensas pruebas de repetición en pista antes de ser aprobadas e instaladas en el prototipo Meteoro ($v2.0$).

---

## Diagnóstico del Prototipo v1.1 ("Pit Dinoco") y Lecciones Aprendidas

Al finalizar nuestra primera participación con Pit Dinoco, analizamos detalladamente su comportamiento para entender por qué cometía errores en la pista. Este análisis nos reveló cuatro problemas mecánicos y eléctricos clave:

* **Cables Expuestos y Doblados:** Al no tener un camino ordenado para los cables, estos rozaban con las partes móviles o se doblaban en exceso, provocando fallas o falsos contactos involuntarios.
* **Reparto de Peso Desequilibrado:** Las baterías de litio estaban colocadas en la parte trasera del auto. Esto hacía que la parte delantera quedara muy liviana, perdiendo agarre y haciendo que el auto *"se fuera de frente"* (subviraje) en las curvas cerradas de 90°.
* **Interferencia de Sensores con las Ruedas:** Los sensores de ultrasonido estaban instalados muy cerca de las ruedas delanteras. Cuando el servomotor giraba al máximo, las ruedas golpeaban los sensores físicamente.
* **Desgaste en la Dirección:** El brazo mecánico conectado al servomotor era plano y de plástico simple. Con el uso continuo y el calor de la fricción, el plástico se ablandaba y se barría, perdiendo la alineación del centro.

### Nuevos Principios de Diseño Arquitectónico para "Meteoro" (v2.0)

Tomando como base los errores de Pit Dinoco, establecimos cuatro pilares esenciales para construir a Meteoro:

1. **Facilidad de Mantenimiento:** Diseñar un sistema donde se puedan cambiar las baterías o revisar las placas sin necesidad de desarmar todo el vehículo en la mesa de trabajo.
2. **Orden y Protección Eléctrica:** Crear canaletas internas que guíen los cables y mantengan separados los cables de alimentación (potencia) de los cables de datos (señales).
3. **Resistencia Mecánica:** Imprimir las piezas de alto impacto con patrones de relleno resistentes (Giroide al 20% y 5 capas de pared) para soportar vibraciones y posibles choques.
4. **Dirección Precisa:** Adoptar un sistema de dirección estilo F1 guiado por la geometría Ackermann y el mecanismo de Yugo Escocés.

---

## Inspiraciones Técnicas y Cambios de Ingeniería

Mantuvimos la combinación que nos dio excelentes resultados en durabilidad: chasis principal en impresión 3D (PLA+/PETG), electrónica estándar y componentes mecánicos de LEGO Technic (ejes estriados en cruz, cojinetes de precisión y ruedas de 40 mm de diámetro por 20 mm de grosor).

Reemplazamos los sensores tradicionales HC-SR04 por el modelo **RCWL-1601**. Aunque se conectan exactamente igual (pines `VCC`, `TRIG`, `ECHO` y `GND`), este nuevo modelo ofrece ventajas marcadas en espacio y precisión:

| Parámetro Técnico | Módulo Anterior: HC-SR04 | Módulo Actual: RCWL-1601 | Impacto en el Vehículo Meteoro |
| :--- | :--- | :--- | :--- |
| **Dimensiones** | Estándar (45 mm $\times$ 20 mm) | Compacto (21 mm $\times$ 18 mm) | Permite empotrar los tres sensores dentro del alerón frontal. |
| **Voltaje de Trabajo** | 5.0V DC rígido | 3.0V a 5.5V DC | Soporta pequeñas variaciones de voltaje sin fallar. |
| **Ángulo de Visión** | $\approx 15^\circ$ (propenso a ecos) | $< 12^\circ$ (haz estrecho) | Evita lecturas falsas al rebotar en paredes en diagonal. |
| **Precisión de Medida** | $\pm 3\text{ mm}$ | $\pm 1\text{ mm}$ | Proporciona medidas estables para corregir la trayectoria suavemente. |

### Integración del Alerón Frontal F1

Para mejorar la rapidez de respuesta en las esquinas, estudiamos soluciones aplicadas por equipos internacionales de la WRO, tomando como inspiración la disposición de sensores del equipo **GammaVersion** (campeones de España WRO).

* **Ventaja Cinemática:** Al colocar los sensores por delante del eje delantero de las ruedas, el vehículo "ve" las paredes con anticipación espacial antes de ingresar físicamente a la curva.
* **Protección contra Impactos:** Diseñamos carcasas de plástico rígido con una tolerancia de ajuste de 0.1 mm que protegen las cápsulas de los sensores ante cualquier roce contra los muros.
* **Orientación Espacial:** Para mantener el vehículo dentro de las dimensiones máximas permitidas (30 cm $\times$ 20 cm), colocamos los sensores laterales en posición vertical y el sensor frontal en posición horizontal.

---

## Especificaciones Mecánicas y Planos

Antes de modelar en la computadora, dibujamos los planos a escala real sobre papel milimetrado para verificar que el auto estuviera dentro de las reglas de la competencia:

* **Largo Total:** 26 cm (Límite máximo permitido: 30 cm)
* **Ancho Total:** 13 cm (Límite máximo permitido: 20 cm)
* **Diámetro de Ruedas:** 40 mm (Ancho: 20 mm)

### Reingeniería del Tren de Transmisión: Engranajes Biselados Custom 3D

Al reubicar las baterías en el piso inferior centrado, tuvimos que colocar el motor DC en sentido longitudinal (paralelo al chasis). Como las piezas comerciales no nos daban la relación de giro exacta que necesitábamos, diseñamos e imprimimos en 3D un conjunto de **engranajes biselados a 90°**:

$$\text{Relación de Transmisión} = \frac{\text{Dientes del Engranaje Conducido}}{\text{Dientes del Engranaje Motriz}} = \frac{24}{16} = 1.5$$

Esta relación $1:1.5$ ofrece el equilibrio justo entre aceleración de arranque y velocidad máxima para desplazar los $\approx 660\text{ g}$ de peso de nuestro auto.

---

## Mecanismo de Dirección Ackermann y Convergencia de Ejes

Para evitar que las ruedas delanteras arrastren o patinen al dar curvas de 90°, implementamos una geometría de dirección Ackermann accionada por un servomotor **AD002** mediante una guía con pasador (basada en el Yugo Escocés).

**Condición Cinemática Ideal:**

$$\cot(\theta_{\text{ext}}) - \cot(\theta_{\text{int}}) = \frac{w}{L}$$

Donde $w = 128\text{ mm}$ (distancia entre ruedas delanteras) y $L = 165\text{ mm}$ (distancia entre ejes delantero y trasero).

**Ajuste de Giro en Pista:**

Ajustamos el punto donde convergen las líneas de la dirección 2.5 cm por detrás del eje trasero. Esto brinda un comportamiento ideal:

* **En Tramos Rectos:** El auto se mantiene firme sin hacer movimientos bruscos o zigzags.
* **En Curvas:** La rueda interna ($\theta_{\text{int}}$) gira con un ángulo mayor que la rueda externa ($\theta_{\text{ext}}$), haciendo que la vuelta sea limpia y sin fricción excesiva.

---

## Estructura de Doble Piso y Ruteo Eléctrico

Meteoro está dividido en dos niveles independientes:

* **Planta Inferior (Base Mecánica y Potencia):** Contiene el paquete de baterías Li-ion 3S centrado, el motor de tracción con sus engranajes a 90°, la dirección servoguiada y el alerón frontal F1. Cuenta además con una escotilla inferior para cambiar la batería en segundos.
* **Planta Superior (Cerebro Lógico y Visión):** Sostiene el controlador de motor L298N, la cámara PixyCam2 y los dos microcontroladores Arduino Nano (Maestro y Esclavo). Su carcasa protege el servomotor y mantiene todos los cables ordenados por canaletas.

---

## Estrategia de Navegación de Meteoro

La estrategia de navegación de Meteoro utiliza una arquitectura de control de monitoreo constante (bucle cerrado) dividida en tres pilares: lectura y filtrado EMA, Máquina de Estados Finitos (FSM) y controladores en tiempo real.

### Definición del Algoritmo por Estados

#### Estado RECTA (Centrado PD Adaptativo)
En tramos rectos, el vehículo busca mantener una distancia equivalente respecto a las paredes laterales izquierda y derecha:

$$e(t) = \frac{\text{US}_{\text{der}} - \text{US}_{\text{izq}}}{2}$$

Para evitar tambaleos o sobre-correcciones bruscas causadas por pequeñas imperfecciones en el acrílico, se aplica una **Zona de Tolerancia o Zona Muerta (Deadband)** de $\pm 5.0\text{ cm}$:

* Si $|e(t)| \le 5.0\text{ cm} \implies \text{error} = 0$
* Si $e(t) > 5.0\text{ cm} \implies \text{error} = e(t) - 5.0$
* Si $e(t) < -5.0\text{ cm} \implies \text{error} = e(t) + 5.0$

El ángulo de dirección final se calcula mediante la acción del controlador Proporcional-Derivativo (PD):

$$\text{Salida PD} = K_p \cdot \text{error} + K_d \cdot \frac{d e(t)}{dt}$$

$$\theta_{\text{dirección}} = \theta_{\text{neutral}} + \text{Salida PD}$$

Donde $\theta_{\text{neutral}} = 92^\circ$, $K_p = 10.33$ y $K_d = 14.0$.

---

#### Estado CURVA (Giro Asistido por Giroscopio MPU6050)
Cuando el sensor frontal detecta una pared a una distancia $\le 75.0\text{ cm}$, la FSM cambia al estado **CURVA**:

* **Determinación del Sentido (Primera Esquina):** Si es la primera esquina del recorrido ($\text{sentidoPista} == 0$), se comparan las lecturas de los sensores laterales:
    * **Si `US_izq` > `US_der`:** Sentido Antihorario (Ángulo 65°)
    * **Si `US_izq` ≤ `US_der`:** Sentido Horario (Ángulo 115°)
  
  Este valor se guarda en $\text{sentidoPista}$ y fija la dirección de giro para todas las curvas siguientes del circuito.

* **Cálculo del Ángulo de Giro Acumulado / Yaw ($\theta_z$):** A partir de la velocidad de giro medida en el eje Z ($\omega_z$), se calcula la variación del ángulo acumulado:

$$\theta_z(t) = \theta_z(t - \Delta t) + \left( \frac{\text{Gyro Z}_{\text{crudo}} - \text{offset}_z}{131.0} \right) \cdot \Delta t$$

* **Criterio de Salida:** El giro se mantiene de forma activa hasta que el valor absoluto de la rotación acumulada alcanza la meta fijada:

$$|\theta_z(t)| \ge \theta_{\text{objetivo}} \quad (\theta_{\text{objetivo}} = 72.0^\circ)$$

---

#### Estado COOLDOWN (Pausa de Protección Post-Curva)
Al finalizar el giro de $72^\circ$, el vehículo entra en un periodo de estabilización (**COOLDOWN**) por $1200\text{ ms}$. Durante este intervalo:

1. Se reinicia la memoria del término derivativo ($\text{error anterior} = 0$).
2. Se pausa o ignora temporalmente la lectura del sensor frontal para evitar lecturas erróneas producidas por la inercia del giro o la pared lateral saliente.
3. Se reanuda el control PD con las lecturas laterales para estabilizar la trayectoria antes de regresar al estado **RECTA**.

---

### Filtrado de Datos de Sensores (Filtro EMA Híbrido)

Los sensores de ultrasonido a veces presentan fallas de lectura (*outliers*) o marcajes erróneos de $0\text{ cm}$ debido al rebote del sonido. Para solucionar esto, el algoritmo aplica un filtro híbrido **EMA (Exponential Moving Average)** con umbral de apertura:

```cpp
// Si el sensor detecta espacio abierto (> 70 cm) o error (0 cm),
// responde instantáneamente para no perder la apertura de curva.
// En rangos normales (muros cercanos), aplica suavizado con alpha = 0.4.

float filtrarEMA(float lecturaActual, float lecturaAnterior, float alpha = 0.4) {
    if (lecturaActual == 0 || lecturaActual > 70.0) {
        return lecturaActual; // Respuesta instantánea en aperturas/errores
    }
    return (alpha * lecturaActual) + ((1.0 - alpha) * lecturaAnterior);
}

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
</div>
