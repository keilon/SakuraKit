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
 * 强制下线原因枚举
 *
 */
typedef enum {
    SI_KICKOFF_UNKNOWN = 0, //未知原因
    SI_KICKOFF_LOCKED = 1,  //账号被管理员锁定
    SI_KICKOFF_REMOTE = 2,  //其他同类设备登陆
    SI_KICKOFF_USER = 3     //用户自己发起（如，在手机端关闭web端）
} SIKickOffType;

/*!
 * 会话类型枚举
 *
 */
typedef enum {
    SI_SESSION_CHAT = 0,
    SI_SESSION_GROUP = 1,
    SI_SESSION_SYSTEM = 2,
} SISessionType;

/*!
 * 会话状态枚举
 *
 */
typedef enum {
    SI_SESSION_STATE_ACTIVE = 1,     //用户激活会话（一般是用户主动打开一个会话时发起，目前只会通知用户其他设备，不会通知会话目标）
    SI_SESSION_STATE_COMPOSING = 2,  //用户编辑中  （用户在会话中编辑一条待发送的消息）
    SI_SESSION_STATE_INACTIVE  = 3,  //用户暂离会话（一般是用户主动关闭一个会话时发起，目前只会通知用户其他设备，不会通知会话目标）
} SISessionState;

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
    SI_MESSAGE_FILE = 7,
    SI_MESSAGE_CUSTOM = 8,
    SI_MESSAGE_SYSTEM = 9,
    SI_MESSAGE_RECALL = 10,
    SI_MESSAGE_REMIND = 11,
} SIMessageType;


/*!
 * 消息接受状态
 *
 * TODO 已送达和已接收暂未实现
 */
typedef int32_t SIMessageRecvState;

/// (0x01) 已送达（消息已经送达至接收方）
extern const SIMessageRecvState SI_MESSAGE_RECV_DELIVERED;
/// (0x02) 已读
extern const SIMessageRecvState SI_MESSAGE_RECV_DISPLAYED;
/// (0x04) 已接收（消息已经被服务端接收）
extern const SIMessageRecvState SI_MESSAGE_RECV_ACCEPTED;


/*!
 * 消息的状态类型
 *
 * 此处定义了可能用到的消息状态，客户端可以根据需求定义更多状态，取值从100以后开始
 *
 * TODO SDK 中追加消息状态维护
 *
 */
typedef ushort SIMessageStatus;

/// (1)  上传中，对于语音，图片等
extern const SIMessageStatus SI_MESSAGE_STATUS_UPLOADING;
/// (2)  发送中
extern const SIMessageStatus SI_MESSAGE_STATUS_SENDING;
/// (3)  发送成功
extern const SIMessageStatus SI_MESSAGE_STATUS_SENT;
/// (4)  发送失败
extern const SIMessageStatus SI_MESSAGE_STATUS_FAILED;
/// (5)  由于网络问题没有发送出去,需要再次尝试
extern const SIMessageStatus SI_MESSAGE_STATUS_NEEDREPEAT;
/// (6)  创建中,草稿
extern const SIMessageStatus SI_MESSAGE_STATUS_CREATING;
/// (7)  已送达
extern const SIMessageStatus SI_MESSAGE_STATUS_ARRIVED;
/// (8)  上传失败，对于语音，图片等
extern const SIMessageStatus SI_MESSAGE_STATUS_UPLOADFAILED;
/// (10) 未读
extern const SIMessageStatus SI_MESSAGE_STATUS_UNREAD;
/// (11) 已读
extern const SIMessageStatus SI_MESSAGE_STATUS_READ;
/// (0)  不存在此消息
extern const SIMessageStatus SI_MESSAGE_STATUS_UNKNOW;


/*!
 * 消息内容（抽象类）
 *
 * 消息实体中的消息内容body
 *
 */
@interface SIMessageBody : NSObject

///消息扩展字段
@property(nonatomic, copy) NSString * _Nullable extra;

///JSON 反序列化
+ (instancetype _Nullable)bodyWithJson:(NSString * _Nullable)data
                              withType:(SIMessageType) type;

///JSON 序列化
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
//第一帧图片的高度
@property(nonatomic, readwrite) int32_t height;
//第一帧图片的宽度
@property(nonatomic, readwrite) int32_t width;

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
//视频类型,目前没用,默认mp4格式
@property(nonatomic, readwrite, copy) NSString * _Nullable type;
///图片的长度
@property(nonatomic, readwrite) int32_t height;
///图片的宽度
@property(nonatomic, readwrite) int32_t width;

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
///自定义消息远程推送时显示的内容
@property(nonatomic, readwrite, copy) NSString * _Nullable pushContent;


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
 * 撤回消息
 *
 * 撤回消息的body
 *
 */
@interface SIRecallBody : SIMessageBody

///撤回消息的ID
@property(nonatomic, readwrite, copy) NSString * _Nullable messageId;

@end


/*!
 * 群@消息
 *
 * 群@消息的body
 *
 */
@interface SIRemindBody : SIMessageBody

///被@用户的identify组成的数组.[identify,identify,...] 或者 @所有人时传入群的id [groupId]
@property(nonatomic, readwrite, copy) NSArray * _Nullable identifies;
///内容
@property(nonatomic, readwrite, copy) NSString * _Nullable content;

