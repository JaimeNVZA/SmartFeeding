import serial
import time

def leer_pesos_y_calcular_promedio(puerto, baud_rate, tiempo_lectura):
    try:
        # Abrir conexión serie
        arduino = serial.Serial(puerto, baud_rate, timeout=1)
        print("Conexión establecida con el Arduino")
        time.sleep(2)  # Esperar a que se estabilice la conexión
        
        pesos = []  # Lista para almacenar los pesos
        inicio = time.time()
        
        while time.time() - inicio < tiempo_lectura:
            if arduino.in_waiting > 0:
                linea = arduino.readline().decode('utf-8').strip()
                try:
                    # Intentar convertir la línea a un valor numérico
                    peso = float(linea.replace("Peso: ", "").replace("g", "").strip())
                    pesos.append(peso)
                    print(f"Peso recibido: {peso} g")
                except ValueError:
                    # Ignorar líneas que no puedan convertirse en número
                    print(f"Línea ignorada: {linea}")
        
        if pesos:
            promedio = sum(pesos) / len(pesos)
            print(f"\nPesos recibidos: {pesos}")
            print(f"Promedio: {promedio:.2f} g")
        else:
            print("No se recibieron pesos válidos.")
        
    except serial.SerialException as e:
        print(f"Error al conectar con el puerto serie: {e}")
    finally:
        if 'arduino' in locals():
            arduino.close()
            print("Conexión cerrada.")

# Configuración
puerto = "COM3"  # Cambia esto según el puerto serie que uses
baud_rate = 9600
tiempo_lectura = 10  # Segundos que durará la lectura

# Ejecutar la función
leer_pesos_y_calcular_promedio(puerto, baud_rate, tiempo_lectura)
