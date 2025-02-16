#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LOG_LENGTH 256

// Bagli liste dugum yapisi
typedef struct LogNode {
    char log[MAX_LOG_LENGTH];
    struct LogNode* prev;
    struct LogNode* next;
} LogNode;

// Bagli listenin baslangici
LogNode* head = NULL;
LogNode* tail = NULL;

// Yeni log ekleme fonksiyonu
void addLog(const char* logMessage) {
    LogNode* newNode = (LogNode*)malloc(sizeof(LogNode));
    if (!newNode) {
        printf("Bellek tahsis hatasi!\n");
        return;
    }
    strncpy(newNode->log, logMessage, MAX_LOG_LENGTH);
    newNode->next = NULL;

    if (head == NULL) {
        newNode->prev = NULL;
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
}

// Loglari listeleme fonksiyonu
void displayLogs() {
    LogNode* current = head;
    printf("\nSistemdeki Log Kayitlari:\n");
    while (current) {
        printf("%s\n", current->log);
        current = current->next;
    }
}

// Belirli bir log kaydini silme fonksiyonu
void deleteLog(const char* logMessage) {
    LogNode* current = head;
    while (current) {
        if (strcmp(current->log, logMessage) == 0) {
            if (current->prev)
                current->prev->next = current->next;
            else
                head = current->next;

            if (current->next)
                current->next->prev = current->prev;
            else
                tail = current->prev;

            free(current);
            printf("\n'%s' logu silindi.\n", logMessage);
            return;
        }
        current = current->next;
    }
    printf("\nLog bulunamadi!\n");
}

// Test icin syslog kayitlarini simule etme
int main() {
    addLog("[INFO] Sistem baslatildi.");
    addLog("[WARNING] CPU sicakligi yuksek!");
    addLog("[ERROR] Disk doldu!");
    addLog("[INFO] Yeni kullanici girisi yapildi.");
    addLog("[ERROR] Uygulama yuklenemedi.");
    displayLogs();
    
    deleteLog("[ERROR] Disk doldu!");
    
    displayLogs();
    
    return 0;
}

