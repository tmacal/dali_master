#pragma once
#include <Arduino.h>

#ifndef bitRead
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#endif

#define ON_C                0b00000101 // Alias for RECALLMAXLEVEL_C
#define RECALLMAXLEVEL_C    0b00000101
#define RECALLMINLEVEL_C    0b00000110
#define OFF_C               0x00 // OFF
#define QUERY_MAX_LEVEL_C   0xA1 // Ask for maximum output level

#define QUERY_LAMP_FAIL     0x92 // Check if there is a lamp failure
#define QUERY_OP_MODE       0x93 // Check if the lamp is operating
#define QUERY_SLAVE_FAIL    0x9B // Check if the slave is in power failure mode

#define BLANK_C             0x00 // Easier to type

#define BROADCAST_C         0xFF
#define BROADCAST_DP        0xFE

// Specifically related to initialisation
#define RESET_C             0b00100000 // 0x20
#define TERMINATE_C         0b10100001 // 0xA1
#define INITIALISE_C        0b10100101 // 0xA5
#define RANDOMISE_C         0b10100111 // 0xA7
#define COMPARE_C           0b10101001 // 0xA9
#define SEARCHADDRH_C       0b10110001 // 0xB1
#define SEARCHADDRM_C       0b10110011 // 0xB3
#define SEARCHADDRL_C       0b10110101 // 0xB5
#define PROGRAMSHORT_C      0b10110111 // 0xB7
#define WITHDRAW_C          0b10101011 // 0xAB

// Emergency Lighting
#define QUERY_STATUS        0b10010000

// QUERY STATUS I2C reply bits
#define DUR_TEST_FAIL 7 //0=No
#define FUNCT_TEST_FAIL 6 //0=No
#define DUR_TEST 5 //0=No
#define FUNC_TEST_DELAY_EXCEED 4 //0=No
#define EL_FAIL 3 //0=No
#define BATT_FAIL 2 //0=No
#define BATT_DUR_FAIL 1 //0=No
#define CIRC_FAIL 0 //0=No

#define REST                0b11100000 //224
#define INHIBIT             0b11100001 //225
#define RST_INHIBIT         0b11100010 //226
#define START_FUNCT_TEST    0b11100011 //227
#define START_DUR_TEST      0b11100100 //228
#define START_FUNCT_TEST    0b11100011 //229
#define STOP_TEST           0b11100101 //230
#define RST_FUNCT_FLAG      0b11100110 //231
#define RST_DUR_FLAG        0b11100111 //232
#define RST_LAMP_TIME       0b11101000 //233
#define STO_DTR_EL          0b11101001 //234
#define STO_TESTDELAY_HB    0b11101010 //235
#define STO_TESTDELAY_LB    0b11101011 //236
#define STO_FNTEST_INTR     0b11101100 //237
#define STO_TESTEXC_TO      0b11101110 //238
#define STO_PROLONG_TIME    0b11101111 //239
#define START_ID            0b11110000 //240
#define QUERY_BATT          0b11110001 //241
#define TEST_TIMING         0b11110010 //242
#define QUERY_DUR_TEST_RES  0b11110011 //243
#define QUERY_LAMP_EMTIME   0b11110100 //244
#define QUERY_LAMP_OPTIME   0b11110101 //245
#define QUERY_EMLEVEL       0b11110110 //246
#define QUERY_EM_MINLEVEL   0b11110111 //247
#define QUERY_EM_MAXLEVEL   0b11111000 //248
#define QUERY_RATED_DUR     0b11111001 //249
#define QUERY_EM_MODE       0b11111010 //250
#define QUERY_FEATURES      0b11111011 //251
#define FAILURE_STATUS      0b11111100 //252
#define EM_STATUS           0b11111101 //253
#define PERF_DTR_SEL_FUNCT  0b11111110 //254
#define QUERY_EXT_VER_NO    0b11111111 //255

//272 1100 0001 0000 0001 ENABLE DEVICE TYPE 1

// Led Warrior I2C bits
#define BUSERROR_S 7
#define BUSY_S 6
#define OVERRUN_S 5
#define FRAMEERROR_S 4
#define VALIDREPLY_S 3
#define REPLYTIMEFRAME_S 2
#define REPLY2_S 1
#define REPLY1_S 0

// This is your main class that users will import into their application
class Dali_master
{
public:
    /**
     * Constructor
     */
    Dali_master();
    
    /**
     * Begin; set the address of the LED Warrior
     */
    void begin(uint8_t _address);
    
    /**
     * Transmit a command and optionally wait for a reply
     */
    byte transmitCommand(byte cmd1, byte cmd2, bool &reply, byte &reply1, byte &reply2);
    byte transmitCommand(byte cmd1, byte cmd2);
    
    /**
     * Get command status
     */
    byte getStatus();
    
    /**
     * Get command register
     */
    void getCommandRegister(uint8_t &byte1, uint8_t &byte2);
    
    /**
     * Split 24 bit long into three bytes
     */
    void splitAdd(long input, uint8_t &highbyte, uint8_t &middlebyte, uint8_t &lowbyte);
    
    /**
     * Flash a device
     */
    void flashDevice(byte deviceId);
    
    /**
     * Print the current status in checkbox form
     */
    void explainStatus(byte status);
    
    
private:
    uint8_t address;
    
    /**
     * Clear status register
     */
    void clearStatusRegister();
    
    /**
     * Get status register. Returns true when valid data is available
     */
    bool getStatusRaw();
    
    /**
     * Get command register. Returns true when valid data is available
     */
    bool getCommandRegisterRaw();
};
