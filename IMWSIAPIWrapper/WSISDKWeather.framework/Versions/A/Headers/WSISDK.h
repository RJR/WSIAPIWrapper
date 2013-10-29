//
//  WSISDK.h
//  WSISDK
//
//  Created by WSI on 1/10/13.
//  Copyright (c) 2013 WSI. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <MapKit/MapKit.h>
#import "WSISDKDelegates.h"

extern NSString* const gINRIXAttribution; // you must present this in your app if you use Inrix functionality

typedef enum
{
    ENGLISH = 0,
    METRIC = 1
} WSIUnitPreferences;


@class WSIMapObjectWrapper;
@interface WSISDK : NSObject

/*
 Library initialization method. Parameters:
	- frame - frame to init map view. Access to this view provided with
	  mapSDKView property
    - delegate - your implementation of WSISDKDelegate protocol to catch
	  responses from library
 */
- (id)initWithFrame:(CGRect)frame withDelegate:(id<WSISDKDelegate>)delegate;


/*
 To use this library you need to contact WSI to obtain these keys:
      - memberID
      - mapID
 Without these keys the SDK will be unable to connect to WSI's service provider.
 Set the keys immediately after library initialization.
 */
- (void)setMemberID:(NSString *)memberID mapID:(NSString *)mapID;

//------------------------------------------------------------------------------
// Map
//------------------------------------------------------------------------------

/*
 Passed to the MKMapView's setRegion:animated: method.
 Use the mapSDKView (see below) to access MKMapView methods and properties.
 */
- (void)setRegion:(MKCoordinateRegion)region animated:(BOOL)animated;


/*
 Passed to the MKMapView's setCenterCoordinate:animated: method.
 Use the mapSDKView (see below) to access MKMapView methods and properties.
 */
- (void)setCenterCoordinate:(CLLocationCoordinate2D)coordinate animated:(BOOL)animated;


/*
 Causes the map view to refresh map objects including layers.
 */
- (void)refreshMapView;

//------------------------------------------------------------------------------
// Layers
//------------------------------------------------------------------------------

/*
 This call is used to request a list of available layers from the WSI SDK.
 You can catch the response using WSISDKDelegate's implementation:
      - (void)mapSDK:(WSISDK *)sdk layersList:(NSArray *)layers;
 If layers are inaccessible, the SDK will send an NSError to this delegate:
      - (void)mapSDK:(WSISDK *)sdk error:(NSError *)error;
 */
- (void)requestForLayersList;


/*
 This call is used to switch on a particular layer on the map view.
 Only one layer at a time can be shown. 
 If you select a layer the previous layer (if any) will be switched off.
 Use nil to set the active layer to "none".
 */
- (void)selectActiveLayer:(WSIMapObjectWrapper *)layer;


/*
 Set transparency of the active layer. Use values from 0 (fully opaque) to 100
 (fully transparent).
 */
- (void)setTransparencyForActiveLayer:(NSUInteger)transparency;


/*
 Returns a UIImageView* containing legend for particular layer using the 
 currently set units (see setPreferredUnits).
 */
- (UIImageView *)getLegendViewForLayer:(WSIMapObjectWrapper *)layer;


/*
 Returns a UIImageView* containing legend for particular layer.
 Deprecated method that accepts an unit preferences parameter -- use 
 setPreferredUnits / getLegendViewForLayer instead.
 */
- (UIImageView *)getLegendViewForLayer:(WSIMapObjectWrapper *)layer unitPreferences:(WSIUnitPreferences)units;


/*
 Starts looping for active layer. Has no effect if there is no active layer.
 */
- (void)startLoopingForActiveLayer;


/*
 Stops looping for active layer. Has no effect if there is no active layer.
 */
- (void)stopLoopingForActiveLayer;


/*
 Returns actual time of active layer.
 */
- (NSString *)getTimeForActiveLayer;


/*
 Sets layer to future mode when looping.
 */
- (void)switchToFuture;


/*
 Sets layer to past mode when looping.
 */
- (void)switchToPast;

//------------------------------------------------------------------------------
// Overlays
//------------------------------------------------------------------------------

