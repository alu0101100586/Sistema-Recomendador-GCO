/**
 * @file neighbours.h
 * @author Jonay Estévez Díaz (alu0101100586@ull.edu.es)
 * @author Bruno Lorenzo Arroyo Pedraza (alu0000000000@ull.edu.es)
 * @author Carla Cristina Olivares Rodriguez (alu0101120218@ull.edu.es)
 * @author Jose Miguel Hernández Santana (alu0101101507@ull.edu.es)
 * 
 * @brief Clase neighbour que nos permite contar y utilizar a los vecinos
 *        NEIGHBOURS_CLASS_H
 * @version 0.5
 * @date 2022-10-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef NEIGHBOURS_CLASS_H
#define NEIGHBOURS_CLASS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <vector>

class Neighbours {
  public:
    Neighbours();
    Neighbours(std::vector<bool> neighbours);
    ~Neighbours(); 

    std::vector<bool> GetNeighbours() const;

    void SetNeighbours(std::vector<bool> new_neighbours);

  private:
    std::vector<bool> neighbours_;

 };

#endif //NEIGHBOURS_CLASS_H