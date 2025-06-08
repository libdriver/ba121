[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BA121
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ba121/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Ein spezieller Chip zur Erfassung der Leitfähigkeit und Wassertemperatur wässriger Lösungen, der hochpräzise Schwingkreise, Analog-Digital-Wandler und Gleitkomma-Rechenwerke integriert. Durch den Einsatz patentierter Leitfähigkeits-Umwandlungsalgorithmen und Temperaturkorrekturalgorithmen lässt sich die Leitfähigkeit wässriger Lösungen schnell erfassen. Zudem ist eine automatische Temperaturkorrektur über einen weiten Temperaturbereich möglich, um Messfehler durch temperaturabhängige Leitfähigkeitsänderungen zu reduzieren.

LibDriver BA121 ist ein vollfunktionaler Treiber für BA121, der von LibDriver eingeführt wurde. Er bietet Funktionen zur Messung der Leitfähigkeit, Temperatur und anderer Parameter. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver BA121-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver BA121 UART.

/test enthält den Testcode des LibDriver BA121-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver BA121-Beispielcode.

/doc enthält das LibDriver BA121-Offlinedokument.

/Datenblatt enthält BA121-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige UART-Schnittstellenvorlage und stellen Sie Ihren Plattform-UART-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_ba121_basic.h"

uint8_t res;
uint16_t conductivity_us_cm;
float temperature;
uint32_t i;

/* init */
res = ba121_basic_init();
if (res != 0)
{
    return 1;
}

...
    
for (i = 0; i < 3; i++)
{
    /* delay 1000ms */
    ba121_interface_delay_ms(1000);

    /* read */
    res = ba121_basic_read(&conductivity_us_cm, &temperature);
    if (res != 0)
    {
        ba121_interface_debug_print("ba121: read failed.\n");
        (void)ba121_basic_deinit();

        return 1;
    }

    /* output */
    ba121_interface_debug_print("ba121: %d/%d.\n", i + 1, times);
    ba121_interface_debug_print("ba121: conductivity is %d uS/cm.\n", conductivity_us_cm);
    ba121_interface_debug_print("ba121: temperature is %0.2fC.\n", temperature);
    
    ...
}

...
    
/* deinit */
(void)ba121_basic_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/ba121/index.html](https://www.libdriver.com/docs/ba121/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.