#include "tamagawaheader.h"


#define DOS_DEVICE_NAME L"\\DosDevices\\Tamagawa2Driver"

HID_REPORT_DESCRIPTOR       G_DefaultReportDescriptor[] = {

    0x06,0x00, 0xFF,                // USAGE_PAGE (Vender Defined Usage Page)
    0x09,0x01,                      // USAGE (Vendor Usage 0x01)
    0xA1,0x01,                      // COLLECTION (Application)
    0x85,CONTROL_FEATURE_REPORT_ID,    // REPORT_ID (1)
    0x09,0x01,                         // USAGE (Vendor Usage 0x01)
    0x15,0x00,                         // LOGICAL_MINIMUM(0)
    0x26,0xff, 0x00,                   // LOGICAL_MAXIMUM(255)
    0x75,0x08,                         // REPORT_SIZE (0x08)
    0x96,(FEATURE_REPORT_SIZE_CB & 0xff), (FEATURE_REPORT_SIZE_CB >> 8), // REPORT_COUNT
    0xB1,0x00,                         // FEATURE (Data,Ary,Abs)
    0x09,0x01,                         // USAGE (Vendor Usage 0x01)
    0x75,0x08,                         // REPORT_SIZE (0x08)
    0x96,(INPUT_REPORT_SIZE_CB & 0xff), (INPUT_REPORT_SIZE_CB >> 8), // REPORT_COUNT
    0x81,0x00,                         // INPUT (Data,Ary,Abs)
    0x09,0x01,                         // USAGE (Vendor Usage 0x01)
    0x75,0x08,                         // REPORT_SIZE (0x08)
    0x96,(OUTPUT_REPORT_SIZE_CB & 0xff), (OUTPUT_REPORT_SIZE_CB >> 8), // REPORT_COUNT
    0x91,0x00,                         // OUTPUT (Data,Ary,Abs)
    0xC0,                           // END_COLLECTION

    0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
    0x09, 0x02,                    // USAGE (Mouse)
    0xa1, 0x01,                    // COLLECTION (Application)
    0x85, M_CONTROL_FEATURE_REPORT_ID,    // REPORT_ID (2)
    0x09, 0x01,                    //   USAGE (Pointer)
    0xa1, 0x00,                    //   COLLECTION (Physical)
    0x05, 0x09,                    //     USAGE_PAGE (Button)
    0x19, 0x01,                    //     USAGE_MINIMUM (Button 1)
    0x29, 0x03,                    //     USAGE_MAXIMUM (Button 3)
    0x15, 0x00,                    //     LOGICAL_MINIMUM (0)
    0x25, 0x01,                    //     LOGICAL_MAXIMUM (1)
    0x95, 0x03,                    //     REPORT_COUNT (3)
    0x75, 0x01,                    //     REPORT_SIZE (1)
    0x81, 0x02,                    //     INPUT (Data,Var,Abs)
    0x95, 0x01,                    //     REPORT_COUNT (1)
    0x75, 0x05,                    //     REPORT_SIZE (5)
    0x81, 0x01,                    //     INPUT (Cnst,Ary,Abs)
    0x05, 0x01,                    //     USAGE_PAGE (Generic Desktop)
    0x09, 0x30,                    //     USAGE (X)
    0x09, 0x31,                    //     USAGE (Y)
    0x16, 0x01, 0x80,              //     LOGICAL_MINIMUM (-32767)
    0x26, 0xff, 0x7f,              //     LOGICAL_MAXIMUM (32767)
    0x75, 0x10,                    //     REPORT_SIZE (16)
    0x95, 0x02,                    //     REPORT_COUNT (2)
    0x81, 0x06,                    //     INPUT (Data,Var,Rel)
    0xc0,                          //     END_COLLECTION
    0xc0,                           // END_COLLECTION

    0x05, 0x01,                         // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,                         // USAGE (Keyboard)
    0xa1, 0x01,                         // COLLECTION (Application)
    0x85, K_CONTROL_FEATURE_REPORT_ID,            //   REPORT_ID (3)    
    0x05, 0x07,                         //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,                         //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,                         //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,                         //   LOGICAL_MINIMUM (0)
    0x25, 0x01,                         //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,                         //   REPORT_SIZE (1)
    0x95, 0x08,                         //   REPORT_COUNT (8)
    0x81, 0x02,                         //   INPUT (Data,Var,Abs)
    0x95, 0x01,                         //   REPORT_COUNT (1)
    0x75, 0x08,                         //   REPORT_SIZE (8)
    0x81, 0x03,                         //   INPUT (Cnst,Var,Abs)
    0x95, 0x06,                         //   REPORT_COUNT (6)
    0x75, 0x08,                         //   REPORT_SIZE (8)
    0x15, 0x00,                         //   LOGICAL_MINIMUM (0)
    0x25, 0x65,                         //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,                         //   USAGE_PAGE (Keyboard)
    0x19, 0x00,                         //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,                         //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,                         //   INPUT (Data,Ary,Abs)
    0xc0,                               // END_COLLECTION

};


