#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mutex>

const int PUERTO = 8080;
std::mutex mtx;
int contador_peticiones = 0;

void manejar_cliente(int socket_cliente) {
    char buffer[1024] = {0};
    // Leer el nombre del cliente
    read(socket_cliente, buffer, 1024);

    {
        // Sección crítica: actualizar el contador compartido
        std::lock_guard<std::mutex> lock(mtx);
        contador_peticiones++;
        std::cout << "Cliente " << buffer << " atendido. Total peticiones: " << contador_peticiones << std::endl;
    }

    const char* respuesta = "Hola, conexión exitosa!";
    send(socket_cliente, respuesta, strlen(respuesta), 0);
    close(socket_cliente);
}

int main() {
    int servidor_fd, nuevo_socket;
    struct sockaddr_in direccion;
    int opt = 1;
    int addrlen = sizeof(direccion);
    std::vector<std::thread> hilos;

    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(servidor_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PUERTO);

    bind(servidor_fd, (struct sockaddr*)&direccion, sizeof(direccion));
    listen(servidor_fd, 3);
    std::cout << "Servidor concurrente escuchando en puerto " << PUERTO << std::endl;

    while (true) {
        nuevo_socket = accept(servidor_fd, (struct sockaddr*)&direccion, (socklen_t*)&addrlen);
        // Lanzar un nuevo hilo para cada cliente
        hilos.emplace_back(manejar_cliente, nuevo_socket);
    }
    return 0;
}
