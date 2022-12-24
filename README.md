# m5stack-timelapse

A nodejs/arduino combo to take photos every \_ minutes. The photos are then uploaded to a server via wifi.

## Credits

-   [esp-upload-download-file-http](https://github.com/nhatuan84/esp32-upload-download-multipart-http), but with some modifications.
    -   `==` and some `--` were removed from the boundary string.
    -   `Expect` header removed
-   [ttf2fnt](https://ttf2fnt.com/) to convert the font to a .fnt file, used for the video processing (I used open sans light at 32pt)
