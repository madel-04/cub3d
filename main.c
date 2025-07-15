#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>


int main(void)
{
int fd = open("./textures/greystone.xpm", O_RDONLY);
if (fd == -1)
{
    perror("Error al abrir el archivo");
    // Maneja el error o termina
}
else
{
    printf("Archivo abierto correctamente\n");
    close(fd); // Siempre cerrar si se abrió
}   
return (0);
}

