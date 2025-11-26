#ifndef WLED_ETHERNET_H
#define WLED_ETHERNET_H

#include "pin_manager.h"

#ifdef WLED_USE_ETHERNET

// ESP32-P4 uses different clock mode type (emac_rmii_clock_mode_t)
// Define compatibility macros for the classic ESP32 clock modes
#ifdef CONFIG_IDF_TARGET_ESP32P4
  // P4 only supports external clock input from PHY
  #define ETH_CLOCK_GPIO0_IN    EMAC_CLK_EXT_IN
  #define ETH_CLOCK_GPIO0_OUT   EMAC_CLK_OUT      // Not typically used on P4
  #define ETH_CLOCK_GPIO16_OUT  EMAC_CLK_OUT      // Not typically used on P4
  #define ETH_CLOCK_GPIO17_OUT  EMAC_CLK_OUT      // Not typically used on P4
#endif

// For ESP32, the remaining five pins are at least somewhat configurable.
// eth_address  is in range [0..31], indicates which PHY (MAC?) address should be allocated to the interface
// eth_power    is an output GPIO pin used to enable/disable the ethernet port (and/or external oscillator)
// eth_mdc      is an output GPIO pin used to provide the clock for the management data
// eth_mdio     is an input/output GPIO pin used to transfer management data
// eth_type     is the physical ethernet module's type (ETH_PHY_LAN8720, ETH_PHY_TLK110, ETH_PHY_IP101)
// eth_clk_mode defines the GPIO pin and GPIO mode for the clock signal
//              ESP32 options:
//              ETH_CLOCK_GPIO0_IN    == External oscillator, clock input  via GPIO0
//              ETH_CLOCK_GPIO0_OUT   == ESP32 provides 50MHz clock output via GPIO0
//              ETH_CLOCK_GPIO16_OUT  == ESP32 provides 50MHz clock output via GPIO16
//              ETH_CLOCK_GPIO17_OUT  == ESP32 provides 50MHz clock output via GPIO17
//              ESP32-P4 uses EMAC_CLK_EXT_IN for external clock

typedef struct EthernetSettings {
  uint8_t        eth_address;
  int            eth_power;
  int            eth_mdc;
  int            eth_mdio;
  eth_phy_type_t eth_type;
  eth_clock_mode_t eth_clk_mode;
} ethernet_settings;

extern const ethernet_settings ethernetBoards[];

// ESP32-P4 uses different RMII pins, defined via Kconfig/sdkconfig
#ifdef CONFIG_IDF_TARGET_ESP32P4
  // P4 uses internal RMII pins, fewer pins to allocate
  #define WLED_ETH_RSVD_PINS_COUNT 2  // Only MDC, MDIO configurable
#else
  #define WLED_ETH_RSVD_PINS_COUNT 6
#endif
extern const managed_pin_type esp32_nonconfigurable_ethernet_pins[WLED_ETH_RSVD_PINS_COUNT];
#endif

#endif
