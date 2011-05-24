//
//  OpenFeintWrapper.m
//  Copyright 2011 Modern Alchemists. All rights reserved.
//

#import "OpenFeintWrapper.h"
#import "OpenFeint/OpenFeint.h"
//#import "OpenFeint/OFAchievementService.h" //TODO: still needed?
#import "OpenFeint/OFAchievement.h"
#import "OpenFeint/OFHighScoreService.h"
#import "OpenFeint/OFDelegate.h"
#import "OpenFeint/OpenFeint+Dashboard.h"
//#import "OFSocialNotificationService.h"
#import "OpenFeint/OFSocialNotificationApi.h"
#import "AchievementInfo.h"

@implementation OpenFeintWrapper

+ (void) initialize {
//  if ([self class] == [MyParentClass class]) {
    // Once-only initializion
  //}
  // Initialization for this class and any subclasses

	achievements = [[NSMutableArray alloc] init];
    initialized = FALSE;
}

-(void) dealloc {
	[super dealloc];
	[achievements removeAllObjects];
	[achievements release];

}


+ (void)showDashBoard
{
	if(!initialized)
	{
		[self init];
	}
	
	//NSLog(@"dashboard");
	[OpenFeint launchDashboard];
	//[OFHighScoreService ]
	//[OpenFeint launchDashboardWithHighscorePage:@"464104"];
}

+ (void)showDashBoardWithLeaderBoard:(NSString*)sId
{
	if(!initialized)
	{
		[self init];
	}
	
	[OpenFeint launchDashboardWithHighscorePage:sId];
}


+ (void) init:(NSString*)sProductKey andSecret:(NSString*)sSecret andName:(NSString*)sName
{
	NSDictionary* settings = [NSDictionary dictionaryWithObjectsAndKeys:   
							  [NSNumber numberWithInt:UIInterfaceOrientationPortrait], OpenFeintSettingDashboardOrientation,
							  @"ShortName", OpenFeintSettingShortDisplayName, 
							  [NSNumber numberWithBool:NO], OpenFeintSettingEnablePushNotifications, 
							 // [NSNumber numberWithBool:NO], OpenFeintSettingDisableChat,
							  nil
							  ];
	
	[OpenFeint initializeWithProductKey:sProductKey 
							  andSecret:sSecret 
						 andDisplayName:sName 
							andSettings:settings
						   andDelegates:nil];
	
	initialized = YES;
}

+ (void)shutdown
{
    [OpenFeint shutdown];
}


+ (void)unlockAchievement:(NSString*)sId andProgress:(float)nProgress andShowNotification:(int)bShowNotification andDeferred:(int)bDeferred
{
    //Check if deferred unlocking:
    if( bDeferred == 1 )
    {
        NSLog(@"Defered Achievement");

        //Check for double strings:
        int n = [achievements count];
        for(int i=0; i < n; ++i) 
        {
            AchievementInfo *af = (AchievementInfo*) [achievements objectAtIndex:i];

            if([sId isEqualToString:af.sId]){
                NSLog(@"Achievement already added - returning now.");
                return;
            }
        }

        AchievementInfo *af = [[AchievementInfo alloc] init]; 
        
        af.sId = sId;
        af.nProgress = nProgress;
        af.bShowNotification = bShowNotification;
        af.bDeferred = bDeferred;
        
        [achievements addObject:af];

        NSLog(@"Array count: %i", [achievements count]);
    }
    
    //If not, unlock achievement: 
    else
    {
        if( bShowNotification == 1 )
        {
            NSLog(@"Immediate Achievement with Social");            
            [[OFAchievement achievement: sId] updateProgressionComplete: nProgress andShowNotification: YES];
        }
        else
        {
            NSLog(@"Immediate Achievement with no Social");
            [[OFAchievement achievement: sId] updateProgressionComplete: nProgress andShowNotification: NO];
        }
    }
}

+ (void)flushUnlockedAchievements
{

    int n = [achievements count];
	for(int i=0; i < n; ++i) 
	{
        AchievementInfo *af = (AchievementInfo*) [achievements objectAtIndex:i];
		[self unlockAchievement:af.sId
                    andProgress:af.nProgress
          andShowNotification:af.bShowNotification
                    andDeferred:0];
        NSLog(@"Flushing achievement id:%@",af.sId);
    }

    //Release Achievements:
    for(int i=0; i < n; ++i) 
	{
        AchievementInfo *af = (AchievementInfo*) [achievements objectAtIndex:i];

        [af release];
	}
	
	[achievements removeAllObjects];
}

+ (void)submitHighscore:(int)score andId:(NSString*) sId
{
	if(!initialized)
	{
		[self init];
	}
	

	[OFHighScoreService setHighScore:score 
					  forLeaderboard:sId 
						   onSuccess:OFDelegate()
						   onFailure:OFDelegate()];

	/*if(score > 400)
	{
		NSString *msg;

		NSString* myNewString = [[NSNumber numberWithInt:score] stringValue];


		msg = [[NSString alloc] init];

		msg = [msg stringByAppendingString:@"scored "];
		msg = [msg stringByAppendingString:myNewString];
		msg = [msg stringByAppendingString:@" points playing AaargPimples!"];

		[OFSocialNotificationApi sendWithText:msg imageNamed:nil];
	}
*/

}

+ (void)sendSocialNotification: (NSString*)sText andMessage:(NSString*)sMessage andImageName:(NSString*)sImageName
{
   //+ (void)sendWithPrepopulatedText:(NSString*)text originalMessage:(NSString*)message imageNamed(NSString*)imageName 
    [OFSocialNotificationApi sendWithPrepopulatedText:sText originalMessage:sMessage imageNamed:sImageName];
}


@end
