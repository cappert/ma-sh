/*
 *  maslib.h
 *  Modern Alchemists Store Library
 *
 *  Created by Stein0r on 11/23/10.
 *  Copyright 2010 Modern Alchemists. All rights reserved.
 *
 */


#ifndef MAOFLIB_H
#define MAOFLIB_H

#ifdef __cplusplus
extern "C"
{
#endif

	void openfeint_init( const char *sProductKey, const char *sSecret, const char *sName, const char *sClientId);
    void openfeint_shutdown();
    
    void openfeint_showDashBoard();
    void openfeint_launchDashboardWithHighscorePage(const char *sId);
    
    void openfeint_submitHighscore(int nScore, const char *sId);
    
    void openfeint_unlockAchievement( const char *sId, float nProgress, int bShowNotification, int bDeferred ); 
    void openfeint_flushUnlockedAchievements();

    void openfeint_sendSocialNotification( const char *sText, const char *sMessage, const char *sImageName );
    
#ifdef __cplusplus
}
#endif
	
#endif