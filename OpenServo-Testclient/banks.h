// Define the number of banks available.
#define MAX_BANKS 3

#define BANK_0 0
#define BANK_1 1
#define BANK_2 2
#define BANK_3 3  //not used
#define BANK_4 4  //not used

//bank0
#define ALERT_BANK                  BANK_0
#define INFORMATION_BANK            BANK_0

#define ALERT_STATUS                0x00
#define REG_BACKEMF_HI              0x01
#define REG_BACKEMF_LO              0x02
#define BANK0_RESERVED_03           0x03
#define BANK0_RESERVED_04           0x04
#define BANK0_RESERVED_05           0x05
#define BANK0_RESERVED_06           0x06
#define BANK0_RESERVED_07           0x07
#define BANK0_RESERVED_08           0x08
#define BANK0_RESERVED_09           0x09
#define BANK0_RESERVED_0A           0x0A
#define BANK0_RESERVED_0B           0x0B
#define BANK0_RESERVED_0C           0x0C
#define BANK0_RESERVED_0D           0x0D
#define BANK0_RESERVED_0E           0x0E
#define BANK0_RESERVED_0F           0x0F

// Bank1
// TWI safe read/write registers.  These registers
// may only be written to when write enabled.
#define POS_PID_BANK                BANK_1
#define ALERT_CONFIG_BANK           BANK_1
#define CONFIG_BANK                 BANK_1

#define REG_TWI_ADDRESS             0x00
#define REG_PID_DEADBAND            0x01
#define REG_PID_PGAIN_HI            0x02
#define REG_PID_PGAIN_LO            0x03
#define REG_PID_DGAIN_HI            0x04
#define REG_PID_DGAIN_LO            0x05
#define REG_PID_IGAIN_HI            0x06
#define REG_PID_IGAIN_LO            0x07
#define REG_MIN_SEEK_HI             0x08
#define REG_MIN_SEEK_LO             0x09
#define REG_MAX_SEEK_HI             0x0A
#define REG_MAX_SEEK_LO             0x0B
#define REG_REVERSE_SEEK            0x0C
#define REG_PWM_FREQ_DIVIDER_HI     0x0D
#define REG_PWM_FREQ_DIVIDER_LO     0x0E
#define REG_PWM_MAX                 0x0F

#define ALERT_CURR_MAX_LIMIT_HI     0x10
#define ALERT_CURR_MAX_LIMIT_LO     0x11
#define ALERT_VOLT_MAX_LIMIT_HI     0x12
#define ALERT_VOLT_MAX_LIMIT_LO     0x13
#define ALERT_VOLT_MIN_LIMIT_HI     0x14
#define ALERT_VOLT_MIN_LIMIT_LO     0x15
#define ALERT_TEMP_MAX_LIMIT_HI     0x16
#define ALERT_TEMP_MAX_LIMIT_LO     0x17
// A mask containing alert sources that cause an interrupt on int(n)
#define REG_ALERT_CAUSES_INT        0x1E
// This is a mask bit used to disable the alerts individually
// over just zeroing the above. Masks are defined in alert.h
#define REG_ALERT_ENABLE            0x1F

#define REG_GENERAL_CALL_GROUP      0x20
#define REG_BRAKE_STRENGTH          0x21
// Delay in ms for the back emf spike collapse
#define REG_EMF_COLLAPSE_DELAY      0x2A
// This is 41us * n us delay for back emf charging cap
#define REG_EMF_CHARGE_TIME         0x2B
#define REG_STEP_MODE               0x2C

#define CONFIG_SAVE_MIN             0x00
#define CONFIG_SAVE_MAX             0x2C 
#define CONFIG_SAVE_COUNT (CONFIG_SAVE_MAX - CONFIG_SAVE_MIN + 1)

// Bank 2
// Put the redirects into bank 2
#define REDIRECTED_BANK BANK_2

#define MIN_REDIRECT_REGISTER       0x00
#define MAX_REDIRECT_REGISTER       0x0F
#define MIN_REDIRECTED_REGISTER     0x10
#define MAX_REDIRECTED_REGISTER     0x1F

// Define the number of redirect registers.
#define REDIRECT_REGISTER_COUNT         (MAX_REDIRECT_REGISTER - MIN_REDIRECT_REGISTER + 1)

// Define the number of banked registers.
#define BANK_REGISTER_COUNT             (MAX_BANK_REGISTER - MIN_BANK_REGISTER + 1)
