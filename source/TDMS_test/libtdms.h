/*============================================================================*/
/*                           TDM Streaming Library                            */
/*----------------------------------------------------------------------------*/
/*    Copyright (c) National Instruments 2006-2019.  All Rights Reserved.     */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Title:       cvitdms.h                                                     */
/* Purpose:     Include file for TDM Streaming Library                        */
/*                                                                            */
/*============================================================================*/

#ifndef _CVITDMS_H
#define _CVITDMS_H

#include "cvidef.h"
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_CVI_) && !defined(__TPC__)
#pragma EnableLibraryRuntimeChecking
#endif

/********************************************************/
/* Typedefs, enums, constants, etc.                     */
/********************************************************/

#ifdef WIN32
    #pragma pack(push)
    #pragma pack(4)
#endif

typedef struct _TDMSFile                TDMSFile;
typedef struct _TDMSChannelGroup        TDMSChannelGroup;
typedef struct _TDMSChannel             TDMSChannel;

typedef TDMSFile*                       TDMSFileHandle;
typedef TDMSChannelGroup*               TDMSChannelGroupHandle;
typedef TDMSChannel*                    TDMSChannelHandle;
typedef void*                           TDMSAnyHandle;

#ifndef CVITime_DECLARED
#define CVITime_DECLARED
typedef struct CVITime { unsigned __int64 lsb; __int64 msb; } CVITime;
#endif

#ifndef CVIAbsoluteTime_DECLARED
#define CVIAbsoluteTime_DECLARED
typedef union CVIAbsoluteTime { CVITime cviTime; unsigned int u32Data[4]; } CVIAbsoluteTime;
#endif

#ifdef WIN32
    #pragma pack(pop)
#endif

typedef enum {
    TDMS_Int8                       = 1,    /* char*/
    TDMS_UInt8                      = 5,    /* unsigned char            */
    TDMS_Int16                      = 2,    /* short                    */
    TDMS_UInt16                     = 6,    /* unsigned short           */
    TDMS_Int32                      = 3,    /* int                      */
    TDMS_UInt32                     = 7,    /* unsigned int             */
    TDMS_Int64                      = 4,    /* __int64                  */
    TDMS_UInt64                     = 8,    /* unsigned __int64         */
    TDMS_Float                      = 9,    /* float                    */
    TDMS_Double                     = 10,   /* double                   */
    TDMS_String                     = 32,   /* string (char *)          */
    TDMS_Boolean                    = 33,   /* boolean (unsigned char)  */
    TDMS_Timestamp                  = 68,   /* timestamp (CVIAbsoluteTime or Year/Month/Day/Hour/Minute/Second/Millisecond components) */
    TDMS_DataTypeForceSizeTo32Bits  = 0xffffffff
} TDMSDataType;

typedef enum {
    TDMS_Streaming2_0                   = 2,    /* TDM Streaming format (.tdms), version 2.0    */
    TDMS_Streaming1_0                   = 1,    /* TDM Streaming format (.tdms), version 1.0    */
    TDMS_Streaming                      = 0,    /* Legacy constant, same as TDMS_Streaming1_0   */
    TDMS_FileFormatForceSizeTo32Bits    = 0xffffffff
} TDMSFileFormat;

typedef enum {
    TDMS_ByteOrderBigEndian         = 0,    /* Big-endian - also called network order           */
    TDMS_ByteOrderNative            = 1,    /* Native - the endian format of the host computer  */
    TDMS_ByteOrderLittleEndian      = 2,    /* Little-endian                                    */
    TDMS_ByteOrderForceSizeTo32Bits = 0xffffffff
} TDMSByteOrder;

typedef enum {
    TDMS_CreateFileDisableBuffering         = 0x00000001,   /* Disable system file buffering- Windows only  */
    TDMS_CreateFileDoNotCreateIndexFile     = 0x00000002,   /* Do not create an index file (not applicable for TDMS_AdvancedCreateFile) */
    TDMS_CreateFileEnableAsyncOperations    = 0x00000004    /* Enable asychronous read/write operations (only applicable for TDMS_AdvancedCreateFile)   */
} TDMSCreateFileOptions;

typedef enum {
    TDMS_OpenFileDisableBuffering       = 0x00000001,   /* Disable system file buffering- Windows only. */
    TDMS_OpenFileDoNotCreateIndexFile   = 0x00000002,   /* Do not create an index file (not applicable for TDMS_AdvancedOpenFile)   */
    TDMS_OpenFileEnableAsyncOperations  = 0x00000004    /* Enable asychronous read/write operations (only applicable for TDMS_AdvancedOpenFile) */
} TDMSOpenFileOptions;

typedef enum {
    TDMS_DataLayoutNonInterleaved       = 0,    /* Values for a single channel are not interleaved (values are contiguous)      */
    TDMS_DataLayoutInterleaved          = 1,    /* Values for a single channel are interleaved with values for other channels   */
    TDMS_DataLayoutForceSizeTo32Bits    = 0xffffffff
} TDMSDataLayout;

typedef enum {
    TDMS_ReserveModeExtendFileSize              = 0,    /* Extend File Size - extends the size of the existing file by the requested size           */
    TDMS_ReserveModeSetTotalFileSize            = 1,    /* Set Total File Size - changes the total size of the existing file to the requested size  */
    TDMS_ReserveFileSizeModeForceSizeTo32Bits   = 0xffffffff
} TDMSReserveFileSizeMode;

typedef enum {
    TDMS_OffsetRelativeToChannelStart           = 0,    /* Start - offset is relative to start and must be >= 0 */
    TDMS_OffsetRelativeToChannelEnd             = 1,    /* End - offset is relative to end and must be <=0      */
    TDMS_OffsetReferencePointForceSizeTo32Bits  = 0xffffffff
} TDMSOffsetReferencePoint;

typedef enum {
    TDMS_ThermocoupleTypeB                  = 10047,    /* B-type */
    TDMS_ThermocoupleTypeE                  = 10055,    /* E-type */
    TDMS_ThermocoupleTypeJ                  = 10072,    /* J-type */
    TDMS_ThermocoupleTypeK                  = 10073,    /* K-type */
    TDMS_ThermocoupleTypeN                  = 10077,    /* N-type */
    TDMS_ThermocoupleTypeR                  = 10082,    /* R-type */
    TDMS_ThermocoupleTypeS                  = 10085,    /* S-type */
    TDMS_ThermocoupleTypeT                  = 10086,    /* T-type */
    TDMS_ThermocoupleTypeForceSizeTo32Bits  = 0xffffffff
} TDMSThermocoupleType;

