#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstring>

using namespace std;

/* --- CONFIGURACION Y ESTRUCTURAS --- */
const int MAX_C = 10;
const int MAX_N = 10;
const string NOMBRE_ARC = "cursos.txt";

struct Curso {
    string nombre;
    float notas[MAX_N];
    int numNotas;
};

/* --- PROTOTIPOS --- */
void limpiar();
int validarEntero(int min, int max);
float validarNota(float min, float max);
float sumarRecursivo(float notas[], int n); 
void registrar(Curso c[], int &total); 
void mostrar(Curso c[], int total);    
void buscar(Curso c[], int total);     
void guardar(Curso c[], int total);    
int cargar(Curso c[]);

/* --- BLOQUE PRINCIPAL --- */
int main() {
    Curso cursos[MAX_C];
    int totalCursos = 0;
    int opcion;

    // Carga automatica al iniciar
    totalCursos = cargar(cursos);

    do {
        cout << "\n--- MENU DE GESTION ACADEMICA (C++) ---";
        cout << "\n1. Registrar Curso";
        cout << "\n2. Mostrar Promedios";
        cout << "\n3. Buscar Curso";
        cout << "\n4. Guardar en Archivo";
        cout << "\n5. Salir";
        cout << "\nSeleccione: ";
        
        opcion = validarEntero(1, 5);

        switch(opcion) {
            case 1: registrar(cursos, totalCursos); break;
            case 2: mostrar(cursos, totalCursos); break;
            case 3: buscar(cursos, totalCursos); break;
            case 4: guardar(cursos, totalCursos); break;
            case 5: cout << "\nCerrando programa..." << endl; break;
        }
    } while(opcion != 5);

    return 0;
}

/* --- SECCION 1: REGISTRAR CURSOS Y NOTAS --- */
void registrar(Curso c[], int &total) {
    if (total >= MAX_C) {
        cout << "\nError: Cupo de cursos lleno." << endl;
        return;
    }

    cout << "\nNombre del curso: ";
    getline(cin, c[total].nombre);

    cout << "¿Cuantas notas tiene? (1-" << MAX_N << "): ";
    c[total].numNotas = validarEntero(1, MAX_N);

    for (int i = 0; i < c[total].numNotas; i++) {
        cout << "  Ingrese nota " << (i + 1) << " (0-20): ";
        c[total].notas[i] = validarNota(0.0, 20.0);
    }

    total++;
    cout << "Curso registrado exitosamente." << endl;
}

/* --- SECCION 2: MOSTRAR PROMEDIOS --- */
void mostrar(Curso c[], int total) {
    if (total == 0) {
        cout << "\nNo hay cursos para mostrar." << endl;
        return;
    }

    cout << "\n" << left << setw(15) << "CURSO" << setw(20) << "NOTAS" << "PROMEDIO";
    cout << "\n--------------------------------------------------";
    for (int i = 0; i < total; i++) {
        float suma = sumarRecursivo(c[i].notas, c[i].numNotas);
        float prom = suma / c[i].numNotas;

        cout << "\n" << left << setw(15) << c[i].nombre << " ";
        for(int j = 0; j < c[i].numNotas; j++) {
            cout << fixed << setprecision(1) << c[i].notas[j] << " ";
        }
        cout << " -> " << setprecision(2) << prom;
    }
    cout << "\n--------------------------------------------------" << endl;
}

/* --- SECCION 3: BUSCAR CURSO --- */
void buscar(Curso c[], int total) {
    string nombreBusca;
    bool hallado = false;

    cout << "\nNombre del curso a buscar: ";
    getline(cin, nombreBusca);

    for (int i = 0; i < total; i++) {
        if (c[i].nombre == nombreBusca) {
            float suma = sumarRecursivo(c[i].notas, c[i].numNotas);
            cout << "\n--- Curso Encontrado ---";
            cout << "\nNombre: " << c[i].nombre;
            cout << "\nPromedio: " << fixed << setprecision(2) << (suma / c[i].numNotas) << endl;
            hallado = true;
            break;
        }
    }
    if (!hallado) cout << "El curso '" << nombreBusca << "' no existe." << endl;
}

/* --- SECCION 4: GUARDAR EN ARCHIVO --- */
void guardar(Curso c[], int total) {
    ofstream archivo(NOMBRE_ARC);

    if (!archivo.is_open()) {
        cout << "\nError critico: No se pudo crear el archivo." << endl;
        return;
    }

    archivo << total << endl;

    for (int i = 0; i < total; i++) {
        archivo << c[i].nombre << ";" << c[i].numNotas;
        for (int j = 0; j < c[i].numNotas; j++) {
            archivo << ";" << fixed << setprecision(2) << c[i].notas[j];
        }
        archivo << endl;
    }

    archivo.close();
    cout << "\nDatos guardados en '" << NOMBRE_ARC << "' correctamente." << endl;
}

/* --- SECCION 5: RECURSIVIDAD PARA SUMAR --- */
float sumarRecursivo(float notas[], int n) {
    if (n <= 0) return 0;
    return notas[n - 1] + sumarRecursivo(notas, n - 1);
}

/* --- FUNCIONES DE APOYO Y CARGA --- */

void limpiar() {
    cin.clear();
    // cin.ignore se usa para descartar caracteres incorrectos en el buffer
    cin.ignore(10000, '\n');
}

int validarEntero(int min, int max) {
    int n;
    while (!(cin >> n) || n < min || n > max) {
        cout << "Error. Ingrese un numero entre " << min << " y " << max << ": ";
        limpiar();
    }
    cin.ignore(); // Limpiar el salto de linea despues del numero
    return n;
}

float validarNota(float min, float max) {
    float n;
    while (!(cin >> n) || n < min || n > max) {
        cout << "Error. Ingrese una nota entre " << min << " y " << max << ": ";
        limpiar();
    }
    cin.ignore();
    return n;
}

int cargar(Curso c[]) {
    ifstream archivo(NOMBRE_ARC);
    if (!archivo.is_open()) return 0;

    int total = 0;
    if (!(archivo >> total)) {
        archivo.close();
        return 0;
    }
    archivo.ignore(); 

    for (int i = 0; i < total; i++) {
        string linea;
        if (getline(archivo, linea)) {
            char* str = new char[linea.length() + 1];
            strcpy(str, linea.c_str());
            
            char *token = strtok(str, ";");
            if (token) c[i].nombre = token;
            
            token = strtok(NULL, ";");
            if (token) c[i].numNotas = atoi(token);

            for (int j = 0; j < c[i].numNotas; j++) {
                token = strtok(NULL, ";");
                if (token) c[i].notas[j] = atof(token);
            }
            delete[] str;
        }
    }
    archivo.close();
    cout << "[INFO] Se cargaron " << total << " cursos del archivo." << endl;
    return total;
}