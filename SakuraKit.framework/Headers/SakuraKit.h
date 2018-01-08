//
//  SakuraKit.h
//  SakuraKit
//
//  Created by keilon on 2017/12/20.
//  Copyright © 2017年 keilon. All rights reserved.
//

#ifdef __OBJC__
#import <Foundation/Foundation.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

//! Project version number for SakuraKit.
FOUNDATION_EXPORT double SakuraKitVersionNumber;

//! Project version string for SakuraKit.
FOUNDATION_EXPORT const unsigned char SakuraKitVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <SakuraKit/PublicHeader.h>
#import "SakuraTypes.h"
#import "SakuraMessage.h"
#import "SakuraDelegate.h"
