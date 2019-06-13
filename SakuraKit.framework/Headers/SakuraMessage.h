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
#import <UIKit/UIKit.h>

@protocol SakuraDelegate;

@interface SakuraMessage : NSObject

@property(nullable, assign) id<SakuraDelegate> delegate;

/*!
 * 获取SDK的实例
 *
 * @discussion SakuraMessage 采用单实例模式，只能通过此方法获取SDK的实例
 * 调用 class method 时，涉及的操作对象仍然是该实例
 *
 */
+ (instancetype _Nonnull )sharedInstance;

/*!
 * 初始化 Sakura 参数配置
 *
 * @param identify    用户在 Sakura 中的id
 * @param label       用户的名称标签
 * @param token       用户连接 Sakura 的凭证
 * @param appId       应用开发者向 sakura 注册的 appId
 * @param msgServer   Sakura message server 的地址
 *
 * @discussion 此方法必须被调用, 用来初始化相关配置
 * msgServer 为 `NSDictionary` 类型，由 Sakura 服务端返回的 msgServer 地址直接用于此处，不要做转换操作
 */
+ (void)configSakura:(NSString * _Nonnull)identify
               label:(NSString * _Nonnull)label
               token:(NSString * _Nonnull)token
               appId:(NSString * _Nonnull)appId
           msgServer:(NSDictionary * _Nonnull)msgServer;

/*!
 * 清除 Sakura 参数配置
 *
 * @discussion 清除 [configSakura] 中的各项设置
 * */
+ (void)clearConfigSakura;

/*!
 * 提供 Sakura 服务端地址配置
 *
 * @param apiBase    指定 sakura api 的 base uri 地址
 * @param fileBase   指定 sakura file 的 base uri 地址
 *
 * @discussion 默认为 sakura 生产环境
 * base uri 地址格式为 scheme://host[:port] 例如：
 *      https://tkim.top
 *      https://tkim.top:8443
 *      http://tkim.top
 *      http://tkim.top:8080
 */
+ (void)configServer:(NSString * _Nonnull)apiBase
            fileBase:(NSString * _Nonnull)fileBase;

/*!
 * 连接 Sakura 服务器
 *
 * @discussion 此方法需要在 [configSakura] 之后调用，用来创建连接
 *
 */
+ (void)connectSakura;

/*!
 * 断开当前连接
 *
 * @discussion 断开连接失败或者连接不存在时返回false
 *
 */
+ (BOOL)disconnectSakura;

/*!
 * 注册 DeviceToken
 *
 * @param deviceToken 从注册推送回调中拿到的 DeviceToken
 *
 * @discussion 相当于 [registerDeviceToken:xxx useSandbox:false]
 *
 */
+ (void)registerDeviceToken:(NSData *_Nullable)deviceToken;

/*!
 * 注册 DeviceToken
 *
 * @param deviceToken 从注册推送回调中拿到的 DeviceToken
 * @param useSandbox  是否使用沙箱环境
 *
 * @discussion 需要离线推送功能时，必须调用此方法
 * app 为开发版时，useSandbox 的值需要指定为 true
 *
 */
+ (void)registerDeviceToken:(NSData *_Nullable)deviceToken
                 useSandbox:(BOOL)useSandbox;

/*!
 * 设置角标(到服务器)
 *
 * @param value      角标的值
 *
 * @discussion 本接口不会改变应用本地的角标值.
 * 本地仍须调用 UIApplication:setApplicationIconBadgeNumber 函数来设置脚标.
 *
 */
+ (BOOL)setBadge:(NSInteger)value;

/*!
 * 重置角标(为0)
 *
 * @discussion 相当于 [setBadge:0] 的效果.
 *
 */
+ (void)resetBadge;

/*!
 * 是否打印日志
 * @param logFlag    是否开启的标志
 *
 * @discussion 默认不开启
 *
 */
+ (void)setEnableLog:(BOOL)logFlag;

/*!
 * 获取图片资源地址
 *
 * @param mediaId 图片的mediaId
 *
 * @discussion 获取图片的资源(downloadURL).
 *
 */
+ (NSString *_Nonnull)getImageResource: (NSString * _Nonnull)mediaId;

/*!
 * 获取视频资源地址
 *
 * @param mediaId 视频的mediaId
 *
 * @discussion 获取视频的资源(downloadURL).
 *
 */
+ (NSString *_Nonnull)getVideoResource: (NSString * _Nonnull)mediaId;

/*!
 * 创建会话
 *
 * @param sessionType 会话类型
 * @param sessionMain 会话的主要目标
 *
 * @discussion 此接口用于客户端建立新的聊天会话
 * 根据传入的 sessionType，sessionMain，返回包含 sessionId 信息的会话对象
 */
+ (SISession *_Nullable)createSession:(SISessionType )sessionType
                          sessionMain:(NSString * _Nonnull)sessionMain;