HID_DESCRIPTOR              G_DefaultHidDescriptor = {
    0x09,   // length of HID descriptor
    0x21,   // descriptor type == HID  0x21
    0x0100, // hid spec release
    0x00,   // country code == Not Specified
    0x01,   // number of HID class descriptors
    {                                       //DescriptorList[0]
        0x22,                               //report descriptor type 0x22
        sizeof(G_DefaultReportDescriptor)   //total length of report descriptor
    }
};


NTSTATUS DriverEntry(_In_  PDRIVER_OBJECT    DriverObject, _In_  PUNICODE_STRING   RegistryPath) {

    WDF_DRIVER_CONFIG       config;
    NTSTATUS                status;

    WDF_DRIVER_CONFIG_INIT(&config, EvtDeviceAdd);

    status = WdfDriverCreate(DriverObject,
        RegistryPath,
        WDF_NO_OBJECT_ATTRIBUTES,
        &config,
        WDF_NO_HANDLE);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Error: WdfDriverCreate failed 0x%x\n", status));
        return status;
    }

    return status;


}

NTSTATUS
EvtDeviceAdd(
    _In_  WDFDRIVER         Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
) {

    NTSTATUS                status;
    WDF_OBJECT_ATTRIBUTES   deviceAttributes;
    WDFDEVICE               device;
    PDEVICE_CONTEXT         deviceContext;
    PHID_DEVICE_ATTRIBUTES  hidAttributes;
    UNREFERENCED_PARAMETER(Driver);


    WdfFdoInitSetFilter(DeviceInit);
    
    

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(
        &deviceAttributes,
        DEVICE_CONTEXT);

    status = WdfDeviceCreate(&DeviceInit,
        &deviceAttributes,
        &device);
    if (!NT_SUCCESS(status)) {
        KdPrint(("Error: WdfDeviceCreate failed 0x%x\n", status));
        return status;
    }


    deviceContext = GetDeviceContext(device);
    deviceContext->Device = device;
    deviceContext->DeviceData = 0;
    deviceContext->Button = 0;
    deviceContext->X = 0;
    deviceContext->Y = 0;
    deviceContext->ShiftKeyFlags = 0;
    deviceContext->Reserved = 0;

    for (int i = 0; i < KBD_KEY_CODES; i++) {
        deviceContext->KeyCodes[i] = 0;
    }
    



    hidAttributes = &deviceContext->HidDeviceAttributes;
    RtlZeroMemory(hidAttributes, sizeof(HID_DEVICE_ATTRIBUTES));
    hidAttributes->Size = sizeof(HID_DEVICE_ATTRIBUTES);
    hidAttributes->VendorID = HIDMINI_VID;
    hidAttributes->ProductID = HIDMINI_PID;
    hidAttributes->VersionNumber = HIDMINI_VERSION;

    


     //シンボリックリンク
    DECLARE_CONST_UNICODE_STRING(symboriclink, DOS_DEVICE_NAME);
    WdfDeviceCreateSymbolicLink(device, &symboriclink);

    status = QueueCreate(device,
        &deviceContext->DefaultQueue);
    if (!NT_SUCCESS(status)) {
        return status;
    }


    deviceContext->HidDescriptor = G_DefaultHidDescriptor;

    status = CheckRegistryForDescriptor(device);
    if (NT_SUCCESS(status)) {
        //
        // We need to read read descriptor from registry
        //
        status = ReadDescriptorFromRegistry(device);
        if (!NT_SUCCESS(status)) {
            KdPrint(("Failed to read descriptor from registry\n"));
        }
    }

    //
    // We will use hard-coded report descriptor if registry one is not used.
    //
    if (!NT_SUCCESS(status)) {
        deviceContext->ReportDescriptor = G_DefaultReportDescriptor;
        KdPrint(("Using Hard-coded Report descriptor\n"));
        status = STATUS_SUCCESS;
    }


    return status;


}



EVT_WDF_IO_QUEUE_IO_DEVICE_CONTROL          EvtIoDeviceControl;


