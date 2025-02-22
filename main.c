#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct {
    time_t timestamp;
    char facility[32];
    char severity[32];
    char message[256];      
} SyslogData;  


typedef struct Node {
    SyslogData data;         // Düğümde tutulan syslog verisi
    struct Node* next;       // Sonraki düğüme işaretçi
} Node;  // Bağlantılı liste düğümü yapısı

// Yeni dugum olusturma fonksiyonu
Node* createNode(SyslogData data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Bellekten yeni düğüm için yer ayır
    if (newNode == NULL) {
        printf("Bellek tahsis hatasi!\n");  // Bellek hatası kontrolü
        exit(1);  
    }
    newNode->data = data;
    newNode->next = NULL; 
    return newNode;
}

// Listeye yeni mesaj ekleme fonksiyonu
Node* addSyslogMessage(Node* head, SyslogData data) {
    Node* newNode = createNode(data);
    
    if (head == NULL) {  // Liste boşsa, yeni düğüm baş düğüm olur
        return newNode;
    }
    
    Node* current = head;
    while (current->next != NULL) {  // Listenin sonuna git
        current = current->next;
    }
    current->next = newNode;  // Yeni düğümü sona ekle
    return head;  // Liste başını döndür
}

// Ornek bir syslog mesajini parse etme fonksiyonu
SyslogData parseSyslogMessage(const char* message) {
    SyslogData data;
    data.timestamp = time(NULL);  // Mevcut zamanı al
    
    // Mesajı ayrıştırarak facility, severity ve mesaj içeriğini ayıkla
    sscanf(message, "<%[^>]>%[^:]:%[^\n]", 
           data.facility,
           data.severity,
           data.message);
    
    return data;  // Ayrıştırılmış veriyi döndür
}

// Listedeki tüm mesajları yazdırma fonksiyonu
void printSyslogList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        char timeStr[64];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", 
                localtime(&current->data.timestamp));  // Zamanı okunabilir formatta yazdır
        
        // Mesaj bilgilerini ekrana yazdır
        printf("Zaman: %s\n", timeStr);
        printf("Facility: %s\n", current->data.facility);
        printf("Severity: %s\n", current->data.severity);
        printf("Mesaj: %s\n", current->data.message);
        printf("------------------------\n");
        
        current = current->next;  // Sonraki düğüme geç
    }
}

// Listeyi temizleme fonksiyonu
void freeList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);  // Belleği serbest bırak
    }
}

int main() {
    Node* head = NULL;  // Başlangıçta liste boş
    
    // Ornek syslog mesajlari
    const char* messages[] = {
        "<kern>ERROR:Sistem coktu",
        "<auth>WARNING:Basarisiz giris denemesi",
        "<daemon>INFO:Servis baslatildi",
        "<syslog>DEBUG:Yapilandirma dosyasi yuklendi"
    };
    
    // Mesajları listeye ekle
    for (int i = 0; i < 4; i++) {
        SyslogData data = parseSyslogMessage(messages[i]);  // Mesajı ayrıştır
        head = addSyslogMessage(head, data);  // Mesajı listeye ekle
    }
    
    // Listeyi yazdır
    printf("Syslog Mesajlari:\n");
    printSyslogList(head);
    
    // Belleği temizle
    freeList(head);
    
    return 0;
}
