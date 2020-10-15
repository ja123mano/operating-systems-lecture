#Link de la gráfica
#https://drive.google.com/file/d/1_bgluZkYZWpnagx0BlLBls3vyzsHpBv3/view?usp=sharing

import sys

def main():

    t_cuantico = int(input("Tiempo cuántico (entero >= 1) = "))
    if t_cuantico < 1:
        print("Por favor da un tiempo cuántico entero >= 1")
        sys.exit(-1)
    t_cambio_contexto = 2
    t_ejecucion = 0
    tprom_turnaround = 0.0
    cambios_de_contexto = 0

   # procesos = [] #Aquí se guardan los procesos que ingrese el usuario, o se pueden usar los ya predefinidos abajo comentando esta lista y descomentando una de abajo
    #procesos = [1,2,3,4,5,5,4,3,2,1]
    #procesos = [10,9,3,6,1,9,12,4,7]
    procesos = [20, 30, 4, 12, 27, 9, 15]
    pos_proceso = 0
    pos_temp = 999999
    xp = 0

    print("Por favor escriba el tiempo de ejecución de cada proceso para el número de procesos que quiera, cuando esté satisfecho, escriba 0 o un número negativo\n")

    while(True):
        print("Proceso número ", xp, "=", end=" ")
        x = int(input())
        xp += 1
        if x > 0:
            procesos.append(x)
        else:
            num_procesos = len(procesos)
            break


    print("\nEstos son los tiempos de ejecución de cada proceso, y la posición indica el # del proceso, empezando por el 0 \n", procesos, "\n\n")

    for p in procesos:
        if p <= t_cuantico:
            print("Proceso ", pos_proceso, " ejecutado")
            t_ejecucion += p
            print("Tiempo de ejecución ", str(t_ejecucion))
        else:
            print("Proceso ", pos_proceso, " interrumpido")
            if pos_proceso <= pos_temp:
                pos_temp = pos_proceso
            t_restante = p - t_cuantico
            cambios_de_contexto += 1
            print("Tiempo de ejecución del proceso: ", str(t_cuantico))
            t_ejecucion = t_ejecucion + t_cuantico + t_cambio_contexto
            print("Tiempo de ejecución ", str(t_ejecucion))
            procesos.append(t_restante)

        pos_proceso += 1
        if pos_proceso > num_procesos:
            pos_proceso = pos_temp
        procesos[procesos.index(p)] = 0

        print(procesos, "\n")

    tprom_turnaround = float(t_ejecucion)/float(num_procesos)
    print("Número de procesos ejecutados: ", str(num_procesos))
    print("Número de cambios de contexto: ", str(cambios_de_contexto))
    print("Tiempo promedio de turnaround: ", str(tprom_turnaround))

if __name__ == "__main__":
    main()