NTSTATUS
QueueCreate(
    _In_  WDFDEVICE         Device,
    _Out_ WDFQUEUE* Queue
) {

    NTSTATUS                status;
    WDF_IO_QUEUE_CONFIG     queueConfig;
    WDF_OBJECT_ATTRIBUTES   queueAttributes;
    WDFQUEUE                queue;
    PQUEUE_CONTEXT          queueContext;

    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(
        &queueConfig,
        WdfIoQueueDispatchParallel);

    queueConfig.EvtIoDeviceControl = EvtIoDeviceControl;

    WDF_OBJECT_ATTRIBUTES_INIT_CONTEXT_TYPE(
        &queueAttributes,

        QUEUE_CONTEXT);

    status = WdfIoQueueCreate(
        Device,
        &queueConfig,
        &queueAttributes,
        &queue);

    queueContext = GetQueueContext(queue);
    queueContext->Queue = queue;
    queueContext->DeviceContext = GetDeviceContext(Device);
    queueContext->OutputReport = 0;
    

    *Queue = queue;
    return status;


}


VOID
EvtIoDeviceControl(
    _In_  WDFQUEUE          Queue,
    _In_  WDFREQUEST        Request,
    _In_  size_t            OutputBufferLength,
    _In_  size_t            InputBufferLength,
    _In_  ULONG             IoControlCode
) {

    NTSTATUS                status;
    BOOLEAN                 completeRequest = TRUE;
    WDFDEVICE               device = WdfIoQueueGetDevice(Queue);
    PDEVICE_CONTEXT         deviceContext = NULL;
    PQUEUE_CONTEXT          queueContext = GetQueueContext(Queue);
    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(InputBufferLength);


    deviceContext = GetDeviceContext(device);

    switch (IoControlCode)
    {
    case IOCTL_HID_GET_DEVICE_DESCRIPTOR:   // METHOD_NEITHER
    //
    // Retrieves the device's HID descriptor.
    //
        _Analysis_assume_(deviceContext->HidDescriptor.bLength != 0);
        status = RequestCopyFromBuffer(Request,
            &deviceContext->HidDescriptor,
            deviceContext->HidDescriptor.bLength);
        break;

    case IOCTL_HID_GET_DEVICE_ATTRIBUTES:   // METHOD_NEITHER
        //
        //Retrieves a device's attributes in a HID_DEVICE_ATTRIBUTES structure.
        //
        status = RequestCopyFromBuffer(Request,
            &queueContext->DeviceContext->HidDeviceAttributes,
            sizeof(HID_DEVICE_ATTRIBUTES));
        break;

    case IOCTL_HID_GET_REPORT_DESCRIPTOR:   // METHOD_NEITHER
        //
        //Obtains the report descriptor for the HID device.
        //
        status = RequestCopyFromBuffer(Request,
            deviceContext->ReportDescriptor,
            deviceContext->HidDescriptor.DescriptorList[0].wReportLength);
        break;

    case IOCTL_HID_READ_REPORT:             // METHOD_NEITHER
    //
    // Returns a report from the device into a class driver-supplied
    // buffer.
    //
        status = ReadReport(queueContext, Request, &completeRequest);
        break;

    case IOCTL_HID_WRITE_REPORT:            // METHOD_NEITHER
        //
        // Transmits a class driver-supplied report to the device.
        //
        status = WriteReport(queueContext, Request);
        break;

    default:
        status = STATUS_NOT_IMPLEMENTED;
        break;

    }


    if (completeRequest) {
        WdfRequestComplete(Request, status);
    }
}


NTSTATUS
RequestGetHidXferPacket_ToWriteToDevice(
    _In_  WDFREQUEST        Request,
    _Out_ HID_XFER_PACKET* Packet
)
{


    NTSTATUS                status;
    WDFMEMORY               inputMemory;
    WDFMEMORY               outputMemory;
    size_t                  inputBufferLength;
    size_t                  outputBufferLength;
    PVOID                   inputBuffer;


    status = WdfRequestRetrieveOutputMemory(Request, &outputMemory);
    if (!NT_SUCCESS(status)) {
        KdPrint(("WdfRequestRetrieveOutputMemory failed 0x%x\n", status));
        return status;
    }
    WdfMemoryGetBuffer(outputMemory, &outputBufferLength);
    Packet->reportId = (UCHAR)outputBufferLength;


    status = WdfRequestRetrieveInputMemory(Request, &inputMemory);
    if (!NT_SUCCESS(status)) {
        KdPrint(("WdfRequestRetrieveInputMemory failed 0x%x\n", status));
        return status;
    }
    inputBuffer = WdfMemoryGetBuffer(inputMemory, &inputBufferLength);

    Packet->reportBuffer = (PUCHAR)inputBuffer;
    Packet->reportBufferLen = (ULONG)inputBufferLength;

    return status;
}


