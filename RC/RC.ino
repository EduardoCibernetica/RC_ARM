#include <AP_Common.h>
#include <AP_Math.h>
#include <AP_Param.h>
#include <AP_Progmem.h>
#include <AP_ADC.h>
#include <AP_InertialSensor.h>

#include <AP_HAL.h>
#include <AP_HAL_AVR.h>

#define RCMIN 990
#define RCMAX 2015

#define CHPITCH 2
#define CHROLL 1
#define CHYAW 4
#define CHTROUTTLE 3

/*
CH1 PITCH ;
CH2 ROLL ;
CH3 TROUTTLE;
CH4 YAW;
*/

#define wrap_180(x) (x < -180 ? x+360 : (x > 180 ? x - 360: x))

 float rcthr, rcyaw, rcpit, rcroll;
const AP_HAL::HAL& hal = AP_HAL_AVR_APM2;


float map(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

int Acoplar_Canales(int x)
{
    if(x>0)
    {
      return x-1;
    }
    else 
    {
      hal.console->printf_P(PSTR("Canal Invalido"));
    }
}



void setup(){}
void loop()
{
  uint16_t Canales_Entrada[4];  // array for raw channel values
  hal.rcin->read(Canales_Entrada, 4);
 
    rcthr = Canales_Entrada[Acoplar_Canales(CHTROUTTLE)];
    rcyaw = map(Canales_Entrada[Acoplar_Canales(CHYAW)],   RCMIN, RCMAX, -180, 180);
    rcpit = map(Canales_Entrada[Acoplar_Canales(CHPITCH)], RCMIN, RCMAX, -45, 45);
    rcroll = map(Canales_Entrada[Acoplar_Canales(CHROLL)], RCMIN, RCMAX, -45, 45);
   
        hal.console->printf_P(PSTR("T :%4.1f  "),   rcthr);
        hal.console->printf_P(PSTR("Y : %4.1f   "), rcyaw);
        hal.console->printf_P(PSTR("P : %4.1f   "), rcpit);
        hal.console->printf_P(PSTR("R : %4.1f\n"),  rcroll);

}
AP_HAL_MAIN(); 
