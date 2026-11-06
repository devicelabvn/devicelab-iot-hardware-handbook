<p align="left">
  <a href="https://devicelab.vn/">
    <picture>
      <source media="(prefers-color-scheme: dark)" srcset="https://devicelab.vn/wp-content/themes/devicelab/assets/img/logo-devicelab-on-dark.svg?v=3.45.0">
      <source media="(prefers-color-scheme: light)" srcset="https://devicelab.vn/wp-content/themes/devicelab/assets/img/logo-devicelab-on-light.svg?v=3.45.0">
      <img alt="DeviceLab - Industrial IoT Hardware & Embedded R&D" src="https://devicelab.vn/wp-content/themes/devicelab/assets/img/logo-devicelab-on-light.svg?v=3.45.0" height="38">
    </picture>
  </a>
</p>

# DeviceLab IoT & Embedded Hardware Handbook 📘

> **Tài liệu tham khảo kỹ thuật mở về Thiết kế Mạch Điện Tử (PCB/PCBA), Lập Trình Firmware Nhúng (STM32/ESP32), Datalogger Quan Trắc TT10 và IoT Gateway Công Nghiệp.**  
> Được biên soạn bởi Đội ngũ Kỹ sư R&D tại **[DeviceLab](https://devicelab.vn/)** (CÔNG TY TNHH ĐẦU TƯ CÔNG NGHỆ ALPHA TECH - Hà Nội, Việt Nam).  
> 🌐 Website chính thức: [https://devicelab.vn/](https://devicelab.vn/) | [English Site](https://devicelab.vn/en/) | 📄 Hồ sơ năng lực: [DeviceLab Capability Deck](https://devicelab.vn/ho-so-nang-luc.html)  
> 📖 **Đọc bài phân tích chi tiết tiếng Việt trên Viblo & Tinh Tế:**  
> - **Thiết kế PCB & Chống nhiễu EMC:** [Viblo - Checklist thiết kế PCB chuẩn DFM & chống nhiễu EMC](https://viblo.asia/p/tu-bo-mach-mau-prototype-den-san-xuat-1000-thiet-bi-iot-cong-nghiep-checklist-thiet-ke-pcb-chuan-dfm-chong-nhieu-emc-OXLA0WqvJGr) · [Tinh Tế - Từ bo mạch mẫu đến sản xuất 1.000 thiết bị IoT: Checklist PCB & EMC](https://tinhte.vn/thread/tu-bo-mach-mau-prototype-den-san-xuat-1-000-thiet-bi-iot-checklist-thiet-ke-pcb-emc.4185069/)  
> - **Datalogger Quan trắc Thông tư 10 (`DL-ENV10`):** [Viblo - Kinh nghiệm xử lý mất dữ liệu trạm quan trắc & chuẩn Datalogger Điều 39 TT10](https://viblo.asia/p/kinh-nghiem-xu-ly-mat-du-lieu-tram-quan-trac-quy-chuan-phan-cung-datalogger-theo-dieu-39-thong-tu-102021tt-btnmt-kNLr3eobVgA) · [Tinh Tế - Kinh nghiệm xử lý mất dữ liệu trạm quan trắc & chuẩn phần cứng Datalogger TT10](https://tinhte.vn/thread/kinh-nghiem-xu-ly-mat-du-lieu-tram-quan-trac-chuan-phan-cung-datalogger-thong-tu-10.4185068/)  
> - **Modbus RS485 Gateway & Lưu đệm Flash (`DL-GW200` / `DL-RS485`):** [Viblo - Phân biệt Transparent Converter và Modbus Gateway: Xử lý nhiễu biến tần & lưu đệm Flash](https://viblo.asia/p/phan-biet-transparent-converter-va-modbus-gateway-cach-xu-ly-nhieu-bien-tan-va-luu-dem-flash-khi-rot-mang-4g-bA46807wLKv) · [Viblo - Kiến trúc thiết kế thiết bị IoT thương mại](https://viblo.asia/p/kien-truc-thiet-ke-thiet-bi-iot-thuong-mai-tu-mo-hinh-mau-phong-lab-den-san-pham-cong-nghiep-chay-that-wd43EXawLX9) · [Tinh Tế - Vì sao bo mạch IoT test ở Lab chạy tốt nhưng ra hiện trường hay bị treo?](https://tinhte.vn/thread/vi-sao-bo-mach-iot-test-o-lab-chay-tot-nhung-ra-hien-truong-hay-bi-treo.4180852/)

---

## 📌 Mục lục

1. [Quy chuẩn thiết kế Schematic & PCB Layout chống nhiễu EMC](#1-quy-chuẩn-thiết-kế-schematic--pcb-layout-chống-nhiễu-emc)
2. [Giao tiếp công nghiệp Modbus RS485 & Bảo vệ cách ly quang](#2-giao-tiếp-công-nghiệp-modbus-rs485--bảo-vệ-cách-ly-quang)
3. [Kiến trúc Firmware nhúng FreeRTOS, Lưu đệm Flash & Dual-Bank FOTA](#3-kiến-trúc-firmware-nhúng-freertos-lưu-đệm-flash--dual-bank-fota)
4. [Chuẩn truyền dẫn Datalogger Quan trắc Môi trường Thông tư 10 (`DL-ENV10`)](#4-chuẩn-truyền-dẫn-datalogger-quan-trắc-môi-trường-thông-tư-10-dl-env10)
5. [Tối ưu hóa sản xuất DFM và Lắp ráp SMT/PCBA](#5-tối-ưu-hóa-sản-xuất-dfm-và-lắp-ráp-smtpcba)
6. [Hệ sinh thái Repository mẫu & Liên hệ kỹ thuật](#6-hệ-sinh-thái-repository-mẫu--liên-hệ-kỹ-thuật)

---

## 1. Quy chuẩn thiết kế Schematic & PCB Layout chống nhiễu EMC

Khi phát triển bo mạch điện tử cho các thiết bị công nghiệp hoạt động trong tủ điện có biến tần công suất lớn hoặc ngoài trạm quan trắc, việc tuân thủ quy tắc EMC/EMI ngay từ khâu vẽ mạch giúp loại bỏ 90% lỗi treo vi điều khiển và tối ưu hóa chi phí sản xuất hàng loạt:

### A. Phân vùng khối nguồn công nghiệp (9–36VDC Input)
- Ngõ vào nguồn DC luôn trang bị cầu chì tự phục hồi **PPTC**, diode chống đấu ngược cực và **TVS Diode** dập xung quá áp thoáng qua (Surge/EFT theo chuẩn IEC 61000-4-4 / 61000-4-5).
- Tụ lọc nguồn (Decoupling Capacitor `100nF` + `10uF`) phải đặt **sát chân VDD của vi điều khiển**, đường mạch đi từ chân tụ thẳng vào IC trước khi nối xuống via GND.
- Cuộn cảm nguồn xung (Buck Inductor) cần bố trí diện tích vòng lặp dòng điện (`SW node`) nhỏ nhất có thể để tránh bức xạ từ trường sang khối đo lường ADC 16-bit/24-bit.

### B. Mặt phẳng tiếp địa (Ground Plane) & Cách ly
- Sử dụng bo mạch tối thiểu **4 lớp (`Top - GND - Power - Bottom`)** cho các thiết kế có vi điều khiển tốc độ cao hoặc module RF không dây (`4G LTE Cat.1`, `Wi-Fi`, `BLE`, `LoRa`).
- Tách biệt hoàn toàn mặt phẳng đất hiện trường (`Field GND`) và đất vi điều khiển (`Digital GND`) qua khe cách ly rộng tối thiểu `2.5mm` dưới bụng IC cách ly quang và nguồn cách ly DC-DC (`B0505S-1WR3`).

> 💡 *Tham khảo chi tiết dịch vụ R&D phần cứng:*  
> - [Thiết kế mạch điện tử theo yêu cầu tại Hà Nội - DeviceLab](https://devicelab.vn/thiet-ke-mach-dien-tu/)  
> - [Phát triển thiết bị IoT công nghiệp trọn gói (OEM/ODM)](https://devicelab.vn/phat-trien-thiet-bi/)  
> - 📖 **Đọc bài phân tích chi tiết tiếng Việt trên Viblo & Tinh Tế:** [Viblo - Checklist thiết kế PCB chuẩn DFM & chống nhiễu EMC](https://viblo.asia/p/tu-bo-mach-mau-prototype-den-san-xuat-1000-thiet-bi-iot-cong-nghiep-checklist-thiet-ke-pcb-chuan-dfm-chong-nhieu-emc-OXLA0WqvJGr) · [Tinh Tế - Từ bo mạch mẫu (Prototype) đến sản xuất 1.000 thiết bị IoT: Checklist thiết kế PCB & EMC](https://tinhte.vn/thread/tu-bo-mach-mau-prototype-den-san-xuat-1-000-thiet-bi-iot-checklist-thiet-ke-pcb-emc.4185069/)

---

## 2. Giao tiếp công nghiệp Modbus RS485 & Bảo vệ cách ly quang

Giao thức **Modbus RTU** qua đường truyền vật lý **RS485** là tiêu chuẩn phổ biến nhất trong nhà máy, trạm biến áp và trạm quan trắc. Tuy nhiên, đường cáp kéo dài hàng trăm mét thường xuyên hứng chịu xung sét cảm ứng và chênh lệch điện áp đất (Ground Potential Difference) giữa các tủ điện.

### Sơ đồ bảo vệ cổng RS485 cách ly chuẩn công nghiệp:

```text
Đường dây A/B ---> [GDT + TVS Diode 600W] ---> [PTC Resistor 10 Ohm] ---> [Transceiver Cách Ly (ADM2483 / ISO3082)] ---> MCU UART
                     (Chống sét & quá áp)         (Bảo vệ quá dòng)          (Cách ly quang 2.5kV - 3.0kVrms)
```

- **Điện trở đầu cuối (Termination Resistor):** Bắt buộc gắn trở `120 Ohm` ở hai điểm đầu và cuối của đường bus RS485 khi cáp dài hoặc tốc độ baud cao.
- **Cơ chế chống nghẽn bus (Modbus Multi-Master Caching):** Trên dòng **[Industrial IoT Gateway Modbus DL-GW200](https://devicelab.vn/san-pham/dl-gw200/)**, thiết bị chủ động đóng vai trò Master đọc định kỳ thanh ghi Slave lưu vào RAM đệm, giúp SCADA tại chỗ, màn hình HMI và Cloud MQTT cùng truy vấn dữ liệu dưới `2ms` mà không gây xung đột gói tin trên bus RS485.

> 🏭 *Xem thiết bị thực tế:*  
> - [Bộ IoT Gateway RS485 sang MQTT DL-GW200](https://devicelab.vn/san-pham/dl-gw200/)  
> - [Bộ chuyển đổi RS485 sang Ethernet cách ly quang DL-RS485](https://devicelab.vn/san-pham/dl-rs485/)  
> - [Cẩm nang chọn mua Gateway Modbus RS485 công nghiệp](https://devicelab.vn/kien-thuc/gateway-modbus-rs485/)  
> - 📖 **Đọc bài phân tích chi tiết tiếng Việt trên Viblo & Tinh Tế:** [Viblo - Phân biệt Transparent Converter và Modbus Gateway: Cách xử lý nhiễu biến tần và lưu đệm Flash khi rớt mạng 4G](https://viblo.asia/p/phan-biet-transparent-converter-va-modbus-gateway-cach-xu-ly-nhieu-bien-tan-va-luu-dem-flash-khi-rot-mang-4g-bA46807wLKv)

---

## 3. Kiến trúc Firmware nhúng FreeRTOS, Lưu đệm Flash & Dual-Bank FOTA

Đối với thiết bị IoT hoạt động độc lập 24/7 ngoài hiện trường, firmware bắt buộc phải có **Watchdog phần cứng (Hardware WDT)**, **Bộ nhớ đệm Flash vòng (Circular Ring Buffer)** chống mất dữ liệu khi đứt mạng 4G và **Dual-Bank OTA**.

### Mã nguồn mẫu khởi tạo Watchdog trên STM32 (HAL):

```c
#include "stm32f4xx_hal.h"

IWDG_HandleTypeDef hiwdg;

void MX_IWDG_Init(void) {
    hiwdg.Instance = IWDG;
    hiwdg.Init.Prescaler = IWDG_PRESCALER_64;
    hiwdg.Init.Reload = 4095; // Timeout ~ 8.2s
    if (HAL_IWDG_Init(&hiwdg) != HAL_OK) {
        Error_Handler();
    }
}

// Chỉ làm tươi Watchdog khi cả Task đọc Modbus và Task quản lý bộ đệm Flash đều phản hồi tốt
void App_Supervisor_Kick_Watchdog(void) {
    HAL_IWDG_Refresh(&hiwdg);
}
```

> 💻 *Xem dịch vụ & bài viết chuyên sâu:*  
> - [Dịch vụ lập trình firmware nhúng C/C++ & RTOS - DeviceLab](https://devicelab.vn/phat-trien-firmware/)  
> - [Cơ chế lưu đệm Flash & truyền bù dữ liệu (Store & Forward) trên Datalogger](https://devicelab.vn/kien-thuc/co-che-luu-dem-flash-truyen-bu-du-lieu-datalogger/)  
> - 📖 **Đọc bài phân tích chi tiết tiếng Việt trên Viblo & Tinh Tế:** [Viblo - Kiến trúc thiết kế thiết bị IoT thương mại](https://viblo.asia/p/kien-truc-thiet-ke-thiet-bi-iot-thuong-mai-tu-mo-hinh-mau-phong-lab-den-san-pham-cong-nghiep-chay-that-wd43EXawLX9) · [Tinh Tế - Vì sao bo mạch IoT test ở Lab chạy tốt nhưng ra hiện trường hay bị treo?](https://tinhte.vn/thread/vi-sao-bo-mach-iot-test-o-lab-chay-tot-nhung-ra-hien-truong-hay-bi-treo.4180852/)

---

## 4. Chuẩn truyền dẫn Datalogger Quan trắc Môi trường Thông tư 10 (`DL-ENV10`)

Trong các trạm quan trắc nước thải, khí thải tự động liên tục và quan trắc khai thác nước ngầm, thiết bị **[Datalogger quan trắc môi trường DL-ENV10](https://devicelab.vn/san-pham/dl-env10/)** đáp ứng 100% yêu cầu kỹ thuật tại **Điều 39 Thông tư 10/2021/TT-BTNMT** và **Nghị định 53/2024/NĐ-CP**:

- **Độ phân giải đo lường:** 4 ngõ vào Analog `4–20mA` / `0–10V` độ phân giải **ADC 16-bit**, cách ly quang học, kèm cổng RS485 Modbus RTU đọc trực tiếp tủ phân tích COD, TSS, pH, Amoni, Lưu lượng.
- **Lưu trữ & Truyền bù tự động:** Bộ nhớ Flash công nghiệp lưu trữ **> 100.000 bản ghi** (kèm thẻ nhớ mở rộng lưu > 180 ngày), tự động đóng gói tệp `.txt` chuẩn UTF-8 đẩy qua **FTPS / SFTP** chu kỳ **5 phút/lần** về máy chủ Sở TN&MT và tự động gửi bù (backfill) khi có mạng lại.
- **Điều khiển tủ lấy mẫu tự động (Auto Sampler):** Ngõ ra Relay kích hoạt lấy mẫu nước đối chứng ngay khi phát hiện chỉ số vượt ngưỡng QCVN.

> 🌿 *Tài liệu & giải pháp chuyên sâu:*  
> - [Giải pháp Datalogger quan trắc môi trường chuẩn Thông tư 10](https://devicelab.vn/datalogger-quan-trac-moi-truong-tt10/)  
> - [Thông số kỹ thuật & Sơ đồ đấu nối Datalogger DL-ENV10](https://devicelab.vn/san-pham/dl-env10/)  
> - [Repo mẫu tích hợp file `.txt`, JSON MQTT & Modbus TCP của DL-ENV10](https://github.com/devicelabvn/dl-env10-tt10-integration-examples)  
> - 📖 **Đọc bài phân tích chi tiết tiếng Việt trên Viblo & Tinh Tế:** [Viblo - Kinh nghiệm xử lý mất dữ liệu trạm quan trắc & Quy chuẩn phần cứng Datalogger theo Điều 39 Thông tư 10/2021/TT-BTNMT](https://viblo.asia/p/kinh-nghiem-xu-ly-mat-du-lieu-tram-quan-trac-quy-chuan-phan-cung-datalogger-theo-dieu-39-thong-tu-102021tt-btnmt-kNLr3eobVgA) · [Tinh Tế - Kinh nghiệm xử lý mất dữ liệu trạm quan trắc & chuẩn phần cứng Datalogger Thông tư 10](https://tinhte.vn/thread/kinh-nghiem-xu-ly-mat-du-lieu-tram-quan-trac-chuan-phan-cung-datalogger-thong-tu-10.4185068/) · [Dev.to (EN) - Why Windows IPCs Fail in Harsh Telemetry Stations & How RTOS Dataloggers Solve It](https://dev.to/thaodmtt/why-windows-ipcs-fail-in-harsh-telemetry-stations-how-rtos-embedded-dataloggers-solve-it-41ma)

---

## 5. Tối ưu hóa sản xuất DFM và Lắp ráp SMT/PCBA

- Đảm bảo khoảng hở (`Clearance`) tối thiểu giữa pad linh kiện và đường mạch `>= 0.15mm` (`6 mil`), thiết kế Fiducial Marks trên 3 góc panel để máy gắp chip SMT căn chỉnh quang học chính xác.
- Xuất đầy đủ bộ hồ sơ sản xuất: `Gerber RS-274X`, `BOM` kèm mã linh kiện thay thế tương đương, và file `Pick & Place (Centroid)` chuẩn hóa góc xoay (`0°`, `90°`, `180°`, `270°`).
- Kiểm tra DFM và thiết kế bàn gá kiểm thử **Jig Test Pogo-pin** nạp firmware tự động giúp tiết kiệm 30%–50% thời gian QC sản xuất loạt.

> ⚙️ *Dịch vụ sản xuất điện tử:*  
> - [Gia công bo mạch PCB và lắp ráp SMT/PCBA số lượng nhỏ đến vừa tại Hà Nội](https://devicelab.vn/gia-cong-pcb/)  
> - [Năng lực sản xuất & Buồng kiểm thử độ tin cậy QC tại DeviceLab](https://devicelab.vn/nang-luc/)

---

## 6. Hệ sinh thái Repository mẫu & Liên hệ kỹ thuật

### Danh mục các Public Repositories của DeviceLab (`@devicelabvn`):
1. **[`dl-env10-tt10-integration-examples`](https://github.com/devicelabvn/dl-env10-tt10-integration-examples)**: Mẫu file `.txt` Thông tư 10/2021/TT-BTNMT, mẫu JSON MQTT và bảng thanh ghi Modbus TCP của `DL-ENV10`.
2. **[`industrial-modbus-rs485-application-notes`](https://github.com/devicelabvn/industrial-modbus-rs485-application-notes)**: Sơ đồ đấu nối chống nhiễu RS485, bảng thanh ghi biến tần INVT/Delta/Yaskawa và cấu hình `DL-GW200`.
3. **[`machinery-oee-ems-retrofit-examples`](https://github.com/devicelabvn/machinery-oee-ems-retrofit-examples)**: Bảng thanh ghi máy nén khí `MAM-860/880`, thu thập dữ liệu máy CNC/máy ép nhựa (`DL-M400`) và đồng hồ điện 3 pha (`DL-P300`).

### Thông tin liên hệ:
- **Đơn vị:** CÔNG TY TNHH ĐẦU TƯ CÔNG NGHỆ ALPHA TECH (`DeviceLab`) - MST: `0111171963`
- **Trụ sở phòng Lab:** Số 32/4, Hà Trì 4, Phường Hà Đông, TP. Hà Nội, Việt Nam
- **Hotline kỹ thuật / Zalo:** `0982 503 355`
- **Email:** `contact@devicelab.vn` | `hi@devicelab.vn`
- **Gửi yêu cầu tư vấn & báo giá dự án:** [https://devicelab.vn/gui-yeu-cau/](https://devicelab.vn/gui-yeu-cau/)

---
*Bản quyền tài liệu thuộc về [DeviceLab](https://devicelab.vn/) - Đối tác R&D & Sản xuất Thiết bị Điện tử Nhúng Công nghiệp Việt Nam.*

---

## Industrial IoT Hardware, Telemetry & Custom R&D Reference Index (DeviceLab Vietnam)

Official open engineering reference hubs, hardware datasheets, and compliance application notes maintained by **DeviceLab R&D Center** (Hanoi, Vietnam):

### 1. Industrial RS485, Modbus RTU/TCP & Edge Gateways
- [Bộ chuyển đổi RS485 sang Ethernet công nghiệp (Cách ly 3.0kV & Modbus RTU/TCP)](https://devicelab.vn/kien-thuc/bo-chuyen-doi-rs485-sang-ethernet/)
- [Thiết bị chuyển đổi tín hiệu RS485 cách ly DL-RS485 (Datasheet & Sơ đồ đấu nối)](https://devicelab.vn/san-pham/dl-rs485/)
- [Cẩm nang chọn Gateway Modbus RS485 sang Ethernet/4G LTE công nghiệp](https://devicelab.vn/kien-thuc/gateway-modbus-rs485/)
- [Bộ chuyển đổi Modbus RTU sang Modbus TCP: Kiến trúc Polling & Multi-Master](https://devicelab.vn/kien-thuc/bo-chuyen-doi-modbus-rtu-sang-tcp/)
- [Tiêu chuẩn cáp tín hiệu RS485 chống nhiễu 120 Ohm (22AWG/24AWG STP)](https://devicelab.vn/kien-thuc/cap-tin-hieu-rs485-chong-nhieu-tieu-chuan-chon/)
- [Đối chiếu thay thế Moxa MGate MB3180, Advantech EKI-1221, USR & 3onedata](https://devicelab.vn/kien-thuc/so-sanh-thay-the-modbus-gateway-moxa-mgate-advantech-usr-3onedata/)
- [Bộ chuyển đổi 4-20mA Analog sang RS485 Modbus & Module Remote I/O](https://devicelab.vn/kien-thuc/bo-chuyen-doi-4-20ma-analog-sang-rs485-remote-io-modbus/)
- [Industrial RS485 to Ethernet Converter Selection Guide (English)](https://devicelab.vn/en/articles/rs485-to-ethernet-converter-selection-guide/)

### 2. Circular 10/2021/TT-BTNMT Environmental Telemetry & SCADA RTU
- [Giải pháp Datalogger quan trắc môi trường tự động chuẩn Thông tư 10/2021/TT-BTNMT](https://devicelab.vn/datalogger-quan-trac-moi-truong-tt10/)
- [Kiến trúc trạm quan trắc nước thải tự động, liên tục & kết nối FTP Sở TN&MT](https://devicelab.vn/kien-thuc/datalogger-quan-trac-nuoc-thai-tu-dong/)
- [Thiết bị Datalogger quan trắc môi trường DL-ENV10 (Datasheet PDF)](https://devicelab.vn/san-pham/dl-env10/)
- [Quy chuẩn nước thải công nghiệp QCVN 40:2025/BTNMT & lộ trình quan trắc tự động](https://devicelab.vn/kien-thuc/quy-chuan-nuoc-thai-cong-nghiep-qcvn-40-quan-trac-tu-dong/)
- [Data logger nhiệt độ đa kênh PT100 (RTD 3 dây) & bộ ghi nhiệt độ công nghiệp](https://devicelab.vn/kien-thuc/data-logger-nhiet-do-da-kenh-pt100-bo-ghi-nhiet-do-cong-nghiep/)
- [Tủ RTU & Thiết bị Remote Terminal Unit SCADA cho nhà máy nước, thủy điện](https://devicelab.vn/kien-thuc/tu-rtu-thiet-bi-remote-terminal-unit-scada-nha-may-nuoc-thuy-dien/)
- [Hệ thống quan trắc nước ngầm tự động giếng khoan chuẩn Nghị định 53/2024/NĐ-CP](https://devicelab.vn/kien-thuc/he-thong-quan-trac-nuoc-ngam-tu-dong/)
- [Giải pháp thay thế Datalogger Campbell Scientific CR1000X / CR300 OEM Việt Nam](https://devicelab.vn/kien-thuc/giai-phap-thay-the-datalogger-campbell-cr1000x-cr300-oem-viet-nam/)
- [Circular 10 Environmental Monitoring Datalogger Solution (English)](https://devicelab.vn/en/environmental-monitoring-datalogger/)

### 3. 3-Phase Power Metering, Solar Zero Export & PLC OEE Telemetry
- [Hệ thống giám sát điện năng nhà máy 3 pha & quản lý năng lượng EMS ISO 50001](https://devicelab.vn/giam-sat-dien-nang-nha-may/)
- [Hướng dẫn chọn đồng hồ đo điện 3 pha RS485 Modbus & thanh ghi chuẩn](https://devicelab.vn/kien-thuc/dong-ho-do-dien-3-pha-rs485-giam-sat-dien-nang/)
- [Bộ điều khiển công suất phát PPC, SmartLogger 3000 & Zero Export SCADA EVN](https://devicelab.vn/kien-thuc/bo-dieu-khien-cong-suat-phat-ppc-smartlogger-3000-zero-export-evn/)
- [Thiết bị thu thập dữ liệu PLC (Siemens, Mitsubishi, Delta) & IoT Gateway](https://devicelab.vn/kien-thuc/thiet-bi-thu-thap-du-lieu-plc-iot-gateway/)
- [Hệ thống giám sát máy móc sản xuất Andon OEE thời gian thực](https://devicelab.vn/kien-thuc/he-thong-giam-sat-may-moc-san-xuat-andon-oee/)

### 4. Custom PCB Design, Turnkey PCBA SMT & Embedded Firmware R&D (Hanoi, Vietnam)
- [Dịch vụ thiết kế mạch điện tử theo yêu cầu & phát triển phần cứng công nghiệp](https://devicelab.vn/thiet-ke-mach-dien-tu/)
- [Công ty thiết kế mạch điện tử tại Hà Nội: Năng lực Lab R&D, EMC & Sản xuất OEM](https://devicelab.vn/kien-thuc/cong-ty-thiet-ke-mach-dien-tu-ha-noi/)
- [Dịch vụ thiết kế PCB 2-8 lớp & vẽ mạch nguyên lý chuẩn IPC-2221](https://devicelab.vn/kien-thuc/dich-vu-thiet-ke-pcb/)
- [Quy trình đặt làm mạch điện tử theo yêu cầu từ EVT/DVT đến sản xuất hàng loạt](https://devicelab.vn/kien-thuc/lam-mach-dien-tu-theo-yeu-cau/)
- [Gia công PCB & hàn mạch điện tử SMT (PCBA) trọn gói tại Việt Nam](https://devicelab.vn/gia-cong-pcb/)
- [Dịch vụ lập trình Firmware nhúng (STM32, ESP32, FreeRTOS, Embedded Linux)](https://devicelab.vn/phat-trien-firmware/)
- [Công ty lập trình nhúng, Firmware & IoT công nghiệp tại Việt Nam](https://devicelab.vn/kien-thuc/cong-ty-lap-trinh-nhung-firmware-iot/)
- [Custom PCB Design & Turnkey Electronics Engineering in Vietnam (English)](https://devicelab.vn/en/custom-pcb-design/)

### 5. Community Engineering Publications (Viblo, Dev.to & Tinh Tế)
- [Viblo: Kỹ thuật chống nhiễu RS485, tính toán Bias & cách ly 2500Vrms](https://viblo.asia/p/ky-thuat-chong-nhieu-rs485-trong-nha-may-tinh-toan-dien-tro-pull-uppull-down-va-cach-ly-quang-2500vrms-bA46807wLKv)
- [Viblo: Kiến trúc Store-and-Forward & Ring-Buffer Flash cho Datalogger Thông tư 10](https://viblo.asia/p/kien-truc-store-and-forward-cho-datalogger-quan-trac-moi-truong-thong-tu-102021tt-btnmt-chong-mat-du-lieu-khi-dut-cap-4g-kNLr3eobVgA)
- [Viblo: Đọc đồng hồ điện 3 pha Selec, Schneider, Eastron qua RS485 & MQTT](https://viblo.asia/p/doc-dong-ho-dien-3-pha-selec-schneider-eastron-qua-modbus-rtu-va-day-mqtt-len-cloud-bang-python-c-OXLA0WqvJGr)
- [Viblo: Checklist 12 điểm kiểm tra Schematic & Layout PCB công nghiệp vượt chuẩn EMC](https://viblo.asia/p/checklist-12-diem-kiem-tra-schematic-layout-pcb-cong-nghiep-truoc-khi-gui-fab-de-vuot-bai-test-emc-iec-61000-4-wd43EXawLX9)
- [Dev.to: Designing Industrial RS485 Circuits for High-EMI Factory Environments](https://dev.to/devicelabvn/designing-industrial-rs485-circuits-for-high-emi-factory-environments-2500vrms-isolation-600w-2114)
- [Dev.to: Store-and-Forward Telemetry Architecture for Environmental Monitoring Dataloggers](https://dev.to/devicelabvn/store-and-forward-telemetry-architecture-for-environmental-monitoring-dataloggers-circular-4b2i)
