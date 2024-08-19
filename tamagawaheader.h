#include <windows.h>

#include <wdf.h>


#include <hidport.h> 


#include "common.h"



typedef UCHAR HID_REPORT_DESCRIPTOR, * PHID_REPORT_DESCRIPTOR;

DRIVER_INITIALIZE                   DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD           EvtDeviceAdd;
EVT_WDF_TIMER                       EvtTimerFunc;

typedef struct _DEVICE_CONTEXT
{
    WDFDEVICE               Device;
    WDFQUEUE                DefaultQueue;
    WDFQUEUE                ManualQueue;
    HID_DEVICE_ATTRIBUTES   HidDeviceAttributes;
    BYTE                    DeviceData;
    BYTE                    Button;
    INT16                   X;
    INT16                   Y;
    UCHAR ShiftKeyFlags;
    UCHAR Reserved;
    UCHAR KeyCodes[KBD_KEY_CODES];
    HID_DESCRIPTOR          HidDescriptor;
    PHID_REPORT_DESCRIPTOR  ReportDescriptor;
    BOOLEAN                 ReadReportDescFromRegistry;

} DEVICE_CONTEXT, * PDEVICE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(DEVICE_CONTEXT, GetDeviceContext);

typedef struct _QUEUE_CONTEXT
{
    WDFQUEUE                Queue;
    PDEVICE_CONTEXT         DeviceContext;
    UCHAR                   OutputReport;
    BYTE                    Button;
    INT16                   X;
    INT16                   Y;
    UCHAR ShiftKeyFlags;
    UCHAR Reserved;
    UCHAR KeyCodes[KBD_KEY_CODES];

} QUEUE_CONTEXT, *PQUEUE_CONTEXT;

WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(QUEUE_CONTEXT, GetQueueContext);



typedef struct _MANUAL_QUEUE_CONTEXT
{
    WDFQUEUE                Queue;
    PDEVICE_CONTEXT         DeviceContext;
    WDFTIMER                Timer;

} MANUAL_QUEUE_CONTEXT, *PMANUAL_QUEUE_CONTEXT;


WDF_DECLARE_CONTEXT_TYPE_WITH_NAME(MANUAL_QUEUE_CONTEXT, GetManualQueueContext);



NTSTATUS
QueueCreate(
    _In_  WDFDEVICE         Device,
    _Out_ WDFQUEUE* Queue
);



NTSTATUS
ReadReport(
    _In_  PQUEUE_CONTEXT    QueueContext,
    _In_  WDFREQUEST        Request,
    _Always_(_Out_)
    BOOLEAN* CompleteRequest
);

NTSTATUS
WriteReport(
    _In_  PQUEUE_CONTEXT    QueueContext,
    _In_  WDFREQUEST        Request
);



NTSTATUS
RequestGetHidXferPacket_ToWriteToDevice(
    _In_  WDFREQUEST        Request,
    _Out_ HID_XFER_PACKET* Packet
);

NTSTATUS
RequestCopyFromBuffer(
    _In_  WDFREQUEST        Request,
    _In_  PVOID             SourceBuffer,
    _When_(NumBytesToCopyFrom == 0, __drv_reportError(NumBytesToCopyFrom cannot be zero))
    _In_  size_t            NumBytesToCopyFrom
);

NTSTATUS
CheckRegistryForDescriptor(
    _In_ WDFDEVICE Device
);

NTSTATUS
ReadDescriptorFromRegistry(
    _In_ WDFDEVICE Device
);



#define HIDMINI_PID             0xFEED
#define HIDMINI_VID             0xDEED
#define HIDMINI_VERSION         0x0101

#define CONTROL_FEATURE_REPORT_ID   0x01
#define M_CONTROL_FEATURE_REPORT_ID  0x02  
#define K_CONTROL_FEATURE_REPORT_ID  0x03  