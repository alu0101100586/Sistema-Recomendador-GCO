import argparse
from itertools import count
import sys
import math
from copy import deepcopy

#==============================================================================
#                              MÉTRICAS
#==============================================================================

# Correlación de coeficiente de Pearson
def pearson_correlation_coefficient(user_u, user_v):
  user_vector_u, user_vector_v = common_items(user_u, user_v)
  media_user_u = mean(user_vector_u)
  media_user_v = mean(user_vector_v)

  numerator = 0.0
  root_left = 0.0
  root_right = 0.0
  # Calculo de los componentes de la formula
  for i in range(len(user_vector_u)):
    numerator += (user_vector_u[i] - media_user_u) * (user_vector_v[i] - media_user_v)
    root_left += (user_vector_u[i] - media_user_u) ** 2
    root_right += (user_vector_v[i] - media_user_v) ** 2
  
  # Calculo de las raices y del denominador
  denominator = math.sqrt(root_left) * math.sqrt(root_right)
  
  # Calculo de la correlación
  result = numerator / denominator
  return result


# Distancia coseno
def cosine_distance(user_u, user_v):
  user_vector_u, user_vector_v = common_items(user_u, user_v)
  numerator = 0.0
  denominator1 = 0.0
  denominator2 = 0.0
  result = 0.0
  
  # Calculo de los componentes de la formula
  for i in range(len(user_vector_u)):
      numerator += user_vector_u[i] * user_vector_v[i]
      denominator1 += user_vector_u[i] ** 2
      denominator2 += user_vector_v[i] ** 2
  
  # Calculo de la distancia
  result += (numerator /(math.sqrt(denominator1) * (math.sqrt(denominator2))))
  return result


# Distancia euclidiana
def euclidean_distance(user_u, user_v):
  user_vector_u, user_vector_v = common_items(user_u, user_v)  
  result = 0.0
  for i in range(len(user_vector_u)):
    if (user_vector_u[i] and user_vector_v[i]):
      result += ((user_vector_u[i] - user_vector_v[i]) ** 2)

  result = math.sqrt(result)
  return result

#==============================================================================
#                               PREDICCIONES
#==============================================================================

# Predicción simple
def simple_prediction(val, neighbors_k):
  nominator = 0.0
  denominator = 0.0
  result = 0.0

  for i in neighbors_k:
    nominator += i[1] * matrix[i[0]][val]
    denominator += abs(i[1])

  result += nominator / float(denominator)
  result = float("{:.4f}".format(result))

  if result < 0:
    result = 0
  elif result > 5:
    result = 5

  return result

# Predicción diferencia con la media
def difference_prediction(user_v, val, neighbours_k):
  numerator = 0.0
  denominator = 0.0
  result = 0.0
  user_mean_v = mean(user_v)
  medias = []
  
  #Almacenamos todas las medias 
  for i in neighbours_k:
    medias.append(mean(matrix[i[0]]))
  
  for i in neighbours_k:
    numerator += i[1] * (matrix[i[0]][val] - mean(matrix[i[0]]))
    denominator += abs(i[1])

  result = user_mean_v + (numerator / float(denominator))
  
  if result < 0:
    result = 0
  elif result > 5:
    result = 5

  return result

#==============================================================================
#                            FUNCIONES AUXILIARES
#==============================================================================

# Calculo de la media
def mean(user):
  result = 0.0
  count = 0
  for i in range(len(user)):
    if user[i] != '-':
      result += user[i]
      count += 1
  result = result / count    
  return result

# Calculo de los items comunes a dos usuarios
def common_items(user_u, user_v):
  user_vector_u, user_vector_v = [], []
  for i in range(len(user_u)):
    if user_u[i] != '-' and user_v[i] != '-':
      user_vector_u.append(user_u[i])
      user_vector_v.append(user_v[i])      
  return user_vector_u, user_vector_v

# Calculo de vecinos para el calculo de las predicciones
def calculate_neighbors(metrics, neighbors, user, position):
  neighbors_k = []
  order_user_row = deepcopy(similarity_matrix[user])
  
  # Dependiendo de la metrica se ordena de mayor a menor o de menor a mayor
  if(metrics == "Pearson" or metrics == 'Coseno'):
    order_user_row.sort(reverse=True)
  else:
    order_user_row.sort(reverse=False)
  
  order_user_1 = deepcopy(similarity_matrix[user])
  order_user_2 = deepcopy(order_user_1)
  coincident_neighbors = []

  for element in order_user_row:
    user = order_user_1.index(element)
    order_user_1[user] = 0
    if matrix[user][position] != '-':
      coincident_neighbors.append(user)
  
  # vecinos que se van a utilizar para el calculo de la prediccion
  count_neighbors = coincident_neighbors[0:neighbors]

  # Se calcula la similitud entre el usuario y los vecinos
  for neighbor in count_neighbors:
    similitary_value = order_user_2[neighbor]
    neighbors_k.append((neighbor, similitary_value))
  
  print("Vecinos utilizados para calcular:" + str(user) + " -> Item: " + str(position)) 
  print(neighbors_k)    
  return neighbors_k
  

