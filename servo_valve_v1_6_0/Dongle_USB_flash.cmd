west build
nrfutil pkg generate --hw-version 52 --sd-req=0x00 --application build/zephyr/zephyr.hex --application-version 1 build/zephyr.zip
nrfutil dfu usb-serial -pkg build/zephyr.zip -p COM30