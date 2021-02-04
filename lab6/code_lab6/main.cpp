#include <stdio.h>
#include <iostream>
//#include <libusb.h>
#include "libusb-1.0/libusb.h"
#include <string>

using std::cout;
using std::endl;

std::string getDeviceClassByCode(const int& code) {
	switch (code) {
	case 0x00:
		return "No code";
	case 0x01:
		return "аудиоустройство";
	case 0x02:
		return "коммуникационное устройство (сетевой адаптер)";
	case 0x03:
		return "устройство пользовательского интерфейса";
	case 0x05:
		return "физическое устройство";
	case 0x06:
		return "изображения";
	case 0x07:
		return "принтер";
	case 0x08:
		return "устройство хранения данных";
	case 0x09:
		return "концентратор";
	case 0x0A:
		return "CDC-Data";
	case 0x0B:
		return "Smart Card";
	case 0x0D:
		return "Content Security";
	case 0x0E:
		return "видеоустройство";
	case 0x0F:
		return "персональное медицинское устройство";
	case 0x10:
		return "аудио- и видеоустройства";
	case 0xDC:
		return "диагностическое устройство";
	case 0xE0:
		return "беспроводный контроллер";
	case 0xEF:
		return "различные устройства";
	case 0xFE:
		return "специфическое устройство";

	default:
		return "no info";
	}
	
}

void printDevices(libusb_device** devs) {

	libusb_device* dev;
	int i = 0, j = 0;

	while ((dev = devs[i++]) != NULL) {
		libusb_device_handle* handle = NULL;
		if (!handle) libusb_open(dev, &handle);

		unsigned char string[256];
		int r = 0;

		libusb_device_descriptor desc;

		if (libusb_get_device_descriptor(dev, &desc) < 0) {
			fprintf(stderr, "failed to get device descriptor");
			return;
		}

		// configuration
		libusb_config_descriptor* config;
		libusb_get_config_descriptor(dev, 0, &config);
		cout << "Avaliable confiurations number: " << (int)desc.bNumConfigurations << endl;
		cout << "Device class: "; 
		printf("%x", (int)desc.bDeviceClass);
		cout << " (" << getDeviceClassByCode((int)desc.bDeviceClass) << ") " << endl;
		cout << "Vendor id: " << desc.idVendor << endl;
		cout << "Product id: " << desc.idProduct << endl;

		cout << endl;

		if (desc.iSerialNumber) {
			r = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, string, sizeof(string));
			if (r > 0) cout << "Serial number: " << string << endl;
		}
		else {
			cout << "No serial number info" << endl;
		}
		if (desc.iManufacturer) {
			r = libusb_get_string_descriptor_ascii(handle, desc.iManufacturer, string, sizeof(string));
			if (r > 0) cout << "Manufacturer: " << string << endl;
		}
		else {
			cout << "No manufacturer info" << endl;
		}
		if (desc.iProduct) {
			r = libusb_get_string_descriptor_ascii(handle, desc.iProduct, string, sizeof(string));
			if (r > 0) cout << "Product: " << string << endl;
		}
		else {
			cout << "No product info" << endl;
		}

		cout << endl << "----------------" << endl << endl;
		libusb_close(handle);
	}
}

int main(void) {

	libusb_device** devs;
	ssize_t cnt;

	int r = libusb_init(NULL);
	if (r < 0) return r;

	cnt = libusb_get_device_list(NULL, &devs);
	if (cnt < 0) {
		libusb_exit(NULL);
		return (int)cnt;
	}

	cout << "Found " << cnt << " devices" << endl << endl;

	printDevices(devs);

	libusb_free_device_list(devs, 1);
	libusb_exit(NULL);
	return 0;
}