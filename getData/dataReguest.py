import json
from urllib.request import urlopen
import json.decoder
from datetime import datetime


DATABASE = "city_database.txt"

API_URL = "https://api.darksky.net/forecast/"
API_KEY = "[YOUR_DARK_SKY_API_KEY]/"
API_PARAMETERS = "?exclude=minutely,alerts,hourly,flags&units=si"

#covert unix time to string containing hh:mm
def convertTime(unixTime):
     return datetime.fromtimestamp(unixTime).strftime('%Y-%m-%d %H:%M:%S')


def getDataFromServer():

    # kaupunkina tampere
    vertical = "61.5000045"
    horisontal = "23.75001257"

    # haetaan data serveriltä
    response = urlopen(API_URL+API_KEY+vertical+","+horisontal + API_PARAMETERS)
    print(response.status)
    # str_response = response.read().decode('utf-8')
    # datan muokkaus käsiteltäväksi

    string = response.read().decode('utf-8')
    data = json.loads(string)
    #data = json.loads(response.content.decode('utf-8'))

    
    # lista mihin haluttu data lisätään
    current = []
    data_needed = [ "icon","temperature", "windBearing","windSpeed",
                    "apparentTemperature","pressure",
                      "dewPoint", "humidity",
                    "visibility","time","sunriseTime","sunsetTime"]
    

    for i in range(10):
        current.append(data["currently"][data_needed[i]])


    for i in range(10,12):
        current.append(data["daily"]["data"][0][data_needed[i]])


    # convert time from unixtime to utc and split only hours and minutes
    for i in range(9,12):
        current[i] = str(convertTime(current[i]))
        current[i] = current[i][11:16]



    # avataan tiedosto
    f = open("/home/pi/share/development/eink_test_1/getData/currentWeather.txt", "w")
    
    # kirjotetaan haettu data tiedostoon
    for i in range(len(current)):
        if(i < len(current)-1):
            f.write(str(current[i]))
            f.write("\n")
        else:
            f.write(str(current[i]))

        

    f.close()


def main():
    getDataFromServer()


main()