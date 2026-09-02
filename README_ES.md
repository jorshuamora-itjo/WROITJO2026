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
| **Samuel Castillo** | Técnico Profesional Industrial en Electrónica | Diseñador Mecánico 3D, Mantenimiento e Integración Electromecánica | Diseñó en 3D las piezas y el chasis de los prototipos  $v1.1$  y  $v2.0$, calibró el sistema de dirección, fabricó los engranajes a medida y apoyó en las rutinas de prueba de los motores. |
| **Jorshua Mora** | Técnico Profesional Industrial en Telemática | Programador Principal de Software, Especialista en Visión y Pits | Desarrolló el código base, configuró el sensor de visión PixyCam2, atendió el mantenimiento rápido en la zona de competencia (pits) y ayudó a conectar la red de cables. |
| **Winston Garrido** | Técnico Profesional Industrial en Electrónica | Algoritmos de Control PID, Diseñador de Esquemas y Gestión de Repositorio | Calibró el sistema de control de trayectoria  $PD$, diseñó la red de alimentación eléctrica, dibujó los esquemáticos y organizó toda la documentación técnica en GitHub. |

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
| **Dimensiones** | Estándar (45 mm  $\times$  20 mm) | Compacto (21 mm  $\times$  18 mm) | Permite empotrar los tres sensores dentro del alerón frontal. |
| **Voltaje de Trabajo** | 5.0V DC rígido | 3.0V a 5.5V DC | Soporta pequeñas variaciones de voltaje sin fallar. |
| **Ángulo de Visión** | $\approx 15^\circ$ (propenso a ecos) | $< 12^\circ$ (haz estrecho) | Evita lecturas falsas al rebotar en paredes en diagonal. |
| **Precisión de Medida** | $\pm 3\text{ mm}$ | $\pm 1\text{ mm}$ | Proporciona medidas estables para corregir la trayectoria suavemente. |

### Integración del Alerón Frontal F1

Para mejorar la rapidez de respuesta en las esquinas, estudiamos soluciones aplicadas por equipos internacionales de la WRO, tomando como inspiración la disposición de sensores del equipo **GammaVersion** (campeones de España WRO).

* **Ventaja Cinemática:** Al colocar los sensores por delante del eje delantero de las ruedas, el vehículo "ve" las paredes con anticipación espacial antes de ingresar físicamente a la curva.
* **Protección contra Impactos:** Diseñamos carcasas de plástico rígido con una tolerancia de ajuste de 0.1 mm que protegen las cápsulas de los sensores ante cualquier roce contra los muros.
* **Orientación Espacial:** Para mantener el vehículo dentro de las dimensiones máximas permitidas (30 cm  $\times$  20 cm), colocamos los sensores laterales en posición vertical y el sensor frontal en posición horizontal.

---

## Especificaciones Mecánicas y Planos

Antes de modelar en la computadora, dibujamos los planos a escala real sobre papel milimetrado para verificar que el auto estuviera dentro de las reglas de la competencia:

* **Largo Total:** 26 cm (Límite máximo permitido: 30 cm)
* **Ancho Total:** 13 cm (Límite máximo permitido: 20 cm)
* **Diámetro de Ruedas:** 40 mm (Ancho: 20 mm)

### Reingeniería del Tren de Transmisión: Engranajes Biselados Custom 3D

Al reubicar las baterías en el piso inferior centrado, tuvimos que colocar el motor DC en sentido longitudinal (paralelo al chasis). Como las piezas comerciales no nos daban la relación de giro exacta que necesitábamos, diseñamos e imprimimos en 3D un conjunto de **engranajes biselados a 90°**:

$$\text{Relación de Transmisión} = \frac{\text{Dientes del Engranaje Conducido}}{\text{Dientes del Engranaje Motriz}} = \frac{24}{16} = 1.5$$

Esta relación  $1:1.5$  ofrece el equilibrio justo entre aceleración de arranque y velocidad máxima para desplazar los  $\approx 660\text{ g}$  de peso de nuestro auto.

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

Donde $\theta_{\text{neutral}} = 92^\circ$, $K_p = 10.33$  y  $K_d = 14.0$.

---

#### Estado CURVA (Giro Asistido por Giroscopio MPU6050)
Cuando el sensor frontal detecta una pared a una distancia $\le 75.0\text{ cm}$, la FSM cambia al estado **CURVA**:

* **Determinación del Sentido (Primera Esquina):** Si es la primera esquina del recorrido ($\text{sentidoPista} == 0$), se comparan las lecturas de los sensores laterales:
    * **Si `US_izq` > `US_der`:** Sentido Antihorario (Ángulo 65°)
    * **Si `US_izq` ≤ `US_der`:** Sentido Horario (Ángulo 115°)
  
  Este valor se guarda en  $\text{sentidoPista}$  y fija la dirección de giro para todas las curvas siguientes del circuito.

* **Cálculo del Ángulo de Giro Acumulado / Yaw ($\theta_z$):** A partir de la velocidad de giro medida en el eje Z ($\omega_z$), se calcula la variación del ángulo acumulado:

$$\theta_z(t) = \theta_z(t - \Delta t) + \left( \frac{\text{Gyro Z}_{\text{crudo}} - \text{offset}_z}{131.0} \right) \cdot \Delta t$$

* **Criterio de Salida:** El giro se mantiene de forma activa hasta que el valor absoluto de la rotación acumulada alcanza la meta fijada:

$$|\theta_z(t)| \ge \theta_{\text{objetivo}} \quad (\theta_{\text{objetivo}} = 72.0^\circ)$$

---

