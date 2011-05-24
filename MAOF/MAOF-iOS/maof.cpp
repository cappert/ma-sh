/*
 *  maof.cpp
 *  Modern Alchemists Open Feint
 *
 *  Created by Zog.
 *  Copyright 2011 Modern Alchemists. All rights reserved.
 *
 */


#include "maof.h"
#include "maoflib.h"
//#include "OpenFeintWrapper.h"
#include "S3DXAIVariable.h"
#include "S3DClient_Wrapper.h"


void onFlushUnlockedAchievements(unsigned char argumentCount, const void *arguments, void *userData )
{
    openfeint_flushUnlockedAchievements();
}

void onInitMAOF(unsigned char argumentCount, const void *arguments, void *userData )
{
    if ( arguments && ( argumentCount == 4 ) )
    {
        const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
		
        if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString
			&& variables[1].GetType ( ) == S3DX::AIVariable::eTypeString 
			&& variables[2].GetType ( ) == S3DX::AIVariable::eTypeString 
            && variables[3].GetType ( ) == S3DX::AIVariable::eTypeString )
        {
			openfeint_init( variables[0].GetStringValue(), variables[1].GetStringValue(), variables[2].GetStringValue(), variables[3].GetStringValue() );
        }
    }
}

void onLaunchDashboard(unsigned char argumentCount, const void *arguments, void *userData)
{
    openfeint_showDashBoard();
}

void onLaunchDashboardWithHighscorePage(unsigned char argumentCount, const void *arguments, void *userData)
{
    if ( arguments && ( argumentCount == 1 ) )
    {
        const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
		
        if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString )
        {
			openfeint_launchDashboardWithHighscorePage( variables[0].GetStringValue() );
        }
    }
}

void onSendSocialNotification(unsigned char argumentCount, const void *arguments, void *userData)
{
    if ( arguments && ( argumentCount == 3 ) )
    {
        const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
		
        if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString 
			&& variables[1].GetType ( ) == S3DX::AIVariable::eTypeString 
			&& variables[2].GetType ( ) == S3DX::AIVariable::eTypeString )
        {
			openfeint_sendSocialNotification( variables[0].GetStringValue(), variables[1].GetStringValue(), variables[2].GetStringValue() );
        }
    }
}

void onShutdownMAOF(unsigned char argumentCount, const void *arguments, void *userData)
{
    openfeint_shutdown();
}

void onSubmitHighscore(unsigned char argumentCount, const void *arguments, void *userData)
{
    if ( arguments && ( argumentCount == 2 ) )
    {
        const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
		
        if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeNumber 
			&& variables[1].GetType ( ) == S3DX::AIVariable::eTypeString  )
        {
			openfeint_submitHighscore( variables[0].GetNumberValue(), variables[1].GetStringValue() );
        }
    }
}

void onUnlockAchievement(unsigned char argumentCount, const void *arguments, void *userData)
{
    if ( arguments && ( argumentCount == 4 ) )
    {
        const S3DX::AIVariable *variables = (const S3DX::AIVariable *)arguments ;
		
        if ( variables[0].GetType ( ) == S3DX::AIVariable::eTypeString
			&& variables[1].GetType ( ) == S3DX::AIVariable::eTypeNumber
			&& variables[2].GetType ( ) == S3DX::AIVariable::eTypeBoolean 
			&& variables[3].GetType ( ) == S3DX::AIVariable::eTypeBoolean )
        {
			openfeint_unlockAchievement( variables[0].GetStringValue(), variables[1].GetNumberValue(), variables[2].GetBooleanValue(), variables[3].GetBooleanValue() );
        }
    }
}

void maof_registerCallbacks()
{
	ObjectiveC_LogMessage("MAOF REGISTER CALLBACKS");
	S3DClient_InstallCurrentUserEventHook("MAOF", "onFlushUnlockedAchievements",		onFlushUnlockedAchievements,		NULL);
	S3DClient_InstallCurrentUserEventHook("MAOF", "onInitMAOF",							onInitMAOF,							NULL);
	S3DClient_InstallCurrentUserEventHook("MAOF", "onLaunchDashboard",					onLaunchDashboard,					NULL);
	
	S3DClient_InstallCurrentUserEventHook("MAOF", "onLaunchDashboardWithHighscorePage",	onLaunchDashboardWithHighscorePage,	NULL);
	S3DClient_InstallCurrentUserEventHook("MAOF", "onSendSocialNotification",			onSendSocialNotification,			NULL);
	S3DClient_InstallCurrentUserEventHook("MAOF", "onShutdownMAOF",						onShutdownMAOF,						NULL);
	S3DClient_InstallCurrentUserEventHook("MAOF", "onSubmitHighscore",					onSubmitHighscore,					NULL);
	S3DClient_InstallCurrentUserEventHook("MAOF", "onUnlockAchievement",				onUnlockAchievement,				NULL);
}
