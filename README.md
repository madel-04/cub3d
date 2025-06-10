# Cub3D - Proyecto 42

### Ayuda teórica
- https://hackmd.io/@nszl/H1LXByIE2
- https://github.com/gleal42/cub3d?tab=readme-ov-file

## Objetivo
Crear un motor de raycasting tipo Wolfenstein 3D usando MiniLibX.

## Parsing
El archivo `.cub` contiene:
- Resolución (`R`)
- Texturas (`NO`, `SO`, `WE`, `EA`)
- Colores (`F`, `C`)
- Mapa (con caracteres `01NSEW2`)

### Estructura parseo

+---------------------+
|   Leer línea (GNL)  |
+---------------------+
		  |
		  v
+-----------------------------+
| ¿Es línea vacía o espacio? |
+-----------------------------+
		  |
	+-----+-----+
	|           |
   Sí          No
	|           |
	v           v
[Ignorar]   +-----------------------------+
			| ¿Contiene solo caracteres   |
			| válidos de mapa?           |
			| [0,1,2,N,S,E,W, espacio]    |
			+-----------------------------+
						|
				 +------+------+
				 |             |
				Sí            No
				 |             |
				 v             v
	  +-------------------+  +---------------------------+
	  | Agregar a lista   |  | ¿Es cabecera (R, NO, SO)? |
	  | de líneas de mapa |  +---------------------------+
	  +-------------------+             |
									   +---> Sí: Parsear y guardar
									   |
									   +---> No: Error o ignorar


+------------------------------+
|  ¿Hay exactamente 1 jugador? |
+------------------------------+
		   |
	 +-----+------+
	 |            |
	Sí           No
	 |            |
	 v            v
[Continuar]   [Error: múltiples jugadores]

+-----------------------------+
| ¿El mapa está cerrado?     |
| (Flood fill o bordes)      |
+-----------------------------+
		   |
	 +-----+------+
	 |            |
	Sí           No
	 |            |
	 v            v
[Correcto]    [Error: mapa abierto]
+-----------------------------+ */

#### Flujo de datos

- Check numero de argumentos
- Check archivo .cub
- Apertura de archivo
    - Poner que si se abre una carpeta error!!
- *Inicio de la estructura* de datos del archivo
- Check parseo configuración
    - Retirar espacios y tabulaciones del principio de las líneas
    - check si la línea está o no vacía (Tengo que ver si tiene \n?)
    - Check si la línea es de tipo mapa
        - Parseo del mapa
        - *Revisión del mapa válido!!!*
    - Parseo de otros elementos R, NO, F, C...
        - Parseo de resolución
        - Parseo de texturas
        - Parseo de color
    - QUÉ PASA SI RET ES 0?!?!
- Validar la configuración
- Cierre del fd
- Inicio del juego
- *Free de la estructura* de los datos del archivo


##### COmprobacione que me faltan
Dentro del mapa:
 - Número de jugadores ✓
 - Carácterers inválidos??
    - Mapa
    - Color ✓
    - texturas
 - Mapa sin cerrar ✓

 Fuera del mapa:
 - Comprobar que el archivo de texturas sea .xpm
 - Comprobar que se puede abrir el archivo de texturas (y de que exite)
 - Comprobar que la línea de colores solo tiene números y ","



 Falla si:
 - Tiene muchas líneas vacías al final
 - 



 Pruebas de leaks con valgrind:
 - valgrind --track-fds=yes ./cub3d test.cub 
 - valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --trace-children=yes ./cub3d test.cub