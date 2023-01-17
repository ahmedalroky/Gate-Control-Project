use rcswich and eeprom lib
check if two RF stored in eeprom
if true listen for serial commands 
    turn on green led
    if serial command equals 1 send rf on command
    if serial command equals 2 send rf off command
if RF not stored in eeprom 
    turn on red led
    enable RF reciving 
    when the first code is recived store it on eeprom space 1 
    blink the red led
    enable reciving 
    when the second code is recived store it on eeprom space 2 
    turn of red led
    turn on green led 
    listen for serial commands 
    turn on green led
    if serial command equals 1 send rf on command
    if serial command equals 2 send rf off command


    ```
    Sure, here's an updated version of the Arduino code that uses the RC-Switch library and EEPROMEx library to check if two RF codes are stored in EEPROM, and if so, listens for serial commands to control a device through RF signals. It specifies a specific pin for both the transmitting and receiving functions.
If RF codes are not stored in EEPROM, it turns on a red LED, enables RF receiving on a specified pin, and stores the received codes in EEPROM for later use. It also prints the 
```