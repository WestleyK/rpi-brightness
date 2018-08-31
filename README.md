## A simple command for adjusting your raspberry pi backlight

Designed and tested for raspberry pi with official 7 inch touchdcreen. <br>
<br>

Other script that do the same thing:
 - go: https://github.com/WestleyK/rpi-backlight
 - perl: https://github.com/WestleyK/pi-backlight
 - bash/shell: https://github.com/WestleyK/backlight
 
<br>
<br>

## Install, Update and Uninstall


### To install: <br>

```
cd ~/
mkdir raspberrypi-backlight
cd raspberrypi-backlight/
git clone https://github.com/WestleyK/rpi-brightness.git
cd rpi-brightness/
make
sudo make install
```

<br>

### Easy install:

Paste or type this in your terminal:
```
curl https://raw.githubusercontent.com/WestleyK/rpi-backlight/master/easy-install.sh | sh
```
This will install `rpi-brightness` to the current directory.

To finish the install, do:
```
sudo mv rpi-brightness /usr/local/bin/
```

<br>
<br>

### To update: <br>

```
cd ~/raspberrypi-backlight/rpi-brightness/
make update
sudo make install
```
<br>
<br>

### To uninstall: <br>


```
cd ~/raspberrypi-backlight/rpi-brightness/
sudo make uninstall
```

<br>
<br>

## Usage:


```
pi@raspberrypi:~ $ rpi-brightness -help
Usage: rpi-backlight [OPTION]
        -h | -help | --help (print help menu)
        -u | -up (adjust backlight brighter by: 20/255)
        -d | -down (adjust brightness lower by: 20/255)
        -s | -sleep (enter sleep mode, press <ENTER> to exit)
        -c (print current brightness)
        [15-255] (adjust brightness from: 15 to: 255)
        -i | -info (print compiled info)
        -v | -version | --version (print version & date)
Source code: https://github.com/WestleyK/rpi-brightness
pi@raspberrypi:~ $ 
```
For example, you can do: <br>

```
sudo rpi-backlight 200
```
And: <br>

```
sudo rpi-backlight -sleep
```
Will enter sleep mode. <br>
<br>
<br>
Make sure you type `sudo` before adjusting backlight, <br>
Or you might get this `ERROR` <br>

```
pi@raspberrypi:~ $ rpi-brightness -up
ERROR: Brightness file not writable or doesn't exist:
/sys/class/backlight/rpi_backlight/brightness
Try: $ sudo rpi-brightness [OPTION]  (or)  https://github.com/WestleyK/rpi-brightness (for help)
pi@raspberrypi:~ $ 
```

<br>

### Don't like the sudo?

If you you don't like typing `sudo` before adjusting brightness, then <br>
run the `no-root.sh` script: <br>

```
sudo ./no-root.sh
sudo reboot
```

Now you should not need the `sudo`. <br>
<br>
To undo what you did, type: <br>

```
sudo rm /etc/udev/rules.d/backlight-permissions.rules
sudo reboot
```


<br>
<br>


## Troubleshooting:

```
pi@raspberrypi:~ $ rpi-brightness [OPTION]
ERROR: Brightness file not writable.
Try: sudo rpi-brightness  (or)  https://github.com/WestleyK/rpi-brightness (for help)
pi@raspberrypi:~ $ 
```
Possible causes or fixes: <br>
- Try `sudo` and then the command. <br>
- Try [updating](#To-update). <br>
- File does't exist. <br>
<br>




<br>
<br>

### End README

<br>
<br>