typedef enum {
    TDMS_ResistanceConfig2Wire              = 2,    /* 2-Wire */
    TDMS_ResistanceConfig3Wire              = 3,    /* 3-Wire */
    TDMS_ResistanceConfig4Wire              = 4,    /* 4-Wire */
    TDMS_ResistanceConfigForceSizeTo32Bits  = 0xffffffff
} TDMSResistanceConfig;

typedef enum {
    TDMS_StrainGageConfigFullBridgeI            = 10183,    /* Full Bridge I      */
    TDMS_StrainGageConfigFullBridgeII           = 10184,    /* Full Bridge II     */
    TDMS_StrainGageConfigFullBridgeIII          = 10185,    /* Full Bridge III    */
    TDMS_StrainGageConfigHalfBridgeI            = 10188,    /* Half Bridge I      */
    TDMS_StrainGageConfigHalfBridgeII           = 10189,    /* Half Bridge II     */
    TDMS_StrainGageConfigQuarterBridgeI         = 10271,    /* Quarter Bridge I   */
    TDMS_StrainGageConfigQuarterBridgeII        = 10272,    /* Quarter Bridge II  */
    TDMS_StrainGageConfigForceSizeTo32Bits  = 0xffffffff
} TDMSStrainGageConfig;

typedef enum {
    TDMS_ExcitationTypeVoltage              = 10122,    /* Voltage */
    TDMS_ExcitationTypeCurrent              = 10334,    /* Current */
    TDMS_ExcitationTypeForceSizeTo32Bits    = 0xffffffff
} TDMSExcitationType;

/****************************************************/
/* File property constants                          */
/****************************************************/
#define TDMS_FILE_NAME                  "name"              /* Name         */
#define TDMS_FILE_DESCRIPTION           "description"       /* Description  */
#define TDMS_FILE_TITLE                 "title"             /* Title        */
#define TDMS_FILE_AUTHOR                "author"            /* Author       */

/****************************************************/
/* ChannelGroup property constants                  */
/****************************************************/
#define TDMS_CHANNELGROUP_NAME          "name"              /* Name         */
#define TDMS_CHANNELGROUP_DESCRIPTION   "description"       /* Description  */

/****************************************************/
/* Channel property constants                       */
/****************************************************/
#define TDMS_CHANNEL_NAME               "name"              /* Name         */
#define TDMS_CHANNEL_DESCRIPTION        "description"       /* Description  */
#define TDMS_CHANNEL_UNIT_STRING        "unit_string"       /* Unit String  */

/****************************************************/
/* Special properties                               */
/****************************************************/
#define TDMS_NI_DISK_CACHE_SIZE              "NI_DiskCacheSize"          /* For files */
#define TDMS_NI_DISK_GAP_SIZE                "NI_DiskGapSize"            /* For files */
#define TDMS_NI_MINIMUM_BUFFER_SIZE          "NI_MinimumBufferSize"      /* For files, channelgroups and channels */
#define TDMS_NI_IN_MEMORY_WRITE_BLOCK_SIZE   "NI_InMemoryWriteBlockSize" /* For in-memory files */

/****************************************************/
/* Advanced API callback function prototypes        */
/****************************************************/
typedef void (CVICALLBACK *TDMSAsyncWriteCallbackPtr)(TDMSFileHandle file, int error, void *samples, size_t numSamplesWritten, void *callbackData);
typedef void (CVICALLBACK *TDMSAsyncReadCallbackPtr)(TDMSFileHandle file, int error, void *samples, size_t numSamplesRead, void *callbackData);

