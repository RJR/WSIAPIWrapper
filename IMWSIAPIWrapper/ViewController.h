//
//  ViewController.h
//  IMWSIAPIWrapper
//
//  Created by Janakiraman on 23/10/13.
//  Copyright (c) 2013 Impiger Technologies. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "WSIAPIWrapper.h"
#import "SettingViewController.h"

@interface ViewController : UIViewController<OverlaySettingsDelegate,WSISdKWrapperDelegate>


@property (strong, nonatomic) WSIAPIWrapper *wsiWrap;
@property (strong, nonatomic) IBOutlet UIView *mapContainerView;
@property (strong, nonatomic) IBOutlet UISlider *transperancySlider;
@property (strong, nonatomic) IBOutlet UIButton *startStopLoopingBt;
@property (nonatomic, assign) BOOL isLooping;
@property (strong, nonatomic) IBOutlet UIView *legendView;

-(IBAction)showLayers:(id)sender;
-(IBAction)spotLocation:(id)sender;
-(IBAction)changeUnits:(id)sender;
-(IBAction)playPastorFuture:(id)sender;
-(IBAction)transperancyValueChanges:(id)sender;
-(IBAction)mapMode:(id)sender;

@end
