# Atividade 3 projeto em c
## Gerador de Dados de Sensores (C)

Este projeto é um gerador de dados simulados de sensores, escrito em linguagem C. Ele cria amostras com timestamps aleatórios e valores variados, dependendo do tipo de cada sensor.

### Funcionalidade

O programa gera dados para 4 sensores fictícios:
- `sensor1` → Inteiro (`INT`)
- `sensor2` → Float (`FLOAT`)
- `sensor3` → Booleano (`BOOL`)
- `sensor4` → String (`STR`)

Cada sensor gera 2000 amostras, totalizando 8000 linhas.

### Formato de saída

O programa cria um arquivo chamado `teste_amostras.txt`, contendo linhas neste formato:


### Exemplo:
sensor1 1700001001 482

sensor2 1700001050 23.45

sensor3 1700001075 true

sensor4 1700001100 aB8xZ

### como executar:
gcc -o gera_teste gera_teste.c

./gera_teste
