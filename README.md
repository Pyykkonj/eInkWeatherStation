# eInkWeatherStation
![Picture from front of screen](pictures/front.JPG)

This is my free time project which I made just for fun. 
The idea of the code is to get weather data from darksky API and display it on E-ink display.
On hardware, I use raspberry pi 3 and waveshare 7.5" monochrome e-ink display.

The code contains two main scripts. First named at dataReguest.py is written with Python and its meant is 
handle html request for data receiving. The script gets data from darksky api and after some syntax modifying writes it to file currentWeather.txt.

The end of the project is written with c++ and uses a lot of already given libraries from screen manufacturer waveshare. I have made modifications for main.cpp and edpaint.cpp to supply my needs. And added couple font files and icon files. The c++ code handles data reading from the file currentWeather.txt and writes it to display.

The scripts are run by crontab with 30 min interval so the display is updated every half an hour.

Picture from back: [pictures/back.JPG](https://github.com/Pyykkonj/eInkWeatherStation/blob/master/pictures/back.JPG)

Link to display manufacturer page: https://www.waveshare.com/7.5inch-e-paper-hat.htm

If you want to use my code or part of it remember to take account of some modifications:

In dataReguest.py: 
- at row 10 add your own darksky api key to [API_KEY]
- at row 59 change file path to correspond your own source destination

in main.cpp:
- at row 80 change file path to correspond your own source destination.
