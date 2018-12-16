
#include <string>

#ifndef ICONS_H
#define ICONS_H






typedef struct _tIcon
{
  const uint8_t *table;
  uint16_t Width;
  uint16_t Height;

} sIcon;


extern sIcon clear_day;
extern sIcon clear_night;
extern sIcon cloudy;
extern sIcon fog;
extern sIcon partly_cloudy_day;
extern sIcon partly_cloudy_night;
extern sIcon rain;
extern sIcon sleet;
extern sIcon snow;
extern sIcon wind;






#endif