#### Estado COOLDOWN (Pausa de Protección Post-Curva)
Al finalizar el giro de  $72^\circ$, el vehículo entra en un periodo de estabilización (**COOLDOWN**) por  $1200\text{ ms}$. Durante este intervalo:

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
```

---

## Diseño y Evolución Mecánica

### Diagnóstico Post-Mortem y Desafíos Mecánicos en Pit Dinoco (v1.1)

El análisis de rendimiento durante nuestra primera participación en pista nos dio el diagnóstico real que no podíamos observar del todo durante las pruebas en el taller. Identificamos cuatro inconvenientes clave de origen mecánico y de distribución física:

* **Organización del Cableado y Falta de Espacio:** En el intento de reducir las dimensiones al mínimo en una sola capa (monocapa), saturamos la zona central. Los cables de señal quedaron expuestos al roce constante con las piezas móviles del motor y la transmisión, lo que provocó fallas intermitentes por desgaste de los cables.
* **Desbalance del Centro de Gravedad (CG):** Al colocar las baterías de litio en la parte trasera, desplazamos el centro de gravedad fuera de su punto de equilibrio ideal. Esta falta de peso sobre las ruedas delanteras redujo su agarre al suelo, generando un deslizamiento frontal evidente (subviraje) al tomar curvas de 90°.
* **Obstáculo Físico en la Dirección:** Los sensores de ultrasonido delanteros chocaban directamente con las ruedas al girar al máximo, lo que limitaba el ángulo de viraje del vehículo.
* **Desgaste del Brazo de Dirección:** El brazo del servomotor original (impreso y adaptado manualmente en plástico) no soportó el uso continuo. La fricción constante generó calor y terminó barriendo los dientes del engrane, desalineando el punto neutro de la dirección.

---

### Comparativa de Arquitectura Mecánica: v1.1 vs v2.0

Mantuvimos la combinación de materiales que nos dio buenos resultados: la integración de piezas impresas en 3D (PLA+/PETG), componentes electrónicos estándar y elementos mecánicos de LEGO Technic (ejes con forma de cruz, cojinetes de precisión y ruedas de 40 mm × 20 mm).

Sin embargo, para corregir las debilidades estructurales, rediseñamos el chasis por completo. A continuación se detallan las mejoras implementadas:

| Criterio Constructivo | Prototipo Inicial: Pit Dinoco (v1.1) | Prototipo Competitivo: Meteoro (v2.0) | Impacto Mecánico y Dinámico |
| :--- | :--- | :--- | :--- |
| **Distribución del Chasis** | Una sola capa plana con componentes expuestos. | Doble piso modular interconectado. | Separa la zona de potencia de la electrónica de control y protege los componentes. |
| **Geometría de Dirección** | Pivote directo central (giro simétrico). | Geometría Ackermann accionada por Yugo Escocés. | Elimina el arrastre no deseado de las ruedas en curvas cerradas. |
| **Transmisión Trasera** | Engranajes rectos expuestos en el mismo plano. | Engranajes cónicos a 90° impresos en 3D. | Permite colocar el motor a lo largo del chasis y liberar espacio interior. |
| **Ubicación de Baterías** | Colocadas en la parte trasera (detrás del eje). | Compartimento inferior centrado (entre los dos ejes). | Equilibra el centro de gravedad (50/50) y elimina el deslizamiento frontal. |
| **Montaje de Sensores** | Soportes independientes al lado de las ruedas. | Alerón frontal tipo F1 con protección anticolisión. | Mejora la anticipación de lectura y protege los sensores ante choques. |
| **Mantenimiento en Pits** | Desarme total necesario para cualquier cambio. | Tapa de acceso rápido en el piso inferior. | Permite cambiar baterías en segundos sin tocar la electrónica. |

---

### Reingeniería Mecánica en Meteoro (v2.0)

#### 1. Alerón Frontal Integrado F1 (Inspiración "GammaVersion")
Tomando como referencia la distribución de sensores del equipo **GammaVersion** en la WRO, diseñamos una estructura frontal tipo alerón mediante impresión 3D:

* **Lectura Anticipada:** Ubicar los tres sensores de ultrasonido por delante del eje delantero permite al sistema detectar los muros con mayor anticipación antes de que el cuerpo del vehículo ingrese a la curva.
* **Protección Anticolisión:** Los sensores se encajan firmemente en carcasas rígidas con un ajuste exacto de 0.1 mm, funcionando además como un parachoques protector.
* **Distribución Eficiente:** Los sensores laterales se colocaron en posición vertical y el central en horizontal para no superar las dimensiones máximas permitidas de 30 cm × 20 cm.

---

#### 2. Geometría de Dirección Ackermann
Reemplazamos el pivote simple por un sistema de dirección geométrica tipo Ackermann movido por un servomotor **AD002** con engranajes metálicos, conectado mediante una guía ranurada con pasador (mecanismo de Yugo Escocés).

$$\cot(\theta_{\text{ext}}) - \cot(\theta_{\text{int}}) = \frac{w}{L}$$

Donde  $w = 128\text{ mm}$  (ancho entre ruedas) y  $L = 165\text{ mm}$  (distancia entre ejes).

Esta configuración hace que la rueda interior ($\theta_{\text{int}}$) gire en un ángulo mayor que la exterior ($\theta_{\text{ext}}$), haciendo que ambas sigan el trazado natural de la curva sin derrapar.

* **Calibración de Estabilidad:** Ajustamos la geometría para que el punto de alineación quede 2.5 cm por detrás del centro del eje trasero. Esto mantiene al vehículo firme y estable en rectas sin quitarle agilidad en los giros de 90°.

---

#### 3. Transmisión Rediseñada: Engranajes Cónicos Personalizados a 90°
Para colocar las baterías en el centro del piso inferior, orientamos el motor a lo largo del chasis. Como las piezas comerciales de LEGO no nos daban la relación necesaria en el espacio disponible, diseñamos e imprimimos un par de **engranajes cónicos a 90°**:

$$\text{Relación de Transmisión} = \frac{\text{Dientes Conducidos}}{\text{Dientes Motrices}} = \frac{24}{16} = 1.5$$

Esta relación de 1:1.5 ofrece el equilibrio justo entre fuerza de arranque y velocidad máxima para el peso total del vehículo (660 g).

---

#### 4. Distribución Modular de Doble Piso
La estructura de Meteoro simplifica las revisiones y reparaciones organizándose en dos niveles:

* **Planta Inferior (Transmisión y Potencia):** Aloja el paquete de baterías Li-ion 3S en el centro, el motor principal con sus engranajes cónicos, el servomotor de dirección metálico y el alerón delantero. Incluye una tapa de acceso rápido por debajo para cambiar las baterías cómodamente.
* **Planta Superior (Control y Sensores):** Sostiene los microcontroladores, el módulo del motor L298N, la cámara PixyCam2 y canaletas internas que mantienen los cables de señal aislados de los cables de corriente.

---

#### 5. Verificación de Dimensiones
Antes del modelado final en software CAD, trazamos las medidas sobre papel milimetrado para garantizar el cumplimiento del reglamento WRO (30 cm × 20 cm):

* **Largo Total:** 260 mm
* **Ancho Total:** 130 mm
* **Diámetro de Ruedas:** 40 mm (Ancho: 20 mm)

---

## Arquitectura Electrónica y Sistema de Potencia

En la robótica autónoma, la estabilidad del software depende totalmente de la solidez del sistema eléctrico que lo respalda. En nuestro primer prototipo (Pit Dinoco), sufríamos reinicios inesperados en el cerebro del carro debido a interferencias de energía provocadas por el motor principal y a las exigencias puntuales del motor de dirección.

Para Meteoro (v2.0), rediseñamos por completo la arquitectura electrónica dividiendo el trabajo entre dos microcontroladores conectados en red y construyendo un sistema de energía separado e independiente para cada necesidad.

---

### Arquitectura Lógica Distribuida (Maestro / Esclavo vía I2C)

Para evitar retrasos en el envío de señales a los motores mientras se leen sensores al mismo tiempo, repartimos el trabajo entre dos placas Arduino Nano interconectadas mediante el bus de datos I2C (en la dirección `0x08`):

* **Arduino Nano Maestro:** Funciona como el "cerebro" del vehículo. Se encarga de medir las distancias de los tres sensores de ultrasonido, calcular la inclinación con el giroscopio MPU6050, reconocer colores con la cámara PixyCam2 (conectada por bus SPI) y procesar las ecuaciones matemáticas de control para guiar el carro.
* **Arduino Nano Esclavo:** Funciona como el "músculo" del sistema. Recibe de forma rápida la información enviada por el Maestro y acciona directamente el servomotor de la dirección y el módulo L298N que da movimiento al motor principal.

---

### Asignación de Pines (Pinout Map)

Para consultar los esquemas gráficos completos e ilustrados, puedes revisar la carpeta `schematics/` en el repositorio.

#### Mapeo de Pines - Arduino Nano Maestro

| Módulo / Componente | Pin del Componente | Pin Arduino Nano | Tipo de Señal | Nivel Lógico | Función en el Sistema |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Ultrasonido Izquierdo** | ECHO | D6 | Entrada | 5.0 V | Recepción de eco para pared izquierda |
| | TRIG | D7 | Salida | 5.0 V | Emisión de pulso de ultrasonido |
| **Ultrasonido Derecho** | ECHO | D8 | Entrada | 5.0 V | Recepción de eco para pared derecha |
| | TRIG | D9 | Salida | 5.0 V | Emisión de pulso de ultrasonido |
| **Ultrasonido Frontal** | ECHO | D10 | Entrada | 5.0 V | Recepción de eco para detectar curvas |
| | TRIG | D11 | Salida | 5.0 V | Emisión de pulso de ultrasonido |
| **Giroscopio (MPU6050)** | SDA | A4 | I2C Data | 5.0 V | Lectura de giro en el eje Z |
| | SCL | A5 | I2C Clock | 5.0 V | Reloj de sincronización (100 kHz) |
| **Interconexión I2C (Esclavo)** | SDA | A4 | I2C Data | 5.0 V | Envío de orden de dirección y velocidad |
| | SCL | A5 | I2C Clock | 5.0 V | Canal de reloj compartido |
| **Cámara PixyCam2** | MOSI / MISO / SCK | D11 / D12 / D13 | SPI Bus | 5.0 V | Reconocimiento visual a 60 cuadros por segundo |
| **Alimentación Lógica** | 5V / GND | 5V / GND | Potencia | 5.0 V Reg. | Entrada desde el Regulador Canal 1 |

---

#### Mapeo de Pines - Arduino Nano Esclavo

| Módulo / Componente | Pin del Componente | Pin Arduino Nano | Tipo de Señal | Nivel Lógico | Función en el Sistema |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Servo de Dirección AD002** | Signal (PWM) | D2 | PWM Salida | 5.0 V | Ajuste de ángulo para dirección Ackermann |
| **Driver L298N (Motor DC)** | IN1 / A1 | D5 | PWM Salida | 5.0 V | Control de velocidad para la tracción |
| | IN2 / A2 | D6 | Salida Digital | 5.0 V | Sentido de marcha (LOW para avanzar) |
| **Interconexión I2C (Maestro)** | SDA | A4 | I2C Data | 5.0 V | Recepción de comandos desde el Maestro |
| | SCL | A5 | I2C Clock | 5.0 V | Canal de reloj compartido |
| **Alimentación Lógica** | 5V / GND | 5V / GND | Potencia | 5.0 V Reg. | Entrada desde el Regulador Canal 2 |

---

### Red de Distribución de Potencia y Regulación

La fuente de energía principal consiste en un paquete de 3 baterías de litio conectadas en serie (3S) que entregan una tensión nominal de 11.1 V (llegando a 12.6 V a carga completa).

Para eliminar por completo las caídas de voltaje que reiniciaban el sistema, dividimos la corriente usando dos reguladores de voltaje independientes (módulos Buck DSN-MINI-360):

| Etapa de Potencia | Fuente de Entrada | Salida Regulada | Componentes Alimentados |
| :--- | :--- | :--- | :--- |
| **Baterías de Litio (3S)** | Paquete 3 × 3.7 V | 11.1 V - 12.6 V Directo | Entrada de energía para el motor principal (Driver L298N) |
| **Regulador Buck 1 (Canal 1)** | Paquete de Litio 3S | 5.0 V DC Regulado | Arduino Nano Maestro, Giroscopio MPU6050, 3 Sensores Ultrasónicos y PixyCam2 |
| **Regulador Buck 2 (Canal 2)** | Paquete de Litio 3S | 5.0 V DC Regulado | Arduino Nano Esclavo y Servomotor AD00S |
| **Masa Común (GND)** | N/A | 0 V | Unión de cables de tierra para todas las placas y sensores |

---

### Beneficios del Aislamiento de Potencia

* **Protección ante Exigencias de Energía:** Cuando el servomotor realiza giros muy marcados en curvas cerradas, consume energía únicamente del Canal 2. Esto evita que el voltaje de la cámara o los procesadores baje del límite operativo de 4.5 V.
* **Filtrado de Interferencia:** El motor de tracción recibe energía directa de la batería. Los reguladores de voltaje aislados limpian los picos de corriente y el ruido eléctrico generados por el driver L298N.
* **Referencia Común de Tierra:** A pesar de tener regulaciones separadas, todos los cables negativos (0 V / GND) se unen en un solo punto para garantizar que la información transmitida por el bus I2C sea clara y precisa.

---

### Esquemáticos Electrónicos de Referencia

En la carpeta [`schematics/`](schematics/) del repositorio se encuentran disponibles las guías visuales de interconexión:

* `schematics/nano_master_diagram.jpg`: Diagrama de conexiones del circuito Maestro (Sensores, Visión, I2C y Canal 1 de Potencia).
* `schematics/nano_slave_diagram.jpg`: Diagrama de conexiones del circuito Esclavo (Motores, Driver L298N, Servomotor y Canal 2 de Potencia).
* `schematics/pinout_table.md`: Documento de consulta rápida para verificación de conexiones durante las pruebas en pits.

---

## Arquitectura de Software y Lógica de Control

### Evolución Histórica del Código (v1 a v4)

El desarrollo del software para nuestro vehículo no ocurrió de la noche a la mañana. Enfrentar la pista real nos enseñó que la teoría pura se estrella rápidamente cuando los sensores rebotan en esquinas abiertas o cuando las ruedas tiemblan por ruido numérico. A continuación, documentamos el proceso evolutivo de nuestras firmas de código guardadas en la carpeta `src/history/` hasta llegar a la versión actual en `src/current/`.

* **Versión 1: Monolítico y Bloqueante (`src/history/v1_pid_control.ino`)**
  * **Arquitectura:** Un solo Arduino Uno ejecutando todo el trabajo de forma secuencial.
  * **Mecanismo:** Medición con la función `pulseIn()`, la cual pausaba el procesador hasta 12 ms por cada sensor. Al medir 3 sensores, el procesador perdía más de 35 ms inmóvil por ciclo.
  * **Falla Crítica:** Al llegar a la esquina, el sensor frontal perdía la pared o leía rebotes erróneos. El algoritmo PID intentaba corregir distancias inexistentes, generando giros bruscos de dirección y choques contra la pared exterior.

* **Versión 2: Transición por Estados (`src/history/v2_pid_switch.ino`)**
  * **Innovación:** Implementamos por primera vez una Máquina de Estados Finita (`RECTA` y `CURVA`) para separar la corrección del carril de la maniobra de giro.
  * **Control:** Reducción automática de velocidad al detectar que se aproximaba un muro (fijada al 80% de la velocidad máxima).
  * **Falla Crítica:** El carro volvía al estado `RECTA` antes de terminar de salir del cruce. Al detectar el muro lateral demasiado cerca inmediatamente después del giro, el PID aplicaba un volantazo inverso instantáneo.

* **Versión 3: Temporizadores y Cooldown (`src/history/v3_fsm_cooldown.ino`)**
  * **Innovación:** Se introdujo la constante `COOLDOWN_CURVA` (1500 ms) para impedir que el auto reingresara al estado de curva inmediatamente tras salir de una.
  * **Dirección:** Primera versión en registrar si la pared abierta estaba a la izquierda o derecha antes de iniciar la maniobra fija.
  * **Falla Crítica:** Depender de tiempos fijos (`DURACION_GIRO = 2500 ms`) causaba descarrilamientos si la batería bajaba su carga: a menor voltaje, el auto recorría menos distancia en el mismo tiempo, quedando apuntando en diagonal.

* **Versión 4: Filtro de Mediana y Detección de Huecos (`src/history/v4_median_filter.ino`)**
  * **Innovación:** Incorporación del filtro de mediana sobre arreglos de 4 muestras (`filtroMediana4`) para ignorar picos de ruido causados por la textura del muro.
  * **Lógica:** Detección de aperturas de carril cuando la distancia medida superaba la `distanciaHueco` (90 cm).
  * **Punto de Quiebre:** Aunque el filtro de mediana limpió la señal, el cálculo de ordenamiento consumía ciclos de procesador apreciables. Además, el auto aún no sabía con certeza absoluta cuánto había rotado sobre su propio eje.

---

### Tabla Comparativa de Evolución de Software

| Criterio Térmico / Lógico | v1 (Monolítico) | v2 (Estados Simples) | v3 (Cooldown) | v4 (Filtro Mediana) | Versión Actual (`src/current/`) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| **Procesador** | 1 Arduino Uno | 1 Arduino Uno | 1 Arduino Uno | 1 Arduino Uno | 2 Arduino Nano (I2C) |
| **Lectura Ultrasónica** | `pulseIn()` bloqueante | `pulseIn()` directo | `pulseIn()` con tiempo | Mediana (4 muestras) | Librería NewPing + EMA |
| **Detección de Giro** | Distancia a pared | Umbral frontal fijo | Distancia + Tiempo | Detección de Hueco | Giroscopio MPU6050 Integrado |
| **Filtro de Ruido** | Sin filtro (Crudo) | Umbral rígido | Umbral rígido | Filtro Mediana 4p | EMA ($\alpha = 0.4$) + Límite 180 cm |
| **Seguridad de Sentido** | Inexistente | Reactivo instantáneo | Bloqueo por evento | Memoria de carácter | `sentidoPista` Permanente (EEPROM/RAM) |

---

### Arquitectura de Red Distribuida (Maestro / Esclavo)

Para garantizar un tiempo de ciclo ($\Delta t$) constante y libre de retrasos en la generación de señales de velocidad, el código actual ubicado en `src/current/` divide la carga computacional en dos procesadores a través del bus I2C a 100 kHz.

#### Análisis del Código Esclavo (`src/current/nano_slave.cpp`)

El microcontrolador Esclavo funciona como un controlador periférico dedicado exclusivamente al movimiento físico de la dirección y la tracción, manteniendo la lógica limpia de interrupciones de tiempo de sensores.

##### 1. Interrupción y Búfer Seguro
Para evitar interferencias de datos mientras se ejecutan las órdenes de los motores, los datos recibidos mediante el evento `Wire.onReceive(recibirDatosI2C)` se almacenan en variables protegidas marcadas con el calificador `volatile`:

```cpp
volatile byte anguloRecibido = 90;
volatile byte velRecibida = 255;
volatile bool actualizarMotores = false;
```

La función que atiende la llegada de datos simplemente toma los valores transmitidos y activa una señal de aviso (bandera), dejando que la activación física de los motores ocurra en el ciclo principal (`loop()`) para no congelar la comunicación I2C:

```cpp
void recibirDatosI2C(int cuantosBytes) {
  if (cuantosBytes >= 2) {
    anguloRecibido = Wire.read();    
    velRecibida = Wire.read(); 
    actualizarMotores = true; // Notifica al ciclo principal
  }
}
```

##### 2. Algoritmo de Arranque Progresivo (`arrancarSuave`)
Al encender el auto desde el reposo, el motor eléctrico exige un pico de corriente inicial (*inrush current*) que puede generar interferencias eléctricas en la línea de alimentación. El programa esclavo previene esto aumentando la velocidad de manera escalonada en cuestión de microsegundos:

```cpp
void arrancarSuave() {
  digitalWrite(pinB, LOW);
  for (int vel = 0; vel <= velRecibida; vel++) {
    analogWrite(pinA, vel);
    delayMicroseconds(3921); // Rampa de aceleración ~1 segundo total
  }
}
```

### Análisis del Código Maestro (`src/current/nano_master.cpp`)

El microcontrolador Maestro es el cerebro principal: analiza lo que sucede alrededor con los sensores, mide los giros del auto, administra los cambios de modo y calcula los ajustes necesarios para mantener la ruta ideal.

---

#### Filtrado Digital: Promedio Móvil Exponencial (EMA)

Para eliminar los temblores en las ruedas durante los tramos rectos sin sobrecargar el procesador con ordenamientos de listas complejas, implementamos un filtro de suavizado de datos (EMA).

**Ecuación Matemática:**
$$y[k] = \alpha \cdot x[k] + (1 - \alpha) \cdot y[k-1]$$

Donde:
* $x[k]$ representa la lectura cruda obtenida por el sensor en el instante actual $k$.
* $y[k-1]$ es la distancia filtrada que calculamos en el paso anterior.
* $\alpha = 0.4$ es el factor de suavizado que configuramos mediante pruebas prácticas.

**Tratamiento Espacial de Cero (0 cm = 180 cm):**
Cuando la pared desaparece en un cruce, los sensores ultrasónicos devuelven un valor de 0 cm debido a la ausencia de eco. Interpretamos esto como espacio totalmente libre asignándole una distancia teórica de 180.0 cm, evitando así divisiones por cero o correcciones erróneas:

```cpp
float filtrarLectura(float lecturaCruda, float lecturaAnterior) {
  float lecturaProcesada = lecturaCruda;
  if (lecturaCruda <= 0.0) {
    lecturaProcesada = 180.0; // Espacio abierto en esquina
  }

  // Si detectamos espacio abierto (> 70 cm), permitimos respuesta rápida
  if (lecturaProcesada > 70.0) {
    return lecturaProcesada; 
  }

  // Suavizado EMA para navegación fina cerca de muros
  float alpha = 0.4;
  return (alpha * lecturaProcesada) + ((1.0 - alpha) * lecturaAnterior);
}
```

### Integración Inercial del Giroscopio MPU6050

A diferencia de las versiones anteriores, los giros en la versión actual no dependen de rebotar ondas en muros inexistentes. Calculamos la rotación sumando de forma continua la velocidad de giro ($\omega_z$) medida por el sensor de movimiento MPU6050 a través de la conexión I2C (dirección `0x68`):

**Cálculo del Ángulo de Rotación:**
$$\theta_z = \sum \left( \frac{\text{giroZ}}{131.0} \right) \cdot \Delta t$$

Donde el valor 131.0 LSB/(°/s) corresponde a la escala de sensibilidad de ±250°/s configurada en el sensor MPU6050.

```cpp
// En el bucle dentro del estado CURVA
float giroZ = (leerGiroscopioZ() - offsetZ) / 131.0; 
anguloZ_acumulado += (giroZ * dt);

