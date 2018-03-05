/*
 * Intel License
 */
#include "webrtc/rtc_base/base64.h"
#include "webrtc/rtc_base/criticalsection.h"
#include "webrtc/rtc_base/logging.h"
#include "webrtc/rtc_base/task_queue.h"
#include "talk/ics/sdk/base/stringutils.h"
#include "talk/ics/sdk/include/cpp/ics/p2p/p2pclient.h"
#include "talk/ics/sdk/include/cpp/ics/p2p/p2ppublication.h"

namespace ics {
namespace p2p {

P2PPublication::P2PPublication(std::shared_ptr<P2PClient> client, std::string target_id)
    : target_id_(target_id),
      p2p_client_(client),
      ended_(false) {
  auto that = p2p_client_.lock();
  if (that != nullptr)
    event_queue_ = that->event_queue_;
}

/// Get connection stats of current publication
void P2PPublication::GetStats(
    std::function<void(std::shared_ptr<ConnectionStats>)> on_success,
    std::function<void(std::unique_ptr<Exception>)> on_failure) {
  auto that = p2p_client_.lock();
  if (that == nullptr || ended_) {
    std::string failure_message(
       "Session ended.");
    if (on_failure != nullptr) {
      event_queue_->PostTask([on_failure, failure_message]() {
        std::unique_ptr<Exception> e(new Exception(
           ExceptionType::kP2PUnknown, failure_message));
        on_failure(std::move(e));
      });
    }
  } else {
     that->GetConnectionStats(target_id_, on_success, on_failure);
  }
}

/// Stop current publication.
void P2PPublication::Stop(
    std::function<void()> on_success,
    std::function<void(std::unique_ptr<Exception>)> on_failure) {
  auto that = p2p_client_.lock();
  if (that == nullptr || ended_) {
    std::string failure_message(
       "Session ended.");
    if (on_failure != nullptr) {
      event_queue_->PostTask([on_failure, failure_message]() {
        std::unique_ptr<Exception> e(new Exception(
           ExceptionType::kP2PUnknown, failure_message));
        on_failure(std::move(e));
      });
    }
  } else {
     that->Stop(target_id_, on_success, on_failure);
     ended_ = true;
  }
}

}
}