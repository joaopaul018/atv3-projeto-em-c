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


void generate_value(DataType type, char* buffer, size_t size)
 {
    switch (type) 
    {
        case INT:
            snprintf(buffer, size, "%d", rand() % 1000);
            break;
        case BOOL:
            strcpy(buffer, (rand() % 2) ? "true" : "false");
            break;
        case FLOAT:
            snprintf(buffer, size, "%.2f", ((double)(rand() % 1000)) / 10.0);
            break;
        case STR: 
        {
            const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            int len = rand() % 16 + 1;
            for (int i = 0; i < len && i < 16; i++) 
            {
                buffer[i] = charset[rand() % (sizeof(charset) - 1)];
            }
            buffer[len < 16 ? len : 15] = '\0';
            break;
        }
        default:
            strcpy(buffer, "invalid");
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
    char value[MAX_VAL_LEN];
    generate_value(s.type, value, sizeof(value));
    fprintf(fp, "%s %ld %s\n", s.id, timestamp, value);  
}

    }

    fclose(fp);
    printf("Arquivo 'teste_amostras.txt' gerado com sucesso!\n");

    return 0;
}
