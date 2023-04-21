#include "includes.hpp"

VOID SpoofSerialNumber()
{ 
    // Retrieving SMBIOS Informations
    PSMBIOS_BASEBOARD_INFORMATION BaseboardInformation = (PSMBIOS_BASEBOARD_INFORMATION)GetSMBIOSInformation(SMBIOS_TYPE_BASEBOARD_INFORMATION);

    if (BaseboardInformation)
    {
        // Define a new serial number to be spoofed with
        CHAR SerialNumber[SMBIOS_STRING_MAX_LENGTH] = "rokaspoofer-1525440";

        // Copy the new serial number to the BaseboardInformation structure
        RtlCopyMemory(&BaseboardInformation->SerialNumber, SerialNumber, strlen(SerialNumber) + 1);

        // lol
        DbgPrint("Serial Number spoofed to %s\n", SerialNumber);
    }
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    SpoofSerialNumber();

    DriverObject->DriverUnload = NULL;

    return STATUS_SUCCESS;
}