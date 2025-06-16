#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ID_LEN 32
#define MAX_VAL_LEN 17
#define SAMPLES_PER_SENSOR 2000
#define MAX_SENSORS 10

typedef enum 
{
    INT,
    BOOL,
    FLOAT,
    STR,
    UNKNOWN
} DataType;


typedef struct 
{
    char id[MAX_ID_LEN];
    DataType type;
} Sensor;
 const char* get_type_label(DataType type){
    switch (type) {
        case INT:   return "CONJ_Z";
        case FLOAT: return "CONJ_Q";
        case BOOL:  return "BINARIO";
        case STR:   return "TEXTO";
        default:    return "DESCONHECIDO";
    }
}

long random_timestamp(long start, long end) 
{
    return start + (rand() % (end - start + 1));
}

int main() 
{
    srand((unsigned int)time(NULL));

    
    Sensor sensors[] = 
    {
        {"sensor1", INT},
        {"sensor2", FLOAT},
        {"sensor3", BOOL},
        {"sensor4", STR}
    };

    int num_sensors = sizeof(sensors) / sizeof(sensors[0]);

    
    long start_time = time(NULL);              
    long end_time = start_time + 60 * 60 * 24;  

    

    FILE* fp = fopen("teste_amostras.txt", "w");
    if (!fp) 
    {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    for (int i = 0; i < num_sensors; i++) 
    {
        Sensor s = sensors[i];

        for (int j = 0; j < SAMPLES_PER_SENSOR; j++) 
        {
            long timestamp = random_timestamp(start_time, end_time);
            const char* value_label = get_type_label(s.type);
            fprintf(fp, "%s %ld %s\n", s.id, timestamp, value_label);  
        }
    }

    fclose(fp);
    printf("Arquivo 'teste_amostras.txt' gerado com sucesso!\n");

    return 0;
}
