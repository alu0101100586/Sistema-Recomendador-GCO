/**
 * @file cliente_sistema_recomendador.cc
 * 
 * @author Bruno Lorenzo Arroyo Pedraza (pon tu email puto)
 * @author Carla Cristina Olivares Rodriguez (pon tu email puta)
 * @author Jose Miguel Hernandez Santana (alu0101101507@ull.edu.es)
 * @author Jonay Estévez Diaz (alu0101100586@ull.edu.es)
 * 
 * @brief Sistema recomendador
 * @version 0.1
 * @date 2022-10-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../lib/matrix_utility.h"
#include "../lib/neighbours.h"

enum Metrics {Pearson, Cosine, Euclidean};
enum Prediction {Simple, Mean};

/**
 * Función auxiliar que prepara un fichero para modificarlo
 */
void Openfile(std::string file_name);

/**
 * Función Auxiliar que lee de un fichero
 */
void ReadFile(std::string file_name, std::vector<std::string>& input_txt);

/**
 * @brief Función que muestra un error si se ejecuta mal el programa
 * 
 */
void ExecutionError();

void PearsonCorrelation(/*params*/);

void CosineDistance(/*params*/);

void EuclideanDistance(/*params*/);

/**
 * @brief Función Principal del programa
 * 
 * @param argc numero de argumentos pasados como parametros
 * @param argv variable que almacena los argumentos pasados por terminal
 * @return int 
 */
int main(int argc, char const *argv[]) {
  switch (argc) {
    case 5:
      /* codigo para el tratamiento de datos*/
      break;
    
    default:
      ExecutionError();
      return 1;
  }
  
  return 0;
}

/**
 * @brief Función que muestra un error si se ejecuta mal el programa
 * 
 */ 
int protected_main(int argc, char const *argv[]) {
  switch (argc) {
    case 5:
      /* codigo para el tratamiento de datos*/
      break;
    
    default:
      ExecutionError();
      return 1;
  }
  
  return 0;
}

//Funciones auxiliares
void Openfile(std::string file_name) {
  std::ofstream out_file;
  out_file.open(file_name, std::ios::out);
  if(out_file.fail()) {
    std::cout << "Error al abrir el archivo\n";
    exit(1);
  }
  out_file << "";
  out_file.close();
}

void ReadFile(std::string file_name, std::vector<std::string>& input_txt) {
  std::string aux;
  std::ifstream in_file;

  in_file.open(file_name, std::ios::in);
  if (in_file.fail()) {
    std::cout << "Error al abrir el archivo\n";
    exit(1); 
  }
  while (!in_file.eof()) {
    aux = "";
    getline(in_file, aux);
    input_txt.push_back(aux);    
  }
  in_file.close();
}

void ExecutionError() {
  std::cout << "EXECUTION ERROR:\n";
  std::cout << "USAGE: ~$: ./GCO_S_R [input file name] [Metrica] [numero de signos] [predicción]\n";
}


