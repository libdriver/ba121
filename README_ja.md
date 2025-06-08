[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver BA121

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/ba121/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

高精度発振回路、アナログ-デジタル変換回路、浮動小数点演算ユニットを集積した、水溶液の導電率と水温を検出する専用チップです。特許取得済みの導電率変換アルゴリズムと温度補正アルゴリズムを用いることで、水溶液の導電率を迅速に検出し、広い温度範囲で自動温度補正を実現することで、温度による導電率の変化による測定誤差を低減します。

LibDriver BA121は、LibDriverがリリースしたBA121のフル機能ドライバです。導電率測定、温度測定などの機能を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver BA121のソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver BA121用のプラットフォームに依存しないUARTバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver BA121ドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver BA121プログラミング例が含まれています。

/ docディレクトリには、LibDriver BA121オフラインドキュメントが含まれています。

/ datasheetディレクトリには、BA121データシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないUARTバステンプレートを参照して、指定したプラットフォームのUARTバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/ba121/index.html](https://www.libdriver.com/docs/ba121/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。