//
//  WSIPinAnnotation.m
//  TesterForWSISDK
//
//  Created by WSI on 4/10/13.
//
//

#import "WSIPinAnnotation.h"

@implementation WSIPinAnnotation

- (id)initWithCoordinate:(CLLocationCoordinate2D)coordinate
{
	self = [super init];
	if (!self)
		return nil;
	
	_coordinate = coordinate;
	
	return self;
}


- (void)setCoordinate:(CLLocationCoordinate2D)newCoordinate
{
	_coordinate = newCoordinate;
}


- (NSString *)title
{
	return @"WSIPinAnnotation";
}


- (NSString *)subtitle
{
	return [NSString stringWithFormat:@"lat=%.4f, lon=%.4f", self.coordinate.latitude, self.coordinate.longitude];
}


- (NSString *)description
{
	return [NSString stringWithFormat:@"WSIPinAnnotation lat=%.4f, lon=%.4f", self.coordinate.latitude, self.coordinate.longitude];
}

@end
