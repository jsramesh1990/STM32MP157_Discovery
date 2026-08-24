Make all four scripts executable

From:

cd STM32MP157_Discovery/linux/scripts

run:

chmod +x power_test.sh
chmod +x sensor_test.sh
chmod +x suspend_test.sh
chmod +x wakeup_test.sh

Then:

./power_test.sh
./sensor_test.sh
sudo ./suspend_test.sh
sudo ./wakeup_test.sh



The four scripts have a clear separation:

power_test.sh
     ↓
Power / energy interfaces

sensor_test.sh
     ↓
Sensor + RPMsg validation

suspend_test.sh
     ↓
Linux low-power testing

wakeup_test.sh
     ↓
Wake-up source testing

One important point: these scripts test the Linux interfaces; they do not by themselves guarantee a particular current such as 1 µA. Actual ultra-low-power measurement must be performed with appropriate current-measurement hardware at the relevant power rail.
