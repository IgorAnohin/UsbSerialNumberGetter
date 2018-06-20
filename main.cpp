#include <iostream>
#include <array>
#include <libusb-1.0/libusb.h>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;


    libusb_init(NULL);
    libusb_device **devs;

    if (libusb_get_device_list(NULL, &devs) < 0) {
        std::cerr << "Filed to get device list" << std::endl;
        exit(-2);
    }

    libusb_device *dev;
    int i = 0;

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);

        if (r < 0) {
            std::cerr << "failed get descriptor" << std::endl;
        }


        //if (desc.idProduct == 0x0001 && desc.idVendor == 0x0a5c) {
            libusb_device_handle *handle;
            if (LIBUSB_SUCCESS == libusb_open(dev, &handle)) {

                unsigned char data[200];
                auto ret = libusb_get_string_descriptor_ascii(handle, desc.iSerialNumber, data, sizeof(data));
                if (ret > 0) {
                    std::cout << std::hex << "Vid " << desc.idVendor << " Pid: " << desc.idProduct << std::dec
                              << " return " << ret << std::endl;
                    std::cout << data << std::endl;
                    std::cout << std::endl;
                }

                libusb_close(handle);
            }
        //}

    }

    libusb_free_device_list(devs, 1);

    libusb_exit(NULL);
    return 0;
}
