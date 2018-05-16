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
 * 连接状态枚举
 *
 */
typedef enum {
    SI_CONN_DISCONNECT = 0,
    SI_CONN_CONNECTING = 1,
    SI_CONN_CONNECTED = 2
} SIConnStatus;

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

///消息扩展字段
@property(nonatomic, copy) NSString * _Nullable extra;

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

///图片的素材id，使用 SDK 的上传图片接口上传成功后会返回，若应用方自己保存源文件可自行管理（SDK 透传）
@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
///图片缩略图的素材id，使用 SDK 的上传图片接口上传成功后会返回，若应用方自己保存源文件可自行管理（SDK 透传）
@property(nonatomic, readwrite, copy) NSString * _Nullable thumbMediaId;
///图片的标题
@property(nonatomic, readwrite, copy) NSString * _Nullable title;
///图片文件的大小
@property(nonatomic, readwrite) int64_t size;
///图片的长度
@property(nonatomic, readwrite) int32_t height;
///图片的宽度
@property(nonatomic, readwrite) int32_t width;
///图片文件的格式（扩展名），SDK 上传图片接口统一使用 jpg
@property(nonatomic, readwrite, copy) NSString * _Nullable type;

@end

/*!
 * 语音消息
 *
 * 语音消息的body
 *
 */
@interface SIVoiceBody : SIMessageBody

///语音的素材id，使用 SDK 的上传音频接口上传成功后会返回，若应用方自己保存源文件可自行管理（SDK 透传）
@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
///语音的播放时长
@property(nonatomic, readwrite) int32_t duration;
///语音文件的大小
@property(nonatomic, readwrite) int64_t size;
///语音文件的格式（扩展名），SDK 上传音频接口暂时只支持amr
@property(nonatomic, readwrite, copy) NSString * _Nullable type;

@end

/*!
 * 视频消息
 *
 * 视频消息的body
 *
 */
@interface SIVideoBody : SIMessageBody

///视频的素材id，使用 SDK 的上传文件接口上传成功后会返回，若应用方自己保存源文件可自行管理（SDK 透传）
@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
///视频封面图片素材id，使用 SDK 的上传图片接口上传成功后会返回，若应用方自己保存源文件可自行管理（SDK 透传）
@property(nonatomic, readwrite, copy) NSString * _Nullable thumbMediaId;
///视频的标题
@property(nonatomic, readwrite, copy) NSString * _Nullable title;
///视频的播放时长
@property(nonatomic, readwrite) int32_t duration;
///视频文件的大小
@property(nonatomic, readwrite) int64_t size;
///视频文件的格式（扩展名）
@property(nonatomic, readwrite, copy) NSString * _Nullable type;

@end

/*!
 * 短视频消息
 *
 * 短视频消息的body
 *
 */
@interface SIShortvideoBody : SIMessageBody

///短视频的素材id，使用 SDK 的上传文件接口上传成功后会返回，若应用方自己保存源文件可自行管理（SDK 透传）
@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
///短视频封面图片素材id，使用 SDK 的上传图片接口上传成功后会返回，若应用方自己保存源文件可自行管理（SDK 透传）
@property(nonatomic, readwrite, copy) NSString * _Nullable thumbMediaId;
///短视频的播放时长
@property(nonatomic, readwrite) int32_t duration;
///短视频文件的大小
@property(nonatomic, readwrite) int64_t size;

@end

/*!
 * 图文消息
 *
 * 图文消息的body
 *
 */
@interface SINewsBody : SIMessageBody

///图文消息的标题
@property(nonatomic, readwrite, copy ) NSString * _Nullable title;
///图文消息的详情
@property(nonatomic, readwrite, copy ) NSString * _Nullable desc;
///图文消息跳转的url
@property(nonatomic, readwrite, copy ) NSString * _Nullable linkurl;
///图文消息封面图片的url
@property(nonatomic, readwrite, copy ) NSString * _Nullable picurl;

@end

/*!
 * 文件消息
 *
 * 文件消息的body
 *
 */
@interface SIFileBody : SIMessageBody

///文件的素材id，使用 SDK 的上传文件接口上传成功后会返回，若应用方自己保存源文件可自行管理（SDK 透传）
@property(nonatomic, readwrite, copy) NSString * _Nullable mediaId;
///文件的标题
@property(nonatomic, readwrite, copy) NSString * _Nullable title;
///文件的大小
@property(nonatomic, readwrite) int64_t size;
///文件的格式（扩展名）
@property(nonatomic, readwrite, copy) NSString * _Nullable type;

@end

/*!
 * 自定义消息
 *
 * 自定义消息的body
 *
 */
@interface SICustomBody : SIMessageBody

///自定义消息的类型，SDK 透传给应用层
@property(nonatomic, readwrite, copy) NSString * _Nullable type;
///自定义消息的消息体，SDK 透传给应用层
@property(nonatomic, readwrite, copy) NSString * _Nullable body;

@end

/*!
 * 系统消息
 *
 * 系统消息的body
 *
 */
@interface SISystemBody : SIMessageBody

///系统消息的内容
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
///会话的名称标签，单聊时为聊天对象名称，群聊时为群组名称
@property(nonatomic, strong) NSString * _Nullable sessionLabel;
///消息发送方
@property(nonatomic, strong) NSString * _Nullable senderId;
///消息发送方标签
@property(nonatomic, strong) NSString * _Nullable senderLabel;
///消息id，应用层指定时推荐使用 `[[NSUUID UUID] UUIDString]` 生成，应用层不指定时 SDK 会自己生成
@property(nonatomic, strong) NSString * _Nullable messageId;
///消息类型
@property(nonatomic) SIMessageType messageType;
///消息详情对象
@property(nonatomic, strong) SIMessageBody * _Nullable messageBody;
///消息的时间戳，发送时不需要赋值
@property(nonatomic) double messageTS;
///消息的来源，接收时用来标识消息来源，发送时不需要赋值
@property(nonatomic, strong) NSString * _Nullable domain;


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
///会话的主要目标，即消息的发送目标
@property(nonatomic, strong) NSString * _Nullable sessionMain;
///会话的名称标签，单聊时为聊天对象名称，群聊时为群组名称
@property(nonatomic, strong) NSString * _Nullable sessionLabel;
///最新一条消息的发送方
@property(nonatomic, strong) NSString * _Nullable lastSenderId;
///最新一条消息的发送方标签
@property(nonatomic, strong) NSString * _Nullable lastSenderLabel;
///最新一条消息的Id
@property(nonatomic, strong) NSString * _Nullable lastMessageId;
///最新一条消息的类型
@property(nonatomic) SIMessageType lastMessageType;
///最新一条消息详情对象
@property(nonatomic, strong) SIMessageBody * _Nullable lastMessageBody;
///最新一条消息的时间戳
@property(nonatomic) double lastMessageTS;
///未读消息计数，目前 SDK 暂未记录，由应用层进行统计
@property(nonatomic) unsigned int unreadCount;


@end

#endif /* SakuraTypes_h */