@end


/*!
 * 接受状态事件（回执事件）
 */
@interface SIMessageRecvEvent : NSObject

///目标消息所属会话Id
@property (nonatomic, strong) NSString * _Nullable sessionId;
///目标消息所属会话类型
@property (nonatomic) SISessionType sessionType;
///事件发送方，接收时用来标识发送方，发送时 sdk 会取用户的 identify 赋值
@property(nonatomic, strong) NSString * _Nullable senderId;
///事件接收方，发送时必须指定，一般为目标消息的发送方
@property(nonatomic, strong) NSString * _Nullable receiverId;
///接受状态
@property (nonatomic) SIMessageRecvState recvState;
///目标消息id
@property (nonatomic, strong) NSString * _Nullable targetMessageId;
///事件的 domain，用来标识消息来源appId
@property(nonatomic, strong) NSString * _Nullable domain;

@end


/*!
 * 会话状态事件
 */
@interface SISessionStateEvent : NSObject

///会话Id
@property (nonatomic, strong) NSString * _Nullable sessionId;
///会话类型
@property (nonatomic) SISessionType sessionType;
///会话的主要目标，即消息的发送目标，发送时必须指定
@property(nonatomic, strong) NSString * _Nullable sessionMain;
///事件发送方，接收时用来标识发送方identify，发送时 sdk 会取用户的 identify 赋值
@property(nonatomic, strong) NSString * _Nullable senderId;
///会话状态
@property (nonatomic) SISessionState state;
///事件扩展字段
@property (nonatomic, strong) NSString * _Nullable extra;
///事件的 domain，接收时用来标识消息来源appId，发送时不需要赋值
@property(nonatomic, strong) NSString * _Nullable domain;

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
///会话的主要目标，即消息的发送目标，发送时必须指定
@property(nonatomic, strong) NSString * _Nullable sessionMain;
///会话的名称标签，单聊时为聊天对象名称，群聊时为群组名称，系统会话时为会话标题
@property(nonatomic, strong) NSString * _Nullable sessionLabel;
///会话的类别，仅在系统会话中有效，标识系统会话的具体分类（如公众号，订阅号等）, 由应用方定义(SDK 透传)
@property(nonatomic, strong) NSString * _Nullable sessionCategory;
///消息发送方，接收时用来标识消息发送方identify，发送时 sdk 会取用户的 identify 赋值
@property(nonatomic, strong) NSString * _Nullable senderId;
///消息发送方标签，接收时用来标识消息发送方label，发送时 sdk 会取用户的 label 赋值
@property(nonatomic, strong) NSString * _Nullable senderLabel;
///消息id，应用层指定时推荐使用 `[[NSUUID UUID] UUIDString]` 生成，应用层不指定时 SDK 会自己生成
@property(nonatomic, strong) NSString * _Nullable messageId;
///消息类型
@property(nonatomic) SIMessageType messageType;
///消息来源类型，仅在系统会话中有效，标识消息来源是系统通知类还是客服类，发送时不需要赋值
@property(nonatomic, strong) NSString * _Nullable messageSourceType;
///消息详情对象
@property(nonatomic, strong) SIMessageBody * _Nullable messageBody;
///消息的时间戳，发送时不需要赋值
@property(nonatomic) double messageTS;
///消息的 domain，接收时用来标识消息来源appId，发送时不需要赋值
@property(nonatomic, strong) NSString * _Nullable domain;
///消息的状态
@property(nonatomic) SIMessageStatus messageStatus;
///需要的回执事件(目前仅支持已读事件)，默认为0(即不要求回执)，参考 SIMessageRecvState 定义，多个事件可合并传递
/// 如：2 已读报告，3 送达报告+已读报告，7 接受报告+送达报告+已读报告
@property(nonatomic, assign) int32_t requestEvent;

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
///会话的名称标签，单聊时为聊天对象名称，群聊时为群组名称，系统会话时为会话标题
@property(nonatomic, strong) NSString * _Nullable sessionLabel;
///会话的类别，仅在系统会话中有效，标识系统会话的具体分类（如公众号，订阅号等）, 由应用方定义(SDK 透传)
@property(nonatomic, strong) NSString * _Nullable sessionCategory;
///最新一条消息的发送方
@property(nonatomic, strong) NSString * _Nullable lastSenderId;
///最新一条消息的发送方标签
@property(nonatomic, strong) NSString * _Nullable lastSenderLabel;
///最新一条消息的Id
@property(nonatomic, strong) NSString * _Nullable lastMessageId;
///最新一条消息的类型
@property(nonatomic) SIMessageType lastMessageType;
///最新一条消息的来源类型，仅在系统会话中有效，标识消息来源是系统通知类还是客服类
@property(nonatomic, strong) NSString * _Nullable lastMessageSourceType;
///最新一条消息详情对象
@property(nonatomic, strong) SIMessageBody * _Nullable lastMessageBody;
///最新一条消息的时间戳
@property(nonatomic) double lastMessageTS;
///未读消息计数，目前 SDK 暂未记录，由应用层进行统计
@property(nonatomic) unsigned int unreadCount;


@end

#endif /* SakuraTypes_h */