/****************************************************/
/* Error codes                                      */
/****************************************************/
typedef enum {
    
    TDMS_NoError                                            = 0,        /* No error */
    TDMS_ErrorBegin                                         = -6601,    
    
    TDMS_InvalidArgument                                    = -6601,    /* Invalid argument. */
    TDMS_OutOfMemory                                        = -6602,    /* Out of memory. */
    TDMS_FileAlreadyOpen                                    = -6603,    /* The file is already open. */
    TDMS_FileCouldNotBeOpened                               = -6604,    /* The file could not be opened. */
    TDMS_FileNotFound                                       = -6605,    /* The file could not be found. */
    TDMS_FileAccessDenied                                   = -6606,    /* File access denied. */
    TDMS_DriveIsFull                                        = -6607,    /* The drive is full. */
    TDMS_TooManyOpenFiles                                   = -6608,    /* The maximum number of open files has been reached. Close one or more files and try again. */
    TDMS_PathNotFound                                       = -6609,    /* The path could not be found. */
    TDMS_NotAValidTDMSFile                                  = -6610,    /* The file is not a valid TDMS file. */
    TDMS_FileCouldNotBeClosed                               = -6611,    /* The file could not be closed. */
    TDMS_WriteToFileFailed                                  = -6612,    /* Write to file failed. */
    TDMS_ReadFromFileFailed                                 = -6613,    /* Read from file failed. */
    TDMS_FailedToLoadLibrary                                = -6614,    /* The library failed to load. */
    TDMS_TDMFilesAreNotSupported                            = -6615,    /* TDM files are not supported. Only TDMS files are supported. */
    TDMS_PropertyIsReadOnly                                 = -6616,    /* The specified property is read only. */
    TDMS_DuplicateName                                      = -6617,    /* The file already contains an object with that name. */
    TDMS_RequestCannotBeCompletedWithUnsavedData            = -6618,    /* The request cannot be completed while there are unsaved changes through another file handle. 
                                                                           Close or save the file using the other file handle and try again. */
    TDMS_UnexpectedError                                    = -6619,    /* An unexpected error occurred. */
    TDMS_NullPointerPassed                                  = -6620,    /* A null pointer was passed where a non-null pointer was expected. */
    TDMS_InvalidFileHandle                                  = -6621,    /* Invalid file handle. */
    TDMS_InvalidChannelGroupHandle                          = -6622,    /* Invalid channel group handle. */
    TDMS_InvalidChannelHandle                               = -6623,    /* Invalid channel handle. */
    TDMS_InvalidFilePath                                    = -6624,    /* Invalid file path. */
    TDMS_InvalidDataType                                    = -6625,    /* Invalid data type. */
    TDMS_InvalidFileFormatValue                             = -6626,    /* Invalid value for file format. */
    TDMS_InvalidName                                        = -6627,    /* Invalid name. */
    TDMS_InvalidPropertyName                                = -6628,    /* Invalid property name. */
    TDMS_PropertyDoesNotExist                               = -6629,    /* The property does not exist. */
    TDMS_PropertyAlreadyExists                              = -6630,    /* The property already exists. */
    TDMS_PropertyTypeMismatch                               = -6631,    /* The data type of the property does not match the expected data type. */
    TDMS_RequestExceedsActualNumberOfValues                 = -6632,    /* The request exceeds the actual number of available values. */
    TDMS_BufferIsTooSmall                                   = -6633,    /* The buffer is too small to hold all values. */
    TDMS_StringContainsInvalidCharacters                    = -6634,    /* String contains invalid characters. */
    TDMS_CannotModifyFileOpenedForReadOnlyAccess            = -6635,    /* A file opened for read-only access cannot be modified. */
    TDMS_FileMustHaveTDMSExtension                          = -6636,    /* The file must have a .tdms extension. */
    TDMS_InvalidTimeValue                                   = -6637,    /* The specified time value is invalid. */
    TDMS_InvalidByteOrderValue                              = -6638,    /* Invalid value for byte order. */
    TDMS_InvalidOptionsValue                                = -6639,    /* Invalid value for options. */
    TDMS_ChannelGroupNotFound                               = -6640,    /* The channel group could not be found. */
    TDMS_ChannelNotFound                                    = -6641,    /* The channel could not be found. */
    TDMS_FeatureNotSupportedWithThisFileVersion             = -6642,    /* A feature you have requested is not supported for this version of the TDMS file format. */
    TDMS_HandleInvalidDueToNamePropertyChange               = -6643,    /* The handle is invalid because the channel group or channel it referred to was renamed. */
    TDMS_FileFormatNewerThanSupported                       = -6644,    /* The file format is too new to be supported by this version of the library. */
    TDMS_InvalidDataLayout                                  = -6645,    /* Invalid value for data layout. */
    TDMS_AllChannelsMustHaveSameDatatype                    = -6646,    /* All channels must have the same data type. */
    TDMS_InterleavedDataLayoutNotSupportedForStringDataType = -6647,    /* Interleaved data layout not supported for channels of string data type. */
    TDMS_InterleavedDataLayoutRequiresMultipleChannels      = -6648,    /* Interleaved data layout requires multiple channels. */
    TDMS_NumValuesMustBeMultipleOfNumChannels               = -6649,    /* The number of values must be an even multiple of the number of channels. */
    TDMS_InterleavedDataLayoutRequiresSaveFileParamToBeTrue = -6650,    /* Interleaved data layout requires the save file parameter to be true. */
    TDMS_RequestCannotBeCompletedWhileRenameIsPending       = -6651,    /* The request cannot be completed while there is a pending change to the name property of a channel or 
                                                                           channelgroup through another file handle. Close or save the file using the other file handle and try again.*/
    TDMS_DataTypeNotRecognized                              = -6652,    /* This channel or property value contains a data type that is not recognized by this version of the TDMS library. */
    TDMS_VersionOfTDMSDoesNotMeetMinimumVersionRequirement  = -6653,    /* The version of TDMS found on this system does not meet the minimum version requirement of the LabWindows/CVI TDMS library. */
    TDMS_AdvancedIORequiresLaterFileFormat                  = -6654,    /* Advanced I/O requires a newer version of the TDMS file format than specified. */
    TDMS_InvalidReserveFileSizeMode                         = -6655,    /* Invalid value for reserve file mode. */
    TDMS_InvalidMaxNumConcurrentOperations                  = -6656,    /* Invalid value for maximum number of concurrent operations. */
    TDMS_AllChannelsMustBelongToSameFile                    = -6657,    /* All channels must belong to the same file. */
    TDMS_StringDataTypeNotSupported                         = -6658,    /* Channels with a data type of string are not supported. */
    TDMS_InvalidOffsetReferencePoint                        = -6659,    /* Invalid value for offset reference point. */
    TDMS_InvalidOffset                                      = -6660,    /* Invalid value for offset. */
    TDMS_FunctionRequiresAdvancedFileHandle                 = -6661,    /* This function requires handles that were obtained from a file that was opened using an advanced create or open function. */
    TDMS_FunctionIncompatibleWithAdvancedFileHandle         = -6662,    /* This function is incompatible with handles that were obtained from a file that was opened by calling an advanced create or open function. */
    TDMS_FunctionRequiresFileHandleWithAsyncOption          = -6663,    /* This function requires handles that were obtained from a file that was opened by calling an advanced create or open function with the asynchronous option. */
    TDMS_FunctionIncompatibleWithFileHandleWithAsyncOption  = -6664,    /* This function is incompatible with handles that were obtained from a file that was opened by calling an advanced create or open function with the asynchronous option.*/
    TDMS_MemoryBufferExceeding4GBInSizeIsNotSupported       = -6665,    /* Memory buffers greater than 4GB in size are not supported. */
    TDMS_SamplesPerChannelValuesMustNotBeZero               = -6666,    /* Samples per channel value must not be zero. */
    TDMS_EndOfFile                                          = -6667,    /* End of file reached. */
    TDMS_CannotCallLibraryFunctionsFromCallback             = -6668,    /* TDMS library functions cannot be called from callback functions. */
    TDMS_FilePositionMustBeAlignedOnDiskSectorBoundary      = -6669,    /* File position must be aligned on disk sector boundary when performing advanced I/O and buffering is disabled. */
    TDMS_InvalidNumberOfSamples                             = -6670,    /* Invalid value for number of samples. */
    TDMS_InvalidTimeout                                     = -6671,    /* Invalid value for timeout. */
    TDMS_OperationTimedOut                                  = -6672,    /* The operation exceeded the requested timeout. */
    TDMS_FailedToReserveFileSize                            = -6673,    /* Failed to reserve file size. Confirm that application has elevated privileges if required by the operating system. */
    TDMS_FileCannotBeTruncated                              = -6674,    /* File cannot be truncated. This can happen if there are currently multiple open references to the file. */
    TDMS_OperationCancelled                                 = -6675,    /* The operation was cancelled because it could not be completed within the requested timeout period. */
    TDMS_AsyncOperationNotConfigured                        = -6676,    /* The asynchronous operation has not been configured. Call the appropriate asynchronous configuration function first. */
    TDMS_ChannelAlreadyPresentInChannelInfo                 = -6677,    /* One or more of the specified channels is already present in the channel information. */
    TDMS_DisableBufferingNotSupportedOnThisOS               = -6678,    /* The option to disable buffering is not supported on this operating system. */
    TDMS_AsyncOperationsNotSupportedOnThisOS                = -6679,    /* The option to enable asynchronous operations is not supported on this operating system. */
    TDMS_FunctionNotSupportedOnThisOS                       = -6680,    /* Function not supported on this operating system. */
    TDMS_DataDimensionMismatch                              = -6681,    /* The specified channel contains data with a number of dimensions that does not match the number of dimensions expected by this function. */
    TDMS_MultiDimensionalDataNotSupported                   = -6682,    /* This function does not support files containing channels with multidimensional data in this version of the TDMS library. */
    TDMS_AdditionalHierarchyNotSupported                    = -6683,    /* This function does not support files containing additional levels of hierarchy in this version of the TDMS library. */
    TDMS_InvalidHandle                                      = -6684,    /* Invalid file, channel group, or channel handle. */
    TDMS_CouldNotCreateOrApplyScalingInfo                   = -6685,    /* The scaling information could not be created or the scaling information could not be applied to the data values. */
    TDMS_PropertyNotSupportedOnObjectOfSpecifiedType        = -6686,    /* The property is not supported on an object of the specified type. For example, you are trying to set a property on a channel group when that property is only supported on a channel. */
    TDMS_FileAlreadyExists                                  = -6687,    /* The file already exists. */
    TDMS_OperationIsOnlyValidOnInMemoryFiles                = -6688,    /* Operation is only valid on in-memory files. */
    TDMS_FailedToChangeBlockSize                            = -6689,    /* Failed to change the block size. This can happen if you write to a file before setting this property. */
    TDMS_InvalidBlockSize                                   = -6690,    /* Invalid block size. */

    TDMS_ErrorEnd                                           = -6690,    
    TDMS_ErrorForceSizeTo32Bits                             = 0xffffffff    

} TDMSError;

