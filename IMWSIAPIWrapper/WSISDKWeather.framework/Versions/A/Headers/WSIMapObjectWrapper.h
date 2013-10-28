//
//  WSIMapObjectWrapper.h
//  WSISDK
//
//  Created by WSI on 1/10/13.
//  Copyright (c) 2013 WSI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>

extern NSString* const gWSISDK_LayerRadarConus;
extern NSString* const gWSISDK_LayerHDSatelliteNAmerica;
extern NSString* const gWSISDK_LayerRoadWeather;
extern NSString* const gWSISDK_LayerWindSpeed;
extern NSString* const gWSISDK_LayerHDSatelliteTropics;
extern NSString* const gWSISDK_LayerTemperatureConus;
extern NSString* const gWSISDK_LayerWaterTemperature;
extern NSString* const gWSISDK_LayerSnowCoverConus;
extern NSString* const gWSISDK_LayerRadarConusAndHDSatelliteNAmerica;
extern NSString* const gWSISDK_LayerTrafficFlow;
extern NSString* const gWSISDK_LayerTrafficFlowAndRadarConus;
extern NSString* const gWSISDK_LayerTrafficFlowAndRoadWeather;
extern NSString* const gWSISDK_OverlayEarthquakes;
extern NSString* const gWSISDK_OverlayStormTracks;
extern NSString* const gWSISDK_OverlayTropicalTracks;
extern NSString* const gWSISDK_OverlayTrafficIncidents;
extern NSString* const gWSISDK_WeatherAlertsTropical;
extern NSString* const gWSISDK_WeatherAlertsSevere;
extern NSString* const gWSISDK_WeatherAlertsFlood;
extern NSString* const gWSISDK_WeatherAlertsWinter;
extern NSString* const gWSISDK_WeatherAlertsMarine;
extern NSString* const gWSISDK_WeatherAlertsOther;

@interface WSIMapObjectWrapper : NSObject

/*
 Returns a localized name for the map object.
 Use this method if you want to obtain a displayable name for the map object,
 and provided that your app includes localization for the name.
 The name will be localized based on whether the name appears in the app's
 Localizable.strings table. 
 The demo applications include default localization that you can copy into your
 own app's Localizable.strings. 
 If no localization is found, the unlocalized (raw) name will be returned.
 */
- (NSString *)getName;

/*
 Returns a string that can be used to identify a map object by name. For 
 example, apps might use this method to identify the traffic layer when the
 list of available overlay objects is returned to set the location and/or 
 radius for that.
 Unlike getName, this string is unaffected by localization.
 Compare this value to the above gWSISDK_ values to identify map objects.
 */

- (NSString *)getID;

/*
 Returns the transparency for the map object.
 The returned value will be between 0 (full opaque) and 100 (fully transparent)
 inclusive.
 Only applies to raster layers (like Temperature) -- for overlay objects 0
 will be returned.
 */
- (NSUInteger)getTransparency;

/*
 Sets the transparency of the map object to the given value.
 The given value should be between 0 and 100 inclusive.
 Has no effect on overlay / category map objects.
 */
- (void)setTransparency:(NSUInteger)value;

/*
 Returns YES if the map object is currently on the map view.
 */
- (BOOL)isActive;

/*
 Returns YES if the map object has any future tiles.
 Most raster layers only have past tiles.
 Only applies to raster layers (like Temperature) -- for overlay objects NO
 will be returned.
 */
- (BOOL)hasFuture;

/*
 Returns YES if the map object has any past tiles.
 Most raster layers have past tiles but traffic flow doesn't.
 Only applies to raster layers (like Temperature) -- for overlay objects NO
 will be returned.
 */
- (BOOL)hasPast;


/*
 Returns YES if the map object uses a location.
 Only applies to the traffic incidents overlay currently. Will return NO for any 
 other type of map object.
 */
- (BOOL)hasLocation;


/*
 Sets the location for the map object to the given value and forces a refresh
 if the map object is currently active.
 Only applies to the traffic incidents overlay currently. Calling this for any
 other type of map object will have no effect.
 */
- (void)setLocation:(CLLocationCoordinate2D)location;


/*
 Returns YES if the map object uses a radius.
 Only applies to the traffic incidents overlay currently. Will return NO for any 
 other type of map object.
 */
- (BOOL)hasRadius;


/*
 Sets the radius for the map object to the given value and forces a refresh
 if the map object is currently active.
 Only applies to the traffic incidents overlay currently. Calling this for any
 other type of map object will have no effect.
 */
- (void)setRadius:(float)radius;

@end
