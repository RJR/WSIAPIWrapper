//
//  WSIPinAnnotation.h
//  TesterForWSISDK
//
//  Created by WSI on 4/10/13.
//
//

#import <Foundation/Foundation.h>
#import <CoreLocation/CoreLocation.h>
#import <MapKit/MKAnnotation.h>

/*
 Example annotation object.
 Can be initialized with an initial location.
 Location can be modified at any time.
 */
@interface WSIPinAnnotation : NSObject <MKAnnotation>
@property (nonatomic, readonly) CLLocationCoordinate2D coordinate;
- (id)initWithCoordinate:(CLLocationCoordinate2D)coordinate;
- (void)setCoordinate:(CLLocationCoordinate2D)newCoordinate;
@end
