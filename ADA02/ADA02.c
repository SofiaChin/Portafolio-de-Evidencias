#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>

#define INF (INT_MAX/4)

int i;
int j;
int s;

typedef struct {
    int id;
    int arrival;
    int service;
    int start;
    int finish;
    int queue_id;
} Client;

typedef struct Node {
    int client_idx;
    struct Node* next;
} Node;

typedef struct {
    Node* front;
    Node* rear;
    int size;
} QueueC;

void init_queue(QueueC* q) {
    q->front = q->rear = NULL;
    q->size = 0;
}

void enqueue(QueueC* q, int client_idx) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->client_idx = client_idx;
    n->next = NULL;
    if (q->rear) q->rear->next = n;
    else q->front = n;
    q->rear = n;
    q->size++;
}

bool dequeue(QueueC* q, int* out_client_idx) {
    if (!q->front) return false;
    Node* t = q->front;
    *out_client_idx = t->client_idx;
    q->front = t->next;
    if (!q->front) q->rear = NULL;
    free(t);
    q->size--;
    return true;
}

bool is_empty(QueueC* q) {
    return q->size == 0;
}

int queue_size(QueueC* q) {
    return q->size;
}

void print_header() {
    printf("=== Simulador - Banco ===\n");
}

int rand_between(int a, int b) {
    return a + rand() % (b - a + 1);
}

int main() {
    srand((unsigned)time(NULL));
    print_header();

    int N;
    printf("Ingrese el numero de clientes: ");
    scanf("%d", &N);

    int max_arrival_time;
    printf("Ingrese el tiempo maximo de llegada (minutos): ");
    scanf("%d", &max_arrival_time);

    int min_service, max_service;
    printf("Ingrese el tiempo minimo de servicio (minutos): ");
    scanf("%d", &min_service);
    printf("Ingrese el tiempo maximo de servicio (minutos):");
    scanf("%d", &max_service);
    printf("\n");

    Client* clients = (Client*)malloc(N * sizeof(Client));
    for (i = 0; i < N; i++) {
        clients[i].id = i + 1;
        clients[i].arrival = i;
        clients[i].service = rand_between(min_service, max_service);
        clients[i].start = -1;
        clients[i].finish = -1;
        clients[i].queue_id = -1;
    }

    QueueC q[3];
    for (i = 0; i < 3; i++) init_queue(&q[i]);

    bool serverBusy[3] = {false,false,false};
    int next_free_time[3] = {INF,INF,INF};
    int current_client_idx[3] = {-1,-1,-1};

    long long total_wait[3] = {0,0,0};
    long long total_service[3] = {0,0,0};
    int num_served[3] = {0,0,0};

    int ai = 0;

    while (ai < N || serverBusy[0] || serverBusy[1] || serverBusy[2] || !is_empty(&q[0]) || !is_empty(&q[1]) || !is_empty(&q[2])) {

        int next_arrival_time = (ai < N) ? clients[ai].arrival : INF;
        int next_completion_time = INF;
        for (i = 0; i < 3; i++)
            if (serverBusy[i] && next_free_time[i] < next_completion_time)
                next_completion_time = next_free_time[i];

        int t;
        bool process_completion_first = false;
        if (next_completion_time <= next_arrival_time) {
            t = next_completion_time;
            process_completion_first = true;
        } else {
            t = next_arrival_time;
            process_completion_first = false;
        }
        if (t == INF) break;

        if (process_completion_first) {
            for (s = 0; s < 3; s++) {
                if (serverBusy[s] && next_free_time[s] == t) {
                    int finished_idx = current_client_idx[s];
                    clients[finished_idx].finish = t;
                    printf("Tiempo %3d: Cliente #%d termina atencion en Caja %d (Tiempo total: %d minutos).\n", t, clients[finished_idx].id, s+1, clients[finished_idx].finish - clients[finished_idx].arrival);

                    serverBusy[s] = false;
                    current_client_idx[s] = -1;
                    next_free_time[s] = INF;

                    if (!is_empty(&q[s])) {
                        int next_idx;
                        dequeue(&q[s], &next_idx);
                        clients[next_idx].start = t;
                        int finish = t + clients[next_idx].service;
                        clients[next_idx].finish = finish;
                        serverBusy[s] = true;
                        current_client_idx[s] = next_idx;
                        next_free_time[s] = finish;

                        int waittime = clients[next_idx].start - clients[next_idx].arrival;
                        total_wait[s] += waittime;
                        total_service[s] += clients[next_idx].service;
                        num_served[s]++;

                        printf("Tiempo %3d: Cliente #%d inicia atencion en Caja %d (Tipo de servicio: %d, tiempo de espera: %d minutos).\n", t, clients[next_idx].id, s+1, clients[next_idx].service, waittime);
                    }
                }
            }
        }

        while (ai < N && clients[ai].arrival == t) {
            int idx = ai;
            int assigned_queue = rand_between(0,2);
            clients[idx].queue_id = assigned_queue;
            enqueue(&q[assigned_queue], idx);

            printf("Tiempo %3d: Cliente #%d llega (Tipo de servicio: %d) y se asigna en Cola %d.\n", t, clients[idx].id, clients[idx].service, assigned_queue+1);

            if (!serverBusy[assigned_queue] && queue_size(&q[assigned_queue]) == 1) {
                int next_idx;
                dequeue(&q[assigned_queue], &next_idx);
                clients[next_idx].start = t;
                int finish = t + clients[next_idx].service;
                clients[next_idx].finish = finish;
                serverBusy[assigned_queue] = true;
                current_client_idx[assigned_queue] = next_idx;
                next_free_time[assigned_queue] = finish;

                int waittime = clients[next_idx].start - clients[next_idx].arrival;
                total_wait[assigned_queue] += waittime;
                total_service[assigned_queue] += clients[next_idx].service;
                num_served[assigned_queue]++;

                printf("Tiempo %3d: Cliente #%d inicia atencion en Caja %d (Tipo de servicio: %d, tiempo de espera: %d).\n", t, clients[next_idx].id, assigned_queue+1, clients[next_idx].service, waittime);
            }

            ai++;
        }
    }

    printf("\n=== Estadisticas por cola ===\n");
    int total_atendidos = 0;
    long long total_wait_all = 0;
    long long total_service_all = 0;
    for (s = 0; s < 3; s++) {
        printf("Cola %d:\n", s+1);
        printf("  - Clientes atendidos: %d\n", num_served[s]);
        float avg_wait = (num_served[s] > 0) ? (float)total_wait[s] / num_served[s] : 0.0;
        float avg_service = (num_served[s] > 0) ? (float)total_service[s] / num_served[s] : 0.0;
        printf("  - Tiempo promedio de espera: %.2f\n", avg_wait);
        printf("  - Tiempo promedio de servicio: %.2f\n", avg_service);
        printf("  - Tiempo total de servicio: %I64d\n\n", total_service[s]);
        total_atendidos += num_served[s];
        total_wait_all += total_wait[s];
        total_service_all += total_service[s];
    }

    printf("=== Estadisticas generales ===\n");
    printf("Total clientes generados: %d\n", N);
    printf("Total clientes atendidos: %d\n", total_atendidos);
    float avg_wait_all = (total_atendidos > 0) ? (float)total_wait_all / total_atendidos : 0.0;
    printf("Tiempo promedio de espera general: %.2f\n", avg_wait_all);
    printf("Tiempo total de servicio: %I64d\n", total_service_all);

    printf("\nFin de la simulacion.\n");

    free(clients);
    return 0;
}