/*
 This call is used to request a list of available overlays from the WSI SDK.
 You can catch the response using WSISDKDelegate's implementation:
      - (void)mapSDK:(WSISDK *)sdk overlaysList:(NSArray *)overlays;
 If overlays are inaccessible, the SDK will send an NSError to this delegate:
      - (void)mapSDK:(WSISDK *)sdk error:(NSError *)error;
 */
- (void)requestForOverlaysList;


/*
 This call is used to switch ON/OFF particular type of overlay.
 It is possible to have multiple overlays on at the same time.
 */
- (void)setStateForOverlay:(WSIMapObjectWrapper *)overlay turnedOn:(BOOL)turnedOn;

//------------------------------------------------------------------------------
// Categories
//------------------------------------------------------------------------------

/*
 This call is used to request a list of available categories from the WSI SDK.
 You can catch the response using WSISDKDelegate's implementation:
      - (void)mapSDK:(WSISDK *)sdk categoriesList:(NSArray *)categories;
 If categories are inaccessible, the SDK will send an NSError to this delegate:
      - (void)mapSDK:(WSISDK *)sdk error:(NSError *)error;
 */
- (void)requestForCategoriesList;


/*
 This call is used to switch on a particular category on the map view. 
 Only one category at a time can be shown. 
 If you select a category the previous category (if any) will be switched off.
 Use nil to set the active category to "none".
 */
- (void)selectActiveCategory:(WSIMapObjectWrapper *)category;

//------------------------------------------------------------------------------
// Miscellaneous API methods (availability depends on SDK version).
//------------------------------------------------------------------------------

/*
 Use this method to set the units to use for layers, overlays and categories,
 legends and annotation callouts.
 The default if you don't call this method is ENGLISH (STANDARD).
 */
- (void)setPreferredUnits:(WSIUnitPreferences)units;


/*
 Use this method to set the Inrix VendorID to the given value.
 The SDK uses a default (shared) value so you normally only have to call this
 method if you are provided with a different (unique) value.
 */
- (void)setInrixVendorID:(NSString *)inrixVendorID;

/*
 Obtains routes for the given parameters.
 	waypoints:
		Should contain 2-10 CLLocation* entries with the latitude / longitude 
		for each waypoint.
	maxRoutes:
		Specifies the maximum number of routes to return (1-3).
	departureTimeSecondsFromNow:
		Specifies the departure time to use for the trip in seconds from the
		current time. Use 0 for "now".
	orArrivalTimeSecondsFromNow:
		Specifies the arrival time to use for the trip in seconds from the
		current time. Ignored if departureTimeSecondsFromNow is set.
	units:
		Units to use (see WSIUnitPreferences).
		
This is an asynchronous method with results returned via the gotInrixRouteData:
 or onInrixRouteFailure: WSISDKDelegate delegate methods.
 */
- (void)getRoutesForWaypointsAsynchronous:(NSArray *)waypoints
	maxRoutes:(int)maxRoutes
	departureTimeSecondsFromNow:(NSTimeInterval)departureTimeSecondsFromNow
	orArrivalTimeSecondsFromNow:(NSTimeInterval)arrivalTimeSecondsFromNow
	units:(WSIUnitPreferences)units;

/*
 Sets the map heading (the direction it's facing).
 	rotationDegrees: 
		Heading in degrees relative to north up (0 degrees).
		Use 0.0 for north up.
		Use 180.0 / -180.0 for north down.
		West could be either -90 or +270.
 */
- (void)setMapHeadingDegrees:(double)rotationDegrees;

//------------------------------------------------------------------------------
// Properties
//------------------------------------------------------------------------------

/*
 Use this property to obtain / set the WSISDKDelegate delegate used by the SDK.
 This is optional -- the delegate can also be specified via the
 initWithFrame:withDelegate: method used to initialize the SDK.
 */
@property (nonatomic, assign) id<WSISDKDelegate> delegate;


/*
 Use this property to add the MKMapView to your own view hierarchy.
 */
@property (nonatomic, readonly) MKMapView *mapSDKView;

@end
