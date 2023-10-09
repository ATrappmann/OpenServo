// TWI read/only status registers.  Writing
// values to these registers has no effect.

#define REG_DEVICE_TYPE             0x00
#define REG_DEVICE_SUBTYPE          0x01
#define REG_VERSION_MAJOR           0x02
#define REG_VERSION_MINOR           0x03
#define REG_FLAGS_HI                0x04
#define REG_FLAGS_LO                0x05
#define REG_TIMER_HI                0x06
#define REG_TIMER_LO                0x07

#define REG_POSITION_HI             0x08
#define REG_POSITION_LO             0x09
#define REG_VELOCITY_HI             0x0A
#define REG_VELOCITY_LO             0x0B
#define REG_POWER_HI                0x0C
#define REG_POWER_LO                0x0D
#define REG_PWM_DIRA                0x0E
#define REG_PWM_DIRB                0x0F
#define REG_VOLTAGE_HI              0x10
#define REG_VOLTAGE_LO              0x11
#define REG_CURVE_BUFFER            0x12
#define REG_TEMPERATURE_HI          0x13
#define REG_TEMPERATURE_LO          0x14


// TWI read/write registers.  Writing these
// registers controls operation of the servo.

#define REG_SEEK_POSITION_HI        0x20
#define REG_SEEK_POSITION_LO        0x21
#define REG_SEEK_VELOCITY_HI        0x22
#define REG_SEEK_VELOCITY_LO        0x23

#define REG_CURVE_DELTA_HI          0x24
#define REG_CURVE_DELTA_LO          0x25
#define REG_CURVE_POSITION_HI       0x26
#define REG_CURVE_POSITION_LO       0x27
#define REG_CURVE_IN_VELOCITY_HI    0x28
#define REG_CURVE_IN_VELOCITY_LO    0x29
#define REG_CURVE_OUT_VELOCITY_HI   0x2A
#define REG_CURVE_OUT_VELOCITY_LO   0x2B
#define REG_CURVE_RESERVED          0x2C
#define REG_GENERAL_CALL_GROUP_START 0x2D
#define REG_BANK_SELECT             0x2F

// TWI safe read/write registers.  These registers
// may only be written to when write enabled.

//
// Define the register ranges.
//
#define MIN_READ_ONLY_REGISTER      0x00
#define MAX_READ_ONLY_REGISTER      0x1F
#define MIN_READ_WRITE_REGISTER     0x20
#define MAX_READ_WRITE_REGISTER     0x37
#define MIN_WRITE_PROTECT_REGISTER  0x38
#define MAX_WRITE_PROTECT_REGISTER  0x3F
#define MIN_UNUSED_REGISTER         0x3F
#define MAX_UNUSED_REGISTER         0x3F
#define MIN_BANK_REGISTER           0x40
#define MAX_BANK_REGISTER           0x7F

// Define the total number of registers define.  This includes
// all registers except unused and redirected registers.
#define REGISTER_COUNT              (MIN_UNUSED_REGISTER)

// Define the number of write protect registers.
#define WRITE_PROTECT_REGISTER_COUNT    (MAX_WRITE_PROTECT_REGISTER - MIN_WRITE_PROTECT_REGISTER + 1)

//
// Define the flag register REG_FLAGS_HI and REG_FLAGS_LO bits.
//

#define FLAGS_HI_RESERVED_07         0x07
#define FLAGS_HI_RESERVED_06         0x06
#define FLAGS_HI_RESERVED_05         0x05
#define FLAGS_HI_RESERVED_04         0x04
#define FLAGS_HI_RESERVED_03         0x03
#define FLAGS_HI_RESERVED_02         0x02
#define FLAGS_HI_RESERVED_01         0x01
#define FLAGS_HI_RESERVED_00         0x00

#define FLAGS_LO_RESERVED_07         0x07
#define FLAGS_LO_PWM_BRAKE_ENABLED   0x06
#define FLAGS_LO_GENERALCALL_START   0x05
#define FLAGS_LO_GENERALCALL_WAIT    0x04
#define FLAGS_LO_GENERALCALL_ENABLED 0x03
#define FLAGS_LO_MOTION_ENABLED      0x02
#define FLAGS_LO_WRITE_ENABLED       0x01
#define FLAGS_LO_PWM_ENABLED         0x00
