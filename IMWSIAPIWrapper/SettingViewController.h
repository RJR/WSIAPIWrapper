//
//  SettingViewController.h
//  IMWSIAPIWrapper
//
//  Created by ManjuChandran on 23/10/13.
//  Copyright (c) 2013 Impiger Technologies. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol OverlaySettingsDelegate
- (void)applyOverlays:(NSMutableArray *)overlaysArr;
@end

@interface SettingViewController : UIViewController<UITableViewDataSource,UITableViewDelegate>
{
    
}
@property (strong, nonatomic)NSMutableArray *overlaysArr;
@property (strong, nonatomic)NSMutableArray *selectedOverlays;
@property (strong, nonatomic)IBOutlet UITableView *layersTV;
@property (strong, nonatomic)id<OverlaySettingsDelegate> delegate;

-(IBAction)doneBtAction:(id)sender;
@end
