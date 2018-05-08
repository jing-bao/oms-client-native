//
//  Copyright (c) 2018 Intel Corporation. All rights reserved.
//

#import <WebRTC/RTCVideoCodecFactory.h>

RTC_EXPORT
@interface ICSDefaultVideoEncoderFactory : RTCDefaultVideoEncoderFactory

@property(nonatomic, retain) RTCVideoCodecInfo* preferredCodec;

+ (NSArray<RTCVideoCodecInfo*>*)supportedCodecs;

@end
