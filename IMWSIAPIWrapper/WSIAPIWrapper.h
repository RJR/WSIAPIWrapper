//
//  WSIAPIWrapper.h
//  IMWSIAPIWrapper
//
//  Created by ManjuChandran on 23/10/13.
//  Copyright (c) 2013 Impiger Technologies. All rights reserved.
//
#import "WSISDKWeather/WSISDK.h"
#import "MapKit/MapKit.h"
#import <MapKit/MKAnnotation.h>

#import <Foundation/Foundation.h>

@class WSIPinAnnotation;

typedef enum
{
    overlayTypeLayer=0,
    overlayTypeOverlay,
    overlayTypeCategory
}eObjectType;

typedef enum
{
    mapModeStandard=0,
    mapModeSatellite,
    mapModeHybrid
}eMapType;

static const float kFrameScaleFactor 		= 1.30f;

static const int kMaxLayers 				= 20;
static const int kMaxOverlays 				= 10;
static const int kMaxCategories 			= 10;

static const float kInitialLatitude			=  38.89f;
static const float kInitialLongitude		= -77.05f;
static const float kInitialLatitudeSpan		=  10.0f;
static const float kInitialLongitudeSpan	=  10.0f;
static const MKMapType kDefaultMapType 		= MKMapTypeHybrid;

static const double kCancelFollowMePointDistance = 25.0;
static const double kMinDistanceDeltaToUpdateTrafficIncidentsMeters = 100.0;

@protocol WSISdKWrapperDelegate
- (void)applyTransperancy:(NSUInteger)transperancy;
- (void)unitDisplay:(UIView*)legendview;
@end

@interface WSIAPIWrapper : NSObject<WSISDKDelegate,MKMapViewDelegate>
{
    WSIPinAnnotation *_pinAnnotation;
}


@property (nonatomic, strong) WSISDK *wsiSDK;
@property (nonatomic,assign)NSInteger currentOverlayType;
@property (nonatomic,assign)BOOL activeLayerhasFuture;
@property (strong, nonatomic) NSArray *layersArray;
@property (strong, nonatomic) NSArray *overlaysArray;
@property (strong, nonatomic) NSArray *categoriesArray;
@property (strong, nonatomic) WSIMapObjectWrapper *activeLayer;
@property (strong, nonatomic) id<WSISdKWrapperDelegate> delegate;
@property (nonatomic, assign) WSIUnitPreferences currentUnitPreference;



- (MKMapView *)MapView;
- (void)mapMode:(NSInteger)mode;
- (void)showWeather:(NSMutableArray*)categories;
- (void)spotLocation;
- (void)updateUserLocationVisibility;
- (void)pastFutureAction:(BOOL)pastSelected;
- (void)startLooping;
- (void)stopLooping;
- (NSArray *)overlaysList;
- (void)transperancy:(NSUInteger)transperancyValue;
- (void)switchUnits;


@end
