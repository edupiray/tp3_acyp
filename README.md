1. Clonar/Fork del Repositorio.

2. Ejecutar en Codespaces: El mismo devcontainer.json que usaste para MPI (con build-essential) funcionará perfectamente, ya que solo necesita g++ y la biblioteca pthread (que viene incluida).

3. Nivel 1: Compilar y ejecutar el servidor de eco y el cliente. Observar que el servidor se bloquea después de atender a un cliente.

4. Nivel 2: Compilar y ejecutar el servidor concurrente. Abrir múltiples terminales (o usar tmux) para ejecutar varios clientes a la vez y ver cómo se atienden concurrentemente.

5. Nivel 3: Compilar y ejecutar el servidor del banco. Desde diferentes clientes, probar a consultar saldos y realizar transferencias concurrentes, verificando la consistencia de los datos (ej. que no se pueda generar dinero de la nada).
