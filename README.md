# eInkWeatherStation
![Picture from front of screen](pictures/front.JPG)

This is my freetime project which I make just for fun. 
The idea of the code was get weatherdata from darksky API and display it on E-ink display.
On hardware I use raspberry pi 3 and waveshare 7.5" monochrome e-ink display.

The code contains two main scripts. First named at dataReguest.py was written by python and its mean is 
handle html reguest for data receiving. The script gets data from darksky api and after some syntax modifying write it to file currentWeather.txt.

The end of project was written by c++ and uses a lot of allready given libraries from manufacturer waveshare. I have made modifications for main.cpp and edpaint.cpp to supply my needs. And added couple font files and icon files. The c++ code handle data reading from the file currentWeather.txt and writing it to display.

The scripts are run by crontab with 30 min interval so the display was updated every half an hour.

Picture from back: [pictures/back.JPG](https://github.com/Pyykkonj/eInkWeatherStation/blob/master/pictures/back.JPG)

Link to display manufacturer page: https://www.waveshare.com/7.5inch-e-paper-hat.htm

If you want to use my code or part of it remember to take account of some modifications:

In dataReguest.py: 
- at row 10 add your own darksky api key to [API_KEY]
- at row 59 change file path to correspond your own source destination

in main.cpp:
- at row 80 change file path to correspond your own source destination.
