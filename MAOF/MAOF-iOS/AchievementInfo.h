
#import <Foundation/Foundation.h>


@interface AchievementInfo : NSObject {

    NSString*   sId;
    float       nProgress;
    int         bShowNotification;
    int         bDeferred;
}

@property (nonatomic, retain) NSString* sId;
@property (nonatomic, readwrite) float nProgress;
@property (nonatomic, readwrite) int bShowNotification;
@property (nonatomic, readwrite) int bDeferred;

@end
