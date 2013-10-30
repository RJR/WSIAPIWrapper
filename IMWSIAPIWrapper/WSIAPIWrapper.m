//
//  WSIAPIWrapper.m
//  IMWSIAPIWrapper
//
//  Created by ManjuChandran on 23/10/13.
//  Copyright (c) 2013 Impiger Technologies. All rights reserved.
//

#import "WSISDKWeather/WSISDK.h"
#import "WSISDKWeather/WSIMapObjectWrapper.h"
#import "WSIPinAnnotation.h"

#import "WSIAPIWrapper.h"



@implementation WSIAPIWrapper


- (MKMapView *)MapView
{
    _wsiSDK = [[WSISDK alloc] initWithFrame:CGRectMake(0,0,320,250) withDelegate:self];
    [_wsiSDK setMemberID:@"1194" mapID:@"0001"];
    _layersArray=[[NSMutableArray alloc] initWithCapacity:20];
    _overlaysArray=[[NSMutableArray alloc] initWithCapacity:10];
    _categoriesArray=[[NSMutableArray alloc] initWithCapacity:10];
    [_wsiSDK requestForLayersList];
	[_wsiSDK requestForOverlaysList];
	[_wsiSDK requestForCategoriesList];
    [_wsiSDK setRegion:MKCoordinateRegionMake(
                                      CLLocationCoordinate2DMake(kInitialLatitude, kInitialLongitude), MKCoordinateSpanMake(kInitialLatitudeSpan, kInitialLongitudeSpan))
     animated:NO];
    [_wsiSDK setPreferredUnits:ENGLISH];
    [_wsiSDK.mapSDKView setMapType:kDefaultMapType];
    _currentUnitPreference=ENGLISH;
    return _wsiSDK.mapSDKView;
}

- (void)mapMode:(NSInteger)mode
{
    switch (mode) {
        case mapModeStandard:
            _wsiSDK.mapSDKView.mapType=MKMapTypeStandard;
            break;
        case mapModeSatellite:
            _wsiSDK.mapSDKView.mapType=mapModeSatellite;
            break;
        case mapModeHybrid:
            _wsiSDK.mapSDKView.mapType=MKMapTypeHybrid;
            break;
        default:
            break;
    }
}

- (void)showWeather:(NSMutableArray *)categories
{
    _activeLayerhasFuture=NO;
    
	// IMPORTANT: ENABLE LINE BELOW AND REPLACE PARAMETERS WITH WSI-PROVIDED VALUES!
   
    for(NSString *overlay in categories)
    {
        for(WSIMapObjectWrapper *geoObject in _layersArray)
        {
            NSLog(@"layers name: %@",[geoObject getName]);
            if([[geoObject getName] isEqualToString:overlay])
            {
                _activeLayer=geoObject;
                _activeLayerhasFuture=[_activeLayer hasFuture];
                BOOL enabling = !geoObject.isActive;
                [self updateWeatherUnits:enabling];
                [_wsiSDK selectActiveLayer:(enabling ? geoObject : nil)];
                break;
                
            }
        }
        for(WSIMapObjectWrapper *geoObject in _overlaysArray)
        {
            NSLog(@"layers name: %@",[geoObject getName]);
            if([[geoObject getName] isEqualToString:overlay])
            {
                _activeLayer=geoObject;
                _activeLayerhasFuture=[_activeLayer hasFuture];
                BOOL enabling = !geoObject.isActive;
                [_wsiSDK setStateForOverlay:geoObject turnedOn:enabling];
                break;
            }
        }
        for(WSIMapObjectWrapper *geoObject in _categoriesArray)
        {
            NSLog(@"layers name: %@",[geoObject getName]);
            if([[geoObject getName] isEqualToString:overlay])
            {
                _activeLayer=geoObject;
                _activeLayerhasFuture=[_activeLayer hasFuture];
                BOOL enabling = !geoObject.isActive;
                [_wsiSDK selectActiveCategory:(enabling ? geoObject : nil)];
                break;
            }
        }
        
    }
    [_delegate applyTransperancy:[_activeLayer getTransparency]];
}

- (void) updateWeatherUnits:(BOOL)haveLayer
{
    UIView *legendView=[_wsiSDK getLegendViewForLayer:_activeLayer unitPreferences:_currentUnitPreference];
    if (legendView)
	{
        [_delegate unitDisplay:haveLayer?(UIView*)legendView:nil];
    }
}

- (void)switchUnits
{
    _currentUnitPreference=_currentUnitPreference==ENGLISH?METRIC:ENGLISH;
    [_wsiSDK setPreferredUnits:_currentUnitPreference];
    [self updateWeatherUnits:YES];
}

