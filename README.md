Syslog Mesajları Yönetimi

Bu C programı, syslog mesajlarını ayrıştırarak bir bağlı liste içinde depolayan, listeyi ekrana yazdıran ve belleği temizleyen bir uygulamadır. Syslog mesajları, yazılım uygulamalarının ve sistemlerin hata raporlarını, uyarılarını ve diğer bilgileri loglamak için yaygın olarak kullanılan bir formatı temsil eder. Bu uygulama, bu tür mesajları işlemek için temel bir veri yapısı ve işlevsellik sunar.

Özellikler

1-Syslog Mesajı Ayrıştırma: Syslog mesajları, belirli bir formatta ayrıştırılır. Mesajlar, zaman damgası, facility (kaynak), severity (şiddet seviyesi) ve mesaj içeriğini içerir.

2-Bağlantılı Liste Kullanımı: Syslog mesajları, bağlantılı liste veri yapısında depolanır. Bu sayede, listeye dinamik olarak yeni mesajlar eklenebilir ve gerektiğinde önceki mesajlar kolayca silinebilir.

3-Bağlantılı liste kullanımı, sabit boyutlu dizilere kıyasla daha esnek bir yapı sunar ve belleği etkin bir şekilde yönetmeye olanak tanır. Özellikle programın çalışma zamanında ne kadar veri saklanacağı önceden kestirilemeyeceğinden, bağlantılı liste bu tür dinamik veri yapıları için ideal bir çözümdür.

4-Zaman Damgası Formatı: Mesajların zaman damgası, okunabilir bir tarih-saat formatına dönüştürülür.

5-Bellek Yönetimi: Program, bellek sızıntılarını önlemek amacıyla bağlı listeyi işlerken uygun bellek yönetimini sağlar.

Kullanım

1-Programda yer alan syslog mesajları, <facility>severity:message formatında yazılmıştır.

2-Syslog mesajları parseSyslogMessage fonksiyonu ile ayrıştırılır ve bu veriler, bir bağlı listeye eklenir.

3-Program, bağlı listedeki tüm mesajları ekrana yazdırır.

4-Program, çalıştığında belleği serbest bırakır.

Kod Yapısı

1-SyslogData: Syslog mesajını temsil eden yapı. İçinde zaman damgası, facility, severity ve mesaj bilgilerini tutar.

2-Node: Bağlantılı liste düğümünü temsil eden yapı. Her düğüm bir syslog mesajı ve sonraki düğüme işaretçiyi içerir.

3-createNode: Yeni bir düğüm oluşturur.

4-addSyslogMessage: Yeni bir syslog mesajını listeye ekler.

5-parseSyslogMessage: Syslog mesajını ayrıştırarak ilgili verilere dönüştürür.

6-printSyslogList: Listeyi ekrana yazdırır.

7-freeList: Listeyi bellekten serbest bırakır.

Derleme ve Çalıştırma

1-Kodunuzu bir dosyaya kaydedin (örneğin, syslog.c).

2-Terminali açın ve aşağıdaki komutu kullanarak derleyin:
#gcc -o syslog syslog.c

3-Derlenen programı çalıştırın:
#./syslog

Gereksinimler
C derleyicisi (GCC önerilir)

Standart C kütüphaneleri (stdio.h, stdlib.h, string.h, time.h)

Katkı

Bu proje açık kaynaklıdır. Katkı sağlamak isterseniz, pull request gönderebilir veya sorunları bildirebilirsiniz.