/*!
 * 发送消息接口
 *
 * @param message 发送的消息实体
 *
 * @discussion 消息需要封装为 `SIMessage` 类型，再调用此接口发送
 * 消息发送后通过回调 SakuraDelegate onSentMessage 反馈结果
 *
 */
- (void)sendMessage:(SIMessage * _Nonnull)message;

/*!
 * 发送消息回执
 *
 * @param messageRecvEvent 消息回执事件
 *
 * @discussion 消息需要封装为 `SIMessageRecvEvent` 类型，再调用此接口发送
 * 目前仅支持发送 recvState 为 SI_MESSAGE_RECV_DISPLAYED 的事件
 *
 */
- (void)sendMessageAck:(SIMessageRecvEvent * _Nonnull)messageRecvEvent;

/*!
 * 发送会话状态事件
 *
 * @param sessionStateEvent 发送的消息实体
 *
 * @discussion 消息需要封装为 `SISessionStateEvent` 类型，再调用此接口发送
 *
 */
- (void)sendSessionState:(SISessionStateEvent * _Nonnull)sessionStateEvent;

/*!
 * 上传图片接口
 *
 * @param aImage  待上传的图片
 * @param progressBlock 上传进度block
 * @param completionHandler 上传结果block
 *
 * @discussion 上传成功后，通过回调返回 `SIImageBody` 类型
 *
 */
- (void)uploadImage:(UIImage *_Nullable)aImage
           progress:(void (^ _Nullable)(float progress))progressBlock
         completion:(void (^ _Nullable)(SIImageBody * _Nullable imageBody, NSError * _Nullable error))completionHandler;

/*!
 * 上传音频接口
 *
 * @param audioData         待上传音频的二进制数据，目前只支持 amr 格式
 * @param progressBlock     上传进度block
 * @param completionHandler 上传结果block
 *
 * @discussion              上传成功后，通过回调返回 `SIVoiceBody` 类型
 *
 */
- (void)uploadAudio:(NSData *_Nullable)audioData
           progress:(void (^ _Nullable)(float progress))progressBlock
         completion:(void (^ _Nullable)(SIVoiceBody * _Nullable voiceBody, NSError * _Nullable error))completionHandler;

/*!
 * 上传视频接口
 *
 * @param videoData         待上传音频的二进制数据，目前只支持 mov 格式
 * @param progressBlock     上传进度block
 * @param completionHandler 上传结果block
 *
 * @discussion              上传成功后，通过回调返回 `SIVideoBody` 类型
 *
 */
- (void)uploadVideo:(NSData *_Nullable)videoData
           progress:(void (^ _Nullable)(float progress))progressBlock
         completion:(void (^ _Nullable)(SIShortvideoBody * _Nullable videoBody, NSError * _Nullable error))completionHandler;

/*!
 * 下载音频接口
 *
 * @param mediaId           待下载的文件mediaId
 * @param filePath          音频文件下载存放的地址
 * @param progressBlock     下载进度blocknbgg
 * @param completionHandler 下载结果block
 *
 * @discussion              下载成功后，通过回调返回 `data` 类型
 *
 */
- (void)downloadAudio:(NSString * _Nonnull)mediaId
               toPath:(NSString *_Nullable)filePath
             progress:(void (^ _Nullable)(float progress))progressBlock
           completion:(void (^ _Nullable)(BOOL success, NSData * _Nullable data, NSError * _Nullable error))completionHandler;

/*!
 * 下载视频接口
 *
 * @param mediaId           待下载的文件mediaId
 * @param filePath          视频文件下载存放的地址
 * @param progressBlock     下载进度block
 * @param completionHandler 下载结果block
 *
 * @discussion              下载成功后，通过回调返回 `data` 类型
 *
 */
- (void)downloadVideo:(NSString * _Nonnull)mediaId
               toPath:(NSString *_Nullable)filePath
             progress:(void (^ _Nullable)(float progress))progressBlock
           completion:(void (^ _Nullable)(BOOL success, NSData * _Nullable data, NSError * _Nullable error))completionHandler;

/*!
 * 获取历史信息
 *
 * @param completionHandler 获取历史消息结果block
 *
 * @discussion              以数组的形式返回历史消息,调用之前必须先调用 [configSakura]
 *
 */
- (void)getHistoryMessage:(void (^ _Nullable)(NSArray * _Nullable messageList, NSError * _Nullable error))completionHandler;

/*!
 * 拉取消息回执信息
 *
 *
 * @param messageIds        需要获取回执信息的id数组   [messageid1, messageid2]
 * @param completionHandler 获取历史消息结果block
 *
 * @discussion              以字典的形式返回每个消息对应的信息,调用之前必须先调用 [configSakura]
 *
 */
- (void)getReceiptMessage:(NSArray * _Nonnull)messageIds
               completion:(void (^ _Nullable)(NSDictionary * _Nullable messageDictionary, NSError * _Nullable error))completionHandler;

@end

#endif /* SakuraMessage_h */

