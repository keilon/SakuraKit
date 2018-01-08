//
//  SakuraTypes.h
//  SakuraKit
//
//  Created by keilon on 2018/1/3.
//  Copyright © 2018年 keilon. All rights reserved.
//

#ifndef SakuraTypes_h
#define SakuraTypes_h

#import <Foundation/Foundation.h>

// 会话类型
typedef enum {
    SI_SESSION_CHAT = 0,
    SI_SESSION_GROUP = 1,
    SI_SESSION_SYSTEM = 2
} SISessionType;

// 消息类型
typedef enum {
    SI_MESSAGE_TEXT = 1,
    SI_MESSAGE_IMAGE = 2,
    SI_MESSAGE_VOICE = 3,
    SI_MESSAGE_VIDEO = 4,
    SI_MESSAGE_SHORTVIDEO = 5,
    SI_MESSAGE_NEWS = 6,
    SI_MESSAGE_FILE_T = 7,
    SI_MESSAGE_CUSTOM = 8,
    SI_MESSAGE_SYSTEM_T = 9
} SIMessageType;

typedef NSString            SITextMessage;
typedef NSMutableDictionary SIImageMessage;
typedef NSMutableDictionary SIVoiceMessage;
typedef NSMutableDictionary SIVideoMessage;
typedef NSMutableDictionary SIShortvideoMessage;
typedef NSMutableDictionary SINewsMessage;
typedef NSMutableDictionary SIFileMessage;
typedef NSMutableDictionary SICustomMessage;
typedef NSString            SISystemMessage;

/*!
 * 消息
 *
 * 表示一条消息实体
 */
@interface SIMessage : NSObject

///会话Id
@property(nonatomic, strong) NSString *sessionId;
///会话类型
@property(nonatomic) SISessionType sessionType;
///会话的主要目标，即消息的发送目标
@property(nonatomic, strong) NSString *sessionMain;
///消息的发送方
@property(nonatomic, strong) NSString *senderId;
///消息id
@property(nonatomic, strong) NSString *messageId;
///消息类型
@property(nonatomic) SIMessageType messageType;
///消息详情对象
@property(nonatomic, copy) NSObject *messageBodyPtr;
///消息的时间戳
@property(nonatomic) double messageTS;

@end

/*!
 * 会话
 *
 * 表示一个会话实体
 */
@interface SISession : NSObject

///会话Id
@property(nonatomic, strong) NSString *sessionId;
///会话类型
@property(nonatomic) SISessionType sessionType;
///会话的主要目标，即消息的发送目标，可以用来标识会话的名称和头像
@property(nonatomic, strong) NSString *sessionMain;
///最新一条消息的发送方
@property(nonatomic, strong) NSString *lastSenderId;
///最新一条消息的Id
@property(nonatomic, strong) NSString *lastMessageId;
///最新一条消息的类型
@property(nonatomic) SIMessageType lastMessageType;
///最新一条消息详情对象
@property(nonatomic, copy) NSObject *lastMessagePtr;
///最新一条消息的时间戳
@property(nonatomic) double lastMessageTS;
///未读消息计数
@property(nonatomic) unsigned int unreadCount;

@end

#endif /* SakuraTypes_h */
