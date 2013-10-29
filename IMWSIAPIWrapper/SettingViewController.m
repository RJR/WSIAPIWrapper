//
//  SettingViewController.m
//  IMWSIAPIWrapper
//
//  Created by ManjuChandran on 23/10/13.
//  Copyright (c) 2013 Impiger Technologies. All rights reserved.
//

#import "SettingViewController.h"
#import "WSIAPIWrapper.h"

@interface SettingViewController ()

@end

@implementation SettingViewController

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    _layersTV.delegate=self;
    _layersTV.dataSource=self;
    _selectedOverlays=[[NSMutableArray alloc] init];
}


-(IBAction)doneBtAction:(id)sender
{
    [self dismissViewControllerAnimated:YES completion:nil];
    [_delegate applyOverlays:_selectedOverlays];
}

#pragma mark TableView Datasource

//-(NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
//{
//   
//}

-(int)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [_overlaysArr count];
}


-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	static NSString *cellIdentifier = @"Cell";
    UITableViewCell *cell;
	if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                      reuseIdentifier:cellIdentifier];
       // [cell setSelectionStyle:UITableViewCellSelectionStyleNone];
    }
    
    
    cell.textLabel.text = [_overlaysArr objectAtIndex:indexPath.row];
    return cell;
}

//- (UITableViewCell *) getCellContentView:(NSString *)cellIdentifier {
//	
//	CGRect lblFrame = CGRectMake(60.0f, 0.0f, 250.0f, 41.0f);
//    CGRect imgFrame = CGRectMake(20.0f, 10.5f, 20.0f, 20.0f);
//	CGRect imgView1Frame = CGRectMake(0, 0, 320, 41);
//    
//	UITableViewCell *cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue1 reuseIdentifier:@"Cell"];
//	
//    UIImageView *imgView1 = [[UIImageView alloc] init];
//    [imgView1 setFrame:imgView1Frame];
//    [imgView1 setImage:[UIImage imageNamed:@"PL_table_cell1"]];
//    [imgView1 setTag:999];
//    [cell.contentView addSubview:imgView1];
//    
//	//Initialize Label 1 with tag 1.
//	UILabel *lblTemp = [ViewConstants returnStyleB];
//    [lblTemp setFrame:lblFrame];
//    [lblTemp setTextColor:[UIColor customDarkGreyColor]];
//    [lblTemp setNumberOfLines:2];
//	lblTemp.tag = 1;
//	[cell.contentView addSubview:lblTemp];
//    
//    UIImageView *imgView = [[UIImageView alloc] initWithFrame:imgFrame];
//    [imgView setImage:[UIImage imageNamed:@"tick"]];
//    [imgView setHighlightedImage:[UIImage imageNamed:@"tick_on"]];
//    [imgView setTag:2];
//    [cell.contentView addSubview:imgView];
//    
//	return cell;
//}

#pragma mark TableView Delegate
-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath{
    [_selectedOverlays addObject:[_overlaysArr objectAtIndex:indexPath.row]];
}

-(void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath
{
    //cell.accessoryView=[]
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
