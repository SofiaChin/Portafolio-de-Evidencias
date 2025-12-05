			𝚄𝚗𝚒𝚟𝚎𝚛𝚜𝚒𝚍𝚊𝚍 𝙰𝚞𝚝𝚘𝚗𝚘𝚖𝚊 𝚍𝚎 𝚈𝚞𝚌𝚊𝚝𝚊𝚗
 		    		  𝙵𝚊𝚌𝚞𝚕𝚝𝚊𝚍 𝚍𝚎 𝙼𝚊𝚝𝚎𝚖𝚊𝚝𝚒𝚌𝚊𝚜
		    		𝙸𝚗𝚐𝚎𝚗𝚒𝚎𝚛𝚒𝚊 𝚎𝚗 𝙲𝚘𝚖𝚙𝚞𝚝𝚊𝚌𝚒𝚘𝚗
					 𝙴𝚜𝚝𝚛𝚞𝚌𝚝𝚞𝚛𝚊 𝚍𝚎 𝙳𝚊𝚝𝚘𝚜

					 𝘊𝘩𝘪𝘯 𝘊𝘩𝘢𝘯 𝘈𝘯𝘯𝘢 𝘚𝘰𝘧𝘪𝘢
			    			   ╾╌╼
			       𝘗𝘢𝘳𝘦𝘥𝘦𝘴 𝘝𝘢𝘻𝘲𝘶𝘦𝘻 𝘐𝘢𝘯

════════════════════════════════════════════════════════╝
ADA 02: Simulador de Atención al Cliente en un Banco (Queues)
═══════════════════════════════════════════════════════╝
Este proyecto implementa un simulador de atención en un banco con 3
cajas de atención utilizando colas (Queue).

El programa permite:
- Generar clientes con un número aleatorio de transacciones.
- Asignar clientes de manera aleatoria a una de las 3 colas.
- Atender a los clientes mostrando el flujo de llegada y salida.
- Calcular estadísticas como:
> Tiempo promedio de espera en cada cola.
> Número de clientes atendidos en cada cola.


═══════════════════════════════════════════════════════
  ◈ COMPILACIÓN
═══════════════════════════════════════════════════════

Para compilar el programa en Windows (MSYS2 / MinGW / gcc):
    cd "C:\Users\TuUsuario\Documentos\ADA"
    gcc -Wall -Wextra -g3 ADA02.c -o banco_sim

-----------------------------------------------

En Linux/MacOS:
    cd ~/Documents/ADA
    gcc -Wall -Wextra ADA02.c -o banco_sim

Esto generará un ejecutable llamado banco_sim.

════════════════════════════════════════════════════════
 ➣ EJECUCIÓN
════════════════════════════════════════════════════════

En Linux/Mac:

    ./banco_sim

-----------------------------------------------

En Windows (MSYS2/MinGW instalado):

	banco_sim.exe
