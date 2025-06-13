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


## Raycasting
1. Preparar el entorno de renderizado:
 - Función de render_frame y dentro de esa función un draw_background o algo asi

2. Implementación del algoritmo de raycasting
 - una función tipo raycasting_draw() que se llame desde render_frame
 - dentro de la función 



## Corregir
- Colores DONE
- Colores repetidos DONE
- Leaks
- COsas al final del mapa DONE


____________
#### Errores Valgrind
==556007== 431 bytes in 17 blocks are still reachable in loss record 49 of 58
==556007==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==556007==    by 0x403B62: ft_tabtospaces (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x402AB8: ft_read_map_lines (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x402A33: ft_parse_map (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4032C1: ft_handle_config_line (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403145: ft_parse_config (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4026F8: main (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007== 

==556007== 264 bytes in 1 blocks are still reachable in loss record 47 of 58
==556007==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==556007==    by 0x403943: ft_realloc_strarray (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x402BD0: ft_add_map_line (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x402B48: ft_read_map_lines (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x402A33: ft_parse_map (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4032C1: ft_handle_config_line (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403145: ft_parse_config (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4026F8: main (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)

==556007== 35 bytes in 1 blocks are still reachable in loss record 21 of 58
==556007==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==556007==    by 0x407333: ft_strdup (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4029E7: ft_parse_map (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4032C1: ft_handle_config_line (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403145: ft_parse_config (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4026F8: main (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)

==556007== 28 bytes in 1 blocks are still reachable in loss record 14 of 58
==556007==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==556007==    by 0x40366C: ft_strdup_textures (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x402CCC: ft_parse_texture (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403434: ft_parse_element (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403316: ft_handle_config_line (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403145: ft_parse_config (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4026F8: main (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)

==556007== 26 bytes in 1 blocks are still reachable in loss record 13 of 58
==556007==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==556007==    by 0x40366C: ft_strdup_textures (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x402CCC: ft_parse_texture (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4033F5: ft_parse_element (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403316: ft_handle_config_line (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403145: ft_parse_config (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4026F8: main (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)

==556007== 25 bytes in 1 blocks are still reachable in loss record 12 of 58
==556007==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==556007==    by 0x40366C: ft_strdup_textures (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x402CCC: ft_parse_texture (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403473: ft_parse_element (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403316: ft_handle_config_line (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403145: ft_parse_config (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4026F8: main (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)

==556007== 21 bytes in 1 blocks are still reachable in loss record 6 of 58
==556007==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==556007==    by 0x40366C: ft_strdup_textures (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x402CCC: ft_parse_texture (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4034B2: ft_parse_element (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403316: ft_handle_config_line (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x403145: ft_parse_config (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007==    by 0x4026F8: main (in /home/madel-va/Documents/proyectos/cub3d/cube_git/cub3d)
==556007== 