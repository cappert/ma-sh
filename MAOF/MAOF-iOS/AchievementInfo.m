

#import "AchievementInfo.h"


@implementation AchievementInfo

@synthesize sId;
@synthesize nProgress;
@synthesize bShowNotification;
@synthesize bDeferred;


-(void) dealloc {
    NSLog(@"Destroying AchievementInfo");
    
	[super dealloc];
    
    [self.sId release];
}

@end
