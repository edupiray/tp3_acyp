# Compilar
g++ nivel2_servidor_concurrente.cpp -o servidor_conc -pthread

g++ nivel2_cliente.cpp -o cliente

# Ejecutar
## Terminal 1
./servidor_conc
## Terminales 2, 3, 4...
./cliente ClienteA

./cliente ClienteB
