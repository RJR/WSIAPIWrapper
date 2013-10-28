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
@end

@interface WSIAPIWrapper : NSObject<WSISDKDelegate,MKMapViewDelegate>
{
    WSIPinAnnotation *_pinAnnotation;
}


@property (nonatomic, strong) WSISDK *wsiSDK;
@property(nonatomic,assign)NSInteger currentOverlayType;
@property(nonatomic,assign)BOOL activeLayerhasFuture;
@property (strong, nonatomic) NSMutableArray *layersArray;
@property (strong, nonatomic) NSMutableArray *overlaysArray;
@property (strong, nonatomic) NSMutableArray *categoriesArray;
@property (strong, nonatomic) WSIMapObjectWrapper *activeLayer;
@property (strong, nonatomic) id<WSISdKWrapperDelegate> delegate;


- (MKMapView *)MapView;
- (void)showWeather:(NSMutableArray*)categories;
- (void)spotLocation;
- (void)updateUserLocationVisibility;
- (void)pastFutureAction:(BOOL)pastSelected;
- (void)startLooping;
- (void)stopLooping;
- (NSMutableArray *)overlaysList;
- (void)transperancy:(NSUInteger)transperancyValue;



@end