/****************************************************/
/* -> Object Management                             */
/****************************************************/
int CVIFUNC TDMS_CreateFileEx (const char *filePath,
                               TDMSFileFormat fileFormat,
                               TDMSByteOrder byteOrder,
                               unsigned int options,
                               const char *name,
                               const char *description,
                               const char *title,
                               const char *author,
                               TDMSFileHandle *file);
                               
int CVIFUNC TDMS_AddChannelGroup (TDMSFileHandle file,
                                  const char *name,
                                  const char *description,
                                  TDMSChannelGroupHandle *channelGroup);

int CVIFUNC TDMS_AddChannel (TDMSChannelGroupHandle channelGroup,
                             TDMSDataType dataType,
                             const char *name,
                             const char *description,
                             const char *unitString,
                             TDMSChannelHandle *channel);

int CVIFUNC TDMS_SaveFile (TDMSFileHandle file);

int CVIFUNC TDMS_CloseFile (TDMSFileHandle file);

int CVIFUNC TDMS_OpenFileEx (const char *filePath,
                             int readOnly,
                             unsigned int options,
                             TDMSFileHandle *file);

/****************************************************/
/* -> Obsolete                                      */
/****************************************************/
int CVIFUNC TDMS_CreateFile (const char *filePath,
                             TDMSFileFormat fileFormat,
                             const char *name,
                             const char *description,
                             const char *title,
                             const char *author,
                             TDMSFileHandle *file);

int CVIFUNC TDMS_OpenFile (const char *filePath,
                           int readOnly,
                           TDMSFileHandle *file);
/****************************************************/
/* <- Obsolete                                      */
/****************************************************/
/****************************************************/
/* <- Object Management                             */
/****************************************************/

/****************************************************/
/* -> Data Storage                                  */
/****************************************************/
int CVIFUNC TDMS_AppendDataValues (TDMSChannelHandle channel,
                                   void *values,
                                   size_t numValues,
                                   int saveFile);

int CVIFUNC TDMS_AppendDataValuesMultiChannel (TDMSChannelHandle channels[],
                                               size_t numChannels,
                                               void *values,
                                               size_t numValues,
                                               TDMSDataLayout dataLayout,
                                               int saveFile);

/****************************************************/
/* <- Data Storage                                  */
/****************************************************/
/****************************************************/
/* -> Data Retrieval                                */
/****************************************************/

/****************************************************/
/* -> Enumeration                                   */
/****************************************************/
int CVIFUNC TDMS_GetChannelGroupByName (TDMSFileHandle file,
                                        const char *name,
                                        TDMSChannelGroupHandle *channelGroup);

int CVIFUNC TDMS_GetChannelByName (TDMSChannelGroupHandle channelGroup,
                                   const char *name,
                                   TDMSChannelHandle *channel);

int CVIFUNC TDMS_GetChannelGroupAndChannelByName (TDMSFileHandle file,
                                                  const char *channelGroupName,
                                                  const char *channelName,
                                                  TDMSChannelGroupHandle *channelGroup,
                                                  TDMSChannelHandle *channel);

int CVIFUNC TDMS_GetNumChannelGroups (TDMSFileHandle file,
                                      unsigned int *numChannelGroups);

int CVIFUNC TDMS_GetChannelGroups (TDMSFileHandle file,
                                   TDMSChannelGroupHandle channelGroupsBuf[],
                                   size_t numChannelGroups);

int CVIFUNC TDMS_GetNumChannels (TDMSChannelGroupHandle channelGroup,
                                 unsigned int *numChannels);

int CVIFUNC TDMS_GetChannels (TDMSChannelGroupHandle channelGroup,
                              TDMSChannelHandle channelsBuf[],
                              size_t numChannels);

/****************************************************/
/* <- Enumeration                                   */
/****************************************************/

int CVIFUNC TDMS_GetNumDataValues (TDMSChannelHandle channel,
                                   unsigned __int64 *numValues);

int CVIFUNC TDMS_GetDataValuesEx (TDMSChannelHandle channel,
                                  unsigned __int64 indexOfFirstValueToGet,
                                size_t numValuesToGet,
                                void *values);

int CVIFUNC TDMS_GetDataType (TDMSChannelHandle channel,
                              TDMSDataType *dataType);

/****************************************************/
/* -> Obsolete                                      */
/****************************************************/
int CVIFUNC TDMS_GetDataValues (TDMSChannelHandle channel,
                                unsigned int indexOfFirstValueToGet,
                                unsigned int numValuesToGet,
                                void *values);

/****************************************************/
/* <- Obsolete                                      */
/****************************************************/
/****************************************************/
/* <- Data Retrieval                                */
/****************************************************/

/****************************************************/
/* -> Properties                                    */
/****************************************************/
/****************************************************/
/* -> File                                          */
/****************************************************/
int CVIFUNC_C TDMS_SetFileProperty (TDMSFileHandle file,
                                    const char *property,
                                    TDMSDataType dataType,
                                    ...);

int CVIFUNC TDMS_SetFilePropertyV (TDMSFileHandle file,
                                   const char *property,
                                   TDMSDataType dataType,
                                   va_list args);

int CVIFUNC TDMS_GetFileProperty (TDMSFileHandle file,
                                  const char *property,
                                  void *value,
                                  size_t valueSizeInBytes);

int CVIFUNC TDMS_GetFileStringPropertyLength (TDMSFileHandle file,
                                              const char *property,
                                              unsigned int *length);

int CVIFUNC TDMS_FilePropertyExists (TDMSFileHandle file,
                                     const char *property,
                                     int *exists);

int CVIFUNC TDMS_GetNumFileProperties (TDMSFileHandle file,
                                       unsigned int *numProperties);

