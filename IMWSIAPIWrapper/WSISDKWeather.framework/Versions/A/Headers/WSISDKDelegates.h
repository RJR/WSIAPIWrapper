//
//  WSISDKDelegates.h
//  WSISDK
//
//  Created by WSI on 1/10/13.
//  Copyright (c) 2013 WSI. All rights reserved.
//

//------------------------------------------------------------------------------
// WSISDKDelegate
//------------------------------------------------------------------------------

@class WSISDK;

@protocol WSISDKDelegate <NSObject, MKMapViewDelegate>

@optional
//
// Map layers / overlays / categories delegates.
// These are optional however they will need to be implemented on your delegate
// object depending on whether you are using layers / overlays / categories.
//

/*
 Returns layers array. Array contains WSIMapObjectWrapper objects.
 You must implement this if you call requestForLayersList.
 */
- (void)mapSDK:(WSISDK *)sdk layersList:(NSArray *)layers;

/*
 Returns actual layer time while looping is in progress.
 */
- (void)mapSDK:(WSISDK *)sdk layerTime:(NSString *)time;

/*
 Returns overlays array. Array contains WSIMapObjectWrapper objects.
 You must implement this if you call requestForOverlaysList.
 */
- (void)mapSDK:(WSISDK *)sdk overlaysList:(NSArray *)overlays;

/*
 Returns categories array. Array contains WSIMapObjectWrapper objects.
 You must implement this if you call requestForCategoriesList.
 */
- (void)mapSDK:(WSISDK *)sdk categoriesList:(NSArray *)categories;

/*
 Called after a successful call to getRoutesForWaypointsAsynchronous:maxRoutes:
 departureTimeSecondsFromNow:orArrivalTimeSecondsFromNow:units:.
 The parameter is an NSArray * containing NSDictionary * entries. See 
 WSIInrixRouteKeys.h for a list of available keys that can be used to access
 the available data.
 You should implement this delegate if you are using the SDK to obtain routes.
 */
- (void)gotInrixRouteData:(NSArray *)routeInfo;

/*
 Called if there is an error when processing an earlier call to the
 getRoutesForWaypointsAsynchronous:maxRoutes:departureTimeSecondsFromNow:
 orArrivalTimeSecondsFromNow:units: method.
 You should implement this delegate if you are using the SDK to obtain routes.
 */
- (void)onInrixRouteFailure:(NSError *)error;

@required

/*
 Called if there is any error when fetching layers / overlays / categories.
 You must implement this.
 */
- (void)mapSDK:(WSISDK *)sdk error:(NSError *)error;

//
// MKMapViewDelegate delegates -- see MKMapView.h / Apple documentation.
//

@end
