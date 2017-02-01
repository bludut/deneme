#include <stdio.h>
#include <stdlib.h>
#include <math.h>>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */




#define RHO_C0 6.1078
#define RHO_C1 7.5
#define RHO_C2 237.3
#define RHO_RD 287.0531
#define RHO_RV 461.4964


/*
 *
 */
float RhoCalculateSaturationPressure(float Temperature)
{
	float Es;

	Es = RHO_C0 * powf(10.0,RHO_C1 * Temperature / (RHO_C2 + Temperature));

	return Es ;	// in hPa
}

/*
 * DewPoint must be in degree Celcius
 */
float RhoCalculatePPWaterVapor(float DewPoint)
{
	return RhoCalculateSaturationPressure(DewPoint);	//in hPa
}

/*
 * Pressure must be  in hPa (Pa/100)
 *
 */
float RhoCalculatePPDryAir(float Pressure,float PPVapor)
{
	return Pressure-PPVapor;	//in hPa
}


/*
 *  Pressure must be  in hPa (Pa/100)
 *	Temperature must be in Celcius
 *	DewPoint must be in degree Celcius
 */
float RhoCalculateRho(float Pressure, float DewPoint,float Temperature)
{
	float Rho;
	float Pd,Pv;

	Temperature += 273.15 ; //convert Celcius to Kelvin
	Pv = RhoCalculatePPWaterVapor(DewPoint) * 100.0; // convert hPa to Pa
	printf("pv:%f-----",Pv);
	Pd = RhoCalculatePPDryAir(Pressure,Pv) ; // convert hpa to Pa
printf("pd:%f-----",Pd);
	Rho = Pd /(RHO_RD * Temperature) + Pv / (RHO_RV * Temperature);

	return Rho ; // in kg/m^3
}


int main(int argc, char *argv[]) {
	
	float temp,dew,press;
	
	temp = 16.0;
	press = 92300.0;
	dew = -4.0 ;
	
	float es = RhoCalculateSaturationPressure(-4.0);
	
	
	float ro = RhoCalculateRho(press ,dew,temp);
	
	printf("%f \n",ro);  //  1.11 must be
	
	
	return 0;
}