-(NSArray *)overlaysList
{
    NSMutableArray *fullLayersArray=[[NSMutableArray alloc] init];
    for(WSIMapObjectWrapper *geoObj in _layersArray)
        [fullLayersArray addObject:[geoObj getName]];
    for(WSIMapObjectWrapper *geoObj in _overlaysArray)
        [fullLayersArray addObject:[geoObj getName]];
    for(WSIMapObjectWrapper *geoObj in _categoriesArray)
        [fullLayersArray addObject:[geoObj getName]];
    return fullLayersArray;
}

- (void)startOrStopLooping:(BOOL)isLooping
{
	//_isLooping = isLooping;
	if (isLooping)
	{
	   	[_wsiSDK startLoopingForActiveLayer];
	}
	else
	{
	   	[_wsiSDK stopLoopingForActiveLayer];
	}
}

- (void)startLooping
{
    [_wsiSDK startLoopingForActiveLayer];
}

- (void)stopLooping
{
    [_wsiSDK stopLoopingForActiveLayer];
}

- (void)transperancy:(NSUInteger)transperancyValue
{
    [_wsiSDK setTransparencyForActiveLayer:transperancyValue];
}

- (void)spotLocation
{
    _wsiSDK.mapSDKView.delegate=self;
    
    _pinAnnotation = nil;
    
    if (!_pinAnnotation)
    {
        _pinAnnotation = [[WSIPinAnnotation alloc] initWithCoordinate:_wsiSDK.mapSDKView.region.center];
        [_wsiSDK.mapSDKView addAnnotation:_pinAnnotation];
    }
    MKMapView *mapView = _wsiSDK.mapSDKView;
	mapView.showsUserLocation = YES;
	[self updateUserLocationVisibility];
}

- (void)updateUserLocationVisibility
{
	// Not sure why but setting showsUserLocation = NO when the user drags the
	// map doesn't work much of the time so explicitely show / hide it here?
    NSLog(@"User's current location is %@",_wsiSDK.mapSDKView.userLocation.title);
	MKMapView *mapView = _wsiSDK.mapSDKView;
    MKAnnotationView *ulv = [mapView viewForAnnotation:mapView.userLocation];
	ulv.hidden = !mapView.showsUserLocation;
}

- (void)pastFutureAction:(BOOL)pastSelected
{
    if(_activeLayerhasFuture)
    {
        if (pastSelected)
        {
            [_wsiSDK switchToPast];
        }
        else
        {
            [_wsiSDK switchToFuture];
        }
    }
    else
    {
        NSLog(@"Not future for this layer");
    }

}


- (NSString *)convertGMTToLocal:(NSString *)gmtTime
{
	NSTimeZone *timeZone = [NSTimeZone localTimeZone];
	
	NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
	[dateFormatter setDateFormat:@"HH:mm"];
    
	NSLocale *inputLocale = [[NSLocale alloc] initWithLocaleIdentifier:@"en_US_POSIX"];
	[dateFormatter setLocale:inputLocale];

    
	// Create our date from the provided GMT date string
	NSDate *gmtDate = [dateFormatter dateFromString:gmtTime];
    
	NSString *localTimeString = @"";
	if (gmtDate != nil)
	{
		// Now work out what the local date is using the timezone.
		NSDate *localDate = [[NSDate alloc] initWithTimeInterval:[timeZone secondsFromGMT] sinceDate:gmtDate];
        
		[dateFormatter setLocale:[NSLocale currentLocale]];
		[dateFormatter setDateFormat:@"HH:mm"];
		localTimeString = [dateFormatter stringFromDate:localDate];
	}
	
	return localTimeString;
}
//------------------------------------------------------------------------------
#pragma mark WSISDKDelegate -- map layers, overlays and categories
//------------------------------------------------------------------------------

- (void)mapSDK:(WSISDK *)mapSDK layersList:(NSArray *)layers
{
    if (layers)
    {
        _layersArray=layers;
    }
}


- (void)mapSDK:(WSISDK *)mapSDK layerTime:(NSString *)time
{
    //[self setLayerTime:time];
}


- (void)mapSDK:(WSISDK *)sdk overlaysList:(NSArray *)overlays
{
    if (overlays)
    {
//        [_overlaysArray removeAllObjects];
//        [_overlaysArray addObjectsFromArray:overlays];
        _overlaysArray=overlays;
		for (WSIMapObjectWrapper *overlay in overlays)
		{
			if ([overlay.getID isEqualToString:gWSISDK_OverlayTrafficIncidents])
			{
				//_trafficIncidentsOverlay = overlay;
                //[_trafficIncidentsOverlay setLocation:CLLocationCoordinate2DMake(kInitialLatitude, kInitialLongitude)];
                //	[_trafficIncidentsOverlay setRadius:50.0]; // make it more likely that something will be shown for demo purposes
				break;
			}
		}
    }
}


