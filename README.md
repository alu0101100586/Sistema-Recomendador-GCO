# Sistema-Recomendador-GCO
# Integrantes
  - Bruno Lorenzo Arroyo Pedraza - alu0101123677
  - Jonay Estévez Díaz - alu0101100586
  - Carla Cristina Olivares Rodriguez - alu0101120218
  - Jose Miguel Hernandez Santana - alu0101101507

# Usage
Para el uso de la aplicación se deberá tener en cuenta que los parámetros se han de pasar por línea de comando. Primero debemos especificar la métrica que se desea usar, así como el número de vecinos a considerar y el tipo de predicción.

 - La métrica solo puede tener tres valores diferentes los cuales se deben especificar tal y como estan descritos aqui:
    - "Pearson" para la Correlación de Pearson
    - "Euclideo" para la Distancia Euclidea
    - "Coseno" para la Distancia Coseno
 - El número de vecinos deberá ser mayor que tres pues en caso contrario no se podrán realizar los calculos
 - La predicción solo puede tener dos valores:
   - "Simple" para la Predicción Simple
   - "Media" para la Diferencia con la Media

Por tanto, la ejecución por línea de comando se realizaría de la siguiente manera

```bash
~$ python3 sistema_recomendador.py [matrix_file] [metric] [nº_neighbours] [prediction]
```

# Descripción del Código

## Inicialización
Lo primero que se realiza es la obtención de los parámerosd pasador por línea de comandos, para lo que utilizamos la librería **argparse**. Como uno de los parámetros es un fichero, realizamos la lectura del fichero y almacenamos la información en la variable **matrix**. Por lo que se lee línea a línea y se pasa a vector quer será almacenado en dicha variable y así tener la matriz del fichero.

```python
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
  ```
  Luego creamos la matriz de similitud, la cual tendrá unas dimenciones coincidirán con el números de usuarios, por que que ésta si tenemos 5 usuarios, será una matriz cuadrada de 5x5.
  
 ```python
 similarity_matrix = [[0 for y in range(len(matrix))] for x in range(len(matrix))]
 ```
 
 Además se creó un vector donde se almacena qué usuarios tienen algún valor el cual se tenga que predecir, esto es una posición en la matriz cuyo valor sea **-**.
 
## Métricas
Las tres funciones que tenemos para el cálculo de la similitud entre usuarios fueron realizadas a partir de las propias definiciones y formulas, por lo que las funciones quedaron de la siguiente manera. Además tras cada calculo, se realizará en todas las funciones una llamada a otra función que nos proporcionará como ha sido el calculo, es decir, el tipo de distancia y/o el tipo de correlación.

### Correlación de Pearson
A esta función debemos pasarle dos usuarios, es decir, dos vectores los cuales tandrán los items de cada uno. Luego en realizamos los calculos necesarios para poder realizar la fórmula re correlación de Pearson, clculando los que hay dentro de las raices, así como aplicarles las raices y devolvemos el resultado de la divición final, el cual será el valor de la similitud.

```python
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
  ```

### Distancia Euclidea
Al igual que en la función anteriormente descrita, le pasamos a la función dos usuarios y realizamos los calculos, en este caso vamos sumando todas las sumas elevadas al cuadrado y por último el resultado de la similitud será la raíz de dicho sumatorio.

```python
def euclidean_distance(user_u, user_v):
  user_vector_u, user_vector_v = common_items(user_u, user_v)  
  result = 0.0
  for i in range(len(user_vector_u)):
    if (user_vector_u[i] and user_vector_v[i]):
      result += ((user_vector_u[i] - user_vector_v[i]) ** 2)

  result = math.sqrt(result)
  return result
```

### Distancia Coseno
Para la distancia coseno, tendremos los mismos parámetos que las otras funciones, en calculo que se realizará primero calculando los componentes de la formula y luego realizar la divición del numerador entre los dos denominadores dentro de una raíz, de la siguiente manera.

```python
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
```

## Calculo de los k-Vecinos
Parasemos como parámetros, la métyrica elegida, el numero de vecinos, el usuario concreto que queremos explorar sus vecicnos y la posición el item a predecir.

