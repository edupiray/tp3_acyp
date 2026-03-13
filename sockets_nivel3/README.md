# Compilar el servidor
g++ -std=c++11 -pthread nivel3_servidor_banco.cpp -o servidor_banco

# Compilar el cliente
g++ -std=c++11 nivel3_cliente.cpp -o cliente_banco

Nota: La bandera -pthread es necesaria para habilitar el soporte de hilos (POSIX threads) en el servidor.
