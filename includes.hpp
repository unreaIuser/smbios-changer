#pragma once

#include <ntddk.h>
#include <winternl.h>

#include "smbios_informations.h"

#define SMBIOS_TYPE_BASEBOARD_INFORMATION 2 // GOOD (old value was wrong)
#define SMBIOS_STRING_MAX_LENGTH 256 

typedef struct _SMBIOS_DATA
{
    ULONG Length;
    UCHAR SMBIOSData[1];
} SMBIOS_DATA, * PSMBIOS_DATA;

typedef struct _SMBIOS_STRUCTURE_HEADER
{
    UCHAR Type;
    UCHAR Length;
    USHORT Handle;
} SMBIOS_STRUCTURE_HEADER, * PSMBIOS_STRUCTURE_HEADER;

typedef struct _SMBIOS_BASEBOARD_INFORMATION
{
    SMBIOS_STRUCTURE_HEADER Header;
    UCHAR Manufacturer;
    UCHAR Product;
    UCHAR Version;
    UCHAR SerialNumber;
    UCHAR AssetTag;
} SMBIOS_BASEBOARD_INFORMATION, * PSMBIOS_BASEBOARD_INFORMATION;

// very undetected smbios structure