Seleccionamos la fila de la matriz de msimilitud del usuario y la ordenamos. Dependiendo de la métrica utilizada comprobaremos la similitud de mayor a menos o de menor a mayor, pearson y coseno para valores altos y euclidea para los menores.

Luego se procede con la valoración de los vecinos que hayan votado a dicho item, si el vecino no lo ha valorado, no se entrá en cuanta. Llegados aquí ordenamos en base a la similitud y se selecciona los necesarios en base al numero de vecinos elegido.

Como resultado se devuelve un vector de dos elmentos a modo de **pair**.

```python
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
```
## Predicciones
Se desarrollaron dos opciones, la Prediccioón SImple y la Diferencia con la media. Al igual que las métricas el desarrollo de las siguientes funciones se realizó mediante la utilización de la fórmula.

### Predicción Simple
Pasando como parametros el valor y los vecinos calculados por lo descrito anteriormente, realizamos el sumarorio que resá nuestro numerador para luego realizar el sumarotio que pertenede al denominador, devolviendo así el serultado de la división. Finalmente, si el resultado es menor que 0 lo redondeamos a 0 o si es mayor que 5, se redondeará a 5.

```python
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
```

### Diferencia con Media
Resivirá como parámetros, el vector del usuario, así como el valor y los vecinos calculados, y al igual que en la anterior, realizamos el calculo del numerados y denominados tal y como la fórmula lo describe. devolviendo así el resultado, el cual si tiene un valor fuera del rango, será reasignado a 0 o 5 al iguel que en la Predicción Simple.

```python
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
```
## Rellenar la Matriz Resultante
Para rellenar la matrix resultante de toda la operatoria, primero hacemos dos dintenciones, dependiendo de la predicción elegida por el usuario. Primero recorremos el vector de usuarios a predecir, y para dasa uno, recorremos los items que tiene para buscar el que corresponde con **-**, y aplicamos la predicción seleccionada, para terminalk devolviendo la matriz completa.

```python
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
```

# Ejemplo de Ejecución

```bash
~$ python3 sistema_recomendador.py input.txt Euclideo 5 Media
------------------------------------------------------------------------------------------------------------------------------------------
  SISTEMA RECOMENDADOR: 
   - Métrica elegida: Euclideo
   - Número de vecinos: 5
   - Predicción elegida: Media
------------------------------------------------------------------------------------------------------------------------------------------
  MATRIZ ELEGIDA    
[0]    5.00             3.00            4.00            4.00            -
[1]    3.00             1.00            2.00            3.00            3.00
[2]    4.00             3.00            4.00            3.00            5.00
[3]    3.00             3.00            1.00            5.00            4.00
[4]    1.00             5.00            5.00            2.00            1.00
------------------------------------------------------------------------------------------------------------------------------------------
  MATRIZ DE SIMILITUDES     
[0]    0.0000           3.6056          1.4142          3.7417          5.0000
[1]    3.6056           0.0000          3.6056          3.1623          5.8310
[2]    1.4142           3.6056          0.0000          3.8730          5.5678
[3]    3.7417           3.1623          3.8730          0.0000          6.4807
[4]    5.0000           5.8310          5.5678          6.4807          0.0000
------------------------------------------------------------------------------------------------------------------------------------------
Vecinos utilizados para calcular:4 -> Item: 4
[(2, 1.4142135623730951), (1, 3.605551275463989), (3, 3.7416573867739413), (4, 5.0)]
Resultado prediccion - Usuario 0 -> Item 4 = 3.8440359567911297
------------------------------------------------------------------------------------------------------------------------------------------
  RESULTADO     
[0]    5.00             3.00            4.00            4.00            3.84
[1]    3.00             1.00            2.00            3.00            3.00
[2]    4.00             3.00            4.00            3.00            5.00
[3]    3.00             3.00            1.00            5.00            4.00
[4]    1.00             5.00            5.00            2.00            1.00
------------------------------------------------------------------------------------------------------------------------------------------
```