NTSTATUS
ReadReport(
    _In_  PQUEUE_CONTEXT    QueueContext,
    _In_  WDFREQUEST        Request,
    _Always_(_Out_)
    BOOLEAN* CompleteRequest
)

{
    NTSTATUS status = STATUS_SUCCESS;

    
    KdPrint(("ReadReport\n"));

    //
    // forward the request to manual queue
    //
    /*status = WdfRequestForwardToIoQueue(
        Request,
        QueueContext->DeviceContext->ManualQueue);*/

    if (QueueContext->DeviceContext->DeviceData == M_CONTROL_FEATURE_REPORT_ID)
    {
        HIDMINI_INPUT_REPORT    readReport;
        readReport.ReportId = QueueContext->DeviceContext->DeviceData;
        readReport.Button = QueueContext->DeviceContext->Button;
        readReport.X = QueueContext->DeviceContext->X;
        readReport.Y = QueueContext->DeviceContext->Y;

        status = RequestCopyFromBuffer(Request,
            &readReport,
            sizeof(readReport));


        QueueContext->DeviceContext->DeviceData = 0;
        QueueContext->DeviceContext->Button = 0;
        QueueContext->DeviceContext->X = 0;
        QueueContext->DeviceContext->Y = 0;
        QueueContext->DeviceContext->ShiftKeyFlags = 0;
        QueueContext->DeviceContext->Reserved = 0;

        for (int i = 0; i < KBD_KEY_CODES; i++) {
            QueueContext->DeviceContext->KeyCodes[i] = 0;
        }



    }
    else if (QueueContext->DeviceContext->DeviceData == K_CONTROL_FEATURE_REPORT_ID)
    {
        Key_INPUT readReport;

        readReport.ReportId = QueueContext->DeviceContext->DeviceData;
        readReport.ShiftKeyFlags = QueueContext->DeviceContext->ShiftKeyFlags;
        readReport.Reserved = QueueContext->DeviceContext->Reserved;

        for (int i = 0; i < KBD_KEY_CODES; i++) {
            readReport.KeyCodes[i] = QueueContext->DeviceContext->KeyCodes[i];
        }

        status = RequestCopyFromBuffer(Request,
            &readReport,
            sizeof(readReport));


        QueueContext->DeviceContext->DeviceData = 0;
        QueueContext->DeviceContext->Button = 0;
        QueueContext->DeviceContext->X = 0;
        QueueContext->DeviceContext->Y = 0;
        QueueContext->DeviceContext->ShiftKeyFlags = 0;
        QueueContext->DeviceContext->Reserved = 0;

        for (int i = 0; i < KBD_KEY_CODES; i++) {
            QueueContext->DeviceContext->KeyCodes[i] = 0;
        }

    }
        
    if (!NT_SUCCESS(status)) {
        KdPrint(("WdfRequestForwardToIoQueue failed with 0x%x\n", status));
        *CompleteRequest = TRUE;
    }
    else {
        *CompleteRequest = FALSE;
    }

    WdfRequestComplete(Request, status);
        
    
    

    return status;
}


NTSTATUS
WriteReport(
    _In_  PQUEUE_CONTEXT    QueueContext,
    _In_  WDFREQUEST        Request
)


{
    NTSTATUS                status;
    HID_XFER_PACKET         packet;
    
    
    KdPrint(("WriteReport\n"));

    status = RequestGetHidXferPacket_ToWriteToDevice(
        Request,
        &packet);
    if (!NT_SUCCESS(status)) {
        return status;
    }

    if (packet.reportId != CONTROL_FEATURE_REPORT_ID) {
        //
        // Return error for unknown collection
        //
        status = STATUS_INVALID_PARAMETER;
        KdPrint(("WriteReport: unkown report id %d\n", packet.reportId));
        return status;
    }

    
    PHIDMINI_OUTPUT_REPORT  outputReport;
    outputReport = (PHIDMINI_OUTPUT_REPORT)packet.reportBuffer;


    QueueContext->DeviceContext->DeviceData = outputReport->Data;

    //Mouse
    QueueContext->DeviceContext->Button = outputReport->Button;
    QueueContext->DeviceContext->X = outputReport->X;
    QueueContext->DeviceContext->Y = outputReport->Y;

    //Key
    QueueContext->DeviceContext->ShiftKeyFlags = outputReport->ShiftKeyFlags;
    QueueContext->DeviceContext->Reserved = outputReport->Reserved;

    for (int i = 0; i < KBD_KEY_CODES; i++) {
        QueueContext->DeviceContext->KeyCodes[i] = outputReport->KeyCodes[i];
    }

        
    

    
    //
    // set status and information
    //
    WdfRequestSetInformation(Request,  sizeof(HIDMINI_OUTPUT_REPORT));
    return status;
}



