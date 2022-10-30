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
Las tres funciones que tenemos para el cálculo de la similitud entre usuarios fueron realizadas a partir de las propias definiciones y formulas, por lo que las funciones quedaron de la siguiente manera

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
Al igual que en la función anteriormente descrita, le pasamos a la función dos usuarios y realizamos los calculos

### Distancia Coseno

## Calculo de los k-Vecinos

## Predicciones

### Predicción Simple

### Diferencia con Media

## Rellenar la Matriz Resultante

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
