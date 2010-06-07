RPT_DB:

A Set of frequency data bases for using RPT scenarios.
There are 6 data bases:

1. Center Frequency: 2.3 GHz, Bandwidth:  5 MHz; Directory:  23_5
2. Center Frequency: 2.3 GHz, Bandwidth: 10 MHz; Directory: 23_10
3. Center Frequency: 2.5 GHz, Bandwidth:  5 MHz; Directory:  25_5
4. Center Frequency: 2.5 GHz, Bandwidth: 10 MHz; Directory: 25_10
5. Center Frequency: 3.5 GHz, Bandwidth:  5 MHz; Directory:  35_5
6. Center Frequency: 3.5 GHz, Bandwidth: 10 MHz; Directory: 35_10


Each directory includes a script to replace the current data base w/ the required one,
named 23_5\replace_wimax_db.bat.

For reference, the frequencies stores in the data bases were extracted into a CSV table.

How to use the data bases:

1. When changing center frequency and BW settings (i.e replacing the channel data base):
    1.1 Using CU, turn RF to Off.
    1.2 Browse to the desired directory
    1.3 Run the replace_wimax_db batch file
    1.4 In the CU (Connectivity Utility) Select:
           Options -> Advanced -> Troubleshooting Tab -> Restore factory Default Settings
    1.5 In the CU, Turn RF to ON. The channels would be scanned and connected automatically
    1.6 If the channel is found but not connected, press the green Connect button

2. Changing BSE frequency, within the current Center frequency and bandwidth configuration
    (i.e. w/o the need to update the data base)
    2.1 Disconnect
    2.2 Turn RF to OFF
    2.3 Change the frequency of the BSE
    2.4 Turn RF to ON
    2.5 Connect