NTSTATUS
RequestCopyFromBuffer(
    _In_  WDFREQUEST        Request,
    _In_  PVOID             SourceBuffer,
    _When_(NumBytesToCopyFrom == 0, __drv_reportError(NumBytesToCopyFrom cannot be zero))
    _In_  size_t            NumBytesToCopyFrom
)
{
    NTSTATUS                status;
    WDFMEMORY               memory;
    size_t                  outputBufferLength;

    status = WdfRequestRetrieveOutputMemory(Request, &memory);
    if (!NT_SUCCESS(status)) {
        KdPrint(("WdfRequestRetrieveOutputMemory failed 0x%x\n", status));
        return status;
    }

    WdfMemoryGetBuffer(memory, &outputBufferLength);
    if (outputBufferLength < NumBytesToCopyFrom) {
        status = STATUS_INVALID_BUFFER_SIZE;
        KdPrint(("RequestCopyFromBuffer: buffer too small. Size %d, expect %d\n",
            (int)outputBufferLength, (int)NumBytesToCopyFrom));
        return status;
    }

    status = WdfMemoryCopyFromBuffer(memory,
        0,
        SourceBuffer,
        NumBytesToCopyFrom);
    if (!NT_SUCCESS(status)) {
        KdPrint(("WdfMemoryCopyFromBuffer failed 0x%x\n", status));
        return status;
    }

    WdfRequestSetInformation(Request, NumBytesToCopyFrom);
    return status;
}



NTSTATUS
CheckRegistryForDescriptor(
    _In_ WDFDEVICE Device
)


{
    WDFKEY          hKey = NULL;
    NTSTATUS        status;
    UNICODE_STRING  valueName;
    ULONG           value;

    status = WdfDeviceOpenRegistryKey(Device,
        PLUGPLAY_REGKEY_DEVICE,
        KEY_READ,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hKey);
    if (NT_SUCCESS(status)) {

        RtlInitUnicodeString(&valueName, L"ReadFromRegistry");

        status = WdfRegistryQueryULong(hKey,
            &valueName,
            &value);

        if (NT_SUCCESS(status)) {
            if (value == 0) {
                status = STATUS_UNSUCCESSFUL;
            }
        }

        WdfRegistryClose(hKey);
    }

    return status;
}

NTSTATUS
ReadDescriptorFromRegistry(
    _In_  WDFDEVICE Device
)

{
    WDFKEY          hKey = NULL;
    NTSTATUS        status;
    UNICODE_STRING  valueName;
    WDFMEMORY       memory;
    size_t          bufferSize;
    PVOID           reportDescriptor;
    PDEVICE_CONTEXT deviceContext;
    WDF_OBJECT_ATTRIBUTES   attributes;

    deviceContext = GetDeviceContext(Device);

    status = WdfDeviceOpenRegistryKey(Device,
        PLUGPLAY_REGKEY_DEVICE,
        KEY_READ,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hKey);

    if (NT_SUCCESS(status)) {

        RtlInitUnicodeString(&valueName, L"MyReportDescriptor");

        WDF_OBJECT_ATTRIBUTES_INIT(&attributes);
        attributes.ParentObject = Device;

        status = WdfRegistryQueryMemory(hKey,
            &valueName,
            NonPagedPool,
            &attributes,
            &memory,
            NULL);

        if (NT_SUCCESS(status)) {

            reportDescriptor = WdfMemoryGetBuffer(memory, &bufferSize);

            KdPrint(("No. of report descriptor bytes copied: %d\n", (INT)bufferSize));

            //
            // Store the registry report descriptor in the device extension
            //
            deviceContext->ReadReportDescFromRegistry = TRUE;
            deviceContext->ReportDescriptor = reportDescriptor;
            deviceContext->HidDescriptor.DescriptorList[0].wReportLength = (USHORT)bufferSize;
        }

        WdfRegistryClose(hKey);
    }

    return status;
}