# Sacar formateada una matriz
def print_matrix(matrix):
  aux = ""
  counter = 0

  for row in matrix:
    aux = "[" + str(counter) + "]    "
    counter += 1
    for element in row:
      if(type(element) == str):
        aux += element
      else:
        aux += "{:.2f}".format(element) 

      aux += "\t\t"
    print(aux)

# Sacar formateada una matriz de similitud
def print_similarity_matrix():
  aux = ""
  counter = 0

  for row in similarity_matrix:
    aux = "[" + str(counter) + "]    "
    counter += 1
    for element in row:
      if (element < 0):
        aux += "{:.3f}".format(element) 
      else:
        aux += "{:.4f}".format(element)
      aux += "\t\t"
    print(aux)  

# Sacar del argumento el numero de vecino
def get_neighbor_type(a):
  a = int(a)
  if(a < 1):
    raise argparse.ArgumentError("Utilice un minimo de 3 vecinos")
  else: 
    return a
    
def similitary_method(metrics):
  if(metrics == "Pearson"):
    for i in range(len(matrix)):
      for j in range(len(matrix)):
        if(i != j):
          similarity_matrix[i][j] = pearson_correlation_coefficient(matrix[i], matrix[j])
  elif(metrics == "Coseno"):
    for i in range(len(matrix)):
      for j in range(len(matrix)):
        if(i != j):
          similarity_matrix[i][j] = cosine_distance(matrix[i], matrix[j])
  else:
    for i in range(len(matrix)):
      for j in range(len(matrix)):
        if(i != j):
          similarity_matrix[i][j] = euclidean_distance(matrix[i], matrix[j])
        
#==============================================================================
#                             FUNCION PRINCIPAL
#==============================================================================

def main(metrics, prediction, neighbours):
  similitary_method(metrics)
  print("------------------------------------------------------------------------------------------------------------------------------------------")
  print("  MATRIZ ELEGIDA    ")
  print_matrix(matrix)
  print("------------------------------------------------------------------------------------------------------------------------------------------")
  print("  MATRIZ DE SIMILITUDES     ")
  print_similarity_matrix()
  matrix_rslt = deepcopy(matrix)

  if(prediction == "Simple"):
    for i in predict_users:
      for j in range(len(matrix[i])):
        if(matrix_rslt[i][j] == "-"):
          print("------------------------------------------------------------------------------------------------------------------------------------------")
          neighbors_k = calculate_neighbors(metrics, neighbours, i, j)
          pred_aux = simple_prediction(j, neighbors_k)
          matrix_rslt[i][j] = pred_aux
          print("Resultado prediccion: " + str(pred_aux))
  else:
    for i in predict_users:
      for j in range(len(matrix[i])):
        if(matrix_rslt[i][j] == "-"):
          print("------------------------------------------------------------------------------------------------------------------------------------------")
          neighbors_k = calculate_neighbors(metrics, neighbours, i, j)
          pred_aux = difference_prediction(matrix[i], j, neighbors_k)
          matrix_rslt[i][j] = pred_aux
          print("Resultado prediccion - Usuario " + str(i) + " -> Item " 
                + str(j) + " = " + str(pred_aux))
  return matrix_rslt
  
#==============================================================================
#                           EJECUCION DE LAS FUNCIONES
#==============================================================================

# Obtención de los parámetros pasados al programa
parser = argparse.ArgumentParser(description='Practica Sistema Recomendador')
parser.add_argument('matrix_file', type=argparse.FileType('r'))
parser.add_argument('metrics', choices=['Pearson', 'Euclideo', 'Coseno'])
parser.add_argument('neighbours', type=get_neighbor_type, 
      help='Indicar el número de vecinos que debe el programa tener en cuenta')
parser.add_argument('prediction', choices=['Simple', 'Media'])

argv = parser.parse_args()

#Lectura del fichero especificado por el usuario
matrix_lines = argv.matrix_file.readlines()
matrix = []
predict_users = []
for i in matrix_lines:
  line = i.split()
  aux_line = []
  predictable = False
  for j in line:
    if (j == '-'):
      aux = j
      predictable = True
    else:
      aux = int(j)
    aux_line.append(aux)
  if(predictable):
    predict_users.append(len(matrix))
  matrix.append(aux_line)

similarity_matrix = [[0 for y in range(len(matrix))] for x in range(len(matrix))]

#comprobar si esto crea la matriz de las dimenciones que queremos
if(argv.neighbours < 3 and len(matrix) < 3):
  print("Debe proporcionar como mínimo 3 usuarios al sistema")
else:
  print("------------------------------------------------------------------------------------------------------------------------------------------")
  print("  SISTEMA RECOMENDADOR: ")
  print("   - Métrica elegida: " + argv.metrics)
  print("   - Número de vecinos: " + str(argv.neighbours))
  print("   - Predicción elegida: " + argv.prediction)

  result = main(argv.metrics, argv.prediction, argv.neighbours)
  print("------------------------------------------------------------------------------------------------------------------------------------------")
  print("  RESULTADO     ")
  print_matrix(result)
  print("------------------------------------------------------------------------------------------------------------------------------------------")