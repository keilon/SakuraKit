//
//  SakuraMessage.h
//  SakuraKit
//
//  Created by keilon on 2018/1/3.
//  Copyright © 2018年 keilon. All rights reserved.
//

#ifndef SakuraMessage_h
#define SakuraMessage_h

#import "SakuraTypes.h"
#import "SakuraDelegate.h"

@protocol SakuraDelegate;

@interface SakuraMessage : NSObject

@property(nullable, assign) id<SakuraDelegate> delegate;

+ (instancetype _Nonnull )sharedInstance;

+ (void)connectSakura:(NSString * _Nullable )identify
              token:(NSString * _Nullable )token
          msgServer:(NSDictionary * _Nullable )msgServer
         fileServer:(NSDictionary * _Nullable )fileServer;

+ (void)registerForRemoteNotification:(NSUInteger)types
                           categories:(NSSet *_Nullable)categories;

+ (void)registerDeviceToken:(NSData *_Nullable)deviceToken;

- (void)sendMessage:(SIMessage * _Nonnull)message;

@end

#endif /* SakuraMessage_h */

