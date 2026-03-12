#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PUERTO = 8080;

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // 1. Crear el socket del cliente
    sock = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PUERTO);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    // 2. Conectarse al servidor
    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // 3. Enviar un mensaje
    const char* mensaje = "Hola desde el cliente!";
    send(sock, mensaje, strlen(mensaje), 0);
    std::cout << "Mensaje enviado." << std::endl;

    // 4. Recibir la respuesta (eco)
    read(sock, buffer, 1024);
    std::cout << "Eco recibido: " << buffer << std::endl;

    close(sock);
    return 0;
}
