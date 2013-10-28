//
//  WSIInrixRouteKeys.h
//  WSICommon
//
//  Created by WSI on 1/22/13.
//  Copyright (c) 2013 WSI. All rights reserved.
//

#import <Foundation/Foundation.h>

/*
 Keys for INRIX route parameters returned in NSDictionary via routing methods.
 See http://devzonedocs.inrix.com/v3/docs/index.php/cs/findroute/?api=mobile
 for more information.
 */

// Route description.
extern NSString * const kRouteDescriptionKey;

// Route uncongested travel time.
extern NSString * const kRouteUncongestedTravelTimeMinutesKey;

// Route quality, typically scaled from 0 (most congested) to 3 (least
// congested).
extern NSString * const kRouteQualityKey;

// Route ID.
extern NSString * const kRouteIdKey;

// Whether or not there are road closures along the route. If true, then travel
// times will not be returned.
extern NSString * const kRouteHasClosuresKey;

// The currently calculated travel time. If there are road closures or
// restrictions along the route, this attribute will not be present, and you
// should call FindRoute to get a new route.
extern NSString * const kRouteTravelTimeMinutesKey;

// The difference in minutes between the travel time for the returned route and
// the normal travel time expected for the time and day.
extern NSString * const kRouteAbnormalityMinutesKey;

// The average speed on the route. If there are road closures along the route,
// this value will be 0.
extern NSString * const kRouteAverageSpeedKey;

// Whether or not traffic is used in calulating the route.
extern NSString * const kRouteTrafficConsideredKey;

// The status ID for the request
extern NSString * const kRouteStatusIdKey;

// The length of the route, in miles for units=0 and kilometers for units=1.
extern NSString * const kRouteTotalDistanceKey;

