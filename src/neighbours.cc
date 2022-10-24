/**
 * @file neighbours.cc
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

#include "../include/neighbours.h"

/**
 * @brief Constructor de la clase neighbours
 * 
 */
Neighbours::Neighbours(){

}

/**
 * @brief Constructor de la clase neighbours
 * 
 * @param neighbours 
 */
Neighbours::Neighbours(std::vector<bool> neighbours){
  neighbours_ = neighbours;
}

/**
 * @brief Destructor de la clase neighbours
 * 
 */
Neighbours::~Neighbours(){

}

/**
 * @brief Get de la clase neighbours
 * 
 * @return std::vector<bool> 
 */
std::vector<bool> Neighbours::GetNeighbours() const{
  return neighbours_;
}

/**
 * @brief Set de la clase neighbours
 * 
 * @param new_neighbours 
 */
void Neighbours::SetNeighbours(std::vector<bool> new_neighbours){
  neighbours_ = new_neighbours;
}