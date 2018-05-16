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

/*!
 * 接收消息(服务器端下发的)回调
 *
 * @param message 接收到下发的消息
 *
 * @discussion 收到的消息体均为 `SIMessage` 类型，需要根据 sessionType 判断会话类型
 * 消息内容是 `SIMessageBody` 类型，根据 messageType 转换为不同的消息 body
 *
 */
@optional
- (void)onReceiveMessage:(SIMessage *)message;

/*!
 * 发送消息结果返回回调
 *
 * @param message 已经发出的消息
 * @param success 发送结果
 *
 */
@optional
- (void)onSentMessage:(SIMessage *)message
               result:(BOOL) success;

/*!
 * 同步离线消息结果回调
 *
 * @param messageList 离线消息列表，是`SIMessage`类型的数组
 *
 * @discussion 由于同步消息和更新同步时间是两步操作，可能存在不一致导致消息被重复拉取，所以对于此结果应用层需要按照 messageId 去重
 *
 * 上层通过此代理方法监听离线消息同步的结果
 *
 */
@optional
- (void)onSyncOfflineMessage:(NSArray *)messageList;

/*!
 * 连接状态通知回调
 *
 * @param status 当前的连接状态
 *
 * @discussion 由于网络问题导致连接断开时，SDK会自动尝试重连，此时应用层不要主动调用 [SakuraMessage connectSakura] 方法
 *
 * 上层通过此代理方法监听和 Sakura 服务器的连接状态
 *
 */
@optional
- (void)onConnStatusChange:(SIConnStatus)status;

@end

#endif /* SakuraDelegate_h */
