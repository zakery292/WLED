# WLED ESP-IDF Porting Guide

## Goal
Port WLED to compile with ESP-IDF 5.5 + Arduino-ESP32 3.x, targeting ESP32-P4.

## Status: ✅ BUILD SUCCESSFUL

WLED compiles and links for ESP32-P4 using pure ESP-IDF 5.5!

**Binary:** `build/WLED.bin` (~1.4 MB, 27% partition free)

---

## ✅ Completed

### Infrastructure
- [x] ESP-IDF project structure (`CMakeLists.txt`, `main/`)
- [x] Arduino as IDF component via component manager (v3.3.3)
- [x] FastLED 3.10.3 component (P4 compatible, native RMT5)
- [x] NeoPixelBus component (RMT only, I2S disabled for P4)
- [x] Aircoookie's ESPAsyncWebServer (cloned as component)
- [x] me-no-dev's AsyncTCP (cloned as component)
- [x] AsyncMqttClient component
- [x] Partition table and sdkconfig.defaults
- [x] Disabled IR and ESP-NOW (P4 has no built-in WiFi)
- [x] Generated HTML UI files via `npm run build`

### Arduino 3.x API Migration
- [x] LEDC API: `ledcSetup()`/`ledcAttachPin()` → `ledcAttach()`
- [x] LEDC detach: `ledcDetachPin()` → `ledcDetach()`
- [x] FreeRTOS types: `xSemaphoreHandle` → `SemaphoreHandle_t`
- [x] LEDC mutex now internal in Arduino 3.x
- [x] P4 LEDC register workaround using `ledc_set_duty()` HAL
- [x] mbedtls API: `_ret` suffix removed in newer versions

### Library Conflicts Fixed
- [x] SPI host naming: Added `VSPI_HOST=SPI3_HOST` compat for P4
- [x] Network.h conflict: Renamed to WLEDNetwork.h
- [x] NetworkClass conflict: Renamed to WLEDNetworkClass
- [x] ArduinoJson: Using bundled v6 (with Aircoookie ESPAsyncWebServer)
- [x] ESPAsyncWebServer: Using Aircoookie fork (WLED native)
- [x] SPIFFSEditor stub header
- [x] bus_wrapper.h: Added P4 exclusions for I2S methods

---

## 📁 Files Modified/Created

| File | Status | Notes |
|------|--------|-------|
| `CMakeLists.txt` | ✅ | Project root |
| `main/CMakeLists.txt` | ✅ | Component sources, defs, P4 flags |
| `main/main.cpp` | ✅ | app_main entry |
| `main/idf_component.yml` | ✅ | Dependencies |
| `sdkconfig.defaults` | ✅ | P4 config |
| `partitions.csv` | ✅ | 4MB layout |
| `components/FastLED/CMakeLists.txt` | ✅ | Native IDF |
| `components/NeoPixelBus/CMakeLists.txt` | ✅ | RMT only, no I2S for P4 |
| `components/ESPAsyncWebServer/CMakeLists.txt` | ✅ | Aircoookie fork |
| `components/AsyncTCP/CMakeLists.txt` | ✅ | me-no-dev |
| `components/AsyncMqttClient/CMakeLists.txt` | ✅ | Recursive sources |
| `wled00/bus_manager.cpp` | ✅ | LEDC fixes |
| `wled00/bus_wrapper.h` | ✅ | P4 I2S exclusions |
| `wled00/util.cpp` | ✅ | mbedtls API update |
| `wled00/wled.h` | ✅ | ArduinoJson, network fix |
| `wled00/fcn_declare.h` | ✅ | ArduinoJson |
| `wled00/my_config.h` | ✅ | User config stub |
| `wled00/src/dependencies/network/` | ✅ | Renamed to WLEDNetwork |
| `wled00/src/dependencies/spiffseditor/` | ✅ | Stub header |
| `wled00/src/dependencies/espalexa/Espalexa.h` | ✅ | Updated includes |
| `wled00/src/dependencies/e131/ESPAsyncE131.cpp` | ✅ | Updated includes |
| `wled00/html_*.h` | ✅ | Generated via `npm run build` |

---

## 🎯 Build Commands

```bash
# First time: generate HTML files
npm install
npm run build -- --force

# Build for ESP32-P4
source ~/esp/v5.5.1/esp-idf/export.sh
cd /home/zak/Documents/wled/WLED
idf.py set-target esp32p4
idf.py build

# Flash
idf.py -p /dev/ttyUSB0 flash monitor
```

---

## 📝 Notes

### ESP32-P4-NANO Specifics
- Dual-core RISC-V processor @ 400MHz (HP) + single-core @ 40MHz (LP)
- **WiFi 6 / BT5 via ESP32-C6 coprocessor** (SDIO hosted)
- 32MB PSRAM (stacked in package)
- 16MB NOR Flash (QSPI)
- Internal EMAC with IP101GRI PHY (100Mbps Ethernet)
- Uses RMT5 driver for LED strips (no I2S LED output)
- Different LEDC register layout than classic ESP32
- Requires Arduino-ESP32 3.x (3.3.3 used)
- IR disabled (no compatible library)

### Key Dependencies
- ESP-IDF 5.5.1
- Arduino-ESP32 3.3.3 (component manager)
- ESPAsyncWebServer (Aircoookie fork, cloned)
- AsyncTCP (me-no-dev, cloned)
- AsyncMqttClient (cloned)
- ArduinoJson 6.x (bundled)
- FastLED 3.10.3 (cloned)
- NeoPixelBus (cloned)

### Disabled Features for P4
- IR remote (`WLED_DISABLE_INFRARED`)
- I2S LED output (RMT only)

### Enabled Features for P4-NANO
- WiFi 6 via ESP32-C6 coprocessor (configure in menuconfig)
- ESP-NOW sync (via C6 chip)
- Ethernet 100Mbps (IP101GRI PHY)
- PSRAM 32MB for large LED configurations

### ESP32-P4-NANO Ethernet (IP101GRI)
Ethernet is enabled by default with `WLED_ETH_ESP32P4_NANO`:
- PHY: IP101GRI via RMII
- RMII Pins: TX_EN=GPIO49, TXD0/1=GPIO34/35, RXD0/1=GPIO29/30, CRS_DV=GPIO28
- REF_CLK: GPIO50 (50MHz from PHY's crystal oscillator)
- Management: MDC=GPIO31, MDIO=GPIO52
- PHY Reset: GPIO51

### Known Warnings (non-fatal)
- Deprecated `[=]` lambda capture (C++20 style warning)
- Deprecated `NetworkUDP::flush()` (use `clear()`)
- Orphan `.dtors` sections (linker cosmetic)

---

## 🚀 Next Steps

1. **Test on hardware**: Flash to ESP32-P4 dev board
2. **WiFi**: Configure esp_hosted for external WiFi module
3. **Usermods**: Port any required usermods
4. **IR**: Consider alternative IR library if needed
5. **Optimize**: Enable PSRAM if available on P4 board
