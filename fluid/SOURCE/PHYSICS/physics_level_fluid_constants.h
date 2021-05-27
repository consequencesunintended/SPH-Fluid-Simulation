/*
Alex Nasser
http://www.alexnasser.co.uk
Winter 2011
*/
#ifndef __PHSYICS_LEVEL_FLUID_CONSTANTS__
	#define __PHSYICS_LEVEL_FLUID_CONSTANTS__

	// -- LOCAL
	
	// .. REFERENCES

	// -- GLOBAL
	#define PHSYICS_LEVEL_FLUID_Particle_Size  4.0f
	#define PHSYICS_LEVEL_FLUID_CONSTANTS_Smoothing_Radius \
		PHSYICS_LEVEL_FLUID_Particle_Size 
	#define PHSYICS_LEVEL_FLUID_Stifness_K    0.002f
	#define PHSYICS_LEVEL_FLUID_Near_Stifness_Near_K  \
		PHSYICS_LEVEL_FLUID_Stifness_K * 10.0f
	#define PHSYICS_LEVEL_FLUID_Rest_Density 10.0f
	#define PHSYICS_LEVEL_FLUID_Spring_Coefficient 0.2f
	#define PHSYICS_LEVEL_FLUID_Yield_Ratio 0.1f
	#define PHSYICS_LEVEL_FLUID_Plasticity 0.5f
#endif