int CVIFUNC TDMS_GetFilePropertyNames (TDMSFileHandle file,
                                       char** propertyNames,
                                       size_t numPropertyNames);

int CVIFUNC TDMS_GetFilePropertyType (TDMSFileHandle file,
                                      const char *property,
                                      TDMSDataType *dataType);

/************************************************/
/* <- File                                      */
/************************************************/
/************************************************/
/* -> Channel Group                             */
/************************************************/
int CVIFUNC_C TDMS_SetChannelGroupProperty (TDMSChannelGroupHandle channelGroup,
                                            const char *property,
                                            TDMSDataType dataType,
                                            ...);

int CVIFUNC TDMS_SetChannelGroupPropertyV (TDMSChannelGroupHandle channelGroup,
                                           const char *property,
                                           TDMSDataType dataType,
                                           va_list args);

int CVIFUNC TDMS_GetChannelGroupProperty (TDMSChannelGroupHandle channelGroup,
                                          const char *property,
                                          void *value,
                                          size_t valueSizeInBytes);

int CVIFUNC TDMS_GetChannelGroupStringPropertyLength (TDMSChannelGroupHandle channelGroup,
                                                      const char *property,
                                                      unsigned int *length);

int CVIFUNC TDMS_ChannelGroupPropertyExists (TDMSChannelGroupHandle channelGroup,
                                             const char *property,
                                             int *exists);

int CVIFUNC TDMS_GetNumChannelGroupProperties (TDMSChannelGroupHandle channelGroup,
                                               unsigned int *numProperties);

int CVIFUNC TDMS_GetChannelGroupPropertyNames (TDMSChannelGroupHandle channelGroup,
                                               char** propertyNames,
                                               size_t numPropertyNames);

int CVIFUNC TDMS_GetChannelGroupPropertyType (TDMSChannelGroupHandle channelGroup,
                                              const char *property,
                                              TDMSDataType *dataType);
/************************************************/
/* <- Channel Group                             */
/************************************************/
/************************************************/
/* -> Channel                                   */
/************************************************/
int CVIFUNC_C TDMS_SetChannelProperty (TDMSChannelHandle channel,
                                       const char *property,
                                       TDMSDataType dataType,
                                       ...);

int CVIFUNC TDMS_SetChannelPropertyV (TDMSChannelHandle channel,
                                      const char *property,
                                      TDMSDataType dataType,
                                      va_list args);

int CVIFUNC TDMS_GetChannelProperty (TDMSChannelHandle channel,
                                     const char *property,
                                     void *value,
                                     size_t valueSizeInBytes);

int CVIFUNC TDMS_GetChannelStringPropertyLength (TDMSChannelHandle channel,
                                                 const char *property,
                                                 unsigned int *length);

int CVIFUNC TDMS_ChannelPropertyExists (TDMSChannelHandle channel,
                                        const char *property,
                                        int *exists);

int CVIFUNC TDMS_GetNumChannelProperties (TDMSChannelHandle channel,
                                          unsigned int *numProperties);

int CVIFUNC TDMS_GetChannelPropertyNames (TDMSChannelHandle channel,
                                          char** propertyNames,
                                          size_t numPropertyNames);

int CVIFUNC TDMS_GetChannelPropertyType (TDMSChannelHandle channel,
                                         const char *property,
                                         TDMSDataType *dataType);

/****************************************************/
/* <- Channel                                       */
/****************************************************/
/****************************************************/
/* <- Properties                                    */
/****************************************************/

/****************************************************/
/* -> Advanced Data Scaling                         */
/****************************************************/

int CVIFUNC TDMS_CreateLinearScalingInfo (TDMSAnyHandle handle,
                                          double slope,
                                          double yIntercept,
                                          int inputSource,
                                          int *scaleID);

int CVIFUNC TDMS_CreatePolynomialScalingInfo (TDMSAnyHandle handle,
                                              double coefficients[],
                                              size_t numCoefficients,
                                              int inputSource,
                                              int *scaleID);

int CVIFUNC TDMS_CreateThermocoupleScalingInfo (TDMSAnyHandle handle,
                                                TDMSThermocoupleType thermocoupleType,
                                                int inputSource,
                                                int *scaleID);

int CVIFUNC TDMS_CreateRTDScalingInfo (TDMSAnyHandle handle,
                                       double currentExcitation,
                                       double r0NominalResistance,
                                       double a,
                                       double b,
                                       double c,
                                       double leadWireResistance,
                                       TDMSResistanceConfig resistanceConfig,
                                       int inputSource,
                                       int *scaleID);

int CVIFUNC TDMS_CreateTableScalingInfo (TDMSAnyHandle handle,
                                         double preScaledValues[],
                                         double scaledValues[],
                                         size_t numValues,
                                         int inputSource,
                                         int *scaleID);

int CVIFUNC TDMS_CreateStrainGageScalingInfo (TDMSAnyHandle handle,
                                              TDMSStrainGageConfig configuration,
                                              double poissonRatio,
                                              double gageResistance,
                                              double leadWireResistance,
                                              double initialBridgeVoltage,
                                              double gageFactor,
                                              double voltageExcitation,
                                              int inputSource,
                                              int *scaleID);

int CVIFUNC TDMS_CreateThermistorScalingInfo (TDMSAnyHandle handle,
                                              TDMSResistanceConfig resistanceConfig,
                                              TDMSExcitationType excitationType,
                                              double excitationValue,
                                              double r1ReferenceResistance,
                                              double leadWireResistance,
                                              double a,
                                              double b,
                                              double c,
                                              int inputSource,
                                              int *scaleID);

int CVIFUNC TDMS_CreateReciprocalScalingInfo (TDMSAnyHandle handle,
                                              int inputSource,
                                              int *scaleID);
/********************************************************/
/* <- Advanced Data Scaling                             */
/********************************************************/
/********************************************************/
/* -> Advanced Synchronous and Asynchronous I/O         */
/********************************************************/
int CVIFUNC TDMS_AdvancedCloseFile (TDMSFileHandle file,
                                    int truncate,
                                    double timeoutInSec);

int CVIFUNC TDMS_AdvancedCreateFile (const char *filePath,
                                     TDMSFileFormat fileFormat,
                                     unsigned int options,
                                     const char *name,
                                     const char *description,
                                     const char *title,
                                     const char *author,
                                     TDMSFileHandle *file,
                                     size_t *sectorSize);

int CVIFUNC TDMS_AdvancedOpenFile (const char *filePath,
                                   int readOnly,
                                   unsigned int options,
                                   TDMSFileHandle *file,
                                   size_t *sectorSize);

int CVIFUNC TDMS_ReserveFileSize (TDMSFileHandle file,
                                  unsigned __int64 numReservedSamples,
                                  TDMSDataType dataType,
                                  TDMSReserveFileSizeMode reserveFileSizeMode);

