#import "WebRTC/RTCVideoCodec.h"
#import "WebRTC/RTCVideoCodecFactory.h"
#if !defined(RTC_DISABLE_H265)
#import "WebRTC/RTCVideoCodecH265.h"
#endif
#import "talk/ics/sdk/base/objc/ICSDefaultVideoEncoderFactory.h"

@implementation ICSDefaultVideoEncoderFactory

@synthesize preferredCodec;

+ (NSArray<RTCVideoCodecInfo*>*)supportedCodecs {
  NSMutableArray<RTCVideoCodecInfo*>* codecs =
      [[RTCDefaultVideoEncoderFactory supportedCodecs] mutableCopy];
#if !defined(RTC_DISABLE_H265)
  if (@available(iOS 11.0, *)) {
    [codecs addObject:[[RTCVideoCodecInfo alloc]
                          initWithName:kRTCVideoCodecH265Name]];
  }
#endif
  return codecs;
}

- (id<RTCVideoEncoder>)createEncoder:(RTCVideoCodecInfo*)info {
#if !defined(RTC_DISABLE_H265)
  if (@available(iOS 11.0, *)) {
    if ([info.name isEqualToString:kRTCVideoCodecH265Name]) {
      return [[RTCVideoEncoderH265 alloc] initWithCodecInfo:info];
    }
  }
#endif
  return [super createEncoder:info];
}

- (NSArray<RTCVideoCodecInfo*>*)supportedCodecs {
  return [super supportedCodecs];
}

@end
