## Install:


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
<br>

## Updating:


```
cd ~/raspberrypi-backlight/rpi-brightness/
sudo make update
```
**Note:** This will install after updating. <br>

<br>
<br>

## Uninstalling:

```
cd ~/raspberrypi-backlight/rpi-brightness/
sudo make uninstall
```

<br>
<br>

## Running no-root.sh:

If you run this, you dont need the `sudo` before changing the brightness. <br>

```
cd ~/raspberrypi-backlight/rpi-brightness/
sudo ./no-root.sh
sudo reboot
```

<br>

To undo that, type: <br>

```
sudo rm /etc/udev/rules.d/backlight-permission.rules
sudo reboot
```


<br>
<br>



### End INSTALL.md