int CVIFUNC TDMS_SetChannelInfo (TDMSChannelHandle channels[],
                                 size_t numChannels,
                                 size_t samplesPerChannel,
                                 TDMSDataLayout dataLayout);

int CVIFUNC TDMS_SetNextReadPosition (TDMSChannelHandle channel,
                                      __int64 offset,
                                      TDMSOffsetReferencePoint offsetReferencePoint);

int CVIFUNC TDMS_SetNextWritePosition (TDMSChannelHandle channel,
                                       __int64 offset,
                                       TDMSOffsetReferencePoint offsetReferencePoint);

/********************************************************/
/* -> Advanced Asynchronous I/O                         */
/********************************************************/
int CVIFUNC TDMS_AdvancedAsyncRead (TDMSFileHandle file,
                                    void *samples,
                                    size_t numSamples,
                                    TDMSDataType dataType,
                                    TDMSAsyncReadCallbackPtr callback,
                                    void *callbackData,
                                    int *readProcessFinished);

int CVIFUNC TDMS_AdvancedAsyncWrite (TDMSFileHandle file,
                                     void *samples,
                                     size_t numSamples,
                                     TDMSDataType dataType,
                                     TDMSAsyncWriteCallbackPtr callback,
                                     void *callbackData);

int CVIFUNC TDMS_ConfigureAsyncReads (TDMSFileHandle file,
                                      unsigned int maxNumConcurrentAsyncReads,
                                      __int64 totalSamplesToRead,
                                      TDMSDataType dataType,
                                      double readTimeoutInSec);

int CVIFUNC TDMS_ConfigureAsyncWrites (TDMSFileHandle file,
                                       unsigned int maxNumConcurrentAsyncWrites,
                                       double writeTimeoutInSec);

int CVIFUNC TDMS_GetAsyncReadStatus (TDMSFileHandle file,
                                     unsigned int *numPendingReads);

int CVIFUNC TDMS_GetAsyncWriteStatus (TDMSFileHandle file,
                                      unsigned int *numPendingWrites);
/********************************************************/
/* <- Advanced Asynchronous I/O                         */
/********************************************************/

/********************************************************/
/* -> Advanced Synchronous I/O                          */
/********************************************************/
int CVIFUNC TDMS_AdvancedSyncRead (TDMSFileHandle file,
                                   void *samples,
                                   size_t numSamples,
                                   TDMSDataType dataType,
                                   size_t *numSamplesRead);

int CVIFUNC TDMS_AdvancedSyncWrite (TDMSFileHandle file,
                                    void *samples,
                                    size_t numSamples,
                                    TDMSDataType dataType);

/********************************************************/
/* <- Advanced Synchronous I/O                          */
/********************************************************/
/********************************************************/
/* <- Advanced Synchronous and Asynchronous I/O         */
/********************************************************/

/********************************************************/
/* -> In-memory TDMS         */
/********************************************************/
int CVIFUNC TDMS_CreateInMemoryFile (const char *name,
                                     const char *description,
                                     const char *title,
                                     const char *author,
                                     TDMSFileHandle *file);

int CVIFUNC TDMS_OpenInMemoryFileFromData (const void* data,
                                           unsigned __int64 numBytes,
                                           TDMSFileHandle *file);

int CVIFUNC TDMS_OpenInMemoryFileFromDisk (const char *filePath,
                                           TDMSFileHandle *file);

int CVIFUNC TDMS_SaveInMemoryFileToDisk (TDMSFileHandle file,
                                         const char *filePath,
                                         int overWrite);

int CVIFUNC TDMS_GetInMemoryFileSize (TDMSFileHandle file,
                                      unsigned __int64 *fileSizeInBytes);

int CVIFUNC TDMS_ReadInMemoryFileBytes (TDMSFileHandle file,
                                        unsigned __int64 offset,
                                        void *data,
                                        unsigned __int64 numBytesToRead,
                                        unsigned __int64 *actualNumBytesRead);

/********************************************************/
/* -> Miscellaneous                                     */
/********************************************************/
const char * CVIFUNC TDMS_GetLibraryErrorDescription (int errorCode);

void CVIFUNC TDMS_FreeMemory (void *memoryPointer);

int CVIFUNC TDMS_FlushFile (TDMSFileHandle file);

int CVIFUNC TDMS_ConvertFileFormat (const char *filePath, 
                                    TDMSFileFormat newFileFormat);

int CVIFUNC TDMS_GetFileFormat (const char *filePath, 
                                TDMSFileFormat *fileFormat);

int CVIFUNC TDMS_DefragmentFile (const char *filePath);

int CVIFUNC TDMS_CloseChannelGroup (TDMSChannelGroupHandle channelGroup);

int CVIFUNC TDMS_CloseChannel (TDMSChannelHandle channel);

int CVIFUNC TDMS_AllocateAlignedMemory (size_t memorySize, 
                                        size_t memoryAlignment, 
                                        void *memoryPointer);

void CVIFUNC TDMS_FreeAlignedMemory (void *memoryPointer);

int CVIFUNC TDMS_GetDataTypeSize (TDMSDataType dataType, size_t *size);

#ifdef _NI_linux_
int CVIFUNC TDMS_Uninitialize();
#endif 

/********************************************************/
/* <- Miscellaneous                                     */
/********************************************************/

/********************************************************/
/* -> Separate functions for use with UTF-8 strings     */
/********************************************************/

/*
 This group of functions uses UTF-8 encoding for all string values passed as
 input or output parameters. In all other respects, these functions behave the
 same as corresponding functions without the "Utf8" suffix. As these functions 
 are not fully documented, please contact NI support with questions.
*/

int CVIFUNC TDMS_CreateFileExUtf8 (const char *filePath,
                                   TDMSFileFormat fileFormat,
                                   TDMSByteOrder byteOrder,
                                   unsigned int options,
                                   const char *name,
                                   const char *description,
                                   const char *title,
                                   const char *author,
                                   TDMSFileHandle *file);

int CVIFUNC TDMS_CreateInMemoryFileUtf8 (const char *name,
                                         const char *description,
                                         const char *title,
                                         const char *author,
                                         TDMSFileHandle *file);

int CVIFUNC TDMS_OpenFileExUtf8 (const char *filePath,
                                 int readOnly,
                                 unsigned int options,
                                 TDMSFileHandle *file);


int CVIFUNC TDMS_OpenInMemoryFileFromDiskUtf8 (const char* filePath,
                                               TDMSFileHandle *file);

int CVIFUNC TDMS_SaveInMemoryFileToDiskUtf8 (TDMSFileHandle file,
                                             const char *filePath,
                                             int overWrite);

