#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int PUERTO = 8080;

int main() {
    int servidor_fd, nuevo_socket;
    struct sockaddr_in direccion;
    int opt = 1;
    int addrlen = sizeof(direccion);
    char buffer[1024] = {0};

    // 1. Crear el socket del servidor
    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(servidor_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PUERTO);

    // 2. Enlazar el socket al puerto
    bind(servidor_fd, (struct sockaddr*)&direccion, sizeof(direccion));
    // 3. Escuchar por conexiones entrantes
    listen(servidor_fd, 3);

    std::cout << "Servidor de eco escuchando en el puerto " << PUERTO << std::endl;

    while (true) {
        // 4. Aceptar una nueva conexión
        nuevo_socket = accept(servidor_fd, (struct sockaddr*)&direccion, (socklen_t*)&addrlen);
        // 5. Leer el mensaje del cliente
        read(nuevo_socket, buffer, 1024);
        std::cout << "Mensaje recibido: " << buffer << std::endl;
        // 6. Enviar el mensaje de vuelta (eco)
        send(nuevo_socket, buffer, strlen(buffer), 0);
        std::cout << "Eco enviado." << std::endl;
        close(nuevo_socket);
    }
    return 0;
}
