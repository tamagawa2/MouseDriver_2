#pragma once
/*++
Copyright (c) Microsoft Corporation.  All rights reserved.
    THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
    KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
    PURPOSE.
Module Name:
    common.h
Environment:
    User mode
--*/

#ifndef __VHIDMINI_COMMON_H__
#define __VHIDMINI_COMMON_H__

//
// Custom control codes are defined here. They are to be used for sideband 
// communication with the hid minidriver. These control codes are sent to 
// the hid minidriver using Hid_SetFeature() API to a custom collection 
// defined especially to handle such requests.
//
#define  HIDMINI_CONTROL_CODE_SET_ATTRIBUTES              0x00
#define  HIDMINI_CONTROL_CODE_DUMMY1                      0x01
#define  HIDMINI_CONTROL_CODE_DUMMY2                      0x02

//
// This is the report id of the collection to which the control codes are sent
//


#define MAXIMUM_STRING_LENGTH           (126 * sizeof(WCHAR))
#define VHIDMINI_MANUFACTURER_STRING    L"UMDF Virtual hidmini device Manufacturer string"  
#define VHIDMINI_PRODUCT_STRING         L"UMDF Virtual hidmini device Product string"  
#define VHIDMINI_SERIAL_NUMBER_STRING   L"UMDF Virtual hidmini device Serial Number string"  
#define VHIDMINI_DEVICE_STRING          L"UMDF Virtual hidmini device"  
#define VHIDMINI_DEVICE_STRING_INDEX    5

#define KBD_KEY_CODES   6


#include <pshpack1.h>

typedef struct _MY_DEVICE_ATTRIBUTES {

    USHORT          VendorID;
    USHORT          ProductID;
    USHORT          VersionNumber;

} MY_DEVICE_ATTRIBUTES, * PMY_DEVICE_ATTRIBUTES;

typedef struct _HIDMINI_CONTROL_INFO {

    //
    //report ID of the collection to which the control request is sent
    //
    UCHAR    ReportId;

    //
    // One byte control code (user-defined) for communication with hid 
    // mini driver
    //
    UCHAR   ControlCode;

    //
    // This union contains input data for the control request.
    //
    union {
        MY_DEVICE_ATTRIBUTES Attributes;
        struct {
            ULONG Dummy1;
            ULONG Dummy2;
        } Dummy;
    } u;

} HIDMINI_CONTROL_INFO, * PHIDMINI_CONTROL_INFO;

//
// input from device to system
//
typedef struct _HIDMINI_INPUT_REPORT {

    UCHAR ReportId;

    //Mouse
    UCHAR Button;
    INT16 X;
    INT16 Y;
    

} HIDMINI_INPUT_REPORT, * PHIDMINI_INPUT_REPORT;

typedef struct _Key_INPUT {

    UCHAR ReportId;

    //Key
    UCHAR ShiftKeyFlags;
    UCHAR Reserved;
    UCHAR KeyCodes[KBD_KEY_CODES];

} Key_INPUT, * PKey_INPUT;



//
// output to device from system
//
typedef struct _HIDMINI_OUTPUT_REPORT {

    UCHAR ReportId;

    UCHAR Data;

    //Mouse
    UCHAR Button;
    INT16 X;
    INT16 Y;

    //Key
    UCHAR ShiftKeyFlags;
    UCHAR Reserved;
    UCHAR KeyCodes[KBD_KEY_CODES];

} HIDMINI_OUTPUT_REPORT, * PHIDMINI_OUTPUT_REPORT;



#include <poppack.h>



#define FEATURE_REPORT_SIZE_CB      ((USHORT)(sizeof(HIDMINI_CONTROL_INFO) - 1))
#define INPUT_REPORT_SIZE_CB        ((USHORT)(sizeof(HIDMINI_INPUT_REPORT) - 1))
#define OUTPUT_REPORT_SIZE_CB       ((USHORT)(sizeof(HIDMINI_OUTPUT_REPORT) - 1))

#endif //__VHIDMINI_COMMON_H__