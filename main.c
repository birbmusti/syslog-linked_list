#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Syslog mesaji icin yapi
typedef struct {
    time_t timestamp;        // Mesajın zaman damgası
    char facility[32];       // Mesajın kaynağı
    char severity[32];       // Mesajın şiddeti
    char message[256];       // Mesaj içeriği
} SyslogData;  // Syslog verilerini tutan yapı

// Bagli liste dugumu yapisi
typedef struct Node {
    SyslogData data;         // Düğümde tutulan syslog verisi
    struct Node* next;       // Sonraki düğüme işaretçi
} Node;  // Bağlantılı liste düğümü yapısı

// Yeni dugum olusturma fonksiyonu
Node* createNode(SyslogData data) {
    Node* newNode = (Node*)malloc(sizeof(Node));  // Bellekten yeni düğüm için yer ayır
    if (newNode == NULL) {
        printf("Bellek tahsis hatasi!\n");  // Bellek hatası kontrolü
        exit(1);  // Bellek hatası durumunda çık
    }
    newNode->data = data;  // Düğüm verisini ata
    newNode->next = NULL;   // Yeni düğümün sonraki düğümünü NULL yap
    return newNode;         // Yeni düğümü döndür
}

// Listeye yeni mesaj ekleme fonksiyonu
Node* addSyslogMessage(Node* head, SyslogData data) {
    Node* newNode = createNode(data);  // Yeni düğüm oluştur
    
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
           data.facility,  // facility'i ayıkla
           data.severity,  // severity'i ayıkla
           data.message);  // Mesaj içeriğini ayıkla
    
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
        "<kern>ERROR:Sistem coktu",  // Mesaj 1
        "<auth>WARNING:Basarisiz giris denemesi",  // Mesaj 2
        "<daemon>INFO:Servis baslatildi",  // Mesaj 3
        "<syslog>DEBUG:Yapilandirma dosyasi yuklendi"  // Mesaj 4
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
