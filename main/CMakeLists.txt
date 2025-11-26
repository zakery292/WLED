# Main component - this wraps the WLED source code
# The actual WLED source is in ../wled00/

idf_component_register(
    SRCS 
        "main.cpp"
        "../wled00/wled.cpp"
        "../wled00/wled_main.cpp"
        "../wled00/alexa.cpp"
        "../wled00/bus_manager.cpp"
        "../wled00/button.cpp"
        "../wled00/cfg.cpp"
        "../wled00/colors.cpp"
        "../wled00/dmx_input.cpp"
        "../wled00/dmx_output.cpp"
        "../wled00/e131.cpp"
        "../wled00/file.cpp"
        "../wled00/FX.cpp"
        "../wled00/FX_fcn.cpp"
        "../wled00/FX_2Dfcn.cpp"
        "../wled00/FXparticleSystem.cpp"
        "../wled00/hue.cpp"
        "../wled00/image_loader.cpp"
        "../wled00/improv.cpp"
        "../wled00/ir.cpp"
        "../wled00/json.cpp"
        "../wled00/led.cpp"
        "../wled00/lx_parser.cpp"
        "../wled00/mqtt.cpp"
        "../wled00/net_debug.cpp"
        "../wled00/network.cpp"
        "../wled00/ntp.cpp"
        "../wled00/ota_update.cpp"
        "../wled00/overlay.cpp"
        "../wled00/palettes.cpp"
        "../wled00/pin_manager.cpp"
        "../wled00/playlist.cpp"
        "../wled00/presets.cpp"
        "../wled00/remote.cpp"
        "../wled00/set.cpp"
        "../wled00/udp.cpp"
        "../wled00/um_manager.cpp"
        "../wled00/usermod.cpp"
        "../wled00/util.cpp"
        "../wled00/wled_eeprom.cpp"
        "../wled00/wled_math.cpp"
        "../wled00/wled_metadata.cpp"
        "../wled00/wled_serial.cpp"
        "../wled00/wled_server.cpp"
        "../wled00/ws.cpp"
        "../wled00/xml.cpp"
        # Internal dependencies
        "../wled00/src/dependencies/e131/ESPAsyncE131.cpp"
        "../wled00/src/dependencies/espalexa/EspalexaDevice.cpp"
        "../wled00/src/dependencies/network/WLEDNetwork.cpp"
        "../wled00/src/dependencies/time/DateStrings.cpp"
        "../wled00/src/dependencies/time/DS1307RTC.cpp"
        "../wled00/src/dependencies/time/Time.cpp"
        "../wled00/src/dependencies/timezone/Timezone.cpp"
        "../wled00/src/dependencies/dmx/ESPDMX.cpp"
        "../wled00/src/dependencies/dmx/SparkFunDMX.cpp"
    INCLUDE_DIRS 
        "."
        "../wled00"
        "../wled00/src/dependencies/json"
        "../wled00/src/dependencies/e131"
        "../wled00/src/dependencies/espalexa"
        "../wled00/src/dependencies/network"
        "../wled00/src/dependencies/time"
        "../wled00/src/dependencies/timezone"
        "../wled00/src/dependencies/toki"
        "../wled00/src/dependencies/dmx"
        "../wled00/src/dependencies/spiffseditor"
        "../wled00/src/font"
    REQUIRES
        espressif__arduino-esp32
        esp_wifi
        esp_event
        nvs_flash
        esp_netif
        mdns
        esp_http_server
        spiffs
        fatfs
        spi_flash
        FastLED
        NeoPixelBus
        AsyncMqttClient
        ESPAsyncWebServer
        AsyncTCP
    PRIV_REQUIRES
        esp_timer
        driver
        efuse
        app_update
)

# Add compile definitions similar to platformio.ini
# Note: ARDUINO_ARCH_ESP32 and ESP32 are already defined by arduino-esp32
target_compile_definitions(${COMPONENT_LIB} PUBLIC
    "-DCORE_DEBUG_LEVEL=0"
    "-DNDEBUG"
    "-DMQTT_MAX_PACKET_SIZE=1024"
    "-DWLED_USE_MY_CONFIG"
    "-DARDUINOJSON_DECODE_UNICODE=0"
    "-DFASTLED_INTERNAL"
    "-DUSE_GET_MILLISECOND_TIMER"
    "-DWLED_DISABLE_INFRARED"
    # ESPAsyncWebServer v3.x is secure
    "-DSPIFFS_EDITOR_AIRCOOOKIE"
    # ESP32-P4 specific settings
    # Force RMT output method (I2S not available on P4)
    "-DNEOPIXEL_ESP32_RMT_DEFAULT"
    "-DWLED_NO_I2S0_PIXELBUS"
    "-DWLED_NO_I2S1_PIXELBUS"
    # ESP32-P4-NANO Ethernet with IP101GRI
    "-DWLED_USE_ETHERNET"
    "-DWLED_ETH_DEFAULT=WLED_ETH_ESP32P4_NANO"
    # WiFi via ESP32-C6 coprocessor requires ESP-Hosted setup in menuconfig
    # For now, run Ethernet-only mode
    "-DWLED_DISABLE_ESPNOW"
    "-DWLED_ETH_ONLY"  # P4: Disable WiFi, use Ethernet only
)

# Suppress some warnings that aren't critical for porting
target_compile_options(${COMPONENT_LIB} PRIVATE 
    "-Wno-unused-variable"
    "-Wno-attributes"
    "-Wno-reorder"
    "-Wno-format"
    "-Wno-misleading-indentation"
    "-Wno-address"
    "-Wno-array-bounds"
)