int CVIFUNC TDMS_DefragmentFileUtf8 (const char *filePath);

int CVIFUNC TDMS_AddChannelGroupUtf8 (TDMSFileHandle file,
                                      const char *name,
                                      const char *description,
                                      TDMSChannelGroupHandle *channelGroup);

int CVIFUNC TDMS_AddChannelUtf8 (TDMSChannelGroupHandle channelGroup,
                                 TDMSDataType dataType,
                                 const char *name,
                                 const char *description,
                                 const char *unitString,
                                 TDMSChannelHandle *channel);

int CVIFUNC TDMS_AppendDataValuesMultiChannelUtf8 (TDMSChannelHandle channels[],
                                                   size_t numChannels,
                                                   void *values,
                                                   size_t numValues,
                                                   TDMSDataLayout dataLayout,
                                                   int saveFile);

int CVIFUNC TDMS_AppendDataValuesUtf8 (TDMSChannelHandle channel,
                                       void *values,
                                       size_t numValues,
                                       int saveFile);

int CVIFUNC TDMS_GetChannelGroupByNameUtf8 (TDMSFileHandle file,
                                            const char *name,
                                            TDMSChannelGroupHandle *channelGroup);

int CVIFUNC TDMS_GetChannelByNameUtf8 (TDMSChannelGroupHandle channelGroup,
                                       const char *name,
                                       TDMSChannelHandle *channel);

int CVIFUNC TDMS_GetChannelGroupAndChannelByNameUtf8 (TDMSFileHandle file,
                                                      const char *channelGroupName,
                                                      const char *channelName,
                                                      TDMSChannelGroupHandle *channelGroup,
                                                      TDMSChannelHandle *channel);

int CVIFUNC TDMS_GetDataValuesExUtf8 (TDMSChannelHandle channel,
                                      unsigned __int64 indexOfFirstValueToGet,
                                      size_t numValuesToGet,
                                      void *values);

int CVIFUNC TDMS_SetFilePropertyTimestampComponentsUtf8 (TDMSFileHandle file,
                                                         const char *property,
                                                         unsigned int year, 
                                                         unsigned int month, 
                                                         unsigned int day,
                                                         unsigned int hour, 
                                                         unsigned int minute, 
                                                         unsigned int second, 
                                                         double milliSecond);

int CVIFUNC_C TDMS_SetFilePropertyUtf8 (TDMSFileHandle file,
                                        const char *property,
                                        TDMSDataType dataType,
                                        ...);

int CVIFUNC TDMS_SetFilePropertyUtf8V (TDMSFileHandle file,
                                       const char *property,
                                       TDMSDataType dataType,
                                       va_list args);

int CVIFUNC TDMS_GetFilePropertyTimestampComponentsUtf8 (TDMSFileHandle file,
                                                         const char *property,
                                                         unsigned int *year, 
                                                         unsigned int *month, 
                                                         unsigned int *day,
                                                         unsigned int *hour, 
                                                         unsigned int *minute, 
                                                         unsigned int *second, 
                                                         double *milliSecond,
                                                         unsigned int *weekDay);

int CVIFUNC TDMS_GetFilePropertyUtf8 (TDMSFileHandle file,
                                      const char *property,
                                      void *value,
                                      size_t valueSizeInBytes);

int CVIFUNC TDMS_GetFileStringPropertyLengthUtf8 (TDMSFileHandle file,
                                                  const char *property,
                                                  unsigned int *length);

int CVIFUNC TDMS_FilePropertyExistsUtf8 (TDMSFileHandle file,
                                         const char *property,
                                         int *exists);

int CVIFUNC TDMS_GetFilePropertyNamesUtf8(TDMSFileHandle file, 
                                          char** propertyNames, 
                                          size_t numPropertyNames);

int CVIFUNC TDMS_GetFilePropertyTypeUtf8 (TDMSFileHandle file,
                                          const char *property,
                                          TDMSDataType *dataType);

int CVIFUNC TDMS_SetChannelGroupPropertyTimestampComponentsUtf8 (TDMSChannelGroupHandle channelGroup,
                                                                 const char *property,
                                                                 unsigned int year, 
                                                                 unsigned int month, 
                                                                 unsigned int day,
                                                                 unsigned int hour, 
                                                                 unsigned int minute, 
                                                                 unsigned int second, 
                                                                 double milliSecond);

int CVIFUNC_C TDMS_SetChannelGroupPropertyUtf8 (TDMSChannelGroupHandle channelGroup,
                                                const char *property,
                                                TDMSDataType dataType,
                                                ...);

int CVIFUNC TDMS_SetChannelGroupPropertyUtf8V (TDMSChannelGroupHandle channelGroup,
                                               const char *property,
                                               TDMSDataType dataType,
                                               va_list args);

int CVIFUNC TDMS_GetChannelGroupPropertyTimestampComponentsUtf8 (TDMSChannelGroupHandle channelGroup,
                                                                 const char *property,
                                                                 unsigned int *year, 
                                                                 unsigned int *month, 
                                                                 unsigned int *day,
                                                                 unsigned int *hour, 
                                                                 unsigned int *minute, 
                                                                 unsigned int *second, 
                                                                 double *milliSecond,
                                                                 unsigned int *weekDay);

int CVIFUNC TDMS_GetChannelGroupPropertyUtf8 (TDMSChannelGroupHandle channelGroup,
                                              const char *property,
                                              void *value,
                                              size_t valueSizeInBytes);

int CVIFUNC TDMS_GetChannelGroupStringPropertyLengthUtf8 (TDMSChannelGroupHandle channelGroup,
                                                          const char *property,
                                                          unsigned int *length);

int CVIFUNC TDMS_ChannelGroupPropertyExistsUtf8 (TDMSChannelGroupHandle channelGroup,
                                                 const char *property,
                                                 int *exists);

int CVIFUNC TDMS_GetChannelGroupPropertyNamesUtf8 (TDMSChannelGroupHandle channelGroup, 
                                                   char** propertyNames,
                                                   size_t numPropertyNames);

int CVIFUNC TDMS_GetChannelGroupPropertyTypeUtf8 (TDMSChannelGroupHandle channelGroup,
                                                  const char *property,
                                                  TDMSDataType *dataType);

int CVIFUNC TDMS_SetChannelPropertyTimestampComponentsUtf8 (TDMSChannelHandle channel,
                                                            const char *property,
                                                            unsigned int year, 
                                                            unsigned int month, 
                                                            unsigned int day,
                                                            unsigned int hour, 
                                                            unsigned int minute, 
                                                            unsigned int second, 
                                                            double milliSecond);

int CVIFUNC_C TDMS_SetChannelPropertyUtf8 (TDMSChannelHandle channel,
                                           const char *property, 
                                           TDMSDataType dataType,
                                           ...);

