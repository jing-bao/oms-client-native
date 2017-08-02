/*
 * Intel License
 */

#ifndef WOOGEEN_BASE_OBJC_CAMERAVIDEOCAPTUREFACTORY_H_
#define WOOGEEN_BASE_OBJC_CAMERAVIDEOCAPTUREFACTORY_H_

#include <memory>
#include "talk/woogeen/sdk/base/objc/ObjcVideoCapturerInterface.h"
#include "talk/woogeen/sdk/include/cpp/woogeen/base/localcamerastreamparameters.h"
#include "third_party/webrtc/api/mediastreaminterface.h"
#include "third_party/webrtc/base/scoped_ref_ptr.h"

@class RTCVideoCapturer;
@class RTCVideoSource;

namespace woogeen {
namespace base {
/// Wraps an RTCVideoCapturer.
class CameraVideoCapturer : public ObjcVideoCapturerInterface {
 public:
  rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> source() override;
  CameraVideoCapturer(RTCVideoCapturer* capturer, RTCVideoSource* source);
  ~CameraVideoCapturer() override;

 private:
  RTCVideoCapturer* capturer_;
  RTCVideoSource* source_;
};
}  // namespace base
}  // namespace woogeen

#endif  // WOOGEEN_BASE_OBJC_CAMERAVIDEOCAPTUREFACTORY_H_
