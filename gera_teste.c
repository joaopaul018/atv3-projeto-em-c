#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ID_LEN 32
#define MAX_VAL_LEN 17
#define SAMPLES_PER_SENSOR 2000
#define MAX_SENSORS 10

typedef enum {
    INT,
    BOOL,
    FLOAT,
    STR,
    UNKNOWN
} DataType;

const char* get_type_label(DataType type) {
    switch (type) {
        case INT:   return "CONJ_Z";
        case FLOAT: return "CONJ_Q";
        case BOOL:  return "BINARIO";
        case STR:   return "TEXTO";
        default:    return "DESCONHECIDO";
    }
}

DataType get_data_type_from_input(const char* input) {
    if (strcmp(input, "CONJ_Z") == 0) return INT;
    if (strcmp(input, "CONJ_Q") == 0) return FLOAT;
    if (strcmp(input, "TEXTO") == 0) return STR;
    if (strcmp(input, "BINARIO") == 0) return BOOL;
    return UNKNOWN;
}

long random_timestamp(long start, long end) {
    return start + (rand() % (end - start + 1));
}

void generate_value(DataType type, char* buffer, size_t size) {
    switch (type) {
        case INT:
            snprintf(buffer, size, "%d", rand() % 1000);
            break;
        case BOOL:
            strcpy(buffer, (rand() % 2) ? "true" : "false");
            break;
        case FLOAT:
            snprintf(buffer, size, "%.2f", ((double)(rand() % 1000)) / 10.0);
            break;
        case STR: {
            const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            int len = rand() % 16 + 1;
            for (int i = 0; i < len && i < 16; i++) {
                buffer[i] = charset[rand() % (sizeof(charset) - 1)];
            }
            buffer[len < 16 ? len : 15] = '\0';
            break;
        }
        default:
            strcpy(buffer, "invalid");
    }
}

int main() {
    srand((unsigned int)time(NULL));

    char user_input[32];
    DataType selected_type = UNKNOWN;

    // Perguntar ao usuário qual tipo deseja gerar
    while (selected_type == UNKNOWN) {
        printf("Digite o tipo de dado a ser gerado:\n");
        printf("  CONJ_Z  -> Inteiro\n");
        printf("  CONJ_Q  -> Float\n");
        printf("  TEXTO   -> String (alfanumérica)\n");
        printf("  BINARIO -> Booleano (true/false)\n");
        printf("Opcao: ");
        scanf("%s", user_input);

        selected_type = get_data_type_from_input(user_input);

        if (selected_type == UNKNOWN) {
            printf("Tipo invalido! Por favor, digite uma opcao valida.\n\n");
        }
    }

    // Definir sensores com base no tipo escolhido
    Sensor sensors[MAX_SENSORS];
    for (int i = 0; i < MAX_SENSORS; i++) {
        char sensor_id[16];
        snprintf(sensor_id, sizeof(sensor_id), "sensor%d", i + 1);
        strcpy(sensors[i].id, sensor_id);
        sensors[i].type = selected_type;
    }

    int num_sensors = MAX_SENSORS;

    long start_time = time(NULL);
    long end_time = start_time + 60 * 60 * 24; // 24 horas à frente

    FILE* fp = fopen("teste_amostras.txt", "w");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    for (int i = 0; i < num_sensors; i++) {
        Sensor s = sensors[i];

        for (int j = 0; j < SAMPLES_PER_SENSOR; j++) {
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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ID_LEN 32
#define MAX_VAL_LEN 17
#define SAMPLES_PER_SENSOR 2000
#define MAX_SENSORS 10

typedef enum {
    INT,
    BOOL,
    FLOAT,
    STR,
    UNKNOWN
} DataType;

const char* get_type_label(DataType type) {
    switch (type) {
        case INT:   return "CONJ_Z";
        case FLOAT: return "CONJ_Q";
        case BOOL:  return "BINARIO";
        case STR:   return "TEXTO";
        default:    return "DESCONHECIDO";
    }
}

DataType get_data_type_from_input(const char* input) {
    if (strcmp(input, "CONJ_Z") == 0) return INT;
    if (strcmp(input, "CONJ_Q") == 0) return FLOAT;
    if (strcmp(input, "TEXTO") == 0) return STR;
    if (strcmp(input, "BINARIO") == 0) return BOOL;
    return UNKNOWN;
}

long random_timestamp(long start, long end) {
    return start + (rand() % (end - start + 1));
}

void generate_value(DataType type, char* buffer, size_t size) {
    switch (type) {
        case INT:
            snprintf(buffer, size, "%d", rand() % 1000);
            break;
        case BOOL:
            strcpy(buffer, (rand() % 2) ? "true" : "false");
            break;
        case FLOAT:
            snprintf(buffer, size, "%.2f", ((double)(rand() % 1000)) / 10.0);
            break;
        case STR: {
            const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
            int len = rand() % 16 + 1;
            for (int i = 0; i < len && i < 16; i++) {
                buffer[i] = charset[rand() % (sizeof(charset) - 1)];
            }
            buffer[len < 16 ? len : 15] = '\0';
            break;
        }
        default:
            strcpy(buffer, "invalid");
    }
}

int main() {
    srand((unsigned int)time(NULL));

    char user_input[32];
    DataType selected_type = UNKNOWN;

    // Perguntar ao usuário qual tipo deseja gerar
    while (selected_type == UNKNOWN) {
        printf("Digite o tipo de dado a ser gerado:\n");
        printf("  CONJ_Z  -> Inteiro\n");
        printf("  CONJ_Q  -> Float\n");
        printf("  TEXTO   -> String (alfanumérica)\n");
        printf("  BINARIO -> Booleano (true/false)\n");
        printf("Opcao: ");
        scanf("%s", user_input);

        selected_type = get_data_type_from_input(user_input);

        if (selected_type == UNKNOWN) {
            printf("Tipo invalido! Por favor, digite uma opcao valida.\n\n");
        }
    }

    // Definir sensores com base no tipo escolhido
    Sensor sensors[MAX_SENSORS];
    for (int i = 0; i < MAX_SENSORS; i++) {
        char sensor_id[16];
        snprintf(sensor_id, sizeof(sensor_id), "sensor%d", i + 1);
        strcpy(sensors[i].id, sensor_id);
        sensors[i].type = selected_type;
    }

    int num_sensors = MAX_SENSORS;

    long start_time = time(NULL);
    long end_time = start_time + 60 * 60 * 24; // 24 horas à frente

    FILE* fp = fopen("teste_amostras.txt", "w");
    if (!fp) {
        perror("Erro ao abrir arquivo");
        return 1;
    }

    for (int i = 0; i < num_sensors; i++) {
        Sensor s = sensors[i];

        for (int j = 0; j < SAMPLES_PER_SENSOR; j++) {
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
