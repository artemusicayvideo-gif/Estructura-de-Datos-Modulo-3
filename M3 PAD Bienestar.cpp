#include <iostream>
// A pesar de que en esta ocasion solo manejaremos números incluí la librería 
// string por si después se requiere incluir el nombre del beneficiario.
#include <string> 

using namespace std;

// 1. DEFINICIÓN DEL NODO (El turno del beneficiario)
struct Turno {
    int numeroTurno;      // Dato: número de turno registrado
    Turno* siguiente;     // Apuntador al siguiente turno en la cola
};

// 2. FUNCIÓN PARA VALIDAR EL TURNO
bool validarTurno(int numero) {
    return numero > 0;
}

// 3. AGREGAR TURNO A LA COLA
void agregarTurno(Turno** frente, Turno** final, int numero) {
    if (!validarTurno(numero)) {
        cout << "-> ❌ Error: El numero de turno debe ser mayor que 0." << endl;
        return;
    }

    // Se pide memoria a la computadora para el nuevo turno
    Turno* nuevo = new Turno;
    nuevo->numeroTurno = numero;
    nuevo->siguiente = nullptr; // Como acaba de llegar, nadie va detras de el

    // AQUI APLIQUE LA INSTRUCCIÓN CLAVE QUE LA PROFESORA DIO EN CLASE
    // Si la cola está vacía, este nodo es el primero y también el último
    if (*frente == nullptr) {
        *frente = nuevo;
        *final = nuevo;
    } else {
        // Si ya hay gente, le decimos al que estaba al final que alguien llego detras
        (*final)->siguiente = nuevo;
        // Actualizamos nuestro apuntador para que el nuevo sea oficialmente el final
        *final = nuevo;
    }

    cout << " ✅ Turno " << numero << " agregado exitosamente a la cola." << endl;
}

// 4. ATENDER TURNO (Respeta el orden FIFO: Primero en llegar, primero en salir)
void atenderTurno(Turno** frente, Turno** final) {
    if (*frente == nullptr) {
        cout << " ⚠️ No hay turnos en espera. La cola esta vacia." << endl;
        return;
    }

    // Identificamos al primero de la fila
    Turno* auxiliar = *frente;
    cout << " 📢 Atendiendo al turno " << auxiliar->numeroTurno << "." << endl;

    // Recorremos la fila hacia adelante
    *frente = (*frente)->siguiente;

    // Si al recorrer la fila, resulta que ya no hay nadie, limpiamos el final
    if (*frente == nullptr) {
        *final = nullptr;
    }

    // Liberamos la memoria (Evita fugas de memoria)
    delete auxiliar;
}

// 5. MOSTRAR COLA DE TURNOS
void mostrarCola(Turno* frente) {
    Turno* actual = frente;

    if (actual == nullptr) {
        cout << " 📭 No hay turnos en espera. La cola esta vacia." << endl;
        return;
    }

    cout << "\n 🎫 Cola de turnos en espera ⏳:" << endl;
    while (actual != nullptr) {
        cout << "[Turno " << actual->numeroTurno << "] -> ";
        actual = actual->siguiente;
    }
    cout << " 🔚 FIN DE LA FILA 🛑 " << endl;
}

// 6. LIBERAR MEMORIA AL SALIR (Corte y queda: Apagamos el set limpiamente)
void liberarCola(Turno** frente, Turno** final) {
    Turno* actual = *frente;

    while (actual != nullptr) {
        Turno* auxiliar = actual;
        actual = actual->siguiente;
        delete auxiliar;
    }
    *frente = nullptr;
    *final = nullptr;
}

// 7. MENÚ PRINCIPAL
int main() {
    Turno* frente = nullptr; // Apuntador al inicio de la fila
    Turno* final = nullptr;  // Apuntador al final de la fila

    int opcion = 0;
    int numero = 0;

    do {
        cout << "\n§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§" << endl;
        cout << "\n" << endl;
        cout << "     SISTEMA PAD-BIENESTAR M3" << endl;
        cout << "\n" << endl;
        cout << "\n§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§§" << endl;
        cout << "\n" << endl;
        cout << "1. Agregar un turno" << endl;
        cout << "2. Atender un turno" << endl;
        cout << "3. Mostrar cola de turnos" << endl;
        cout << "4. Salir" << endl;
        cout << "\n" << endl;
        cout << "Seleccione una opcion: ";
        
        // Validando la entrada del menú (Reciclado del código del M2)
        if (!(cin >> opcion)) {
            cin.clear(); // Limpia la alerta de error
            cin.ignore(10000, '\n'); // Descarta la letra o símbolo escrito
            opcion = 0; // Fuerza a que vaya al mensaje de "Opcion invalida"
        }

        switch (opcion) {
            case 1:
                cout << "Ingrese el numero de turno: ";
                
                // Validando que el turno sea un número y no una letra (Reciclado del código del M2)
                if (!(cin >> numero)) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << " ❌ Error: Ingreso caracteres invalidos. Solo se permiten numeros." << endl;
                } else {
                    agregarTurno(&frente, &final, numero);
                }
                break;

            case 2:
                atenderTurno(&frente, &final);
                break;

            case 3:
                mostrarCola(frente);
                break;

            case 4:
                cout << "\n ¡Hasta pronto! ⚡️📁 Liberando recursos... Sistema cerrado. 👋" << endl;
                liberarCola(&frente, &final);
                break;

            default:
                cout << " ❌ Opcion invalida. Intente nuevamente con un numero del 1 al 4." << endl;
        }

    } while (opcion != 4);

    return 0;
}