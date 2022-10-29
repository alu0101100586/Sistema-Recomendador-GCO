# Sistema-Recomendador-GCO
## Integrantes
  - Bruno Lorenzo Arroyo Pedraza - alu0101123677
  - Jonay Estévez Díaz - alu0101100586
  - Carla Cristina Olivares Rodriguez - alu0101120218
  - Jose Miguel Hernandez Santana - alu0101101507

## Usage
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

## Descripción del Código

## Ejemplo de Ejecución

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