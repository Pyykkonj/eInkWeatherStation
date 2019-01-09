/**
 * This is my freetime coding project just for fun. The code might not be
 * any kind model of grammar. The base of the code was from waveshare which
 * I have made some extra functions to supply my own needs. 
 * 
 * The program reads data from currentWeather.txt file and prints it to display. 
 * The dataReguest.py script must be run before to reguest last weather information.
 * 
 * New source files are:
 * font32.c
 * font48.c
 * dataReguest.py
 * 
 * Source files which are modified:
 * main.cpp
 * edppaint.cpp
 *   added functions:
 *   DrawWeatherIcon()
 *   DrawWindArrow()        
 * 
 * ORIGINAL PERMISSIONS/WARRANTY INFO BELOW: * 
 * 
 *  @filename   :   main.cpp
 *  @brief      :   7.5inch e-paper display demo
 *  @author     :   Yehui from Waveshare
 *
 *  Copyright (C) Waveshare     July 31 2017
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documnetation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to  whom the Software is
 * furished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "epd7in5.h"
#include "epdpaint.h"
#include "imagedata.h"

using namespace std;

#define COLORED      1
#define UNCOLORED    0


/*
Read data from the file which python script was created
and store it to vector.
*/
void readWeatherData(vector<string>* weatherData){

    string temp;

    // index for data hanlding, eg: string or int
    int i = 0;

    // reading weatherdata from file
	ifstream infile;
	infile.open ("/home/pi/share/development/eink_test_1/getData/currentWeather.txt");

    if (infile.is_open())
    {
        while(getline(infile,temp))
        {
         if(!temp.empty()){   

                float ftemp;

                 if(i > 0 && i <=8){
                    // data needs round to integer
                    try{
                        ftemp = stof(temp);
                    }
                    catch(invalid_argument& e){
                        cout << "error i:  " << i << endl;
                    }

                    if(i == 7){
                        // humidity to percents
                        ftemp = ftemp*100;
                    }

                    int itemp = (int)ftemp;
                    temp = to_string(itemp);
                    

                } 
            
            weatherData->push_back(temp); 
            
            i++;
         }
        }
    }
	infile.close();

    /*
     for (unsigned int i = 0; i< weatherData.size(); i++){
         cout << weatherData.at(i) << endl;
     }
    */


    }




/*
This draws the weatherdata to the screen, all text positions are fixed
and "hard coded" to the code.
*/
void DrawWeatherToScreen(Paint* paint,Epd* epd, unsigned char* frame_buffer, 
                        vector <string>* weatherData ){
    
    if(weatherData->size() != 12){
        cout << "Error: Problem loading weather data from file!" << endl;

    }
    else{
    
        map <string, sIcon*> iconit = {
            {"clear-day", &clear_day},
            {"clear-night", &clear_night},
            {"cloudy", &cloudy},
            {"fog", &fog},
            {"partly-cloudy-day", &partly_cloudy_day},
            {"partly-cloudy-night", &partly_cloudy_night},
            {"rain", &rain},
            {"sleet",&sleet},
            {"snow", &snow},
            {"wind", &wind} 
        };
        

        // array for static text to be printed
        string texts[9][2] = {
            {"wind: "," m/s"},
            {"Feels like: "," C"},
            {"Barometer: "," hPa"},
            {"Dewpoint: ", " C"},
            {"Humidity: ", " %"},
            {"Visibility: ", " km"},
            {"Sun rise: ", ""},
            {"Sun set: ", ""},
            {"Data updated: ", ""}

        };

        
        paint->DrawWeatherIcon(32,32,iconit.at(weatherData->at(0)));

        // temperature
        paint->DrawStringAt(32, 320, (weatherData->at(1)+texts[1][1]).c_str() , &Font32, COLORED);
        // wind
        paint->DrawStringAt(210, 320, (weatherData->at(3)+texts[0][1]).c_str(), &Font32, COLORED);

        paint->DrawStringAt(400, 8, "TAMPERE", &Font48, COLORED);

        // Feels like
        paint->DrawStringAt(364,74, (texts[1][0]+weatherData->at(4)+texts[1][1]).c_str(), &Font20, COLORED);
        // Barometer
        paint->DrawStringAt(364,106, (texts[2][0]+weatherData->at(5)+texts[2][1]).c_str(), &Font20, COLORED);
        // Dewpoint
        paint->DrawStringAt(364,138, (texts[3][0]+weatherData->at(6)+texts[3][1]).c_str(), &Font20, COLORED );
        // Humidity
        paint->DrawStringAt(364,170, (texts[4][0]+weatherData->at(7)+texts[4][1]).c_str(), &Font20, COLORED );
        // Visibility
        paint->DrawStringAt(364,202,(texts[5][0]+weatherData->at(8)+texts[5][1]).c_str(), &Font20, COLORED);

        // Sun rise
        paint->DrawStringAt(364,260,(texts[6][0]+weatherData->at(10)+texts[6][1]).c_str(), &Font20, COLORED);
        // Sun set
        paint->DrawStringAt(364,292,(texts[7][0]+weatherData->at(11)+texts[7][1]).c_str(), &Font20, COLORED);

        // Data updated
        paint->DrawStringAt(364,340,(texts[8][0]+weatherData->at(9)+texts[8][1]).c_str(), &Font16, COLORED);

        // wind arrow
        paint->DrawWindArrow(160,336,32,stoi(weatherData->at(2)));
        epd->DisplayFrame(frame_buffer);

    }

}


int main(void)
{
    Epd epd;
    if (epd.Init() != 0) {
        printf("e-Paper init failed\n");
        return -1;
    }

    unsigned char* frame_buffer = new unsigned char[epd.width / 8 * epd.height];

    Paint paint(frame_buffer, epd.width, epd.height);
    paint.Clear(UNCOLORED);



    vector<string> weatherData;
    
    readWeatherData(&weatherData);

    DrawWeatherToScreen(&paint, &epd, frame_buffer, &weatherData );

    delete[] frame_buffer;
    return 0;
}

