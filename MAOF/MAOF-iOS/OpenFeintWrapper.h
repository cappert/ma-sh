
#import <Foundation/Foundation.h>


@interface OpenFeintWrapper : NSObject {


  //  BOOL initialized;
  //  NSMutableArray* achievements;

}

BOOL initialized;
NSMutableArray* achievements;

//+ (void)init;
+ (void) init:(NSString*)sProductKey andSecret:(NSString*)sSecret andName:(NSString*)sName;
+ (void)shutdown;

+ (void)showDashBoard;
+ (void)showDashBoardWithLeaderBoard:(NSString*)sId;

//UnlockAchievement sId, nProgress, bShowNotification, bDeferred
+ (void)unlockAchievement:(NSString*)sId andProgress:(float)nProgress andShowNotification:(int)bShowNotification andDeferred:(int)bDeferred;
+ (void)flushUnlockedAchievements;
//+ (void)unlockAchievement:(NSString*)id;
//+ (void)unlockAchievement:(int)id;
+ (void)submitHighscore:(int)score andId:(NSString*) sId;

+ (void)sendSocialNotification: (NSString*)sText andMessage:(NSString*)sMessage andImageName:(NSString*)sImageName;


@end
