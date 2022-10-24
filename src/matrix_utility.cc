/**
 * @file matrix_utility.cc
 * @author Jonay Estévez Díaz (alu0101100586@ull.edu.es)
 * @author Bruno Lorenzo Arroyo Pedraza (alu0101123677@ull.edu.es)
 * @author Carla Cristina Olivares Rodriguez (alu0101120218@ull.edu.es)
 * @author Jose Miguel Hernández Santana (alu0101101507@ull.edu.es)
 * 
 * @brief Clase Container, que nos permite utilizar una matriz como 
 *        container de la matriz de utilidad
 * @version 0.5
 * @date 2022-10-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "../include/matrix_utility.h"

/**
 * @brief Construct a new MatrixUtility::MatrixUtility object
 * 
 */
MatrixUtility::MatrixUtility() {

}

/**
 * @brief Construct a new MatrixUtility::MatrixUtility object
 * 
 * @param users_items 
 */
MatrixUtility::MatrixUtility(std::vector<std::vector<double>> users_items) {
  user_items_ = users_items;
}

/**
 * @brief Construct a new MatrixUtility::MatrixUtility object
 * 
 * @param users_items 
 */
MatrixUtility::MatrixUtility(std::vector<std::string> users_lines) {
  std::vector<std::string> aux;
  user_items_.resize(users_lines.size());
  for (int i = 0; i < users_lines.size(); i++) {
    aux.clear();
    aux = Split(users_lines[i]);
    for (int j = 0; j < aux.size(); j++) {
      if(aux[j] == "-") user_items_[i].push_back(INFINITY);
      else              user_items_[i].push_back(std::stod(aux[j]));
    }
  }
}

/**
 * @brief Destroy the MatrixUtility::MatrixUtility object
 * 
 */
MatrixUtility::~MatrixUtility() {
  
}

/**
 * @brief 
 * 
 * @return std::vector<std::vector<int>> 
 */
std::vector<std::vector<double>> MatrixUtility::GetUserItems() const {
  return user_items_;
}

/**
 * @brief 
 * 
 * @param user_items_ 
 */
void MatrixUtility::SetUserItems(std::vector<std::vector<double>> new_user_items) {
  user_items_ = new_user_items;
}

/**
 * @brief 
 * 
 * @param i 
 * @param j 
 * @return int& 
 */
double& MatrixUtility::At(int i, int j) {
  return user_items_[i][j];
}

/**
 * @brief 
 * 
 * @param os 
 * @param m 
 * @return std::ostream&
 */
std::ostream& operator<<(std::ostream& os, const MatrixUtility m) {
  for (int i = 0; i < m.user_items_.size(); i++) {
    os << "| ";
    for (int j = 0; j < m.user_items_[i].size(); j++) {
      os << m.user_items_[i][j] << " ";
    }
    os << "|\n";
  }
  return os;
}

/**
 * @brief 
 * 
 * @param line 
 * @return std::vector<std::string> 
 */
std::vector<std::string> MatrixUtility::Split(std::string line) {
  std::vector<std::string> aux;
  std::istringstream totalString(line);
  std::string piece;
  while (!totalString.eof()) {
    totalString >> piece;
    aux.push_back(piece);
  }
  return aux;
}