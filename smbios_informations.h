PVOID GetSMBIOSInformation(UCHAR Type)
{
    // Set initial values
    ULONG BufferSize = 0;
    PVOID SMBIOSInformation = NULL;
    SYSTEM_INFORMATION_CLASS SystemInformationClass = SystemBasicInformation;

    // Get size of buffer needed to hold SMBIOS information
    NtQuerySystemInformation(SystemInformationClass, &SMBIOSInformation, 0, &BufferSize);

    // Check if buffer size is 0 (if you didnt know that ur def a nigger)
    if (BufferSize == 0)
        return NULL;

    // Allocate memory for basic system information
    PSYSTEM_BASIC_INFORMATION BasicInformation = ExAllocatePoolWithTag(PagedPool, BufferSize, 'Smb ');

    // Check if memory allocation was successful
    if (!BasicInformation)
        return NULL;

    // Get basic system information and store it in BasicInformation
    NTSTATUS Status = NtQuerySystemInformation(SystemInformationClass, BasicInformation, BufferSize, &BufferSize);

    // Check if getting system information was successful
    if (!NT_SUCCESS(Status))
    {
        ExFreePool(BasicInformation);
        return NULL;
    }

    // Get SMBIOS data from BasicInformation
    PSMBIOS_DATA SMBIOSData = (PSMBIOS_DATA)BasicInformation->Reserved2;

    // Loop through SMBIOS data to find data of requested type
    while (SMBIOSData->Length != 0)
    {
        if (SMBIOSData->SMBIOSData[0] == Type)
        {
            SMBIOSInformation = SMBIOSData->SMBIOSData;
            break;
        }

        SMBIOSData = (PSMBIOS_DATA)((PUCHAR)SMBIOSData + SMBIOSData->Length);
    }

    // Free memory used for BasicInformation
    ExFreePool(BasicInformation);

    // Return SMBIOS information of requested type
    return SMBIOSInformation;
}