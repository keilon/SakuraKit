//
//  SakuraDelegate.h
//  SakuraKit
//
//  Created by keilon on 2018/1/3.
//  Copyright © 2018年 keilon. All rights reserved.
//

#ifndef SakuraDelegate_h
#define SakuraDelegate_h

#import "SakuraTypes.h"

@protocol SakuraDelegate <NSObject>

@optional
- (void)onReceiveMessage:(SIMessage *)message;

@end

#endif /* SakuraDelegate_h */
