#include <iostream>
#include <cstring>
#include <thread>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PUERTO = 8080;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Uso: " << argv[0] << " <NombreCliente>" << std::endl;
        return 1;
    }
    const char* nombre_cliente = argv[1];

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    sock = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PUERTO);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    send(sock, nombre_cliente, strlen(nombre_cliente), 0);
    read(sock, buffer, 1024);
    std::cout << "Servidor dice: " << buffer << std::endl;

    close(sock);
    return 0;
}
