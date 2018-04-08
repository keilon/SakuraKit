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

/*!
 * 获取SDK的实例
 *
 * @discussion SakuraMessage 采用单实例模式，只能通过此方法获取SDK的实例
 * 调用 instance method 时，涉及的操作对象仍然是该实例
 *
 */
+ (instancetype _Nonnull )sharedInstance;

/*!
 * 连接 Sakura 服务器
 *
 * @param identify    用户在 Sakura 中的id
 * @param token       用户连接 Sakura 的凭证
 * @param appId       应用开发者向 sakura 注册的 appId
 * @param msgServer   Sakura message server 的地址
 * @param fileServer  Sakura file server 的地址
 *
 * @discussion 此方法必须被调用, 用来初始化相关配置并连接 Sakura Server
 * msgServer 和 fileServer 均为 `NSDictionary` 类型，由 Sakura 服务端返回的两个地址直接用于此处，不要做转换操作
 *
 */
+ (void)connectSakura:(NSString * _Nullable )identify
                token:(NSString * _Nullable )token
                appId:(NSString * _Nullable )appId
            msgServer:(NSDictionary * _Nullable )msgServer
           fileServer:(NSDictionary * _Nullable )fileServer;

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
 * @discussion 需要离线推送功能时，必须调用此方法
 *
 */
+ (void)registerDeviceToken:(NSData *_Nullable)deviceToken;

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
 * 创建会话
 *
 * @param sessionType 会话类型
 * @param sessionMain 会话的主要目标
 * @param sessionName 会话的名称
 *
 * 此接口用于客户端建立新的聊天会话
 *
 */
+ (SISession *_Nullable)createSession:(SISessionType )sessionType
                          sessionMain:(NSString * _Nonnull)sessionMain
                          sessionName:(NSString * _Nonnull)sessionName;

/*!
 * 发送消息接口
 *
 * @param message 发送的消息实体
 *
 * @discussion 消息需要封装为 `SIMessage` 类型，再调用此接口发送
 * 消息发送后通过回调 SakuraDelegate onSentMessage 反馈结果
 *
 * 暂时只能发送 SISessionType 为 SI_SESSION_CHAT 或 SI_SESSION_GROUP 的消息
 *
 */
- (void)sendMessage:(SIMessage * _Nonnull)message;

@end

#endif /* SakuraMessage_h */

