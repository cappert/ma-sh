/*
 *  maslib.h
 *  Modern Alchemists Store Library
 *
 *  Created by Stein0r on 11/23/10.
 *  Copyright 2010 Modern Alchemists. All rights reserved.
 *
 */


#import "maoflib.h"
#import "OpenFeintWrapper.h"


void openfeint_init( const char *sProductKey, const char *sSecret, const char *sName, const char *sClientId)
{
	[OpenFeintWrapper init:[NSString stringWithUTF8String:sProductKey] 
		andSecret:[NSString stringWithUTF8String:sSecret]
		andName:[NSString stringWithUTF8String:sName]];
}

void openfeint_shutdown()
{
    [OpenFeintWrapper shutdown];
}

void openfeint_showDashBoard()
{
    [OpenFeintWrapper showDashBoard];
}

void openfeint_launchDashboardWithHighscorePage(const char *sId)
{
    [OpenFeintWrapper showDashBoardWithLeaderBoard:[NSString stringWithUTF8String:sId]];
}

void openfeint_submitHighscore(int nScore, const char *sId)
{
    [OpenFeintWrapper submitHighscore:nScore andId:[NSString stringWithUTF8String:sId]];
}

void openfeint_unlockAchievement( const char *sId, float nProgress, int bShowNotification, int bDeferred )
{
    [OpenFeintWrapper unlockAchievement:[NSString stringWithUTF8String:sId]
                            andProgress:nProgress 
                    andShowNotification:bShowNotification 
                            andDeferred:bDeferred];
    
}

void openfeint_flushUnlockedAchievements()
{
    [OpenFeintWrapper flushUnlockedAchievements];
}

void openfeint_sendSocialNotification( const char *sText, const char *sMessage, const char *sImageName )
{
    [OpenFeintWrapper sendSocialNotification:[NSString stringWithUTF8String:sText] 
                                  andMessage:[NSString stringWithUTF8String:sMessage] 
                                andImageName:[NSString stringWithUTF8String:sImageName]];
}