if (abs(anguloZ_acumulado) >= ANGULO_OBJETIVO) { // ANGULO_OBJETIVO = 72.0°
  estadoActual = COOLDOWN;
  tiempoInicioCooldown = millis();
}
```

### Máquina de Estados Finita y Lógica de Pista

* **Memoria de Sentido de Pista (`sentidoPista`):** Durante el primer giro de la carrera (`sentidoPista == 0`), el vehículo analiza qué lado ofrece mayor apertura y graba permanentemente la dirección del circuito. Una vez asignada la variable, las 11 curvas restantes del recorrido leen directamente `sentidoPista`, ignorando lecturas erróneas causadas por rebotes acústicos.

#### Controlador PD con Zona Muerta (Zona Azul)

En el modo `RECTA`, el vehículo se mantiene centrado entre ambas paredes midiendo la diferencia de centrado  $e(t)$:

$$e(t) = \frac{\text{distDer} - \text{distIzq}}{2}$$

**Filtro de Zona Azul (±5 cm):**
Para evitar correcciones innecesarias por imperfecciones o relieves en la pared de la pista, se aplica una zona muerta de ±5 cm:

```cpp
const float ZONA_AZUL = 5.0; 
float error = 0; 

if (abs(distancia_al_centro) <= ZONA_AZUL) {
  error = 0; 
}
else {
  if (distancia_al_centro > 0) error = distancia_al_centro - ZONA_AZUL; 
  else error = distancia_al_centro + ZONA_AZUL;
}
```

**Ecuación Proporcional-Derivativa:**
$$u(t) = K_p \cdot e(t) + K_d \cdot \frac{e(t) - e(t-\Delta t)}{\Delta t}$$

* **Ganancia Proporcional ($K_p = 10.33$):** Responde a la magnitud del descentrado del vehículo.
* **Ganancia Derivativa ($K_d = 14.0$):** Frena el balanceo lateral prediciendo la velocidad con la que el auto se acerca al muro.
* **Límite Estricto de Giro:** La salida  $u(t)$  está acotada a ±15° alrededor del punto medio del servomotor (92°), restringiendo el ángulo físico de la dirección a la ventana comprendida entre 57° y 127°.

---

### Mantenibilidad del Código y Guía de Parámetros de Pista

Para agilizar el proceso de calibración en el área de pits, los parámetros dinámicos clave están centralizados en las líneas 22 a 35 de `src/current/nano_master.cpp`:

```cpp
// PARÁMETROS CRÍTICOS A CALIBRAR EN PISTA
const float DIST_DETECCION_FRONT = 75.0; // Distancia (cm) para iniciar viraje
const float ANGULO_OBJETIVO = 72.0;       // Grados reales MPU6050 para completar curva
const unsigned long TIEMPO_COOLDOWN = 1200;// Inmunidad tras salir de curva (ms)

