/*
 *  Sys.mm
 *  CondeNastTravelerGoldList
 *
 *  Created by Jan Kalis on 3/1/10.
 *  Copyright 2010 Glow Interactive. All rights reserved.
 *
 */

#import "Sys.h"


#import <sys/time.h>
#import <time.h>

namespace Sys
{

	namespace
	{
		double firstGetSeconds_ = -1.0;
		
		
		std::string resourcesDirectory_ = "";
	}
	
	void Init()
	{
		// set resources directory
        /*char resourcesBuffer[5000];
		
		[[[NSBundle mainBundle] resourcePath] getCString:resourcesBuffer maxLength:1024 encoding:NSUTF8StringEncoding];
        resourcesDirectory_ = resourcesBuffer;*/
	}


	std::string GetAbsolutePath(std::string fileName)
	{
		return resourcesDirectory_ + "/" + fileName;
	}

	double GetSeconds()
	{
		struct timeval now;
		gettimeofday(&now, NULL);
		
		double time = now.tv_sec + now.tv_usec / 1000000.0;
		
		if (firstGetSeconds_ < 0.0) firstGetSeconds_ = time;
		
		return time - firstGetSeconds_;
	}
}
