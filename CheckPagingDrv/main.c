#include <ntddk.h>
#include <intrin.h>

NTSTATUS DispatchDriverEntry
(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
)
{
    UINT64 cr0 = __readcr0();
    BOOLEAN PagingEnabled = cr0 & 0x31;

    DbgPrint("Paging Flag 31th bit of CR0 is %c\n", PagingEnabled ? '1' : '0');

    return STATUS_SUCCESS;
}

//
// this will be called when the driver being unloaded
//
VOID
Unload
(
    IN PDRIVER_OBJECT DriverObject
)
{
    UNREFERENCED_PARAMETER(DriverObject);
}

//
// this will be called after the driver loaded
//
NTSTATUS DriverInitialize
(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
)
{
    UNREFERENCED_PARAMETER(DriverObject);
    UNREFERENCED_PARAMETER(RegistryPath);

    return STATUS_SUCCESS;
}

//
// main entry point of this driver
//
NTSTATUS DriverEntry
(
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
)
{
    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->DriverUnload = Unload;

    return DispatchDriverEntry(DriverObject, RegistryPath);
}