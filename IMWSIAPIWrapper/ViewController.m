//
//  ViewController.m
//  IMWSIAPIWrapper
//
//  Created by Janakiraman on 23/10/13.
//  Copyright (c) 2013 Impiger Technologies. All rights reserved.
//

#import "ViewController.h"
#import "SettingViewController.h"
#import "WSIAPIWrapper.h"

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    _isLooping=NO;
    _wsiWrap=[[WSIAPIWrapper alloc] init];
    [_wsiWrap setDelegate:self];
    [_mapContainerView addSubview:[_wsiWrap MapView]];
    [_legendView setHidden:YES];
    
}


-(IBAction)showLayers:(id)sender
{
    SettingViewController *settingVC=[[SettingViewController alloc] initWithNibName:@"SettingViewController" bundle:nil];
    settingVC.overlaysArr=[_wsiWrap overlaysList];
    settingVC.delegate=self;
    [self presentViewController:settingVC animated:YES completion:nil];
}

-(IBAction)spotLocation:(id)sender
{
    [_wsiWrap spotLocation];
}

-(IBAction)changeUnits:(id)sender
{
    //[_wsiWrap change]
    [_wsiWrap switchUnits];
}

-(IBAction)playPastorFuture:(id)sender
{
   // [_wsiWrap pastFutureAction:YES];
    if(_isLooping)
    {
        [_wsiWrap stopLooping];
        [_startStopLoopingBt setTitle:@"Stop Looping" forState:UIControlStateNormal];
    }
    else
    {
        [_wsiWrap startLooping];
        [_startStopLoopingBt setTitle:@"Loop Past" forState:UIControlStateNormal];
    }
    _isLooping=!_isLooping;
}

-(IBAction)transperancyValueChanges:(id)sender
{
    UISlider *slider=(UISlider *)sender;
    NSLog(@"Transperancy Value: %f",[slider value]);
    [_wsiWrap transperancy:[slider value]];
}

-(IBAction)mapMode:(id)sender
{
    
}

#pragma Mark SettingViewController Delegate
-(void)applyOverlays:(NSMutableArray *)overlaysArr
{
    [_wsiWrap showWeather:overlaysArr];
}

#pragma Mark WSISDKWrapper Delegate

-(void)applyTransperancy:(NSUInteger)transperancy
{
    [_transperancySlider setValue:transperancy animated:YES];
}

-(void)unitDisplay:(UIView*)legendview
{
    if(legendview)
    {
        _legendView.hidden=NO;
        [_mapContainerView bringSubviewToFront:_legendView];
        if([[_legendView subviews] count]>0)
            [(NSArray *)[_legendView subviews] makeObjectsPerformSelector:@selector(removeFromSuperview)];
        CGRect legendViewFrame = legendview.frame;
        legendViewFrame.origin.x = 0.5*(_legendView.frame.size.width - legendViewFrame.size.width);
        legendViewFrame.origin.y = 0.5*(_legendView.frame.size.height - legendViewFrame.size.height);
        legendview.frame = legendViewFrame;
        [_legendView addSubview:legendview];
    }
	else
        _legendView.hidden=YES;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
