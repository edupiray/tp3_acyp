#include <iostream>
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <sstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int PUERTO = 9090;
std::map<int, double> cuentas; // Mapa de ID de cuenta a saldo
std::mutex cuentas_mtx;

// Inicializar algunas cuentas de ejemplo
void inicializar_cuentas() {
    cuentas[1001] = 5000.0;
    cuentas[1002] = 3000.0;
    cuentas[1003] = 10000.0;
}

std::string procesar_comando(const std::string& comando) {
    std::istringstream iss(comando);
    std::string accion;
    iss >> accion;

    if (accion == "SALDO") {
        int id;
        iss >> id;
        std::lock_guard<std::mutex> lock(cuentas_mtx);
        auto it = cuentas.find(id);
        if (it != cuentas.end()) {
            return "SALDO " + std::to_string(id) + " " + std::to_string(it->second) + "\n";
        } else {
            return "ERROR Cuenta no encontrada\n";
        }
    }
    else if (accion == "TRANSFERIR") {
        int origen, destino;
        double monto;
        iss >> origen >> destino >> monto;

        std::lock_guard<std::mutex> lock(cuentas_mtx);
        auto it_origen = cuentas.find(origen);
        auto it_destino = cuentas.find(destino);

        if (it_origen == cuentas.end() || it_destino == cuentas.end()) {
            return "ERROR Cuenta origen o destino no existe\n";
        }
        if (it_origen->second < monto) {
            return "ERROR Saldo insuficiente\n";
        }

        it_origen->second -= monto;
        it_destino->second += monto;
        return "TRANSFERENCIA_OK " + std::to_string(origen) + " " + std::to_string(it_origen->second) + "\n";
    }
    else {
        return "ERROR Comando no reconocido\n";
    }
}

void manejar_cliente(int socket_cliente) {
    char buffer[1024] = {0};
    read(socket_cliente, buffer, 1024);
    std::string comando(buffer);
    std::string respuesta = procesar_comando(comando);
    send(socket_cliente, respuesta.c_str(), respuesta.length(), 0);
    close(socket_cliente);
}

int main() {
    inicializar_cuentas();

    int servidor_fd, nuevo_socket;
    struct sockaddr_in direccion;
    int opt = 1;
    int addrlen = sizeof(direccion);

    servidor_fd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(servidor_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt));

    direccion.sin_family = AF_INET;
    direccion.sin_addr.s_addr = INADDR_ANY;
    direccion.sin_port = htons(PUERTO);

    bind(servidor_fd, (struct sockaddr*)&direccion, sizeof(direccion));
    listen(servidor_fd, 3);
    std::cout << "Banco Central Distribuido escuchando en puerto " << PUERTO << std::endl;

    while (true) {
        nuevo_socket = accept(servidor_fd, (struct sockaddr*)&direccion, (socklen_t*)&addrlen);
        std::thread(manejar_cliente, nuevo_socket).detach(); // Lanzar hilo y desvincularlo
    }
    return 0;
}
