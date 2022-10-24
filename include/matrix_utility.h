/**
 * @file matrix_utility.h
 * @author Jonay Estévez Díaz (alu0101100586@ull.edu.es)
 * @author Bruno Lorenzo Arroyo Pedraza (alu0000000000@ull.edu.es)
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

#ifndef MATRIX_UTILITY_CLASS_H
#define MATRIX_UTILITY_CLASS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <vector>
#include <math.h>

enum Metrics {Pearson, Cosine, Euclidean};
enum Prediction {Simple, Mean};

class MatrixUtility {
  public:
    MatrixUtility();
    MatrixUtility(std::vector<std::vector<double>> users_items);
    MatrixUtility(std::vector<std::string> users_lines);
    ~MatrixUtility();

    std::vector<std::vector<double>> GetUserItems() const;

    void SetUserItems(std::vector<std::vector<double>> new_user_items);

    double& At(int i, int j);

    friend std::ostream& operator<<(std::ostream& os, const MatrixUtility m);

  private:
    std::vector<std::vector<double>> user_items_;
    
    std::vector<std::string> Split(std::string line);
};

#endif //MATRIX_UTILITY_CLASS_H