- (void)mapSDK:(WSISDK *)sdk categoriesList:(NSArray *)categories
{
    if (categories)
    {
//        [_categoriesArray removeAllObjects];
//        [_categoriesArray addObjectsFromArray:categories];
        _categoriesArray=categories;
    }
}


- (void)mapSDK:(WSISDK *)mapSDK error:(NSError *)error
{
	//[self handleError:error];
}


//------------------------------------------------------------------------------
#pragma mark WSISDKDelegate -- MKMapView delegates
//------------------------------------------------------------------------------

/*
 Example MKMapViewDelegate delegates are implemented below.
 For the full list of available MKMapViewDelegate delegates see the
 documentation for MKMapView or look in MKMapView.h.
 */

- (void)mapView:(MKMapView *)mapView regionDidChangeAnimated:(BOOL)animated
{
    //	if (_mapMode == MM_Center)
    //	{
    //		// re-center traffic incidents on new map center location
      //      [self setTrafficIncidentsLocation:_wsiSDK.mapSDKView.region.center];
    //	}
}


- (MKAnnotationView *)mapView:(MKMapView *)mapView viewForAnnotation:(id <MKAnnotation>)annotation
{
#if 0
    /*
     Code showing how to replace the default user location annotation with a
     custom image.
     Return nil to use the default annotation.
     Unfortunately, replacing the default user location annotation disables user
     location updates and the user location delegates will no longer be called so
     this probably isn't a useful approach. For more information see
     http://stackoverflow.com/questions/11432746/custom-annotation-view-for-userlocation-not-moving-the-mapview
     It' s possible that Apple will change this behavior at some point but for
     now the only alternative is to add your custom annotation to the map view
     and use your own CLLocationManager to update its location.
     */
    if ([annotation isKindOfClass:[MKUserLocation class]])
    {
        static NSString * const kUserLocationAnnotationIdentifier = @"WSIUserLocationAnnotation";
        MKAnnotationView *replacementView = [mapView dequeueReusableAnnotationViewWithIdentifier:kUserLocationAnnotationIdentifier];
#if 0 // use a purple pin
        if (!replacementView)
        {
            MKPinAnnotationView *pinView = [[[MKPinAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:kUserLocationAnnotationIdentifier] autorelease];
            pinView.pinColor = MKPinAnnotationColorPurple;
            pinView.animatesDrop = NO;
            replacementView.canShowCallout = NO;
            replacementView = pinView;
        }
#else // use a red dot (custom image)
        if (!replacementView)
        {
            replacementView = [[[MKAnnotationView alloc] initWithAnnotation:annotation reuseIdentifier:kUserLocationAnnotationIdentifier] autorelease];
            replacementView.image = [UIImage imageNamed:@"red.png"];
            replacementView.canShowCallout = YES;
        }
#endif
        replacementView.annotation = annotation;
        return replacementView;
    }
#endif
    
    [self updateUserLocationVisibility];
    
    return nil; // use default for other annotations
}


-(void)mapView:(MKMapView *)mapView didAddAnnotationViews:(NSArray *)views
{
    
#if 0
	/*
     Code showing how to hide the default user location annotation. You would do
     this, for example, if you have showsUserLocation=YES so you can get location
     updates from the MKMapView but don't want to show the user's current
     location.
     Another alternative would be to use your own CLLocationManager object to get
     user location updates without using showsUserLocation=YES (which would also
     allow you to use a custom user location annotation).
     */
    MKAnnotationView *ulv = [mapView viewForAnnotation:mapView.userLocation];
    ulv.hidden = YES;
#endif
	[self updateUserLocationVisibility];
}

#pragma mark WSISDKDelegate -- (user location delegates -- requires showsUserLocation = YES)

- (void)mapView:(MKMapView *)mapView didUpdateUserLocation:(MKUserLocation *)userLocation
{
    
    //	if (_mapMode == MM_FollowMe)
    //	{
    //		// re-center traffic incidents on new user location
    //		// This isn't as smooth as setting mapView.userTrackingMode -- it looks
    //		// like that is using interpolation between the previous and current
    //		// locations to smoothly move the map / user location icon. Presumably,
    //		// something similar could be done here to emulate that?
    		[_wsiSDK.mapSDKView setCenterCoordinate:userLocation.coordinate animated:YES];
    //		//[self setTrafficIncidentsLocation:userLocation.coordinate];
    //	}
}


/*
 Called when tracking mode changes.
 This occurs when we set it ourselves (see below) or if it's disabled internally
 due to the map being moved.
 */
- (void)mapView:(MKMapView *)mapView didChangeUserTrackingMode:(MKUserTrackingMode)mode animated:(BOOL)animated
{
    
	//[self updateTrackingMode];
}


@end
