<p align="center">
  <img src="https://raw.githubusercontent.com/ayogun/42-project-badges/main/badges/cub3dm.png" alt="cub3D Badge"/>
</p>

<h1 align="center">🎮 cub3D</h1>

<p align="center">
  <strong>My first RayCaster with miniLibX</strong><br>
  Motor gráfico 3D inspirado en Wolfenstein 3D usando técnicas de raycasting
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c" />
  <img src="https://img.shields.io/badge/Graphics-miniLibX-red?style=for-the-badge" />
  <img src="https://img.shields.io/badge/School-42_Madrid-black?style=for-the-badge&logo=42" />
</p>

---

## 📋 Tabla de Contenidos

- [Sobre el Proyecto](#-sobre-el-proyecto)
- [Características](#-características)
- [Requisitos](#-requisitos)
- [Instalación](#-instalación)
- [Uso](#-uso)
- [Controles](#-controles)
- [Formato del Mapa](#-formato-del-mapa)
- [Raycasting](#-raycasting)
- [Características Técnicas](#-características-técnicas)
- [Ejemplos Visuales](#-ejemplos-visuales)
- [Recursos](#-recursos)

---

## 🎯 Sobre el Proyecto

**cub3D** es un proyecto del cursus de 42 que consiste en crear un motor gráfico 3D "realista" utilizando la técnica de **raycasting**, similar a los juegos clásicos como Wolfenstein 3D y Doom. El proyecto está desarrollado en C utilizando la biblioteca miniLibX para el renderizado gráfico.

El objetivo es comprender:
- **Raycasting**: Técnica de renderizado 3D pseudo-tridimensional
- **Gráficos por computadora**: Manipulación de píxeles y texturas
- **Geometría vectorial**: Cálculos matemáticos para rayos y colisiones
- **Optimización**: Renderizado eficiente en tiempo real
- **Parsing**: Lectura y validación de archivos de configuración

---

## ✨ Características

### Funcionalidades Core
- ✅ Renderizado 3D en tiempo real usando raycasting
- ✅ Navegación en primera persona
- ✅ Texturas diferentes para cada pared (Norte, Sur, Este, Oeste)
- ✅ Colores personalizables para suelo y techo
- ✅ Sistema de colisiones con paredes
- ✅ Rotación suave de cámara
- ✅ Movimiento fluido en todas direcciones

### Características Gráficas
- ✅ Texturas XPM para paredes
- ✅ Renderizado de perspectiva realista
- ✅ Gestión de ventana y eventos
- ✅ Cierre limpio del programa (ESC, click en X)
- ✅ Minimapa (bonus)
- ✅ Sprites/objetos (bonus)
- ✅ Puertas interactivas (bonus)
- ✅ Minimap en tiempo real (bonus)

### Validación de Mapas
- ✅ Parsing robusto de archivos `.cub`
- ✅ Validación de mapas cerrados
- ✅ Detección de errores en configuración
- ✅ Mensajes de error descriptivos

---

## 🛠️ Requisitos

- **Sistema Operativo**: Linux o macOS
- **Compilador**: `gcc` o `clang`
- **Make**: Para automatizar la compilación
- **Librerías**:
  - `miniLibX` (incluida en el proyecto)
  - `math` library (`-lm`)
  - `X11` (en Linux)

### Instalación de dependencias

**En Ubuntu/Debian:**
```bash
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

**En macOS:**
```bash
# Xcode Command Line Tools (si no están instaladas)
xcode-select --install
```

---

## 📦 Instalación

```bash
# Clonar el repositorio
git clone https://github.com/madel-04/cub3D.git
cd cub3D

# Compilar el proyecto
make

# Ejecutar el programa con un mapa
./cub3D maps/map.cub
```

### Comandos Make disponibles

```bash
make        # Compila el proyecto
make clean  # Elimina archivos objeto
make fclean # Elimina archivos objeto y el ejecutable
make re     # Recompila el proyecto desde cero
make bonus  # Compila la versión con bonus
```

---

## 🚀 Uso

### Ejecutar el juego

```bash
./cub3D <path_to_map.cub>
```

**Ejemplo:**
```bash
./cub3D maps/simple_map.cub
```

### Estructura de un archivo .cub

```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
WE ./textures/west_wall.xpm
EA ./textures/east_wall.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

---

## 🎮 Controles

### Movimiento
| Tecla | Acción |
|-------|--------|
| `W` | Mover adelante |
| `S` | Mover atrás |
| `A` | Mover izquierda (strafe) |
| `D` | Mover derecha (strafe) |

### Rotación de Cámara
| Tecla | Acción |
|-------|--------|
| `←` | Girar cámara a la izquierda |
| `→` | Girar cámara a la derecha |
| `Mouse` | Rotación con ratón (bonus) |

### Controles del Sistema
| Tecla | Acción |
|-------|--------|
| `ESC` | Salir del programa |
| `X` (botón ventana) | Cerrar ventana |

### Controles Bonus
| Tecla | Acción |
|-------|--------|
| `E` | Interactuar (abrir/cerrar puertas) |
| `M` | Toggle minimap |
| `Mouse` | Look around |

---

## 🗺️ Formato del Mapa

### Elementos de Configuración

```
NO <path_to_north_texture.xpm>    # Textura pared norte
SO <path_to_south_texture.xpm>    # Textura pared sur
WE <path_to_west_texture.xpm>     # Textura pared oeste
EA <path_to_east_texture.xpm>     # Textura pared este

F <R,G,B>                          # Color del suelo (floor)
C <R,G,B>                          # Color del techo (ceiling)
```

### Elementos del Mapa

| Carácter | Significado |
|----------|-------------|
| `0` | Espacio vacío (caminable) |
| `1` | Pared |
| `N` | Posición inicial (mirando Norte) |
| `S` | Posición inicial (mirando Sur) |
| `E` | Posición inicial (mirando Este) |
| `W` | Posición inicial (mirando Oeste) |
| ` ` (espacio) | Área fuera del mapa |

### Reglas del Mapa

1. ✅ El mapa debe estar rodeado completamente por paredes (`1`)
2. ✅ Solo puede haber una posición inicial (`N`, `S`, `E`, o `W`)
3. ✅ Solo se permiten caracteres válidos (`0`, `1`, `N`, `S`, `E`, `W`, espacio)
4. ✅ El mapa debe ser el último elemento del archivo `.cub`
5. ✅ Líneas vacías están permitidas entre elementos de configuración

### Ejemplo de Mapa Válido

```
NO ./textures/brick_wall.xpm
SO ./textures/stone_wall.xpm
WE ./textures/wood_wall.xpm
EA ./textures/metal_wall.xpm

F 50,50,50
C 135,206,235

111111
100101
101001
1100N1
111111
```

---

## 🔍 Raycasting

### ¿Qué es el Raycasting?

El **raycasting** es una técnica de renderizado que simula un entorno 3D en una pantalla 2D. Para cada columna vertical de píxeles en la pantalla, se lanza un "rayo" desde la posición del jugador hasta que choca con una pared. La distancia determina la altura de la pared en pantalla.

### Algoritmo Básico

```
Para cada columna X de la pantalla:
  1. Calcular dirección del rayo
  2. Incrementar el rayo paso a paso
  3. Verificar colisión con pared
  4. Calcular distancia perpendicular
  5. Calcular altura de la línea en pantalla
  6. Obtener textura correspondiente
  7. Dibujar línea vertical con textura
```

### Visualización del Proceso

```
        |
        |         Plano
    ----+----   de Visión
        |
        |
        *  ← Jugador (posición y dirección)
       /|\
      / | \
     /  |  \
    /   |   \
   R1   R2  R3  ← Rayos lanzados
   
   R1, R2, R3: Cada rayo representa una columna de píxeles
```

### Corrección de Perspectiva

Para evitar el "efecto ojo de pez", se usa la **distancia perpendicular** en lugar de la distancia euclidiana:

```c
perpendicular_dist = euclidean_dist * cos(angle_difference);
```

---

## 🔬 Características Técnicas

### Estructura del Programa

```c
typedef struct s_data
{
    void        *mlx;              // Puntero a miniLibX
    void        *win;              // Puntero a la ventana
    void        *img;              // Buffer de imagen
    char        *addr;             // Dirección de píxeles
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}   t_data;

typedef struct s_player
{
    double      pos_x;             // Posición X
    double      pos_y;             // Posición Y
    double      dir_x;             // Dirección X
    double      dir_y;             // Dirección Y
    double      plane_x;           // Plano de cámara X
    double      plane_y;           // Plano de cámara Y
}   t_player;

typedef struct s_ray
{
    double      camera_x;          // Coordenada X en cámara
    double      dir_x;             // Dirección del rayo X
    double      dir_y;             // Dirección del rayo Y
    int         map_x;             // Posición en mapa X
    int         map_y;             // Posición en mapa Y
    double      side_dist_x;       // Distancia a lado X
    double      side_dist_y;       // Distancia a lado Y
    double      delta_dist_x;      // Distancia entre lados X
    double      delta_dist_y;      // Distancia entre lados Y
    double      perp_wall_dist;    // Distancia perpendicular
    int         step_x;            // Dirección de paso X
    int         step_y;            // Dirección de paso Y
    int         hit;               // ¿Golpeó pared?
    int         side;              // ¿Lado NS o EW?
}   t_ray;
```

### Algoritmo DDA (Digital Differential Analysis)

El DDA se usa para rastrear el rayo a través del grid del mapa:

```c
while (hit == 0)
{
    if (side_dist_x < side_dist_y)
    {
        side_dist_x += delta_dist_x;
        map_x += step_x;
        side = 0;  // Lado vertical (NS)
    }
    else
    {
        side_dist_y += delta_dist_y;
        map_y += step_y;
        side = 1;  // Lado horizontal (EW)
    }
    if (map[map_x][map_y] == '1')
        hit = 1;
}
```

### Cálculo de Textura

```c
// Coordenada X en la textura
int tex_x = (int)(wall_x * tex_width);

// Para cada píxel Y de la línea vertical
for (int y = draw_start; y < draw_end; y++)
{
    // Coordenada Y en la textura
    int tex_y = ((y * 2 - screen_height + line_height) 
                 * tex_height) / (line_height * 2);
    
    // Obtener color del píxel de la textura
    int color = texture[tex_x][tex_y];
    
    // Dibujar píxel en pantalla
    put_pixel(x, y, color);
}
```

### Optimizaciones

- **Double Buffering**: Renderizado en buffer antes de mostrar
- **Cálculos Precalculados**: Tablas de lookup para valores repetitivos
- **Integer Math**: Uso de enteros donde sea posible
- **Dirty Rectangles**: Solo redibujar áreas que cambiaron (bonus)

---

## 📁 Estructura del Proyecto (visión aproximada)

```
cub3D/
├── Makefile
├── includes/
│   └── cub3d.h              # Cabeceras y estructuras
├── srcs/
│   ├── main.c               # Punto de entrada
│   ├── parsing/             # Parsing del archivo .cub
│   │   ├── parse_config.c
│   │   ├── parse_map.c
│   │   ├── validate_map.c
│   │   └── check_walls.c
│   ├── raycasting/          # Motor de raycasting
│   │   ├── raycasting.c
│   │   ├── dda.c
│   │   ├── draw_walls.c
│   │   └── textures.c
│   ├── movement/            # Sistema de movimiento
│   │   ├── player_move.c
│   │   ├── player_rotate.c
│   │   └── collision.c
│   ├── graphics/            # Gestión gráfica
│   │   ├── init_mlx.c
│   │   ├── draw.c
│   │   ├── colors.c
│   │   └── pixel_operations.c
│   └── utils/               # Funciones auxiliares
│       ├── errors.c
│       ├── free.c
│       └── math_utils.c
├── textures/                # Texturas XPM ejemplo
│   ├── north_wall.xpm
│   ├── south_wall.xpm
│   ├── east_wall.xpm
│   └── west_wall.xpm
├── maps/                    # Mapas de ejemplo
│   ├── simple.cub
│   ├── complex.cub
│   └── test.cub
└── libft/                   # Librería personalizada
```

---

## 🎨 Ejemplos Visuales

### Perspectiva del Jugador

```
Vista desde arriba (mapa):    Vista en primera persona:
                              
     1 1 1 1 1                    _______________
     1 0 0 0 1                   |###|   |   |###|
     1 0 ^ 0 1      --->         |###|   |   |###|
     1 0 0 0 1                   |###|___|___|###|
     1 1 1 1 1                    ‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
     
     ^ = jugador               Renderizado 3D con texturas
```

### Efecto de Distancia

```
Cerca:                        Lejos:
 _____________                ___
|#############|              |###|
|#############|              |###|
|#############|               ‾‾‾
|#############|              
|#############|              Altura menor = más lejos
 ‾‾‾‾‾‾‾‾‾‾‾‾‾
```

---

## 📚 Recursos

### Tutoriales de Raycasting
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - ⭐ Tutorial fundamental
- [Permadi Raycasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [Ray-Casting Tutorial For Game Development](https://www.youtube.com/watch?v=gYRrGTC7GtA)

### miniLibX
- [miniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [miniLibX Tutorial](https://github.com/qst0/ft_libgfx)

### Matemáticas y Algoritmos
- [Digital Differential Analyzer (DDA)](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))
- [Bresenham's Line Algorithm](https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm)
- [Vector Math for 3D Graphics](http://chortle.ccsu.edu/VectorLessons/vectorIndex.html)

### Wolfenstein 3D
- [Wolfenstein 3D Game Engine Black Book](https://fabiensanglard.net/wolf3d/)
- [How Wolfenstein 3D Works](https://www.youtube.com/watch?v=eOCQfxRQ2pY)

### Funciones Matemáticas
```c
#include <math.h>

cos()    // Coseno
sin()    // Seno
tan()    // Tangente
sqrt()   // Raíz cuadrada
fabs()   // Valor absoluto (float)
atan2()  // Arcotangente de dos argumentos
```

---

## 🎓 Aprendizajes Clave

Este proyecto me permitió desarrollar conocimientos profundos en:

- **Gráficos 3D**: Comprensión del raycasting y renderizado en tiempo real
- **Geometría Vectorial**: Aplicación práctica de vectores y trigonometría
- **Optimización**: Técnicas para renderizado eficiente (60 FPS)
- **Parsing Robusto**: Validación exhaustiva de archivos de configuración
- **Gestión de Eventos**: Input handling y game loop
- **Debugging Visual**: Técnicas para depurar problemas gráficos
- **miniLibX**: Dominio de la biblioteca gráfica de 42

---

## 🏆 Bonus Implementados

### Minimapa
- ✅ Mapa 2D en la pantalla al pulsar Espacio
- ✅ Actualización en tiempo real
- ✅ Indicador de posición y dirección del jugador

### Controles Avanzados
- ✅ Colisión mejorada (sliding)
- ✅ Velocidad de movimiento ajustable


---

## 👥 Autores

- **Mayte** - [@madel-04](https://github.com/madel-04)
- **Miguel** - [@MiMendiola](https://github.com/MiMendiola)

---

## 📄 Licencia

Este proyecto es parte del cursus de 42 Madrid y está sujeto a sus normas académicas.

---

<p align="center">
  <sub>Desarrollado con 💻 en 42 Madrid</sub>
</p>