// CONSTANTES DE CONTROL
float Kp = 10.33;  // Ganancia Proporcional de centrado
float Kd = 14.0;   // Ganancia Derivativa de centrado
```

---

## Guía de Despliegue y Operación en Pista

En un entorno de competencia tan dinámico como la WRO, la rapidez de reacción en el área de pits (foso de trabajo) es tan determinante como las líneas de código cargadas en el auto. Un ajuste de último momento o el cambio de baterías no debe convertirse en un enredo de cables desordenados ni en fallas de compilación por falta de componentes en el programa.

Esta guía práctica de campo funciona para cualquier integrante del equipo o evaluador que necesite compilar, comprobar y poner en marcha el software de Meteoro (v2.0) de forma rápida, segura y repetible.

---

### 1. Requisitos Previos a la Compilación

Antes de conectar los cables USB a la computadora en pits, es indispensable verificar que el entorno de desarrollo cuente con las herramientas y librerías exactas empleadas durante nuestras pruebas de rendimiento.

**Entorno de Desarrollo (IDE)**
* **Arduino IDE 2.x (Entorno Principal):** Recomendamos utilizar la versión 2.0 o superior del entorno de Arduino por su monitor de puertos serie integrado, sugerencias de código en tiempo real e inspección instantánea de variables.
* **PlatformIO (VS Code):** Para quienes prefieren trabajar desde la consola de comandos o con un control de versiones avanzado mediante Git, el proyecto incluye la estructura base totalmente lista para PlatformIO.

**Librerías Necesarias y Gestor de Dependencias**
Asegúrate de instalar las siguientes librerías desde el Gestor de Librerías de Arduino IDE (`Ctrl + Shift + I` / `Cmd + Shift + I`) antes de compilar el código:
* **`Servo.h` (Librería Nativa):** Controla las señales de movimiento (a 50 Hz) para orientar el servomotor de dirección tipo Ackermann en la placa esclava.
* **`Wire.h` (Librería Nativa):** Facilita la comunicación en tiempo real a 100 kHz a través del canal I2C entre el microcontrolador Maestro (Dirección `0x00`) y el Esclavo (Dirección `0x08`).
* **`Pixy2.h` (Por Charmed Labs):** Necesaria para la configuración y transferencia de datos por bus SPI con la cámara PixyCam2, encargada del reconocimiento visual de señales en la pista.
* **`NewPing.h` (Por Tim Eckel):** Optimiza las lecturas de los tres sensores de distancia ultrasónicos RCWL-1601, eliminando las pausas de tiempo molestas causadas por la función tradicional `pulseIn()`.

---

### 2. Pasos de Carga de Firmware (Flujo en Boxes)

Debido a que el vehículo utiliza una arquitectura de dos microcontroladores interconectados, el programa debe grabarse de forma independiente en cada tarjeta Arduino Nano.

**Paso 1: Carga en el Arduino Nano Maestro**
1. Conecta la tarjeta Arduino Nano Maestro a la computadora mediante el cable Mini-USB principal.
2. Abre el entorno de desarrollo y abre el archivo del proyecto correspondiente: `src/current/first_challenge/master_nano.ino`
3. En el menú de herramientas del IDE, configura los siguientes parámetros:
   * **Placa:** Arduino Nano
   * **Procesador:** ATmega328P (Si la grabación presenta error, cambia a *ATmega328P (Old Bootloader)*)
   * **Puerto:** Selecciona el puerto serie asignado (por ejemplo, `COM3` en Windows o `/dev/ttyUSB0` en Linux/macOS).
4. Presiona el botón **Subir** (`Ctrl + U`).
5. Abre el Monitor Serie a 115200 baudios para confirmar que el sensor de orientación MPU6050 complete correctamente su calibración inicial en el eje Z.

**Paso 2: Carga en el Arduino Nano Esclavo**
1. Desconecta el cable Mini-USB de la tarjeta Maestra y conéctalo al Arduino Nano Esclavo (nodo de actuadores).
2. Abre el archivo de proyecto correspondiente: `src/current/first_challenge/slave_nano.ino`
3. Confirma que la placa seleccionada siga siendo Arduino Nano con el procesador correspondiente.
4. Presiona el botón **Subir** (`Ctrl + U`).
5. Tras finalizar la grabación del programa, vuelve a conectar los cables de energía interna del auto.

> **Nota de Seguridad:** Desconecta temporalmente la alimentación del paquete de baterías 3S de fuerza mientras realizas la carga del firmware por USB para evitar encendidos accidentales de los motores sobre la mesa de trabajo.

---

### 3. Protocolo Pre-Pista (Pit Stop Checklist)

Para asegurar la estabilidad operativa del prototipo en los intentos oficiales de la competencia, el equipo sigue rigurosamente el protocolo detallado en el archivo del repositorio: `pit_stop_checklist.md`.

Puntos clave a revisar en la mesa de pits antes de trasladar a Meteoro (v2.0) al área de salida:
* **Tensión de Batería 3S:** Medición con multímetro ≥ 11.8 V DC.
* **Ajuste Mecánico Servo:** Verificar dirección centrada a 90°.
* **Limpieza de Transductores:** Limpiar el polvo en los sensores de ultrasonido.
* **Test de Bus I2C:** Verificar que los cables SDA/SCL estén firmes.
* **Calibración IMU:** Colocar el auto plano al encender (esperar 5 segundos).

---

### 4. Rutina de Ejecución en Carrera

1. **Posicionamiento:** Colocar a Meteoro (v2.0) dentro del área de salida de 30 cm × 20 cm alineado paralelo a la pared exterior.
2. **Encendido Lógico y de Potencia:** Activar el interruptor general de alimentación 3S.
3. **Espera de Calibración:** Observar el LED de estado en la placa Maestra hasta que finalice el conteo de referencia inercial del giroscopio.
4. **Lanzamiento:** Presionar el botón de inicio. El auto ejecutará la función `arrancarSuave()` en el esclavo y comenzará el recorrido autónomo de la primera ronda.

---

### 5. Guía Rápida de Solución de Problemas (Troubleshooting)

| Síntoma en Pista | Causa Probable | Solución Inmediata en Pits |
| :--- | :--- | :--- |
| **El auto no gira en la primera esquina** | Fallo en la lectura del giroscopio MPU6050 o bus I2C colgado. | Verificar cables SDA/SCL y reiniciar el auto manteniéndolo inmóvil. |
| **Giro inestable / Serpenteo en rectas** | Ganancia Proporcional $K_p$ muy alta o interferencia en sensores. | Ajustar $K_p = 10.33$ a $8.5$ en la sección de parámetros de `master_nano.ino`. |
| **El servomotor tiembla o pierde fuerza** | Caída de voltaje en el Regulador Buck Canal 2. | Cargar o sustituir el paquete de baterías 3S. |
| **Error "Board not found" al cargar** | Puerto COM incorrecto o driver de chip USB (CH340) ausente. | Cambiar el procesador en el IDE a *ATmega328P (Old Bootloader)*. |

---

## Bitácora de Ingeniería y Desafíos Resueltos

Durante las etapas de prueba de nuestro vehículo Meteoro, el equipo detectó y resolvió diversos problemas técnicos que comprometían la estabilidad y la precisión del sistema autónomo. A continuación, presentamos el historial detallado de los retos enfrentados y las soluciones de ingeniería aplicadas.

---

### Desafíos Técnicos y Soluciones Implementadas

#### 1. Reinicio por Caídas Repentinas de Voltaje (Brownout)
* **Diagnóstico:** Al poner en marcha el motor eléctrico principal, se generaban picos de consumo que provocaban que el voltaje del circuito cayera por debajo de los 4.5 V. Esta baja repentina provocaba el reinicio inesperado del microcontrolador ATmega328P.
* **Solución:** Incorporamos un regulador de voltaje Buck DSN-MINI-360 dedicado de forma exclusiva a suministrar unos 5.0 V constantes y limpios a toda la parte lógica del circuito.

#### 2. Interferencias entre Sensores Ultrasónicos (Ecos Cruzados)
* **Diagnóstico:** Al emitir las señales del pin `TRIG` de forma simultánea en varios sensores RCWL-1601, las ondas de sonido rebotaban al mismo tiempo e interferían entre sí, haciendo que un sensor registrara por error el eco enviado por el sensor vecino.
* **Solución:** Establecimos un calendario de mediciones turno a turno, dejando una pausa de 15 ms entre el disparo de cada sensor. Además, filtramos la información tomando la mediana de grupos de 4 lecturas para desechar cualquier dato fuera de lo normal.

#### 3. Bloqueo del Ajuste de Dirección por Acumulación de Error (Windup)
* **Diagnóstico:** Durante giros prolongados, la suma acumulada de las pequeñas desviaciones fijaba la variable `suma_errores` en su valor máximo. Esto provocaba que las ruedas delanteras se quedaran atascadas en ángulo inclinado al intentar volver a la línea recta.
* **Solución:** Definimos un tope máximo (`LIMITE_INTEGRAL = 1000.0`) para evitar que el valor creciera de forma desmedida y agregamos una instrucción para reiniciar la variable `suma_errores` a cero justo al terminar cada curva.

#### 4. Pérdida de Sincronía en Mensajes Seriales (UART)
* **Diagnóstico:** En las primeras pruebas, los datos enviados entre el Arduino Maestro y el Esclavo perdían el orden de llegada de los bytes, lo que resultaba en movimientos descoordinados e inestables en los motores y la dirección.
* **Solución:** Estructuramos un formato claro de mensaje asignando un símbolo de inicio (`<`), la orden principal y un símbolo de cierre (`>`), verificando la validez de los datos mediante una suma de comprobación (*checksum*).

---

## Lista de Materiales

La elección de los componentes para el vehículo autónomo Meteoro (v2.0) se basó en garantizar estabilidad eléctrica, ligereza y una respuesta rápida durante el recorrido. En la siguiente tabla se presentan los elementos electrónicos y mecánicos utilizados en el prototipo, indicando la cantidad empleada, su función dentro del sistema distribuido y el enlace a su ficha técnica (*datasheet*) guardada en la carpeta local `docs/datasheets/`.

---

### Tabla General de Componentes y Fichas Técnicas

| Componente | Cantidad | Función Técnica en Meteoro (v2.0) | Ficha Técnica (Datasheet) |
| :--- | :---: | :--- | :---: |
| **Arduino Nano (ATmega328P)** | 2 | **Procesamiento Distribuido:**<br>• *Maestro:* Encargado de leer los sensores (RCWL-1601, MPU-6050, PixyCam2) y calcular las correcciones de ruta (control PD).<br>• *Esclavo:* Genera las señales eléctricas (PWM) para controlar el motor principal y el servomotor de dirección. | [Ficha Técnica](docs/datasheets/arduino_nano.pdf) |
| **Regulador Buck DSN-MINI-360** | 2 | **Regulación Aislada de Potencia:**<br>• *Canal 1:* Reduce el voltaje principal de 11.1 V - 12.6 V a unos 5.0 V estables para la lógica y los sensores.<br>• *Canal 2:* Suministra 5.0 V independientes al servomotor para evitar bajas repentinas de energía en los microcontroladores. | [Ficha Técnica](docs/datasheets/dsn_mini_360.pdf) |
| **Puente H L298N** | 1 | **Módulo de Potencia para Tracción:**<br>Amplifica la corriente y permite cambiar el sentido de giro del motor DC principal alimentado a 11.1 V. | [Ficha Técnica](docs/datasheets/l298n.pdf) |
| **Giroscopio / Acelerómetro MPU-6050** | 1 | **Navegación Inercial:**<br>Mide la velocidad de giro en el eje vertical ($\omega_z$) mediante el bus I2C para calcular por software giros precisos de 72° reales. | [Ficha Técnica](docs/datasheets/mpu6050.pdf) |
| **Sensor Ultrasónico RCWL-1601** | 3 | **Lectura del Entorno:**<br>Mide la distancia a las paredes (Izquierda, Frente y Derecha) enviando ráfagas de sonido a 5.0 V. | [Ficha Técnica](docs/datasheets/rcwl_1601.pdf) |
| **Servomotor AD002** | 1 | **Control de Dirección:**<br>Servomotor con engranajes metálicos configurado para ajustar las ruedas delanteras según el sistema de dirección Ackermann. | [Ficha Técnica](docs/datasheets/ad002_servo.pdf) |
| **Motor DC TT (Amarillo)** | 1 | **Tracción Trasera:**<br>Motor de corriente continua conectado a la transmisión con engranajes cónicos a 90° (relación de velocidad 1:1.5). | [Ficha Técnica](docs/datasheets/motor_tt.pdf) |
| **Baterías de Litio Li-ion 3S** | 3 | **Fuente de Energía Principal:**<br>Conjunto de 3 celdas de litio en serie (11.1 V nominales / 12.6 V con carga completa) para abastecer tanto a los motores como a los reguladores. | [Ficha Técnica](docs/datasheets/battery_3s.pdf) |

---

### Notas sobre Organización y Archivos Técnicos

Los archivos enlazados en la columna de **Ficha Técnica** forman parte de la documentación estática del proyecto y se encuentran almacenados dentro de la carpeta: `docs/datasheets/`.

---

## Módulos y Enlaces Directos

* **Firmware del Prototipo:** [`src/`](src/)
* **Tabla de Conexiones (Pinout):** [`schematics/`](schematics/)
* **Lista de Verificación de Foso:** [`docs/`](docs/)

---

## Registro Fotográfico y Multimedia

### Vistas del Vehículo (Obligatorias WRO)

Las 5 fotografías reglamentarias se encuentran disponibles en la carpeta `photos/vehicle/`:

* **Vista Frontal:** `photos/vehicle/front_view.jpg`
* **Vista Trasera:** `photos/vehicle/rear_view.jpg`
* **Vista Lateral Izquierda:** `photos/vehicle/left_view.jpg`
* **Vista Lateral Derecha:** `photos/vehicle/right_view.jpg`
* **Vista Superior:** `photos/vehicle/top_view.jpg`

---

### Demostración en Video (YouTube)

* **Open Challenge Video:** [Recorrido Open Challenge](https://www.youtube.com)
* **Obstacle Challenge Video:** [Recorrido Obstacle Challenge](https://www.youtube.com)

---

## Licencia

Este proyecto se distribuye bajo la licencia **MIT**. Consulta el archivo `LICENSE` para más detalles.

---

<div align="center">

© 2026 **The Pits JO** — Instituto Técnico Jesús Obrero.  
Todos los derechos reservados. Distribuido bajo la [Licencia MIT](LICENSE).

</div>
