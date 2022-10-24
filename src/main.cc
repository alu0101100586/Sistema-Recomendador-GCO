/**
 * @file cliente_sistema_recomendador.cc
 * 
 * @author Bruno Lorenzo Arroyo Pedraza (alu0101123677@ull.edu.es)
 * @author Carla Cristina Olivares Rodriguez (alu0101120218@ull.edu.es)
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
#include <cerrno>
#include <exception>
#include <vector>

#include "../include/matrix_utility.h"
#include "../include/neighbours.h"

//Funciones auxiliares
/**
 * Función Auxiliar que lee de un fichero
 */
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

void PearsonCorrelation(/*params*/);
void CosineDistance(/*params*/);
void EuclideanDistance(/*params*/);

/**
 * @brief Esta función muestra la ayuda del programa
 *
 * La función Help() abre el fichero help.txt y muestra por pantalla el contenido 
 * del fichero.
 */
int Help() {
  std::ifstream file_in;
  file_in.open("help.txt", std::ios::in);

  if (file_in.fail()) {
    std::cout << "No se pudo abrir el archivo" << std::endl;
    throw std::system_error(errno, std::system_category(), "No se pudo abrir el fichero help");
  }
  
  std::string aux;
  while (!file_in.eof()) {
    std::string aux;
    getline(file_in, aux);
    std::cout << aux << std::endl;
  }

  file_in.close();
  return 0;
}

// Programa principal
/**
 * @brief Main siguiendo el patron Protected Main
 * 
 * @param argc Numero de argumentos pasados por parametros
 * @param argv Variable que almacena los argumentos pasados por terminal
 * @return int Valor de salida del programa
 */ 
int ProtectedMain(int argc, char const *argv[]) {
  std::cout << "Recomendador: Inicializando programa" << std::endl;
  std::string help;
  switch (argc) {
    case 2:
      help = argv[1];
      if (help == "-h" || help == "--help") return Help();
      throw std::system_error(errno, std::system_category(), "No se pudo ejecutar el programa, error de entrada");
    case 5:
      /* codigo para el tratamiento de datos*/
      break;    
    default:
      throw std::system_error(errno, std::system_category(), "No se pudo ejecutar el programa, error de entrada");
  }
  
  std::cout << "Recomendador: Finalizando programa" << std::endl;
  return 0;
}

/**
 * @brief Función Principal del programa
 * 
 * @param argc Número de argumentos pasados como parametros
 * @param argv Variable que almacena los argumentos pasados por terminal
 * @return int Valor salida del programa
 */
int main(int argc, char const *argv[]) {
  try {
    return ProtectedMain(argc, argv);
  }
  catch(std::bad_alloc& e) {
    std::cerr << "Recomendador: " << "memoria insuficiente" << std::endl;
    return 1;
  }  
  catch(std::system_error& e) {
    std::cerr << "Recomendador: " << e.what() << std::endl;
    return 2;
  }
  catch(...) {
    std::cout << "Ha ocurrido un error inesperado..." << std::endl;
    return 99;
  }
}




