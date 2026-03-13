# Compilar el servidor
g++ -std=c++11 -pthread nivel3_servidor_banco.cpp -o servidor_banco

# Compilar el cliente
g++ -std=c++11 nivel3_cliente.cpp -o cliente_banco

Nota: La bandera -pthread es necesaria para habilitar el soporte de hilos (POSIX threads) en el servidor.

# Ejecución
## 1. Iniciar el servidor (en una terminal):
./servidor_banco

## 2. Ejecutar uno o más clientes (en terminales separadas):
./cliente_banco

El cliente mostrará un prompt > donde puedes ingresar comandos.

Comandos disponibles:

* SALDO <id_cuenta> – Consulta el saldo de una cuenta.
Ejemplo: SALDO 1001
Respuesta esperada: SALDO 1001 5000

* TRANSFERIR <origen> <destino> <monto> – Transfiere dinero entre cuentas.
Ejemplo: TRANSFERIR 1001 1002 200
Respuesta esperada: TRANSFERENCIA_OK 1001 4800

* salir – Termina el cliente.

