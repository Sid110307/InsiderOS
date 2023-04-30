# InsiderOS

> A minimalistic Operating System that I'm developing for no apparent reason (What am I doing with my life?).

## Quick Start

### Windows

> Note: I've not tested this on a Windows machine, so I'm not sure if it will work.

- Clone the repository

    ```dos
    git clone https://github.com/Sid110307/InsiderOS.git
    ```

- Run the `build.bat` file in the root directory

    ```dos
    cd InsiderOS
    build.bat
    ```

- Copy the image to an empty USB drive

    ```dos
    copy kernel/bin/InsiderOS.img /usb/drive
    ```

- Reboot your computer.
- Enter the boot menu (F10 or F12 for most computers).
- Select the USB drive to boot.

### Linux

- Clone the repository

    ```sh
    git clone https://github.com/Sid110307/InsiderOS.git
    ```

- Run the `build.sh` file in the root directory

    ```sh
    cd InsiderOS
    ./build.sh
    ```

- Copy the image to an empty USB drive

    ```sh
    cp kernel/bin/InsiderOS.img /usb/drive
    ```

- Reboot your computer.
- Enter the boot menu (F10 or F12 for most computers).
- Select the USB drive to boot.
