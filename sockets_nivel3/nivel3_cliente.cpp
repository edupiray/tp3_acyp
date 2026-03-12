#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PUERTO = 9090;

std::string enviar_comando(const std::string& comando) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PUERTO);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        return "ERROR de conexión";
    }

    send(sock, comando.c_str(), comando.length(), 0);
    char buffer[1024] = {0};
    read(sock, buffer, 1024);
    close(sock);
    return std::string(buffer);
}

int main() {
    std::string comando;
    std::cout << "Cliente Bancario Distribuido. Comandos: SALDO <id>, TRANSFERIR <ori> <dest> <monto>" << std::endl;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, comando);
        if (comando == "salir") break;
        std::string respuesta = enviar_comando(comando + "\n");
        std::cout << "Respuesta: " << respuesta;
    }
    return 0;
}
