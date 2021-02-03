/*
 * Generated with the FPGA Interface C API Generator 20.0
 * for NI-RIO 20.0 or later.
 */
#ifndef __NiFpga_IF_5764_FPGA_h__
#define __NiFpga_IF_5764_FPGA_h__

#ifndef NiFpga_Version
   #define NiFpga_Version 200
#endif

#include "NiFpga.h"

/**
 * The filename of the FPGA bitfile.
 *
 * This is a #define to allow for string literal concatenation. For example:
 *
 *    static const char* const Bitfile = "C:\\" NiFpga_IF_5764_FPGA_Bitfile;
 */
#define NiFpga_IF_5764_FPGA_Bitfile "NiFpga_IF_5764_FPGA.lvbitx"

/**
 * The signature of the FPGA bitfile.
 */
static const char* const NiFpga_IF_5764_FPGA_Signature = "20475AFA5EBEC3C04A3A5ACD1A6D3471";

#if NiFpga_Cpp
extern "C"
{
#endif

typedef enum
{
   NiFpga_IF_5764_FPGA_IndicatorBool_acqoverflow = 0x8000005E,
   NiFpga_IF_5764_FPGA_IndicatorBool_acqresetdone = 0x80000056,
   NiFpga_IF_5764_FPGA_IndicatorBool_flexriomoduledatavalid0 = 0x80000042,
   NiFpga_IF_5764_FPGA_IndicatorBool_flexriomoduledramready0 = 0xA,
   NiFpga_IF_5764_FPGA_IndicatorBool_flexriomoduleioready0 = 0x6
} NiFpga_IF_5764_FPGA_IndicatorBool;

typedef enum
{
   NiFpga_IF_5764_FPGA_IndicatorU8_streamstate0 = 0x80000016
} NiFpga_IF_5764_FPGA_IndicatorU8;

typedef enum
{
   NiFpga_IF_5764_FPGA_IndicatorI32_flexriomoduleioerror0 = 0x0
} NiFpga_IF_5764_FPGA_IndicatorI32;

typedef enum
{
   NiFpga_IF_5764_FPGA_IndicatorU64_inputDSP = 0x80000060,
   NiFpga_IF_5764_FPGA_IndicatorU64_outputDSP = 0x80000064,
   NiFpga_IF_5764_FPGA_IndicatorU64_readyforinputdram = 0x80000068,
   NiFpga_IF_5764_FPGA_IndicatorU64_streammetadata0 = 0x8000000C,
   NiFpga_IF_5764_FPGA_IndicatorU64_streamsamplestransferred0 = 0x80000010
} NiFpga_IF_5764_FPGA_IndicatorU64;

typedef enum
{
   NiFpga_IF_5764_FPGA_ControlBool_UserdefinedStartTrigger = 0x8000002A,
   NiFpga_IF_5764_FPGA_ControlBool_acqlatchoverflow = 0x8000005A,
   NiFpga_IF_5764_FPGA_ControlBool_acqreset = 0x80000052,
   NiFpga_IF_5764_FPGA_ControlBool_flexriobufferdelayreset0 = 0x8000003A,
   NiFpga_IF_5764_FPGA_ControlBool_flexrioioiocfilterenabled0 = 0x80000046,
   NiFpga_IF_5764_FPGA_ControlBool_flexriotriggeranalogedgerising0 = 0x80000036
} NiFpga_IF_5764_FPGA_ControlBool;

typedef enum
{
   NiFpga_IF_5764_FPGA_ControlU8_streamrequeststate0 = 0x8000001A
} NiFpga_IF_5764_FPGA_ControlU8;

typedef enum
{
   NiFpga_IF_5764_FPGA_ControlU16_flexriobufferdelayclocks0 = 0x8000003E,
   NiFpga_IF_5764_FPGA_ControlU16_flexriotriggerstartcfg0 = 0x80000026
} NiFpga_IF_5764_FPGA_ControlU16;

typedef enum
{
   NiFpga_IF_5764_FPGA_ControlU64_streamnumsamples0 = 0x8000001C
} NiFpga_IF_5764_FPGA_ControlU64;

typedef enum
{
   NiFpga_IF_5764_FPGA_TargetToHostFifoI16_streamtohost00 = 1,
   NiFpga_IF_5764_FPGA_TargetToHostFifoI16_streamtohost01 = 0
} NiFpga_IF_5764_FPGA_TargetToHostFifoI16;

#if !NiFpga_VxWorks

/* Control: flexriotriggeranalogedgechannel0 */
static const NiFpga_FxpTypeInfo NiFpga_IF_5764_FPGA_ControlFxp_flexriotriggeranalogedgechannel0_TypeInfo =
{
   0,
   2,
   2
};

/* Use NiFpga_WriteU8() to access flexriotriggeranalogedgechannel0 */
static const uint32_t NiFpga_IF_5764_FPGA_ControlFxp_flexriotriggeranalogedgechannel0_Resource = 0x80000022;


/* Control: flexriotriggeranalogedgehysteresis0 */
static const NiFpga_FxpTypeInfo NiFpga_IF_5764_FPGA_ControlFxp_flexriotriggeranalogedgehysteresis0_TypeInfo =
{
   1,
   32,
   1
};

/* Use NiFpga_WriteU32() to access flexriotriggeranalogedgehysteresis0 */
static const uint32_t NiFpga_IF_5764_FPGA_ControlFxp_flexriotriggeranalogedgehysteresis0_Resource = 0x80000030;


/* Control: flexriotriggeranalogedgethreshold0 */
static const NiFpga_FxpTypeInfo NiFpga_IF_5764_FPGA_ControlFxp_flexriotriggeranalogedgethreshold0_TypeInfo =
{
   1,
   32,
   1
};

/* Use NiFpga_WriteU32() to access flexriotriggeranalogedgethreshold0 */
static const uint32_t NiFpga_IF_5764_FPGA_ControlFxp_flexriotriggeranalogedgethreshold0_Resource = 0x8000002C;


/* Control: frequencyshift */
static const NiFpga_FxpTypeInfo NiFpga_IF_5764_FPGA_ControlFxp_frequencyshift_TypeInfo =
{
   1,
   48,
   0
};

/* Use NiFpga_WriteU64() to access frequencyshift */
static const uint32_t NiFpga_IF_5764_FPGA_ControlFxp_frequencyshift_Resource = 0x80000048;


/* Control: outputsamplerate */
static const NiFpga_FxpTypeInfo NiFpga_IF_5764_FPGA_ControlFxp_outputsamplerate_TypeInfo =
{
   0,
   48,
   1
};

/* Use NiFpga_WriteU64() to access outputsamplerate */
static const uint32_t NiFpga_IF_5764_FPGA_ControlFxp_outputsamplerate_Resource = 0x8000004C;


#endif /* !NiFpga_VxWorks */


#if NiFpga_Cpp
}
#endif

#endif