int CVIFUNC TDMS_SetChannelPropertyUtf8V (TDMSChannelHandle channel,
                                          const char *property, 
                                          TDMSDataType dataType,
                                          va_list args);

int CVIFUNC TDMS_GetChannelPropertyTimestampComponentsUtf8 (TDMSChannelHandle channel,
                                                            const char *property,
                                                            unsigned int *year, 
                                                            unsigned int *month, 
                                                            unsigned int *day,
                                                            unsigned int *hour, 
                                                            unsigned int *minute, 
                                                            unsigned int *second, 
                                                            double *milliSecond,
                                                            unsigned int *weekDay);

int CVIFUNC TDMS_GetChannelPropertyUtf8 (TDMSChannelHandle channel,
                                         const char *property,
                                         void *value,
                                         size_t valueSizeInBytes);

int CVIFUNC TDMS_GetChannelStringPropertyLengthUtf8 (TDMSChannelHandle channel,
                                                     const char *property,
                                                     unsigned int *length);

int CVIFUNC TDMS_ChannelPropertyExistsUtf8 (TDMSChannelHandle channel,
                                            const char *property,
                                            int *exists);

int CVIFUNC TDMS_GetChannelPropertyNamesUtf8(TDMSChannelHandle channel, 
                                             char** propertyNames, 
                                             size_t numPropertyNames);

int CVIFUNC TDMS_GetChannelPropertyTypeUtf8 (TDMSChannelHandle channel,
                                             const char *property,
                                             TDMSDataType *dataType);

int CVIFUNC TDMS_ConvertFileFormatUtf8 (const char *filePath, 
                                        TDMSFileFormat newFileFormat);

int CVIFUNC TDMS_GetFileFormatUtf8 (const char *filePath, 
                                    TDMSFileFormat *fileFormat);

int CVIFUNC TDMS_AdvancedCreateFileUtf8 (const char *filePath,
                                         TDMSFileFormat fileFormat,
                                         unsigned int options,
                                         const char *name,
                                         const char *description,
                                         const char *title,
                                         const char *author,
                                         TDMSFileHandle *file,
                                         size_t *sectorSize);

int CVIFUNC TDMS_AdvancedOpenFileUtf8 (const char *filePath,
                                       int readOnly,
                                       unsigned int options,
                                       TDMSFileHandle *file,
                                       size_t *sectorSize);


/****************************************************************/
/* <- Separate functions for use with UTF-8 strings             */
/****************************************************************/

/****************************************************************/
/* -> Separate timestamp functions for non-C users              */
/****************************************************************/
int CVIFUNC TDMS_AppendDataValuesTimestampComponents (TDMSChannelHandle channel,
                                                      unsigned int year[], 
                                                      unsigned int month[], 
                                                      unsigned int day[],
                                                      unsigned int hour[], 
                                                      unsigned int minute[], 
                                                      unsigned int second[],
                                                      double milliSecond[],
                                                      size_t numValues,
                                                      int saveFile);

int CVIFUNC TDMS_AppendDataValuesMultiChannelTimestampComponents (TDMSChannelHandle channels[],
                                                                  size_t numChannels,
                                                                  unsigned int year[], 
                                                                  unsigned int month[], 
                                                                  unsigned int day[],
                                                                  unsigned int hour[], 
                                                                  unsigned int minute[], 
                                                                  unsigned int second[],
                                                                  double milliSecond[],
                                                                  size_t numValues,
                                                                  TDMSDataLayout dataLayout,
                                                                  int saveFile);

int CVIFUNC TDMS_GetDataValuesTimestampComponents (TDMSChannelHandle channel,
                                                   unsigned __int64 indexOfFirstValueToGet,
                                                   size_t numValuesToGet,
                                                   unsigned int year[], 
                                                   unsigned int month[], 
                                                   unsigned int day[],
                                                   unsigned int hour[], 
                                                   unsigned int minute[], 
                                                   unsigned int second[],
                                                   double milliSecond[],
                                                   unsigned int weekDay[]);

int CVIFUNC TDMS_SetFilePropertyTimestampComponents (TDMSFileHandle file,
                                                     const char *property,
                                                     unsigned int year, 
                                                     unsigned int month, 
                                                     unsigned int day,
                                                     unsigned int hour, 
                                                     unsigned int minute, 
                                                     unsigned int second, 
                                                     double milliSecond);

int CVIFUNC TDMS_GetFilePropertyTimestampComponents (TDMSFileHandle file,
                                                     const char *property,
                                                     unsigned int *year, 
                                                     unsigned int *month, 
                                                     unsigned int *day,
                                                     unsigned int *hour, 
                                                     unsigned int *minute, 
                                                     unsigned int *second, 
                                                     double *milliSecond,
                                                     unsigned int *weekDay);

int CVIFUNC TDMS_SetChannelGroupPropertyTimestampComponents (TDMSChannelGroupHandle channelGroup,
                                                             const char *property,
                                                             unsigned int year, 
                                                             unsigned int month, 
                                                             unsigned int day,
                                                             unsigned int hour, 
                                                             unsigned int minute, 
                                                             unsigned int second, 
                                                             double milliSecond);

int CVIFUNC TDMS_GetChannelGroupPropertyTimestampComponents (TDMSChannelGroupHandle channelGroup,
                                                             const char *property,
                                                             unsigned int *year, 
                                                             unsigned int *month, 
                                                             unsigned int *day,
                                                             unsigned int *hour, 
                                                             unsigned int *minute, 
                                                             unsigned int *second, 
                                                             double *milliSecond,
                                                             unsigned int *weekDay);

int CVIFUNC TDMS_SetChannelPropertyTimestampComponents (TDMSChannelHandle channel,
                                                        const char *property,
                                                        unsigned int year, 
                                                        unsigned int month, 
                                                        unsigned int day,
                                                        unsigned int hour, 
                                                        unsigned int minute, 
                                                        unsigned int second, 
                                                        double milliSecond);

int CVIFUNC TDMS_GetChannelPropertyTimestampComponents (TDMSChannelHandle channel,
                                                        const char *property,
                                                        unsigned int *year, 
                                                        unsigned int *month, 
                                                        unsigned int *day,
                                                        unsigned int *hour, 
                                                        unsigned int *minute, 
                                                        unsigned int *second, 
                                                        double *milliSecond,
                                                        unsigned int *weekDay);

/****************************************************************/
/* <- Separate timestamp functions for non-C users              */
/****************************************************************/

#if defined(_CVI_) && !defined(__TPC__)
#pragma PassOrigPtrInfoForVoidPtrParam TDMS_AllocateAlignedMemory
#endif

#ifdef __cplusplus
    }
#endif

#endif /* !defined(_NILIBTDMS_H) */
