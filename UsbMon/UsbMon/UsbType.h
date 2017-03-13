#ifndef __USB_TYPE_HEADER__
#define __USB_TYPE_HEADER__ 

#include <fltKernel.h> 
#include "Hidport.h"
#include "usb.h" 
#include "hubbusif.h"
#include "usbbusif.h" 
#include "Usbioctl.h"
#include "TList.h"
#include "hidpddi.h"
 

//--------------------------------------//
typedef struct _HID_DEVICE_LIST
{
	TChainListHeader*					  	 head; 
	ULONG							  currentSize;
	ULONG								 RefCount;
} HID_DEVICE_LIST, *PHID_DEVICE_LIST; 


typedef struct _HID_USB_DEVICE_EXTENSION {
	ULONG64							   status;			//+0x0	
	PUSB_DEVICE_DESCRIPTOR		    DeviceDesc;			//+0x8
	PUSBD_INTERFACE_INFORMATION		InterfaceDesc;		//+0x10
	USBD_CONFIGURATION_HANDLE 		ConfigurationHandle;//+0x18
	ULONG                           NumPendingRequests;
	KEVENT                          AllRequestsCompleteEvent; 
	ULONG                           DeviceFlags; 
	PIO_WORKITEM                    ResetWorkItem;
	HID_DESCRIPTOR				    HidDescriptor;  
	PDEVICE_OBJECT                  functionalDeviceObject;
}HID_USB_DEVICE_EXTENSION, *PHID_USB_DEVICE_EXTENSION;
static_assert(sizeof(HID_USB_DEVICE_EXTENSION) == 0x68, "Size Check");


typedef struct _HID_DEVICE_NODE
{ 
	PDEVICE_OBJECT					device_object;
	HID_USB_DEVICE_EXTENSION*		mini_extension;
	HIDP_DEVICE_DESC				parsedReport;
}HID_DEVICE_NODE, *PHID_DEVICE_NODE;


typedef struct _EXTRACT_DATA
{
	union
	{
		struct 
		{
			UCHAR OffsetX;
			UCHAR XOffsetSize;
			UCHAR OffsetY;
			UCHAR YOffsetSize;
			UCHAR OffsetZ;
			UCHAR ZOffsetSize;
			UCHAR OffsetButton;
			UCHAR BtnOffsetSize;
			BOOLEAN IsAbsolute;
		}MOUDATA;

		struct
		{
			UCHAR  SpecialKeyOffset;
			UCHAR  SpecialKeySize;
			UCHAR  NormalKeyOffset;
			UCHAR  NormalKeySize;
			UCHAR  LedKeyOffset;
			UCHAR  LedKeySize;
		}KBDDATA;

	};
 
}EXTRACTDATA, *PEXTRACTDATA;

#define CHANNEL_DUMP_ATTRIBUTE_RELATED					1
#define CHANNEL_DUMP_REPORT_REALTED						2
#define CHANNEL_DUMP_REPORT_BYTE_OFFSET_REALTED			4 
#define CHANNEL_DUMP_RANGE_RELATED						8
#define CHANNEL_DUMP_LINK_COL_RELATED					16
#define CHANNEL_DUMP_ALL  CHANNEL_DUMP_ATTRIBUTE_RELATED | CHANNEL_DUMP_REPORT_REALTED | CHANNEL_DUMP_RANGE_RELATED | CHANNEL_DUMP_LINK_COL_RELATED | CHANNEL_DUMP_REPORT_BYTE_OFFSET_REALTED

//--------------------------------------//
#endif