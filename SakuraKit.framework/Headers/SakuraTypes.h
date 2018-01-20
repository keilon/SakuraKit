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

/*!
 * 会话类型枚举
 *
 */
typedef enum {
    SI_SESSION_CHAT = 0,
    SI_SESSION_GROUP = 1,
    SI_SESSION_SYSTEM = 2
} SISessionType;

/*!
 * 消息类型枚举
 *
 */
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

/*!
 * 消息内容（抽象类）
 *
 * 消息实体中的消息内容body
 *
 */
@interface SIMessageBody : NSObject

///JSON反序列化
+ (instancetype _Nullable)bodyWithJson:(NSString * _Nullable)data
                              withType:(SIMessageType) type;

///JSON序列化
- (NSString *_Nullable)toJson;

@end

/*!
 * 文本消息
 *
 * 文本消息的body
 *
 */
@interface SITextBody : SIMessageBody

@property(nonatomic, copy) NSString * _Nullable content;

@end

/*!
 * 图片消息
 *
 * 图片消息的body
 *
 */
@interface SIImageBody : SIMessageBody

@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
@property(nonatomic, readwrite, copy) NSString * _Nullable thumbMediaId;
@property(nonatomic, readwrite, copy) NSString * _Nullable title;
@property(nonatomic, readwrite) int64_t size;
@property(nonatomic, readwrite) int32_t height;
@property(nonatomic, readwrite) int32_t width;
@property(nonatomic, readwrite, copy) NSString * _Nullable type;

@end

/*!
 * 语音消息
 *
 * 语音消息的body
 *
 */
@interface SIVoiceBody : SIMessageBody

@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
@property(nonatomic, readwrite) int32_t duration;
@property(nonatomic, readwrite) int64_t size;
@property(nonatomic, readwrite, copy) NSString * _Nullable type;

@end

/*!
 * 视频消息
 *
 * 视频消息的body
 *
 */
@interface SIVideoBody : SIMessageBody

@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
@property(nonatomic, readwrite, copy) NSString * _Nullable thumbMediaId;
@property(nonatomic, readwrite, copy) NSString * _Nullable title;
@property(nonatomic, readwrite) int32_t duration;
@property(nonatomic, readwrite) int64_t size;
@property(nonatomic, readwrite, copy) NSString * _Nullable type;

@end

/*!
 * 短视频消息
 *
 * 短视频消息的body
 *
 */
@interface SIShortvideoBody : SIMessageBody

@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
@property(nonatomic, readwrite, copy) NSString * _Nullable thumbMediaId;
@property(nonatomic, readwrite) int32_t duration;
@property(nonatomic, readwrite) int64_t size;

@end

/*!
 * 图文消息
 *
 * 图文消息的body
 *
 */
@interface SINewsBody : SIMessageBody

@property(nonatomic, readwrite, copy ) NSString * _Nullable title;
@property(nonatomic, readwrite, copy ) NSString * _Nullable desc;
@property(nonatomic, readwrite, copy ) NSString * _Nullable linkurl;
@property(nonatomic, readwrite, copy ) NSString * _Nullable picurl;

@end

/*!
 * 文件消息
 *
 * 文件消息的body
 *
 */
@interface SIFileBody : SIMessageBody

@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
@property(nonatomic, readwrite, copy) NSString * _Nullable title;
@property(nonatomic, readwrite) int64_t size;
@property(nonatomic, readwrite, copy) NSString * _Nullable type;

@end

/*!
 * 自定义消息
 *
 * 自定义消息的body
 *
 */
@interface SICustomBody : SIMessageBody

@property(nonatomic, readwrite, copy) NSString * _Nullable type;
@property(nonatomic, readwrite, copy) NSString * _Nullable body;

@end

/*!
 * 系统消息
 *
 * 系统消息的body
 *
 */
@interface SISystemBody : SIMessageBody

@property(nonatomic, readwrite, copy) NSString * _Nullable content;

@end

/*!
 * 消息
 *
 * 表示一条消息实体
 */
@interface SIMessage : NSObject

///会话Id
@property(nonatomic, strong) NSString * _Nullable sessionId;
///会话类型
@property(nonatomic) SISessionType sessionType;
///会话的主要目标，即消息的发送目标
@property(nonatomic, strong) NSString * _Nullable sessionMain;
///消息的发送方
@property(nonatomic, strong) NSString * _Nullable senderId;
///消息id
@property(nonatomic, strong) NSString * _Nullable messageId;
///消息类型
@property(nonatomic) SIMessageType messageType;
///消息详情对象
@property(nonatomic, strong) SIMessageBody * _Nullable messageBody;
///消息的时间戳
@property(nonatomic) double messageTS;

@end

/*!
 * 会话
 *
 * 表示一个会话实体
 */
@interface SISession : NSObject

///由SIMessage构建SISession
+ (instancetype _Nullable)initWithSIMessage:(SIMessage * _Nullable)msg;

///会话Id
@property(nonatomic, strong) NSString * _Nullable sessionId;
///会话类型
@property(nonatomic) SISessionType sessionType;
///会话的主要目标，即消息的发送目标，可以用来标识会话的名称和头像
@property(nonatomic, strong) NSString * _Nullable sessionMain;
///最新一条消息的发送方
@property(nonatomic, strong) NSString * _Nullable lastSenderId;
///最新一条消息的Id
@property(nonatomic, strong) NSString * _Nullable lastMessageId;
///最新一条消息的类型
@property(nonatomic) SIMessageType lastMessageType;
///最新一条消息详情对象
@property(nonatomic, strong) SIMessageBody * _Nullable lastMessageBody;
///最新一条消息的时间戳
@property(nonatomic) double lastMessageTS;
///未读消息计数
@property(nonatomic) unsigned int unreadCount;

@end

#endif /* SakuraTypes_h */
