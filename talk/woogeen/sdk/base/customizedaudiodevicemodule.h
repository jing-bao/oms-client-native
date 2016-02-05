/*
 * Intel License
 */

#ifndef WOOGEEN_BASE_CUSTOMIZEDAUDIODEVICEMODULE_H_
#define WOOGEEN_BASE_CUSTOMIZEDAUDIODEVICEMODULE_H_

#if defined(WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE)

#include <memory>
#include "webrtc/modules/audio_device/include/audio_device.h"
#include "webrtc/system_wrappers/interface/critical_section_wrapper.h"
#include "webrtc/modules/audio_device/audio_device_generic.h"
#include "webrtc/base/scoped_ref_ptr.h"
#include "talk/woogeen/sdk/include/cpp/woogeen/base/framegeneratorinterface.h"

namespace woogeen {
namespace base {

using namespace webrtc;

/**
 @brief CustomizedADM is able to create customized audio device use customized
 audio input.
 @detail CustomizedADM does not support audio output yet.
 */
class CustomizedAudioDeviceModule : public webrtc::AudioDeviceModule {
 public:
  CustomizedAudioDeviceModule();
  virtual ~CustomizedAudioDeviceModule();
  int64_t TimeUntilNextProcess() override;
  int32_t Process() override;

  // Factory methods (resource allocation/deallocation)
  static AudioDeviceModule* Create(
      std::unique_ptr<AudioFrameGeneratorInterface> frame_generator);

  // Retrieve the currently utilized audio layer
  int32_t ActiveAudioLayer(AudioLayer* audioLayer) const override;

  // Error handling
  ErrorCode LastError() const override;
  int32_t RegisterEventObserver(AudioDeviceObserver* eventCallback) override;

  // Full-duplex transportation of PCM audio
  int32_t RegisterAudioCallback(AudioTransport* audioCallback) override;

  // Main initialization and termination
  int32_t Init() override;
  int32_t Terminate() override;
  bool Initialized() const override;

  // Device enumeration
  int16_t PlayoutDevices() override;
  int16_t RecordingDevices() override;
  int32_t PlayoutDeviceName(uint16_t index,
                            char name[kAdmMaxDeviceNameSize],
                            char guid[kAdmMaxGuidSize]) override;
  int32_t RecordingDeviceName(uint16_t index,
                              char name[kAdmMaxDeviceNameSize],
                              char guid[kAdmMaxGuidSize]) override;

  // Device selection
  int32_t SetPlayoutDevice(uint16_t index) override;
  int32_t SetPlayoutDevice(WindowsDeviceType device) override;
  int32_t SetRecordingDevice(uint16_t index) override;
  int32_t SetRecordingDevice(WindowsDeviceType device) override;

  // Audio transport initialization
  int32_t PlayoutIsAvailable(bool* available) override;
  int32_t InitPlayout() override;
  bool PlayoutIsInitialized() const override;
  int32_t RecordingIsAvailable(bool* available) override;
  int32_t InitRecording() override;
  bool RecordingIsInitialized() const override;

  // Audio transport control
  int32_t StartPlayout() override;
  int32_t StopPlayout() override;
  bool Playing() const override;
  int32_t StartRecording() override;
  int32_t StopRecording() override;
  bool Recording() const override;

  // Microphone Automatic Gain Control (AGC)
  int32_t SetAGC(bool enable) override;
  bool AGC() const override;

  // Volume control based on the Windows Wave API (Windows only)
  int32_t SetWaveOutVolume(uint16_t volumeLeft, uint16_t volumeRight) override;
  int32_t WaveOutVolume(uint16_t* volumeLeft,
                        uint16_t* volumeRight) const override;

  // Audio mixer initialization
  int32_t InitSpeaker() override;
  bool SpeakerIsInitialized() const override;
  int32_t InitMicrophone() override;
  bool MicrophoneIsInitialized() const override;

  // Speaker volume controls
  int32_t SpeakerVolumeIsAvailable(bool* available) override;
  int32_t SetSpeakerVolume(uint32_t volume) override;
  int32_t SpeakerVolume(uint32_t* volume) const override;
  int32_t MaxSpeakerVolume(uint32_t* maxVolume) const override;
  int32_t MinSpeakerVolume(uint32_t* minVolume) const override;
  int32_t SpeakerVolumeStepSize(uint16_t* stepSize) const override;

  // Microphone volume controls
  int32_t MicrophoneVolumeIsAvailable(bool* available) override;
  int32_t SetMicrophoneVolume(uint32_t volume) override;
  int32_t MicrophoneVolume(uint32_t* volume) const override;
  int32_t MaxMicrophoneVolume(uint32_t* maxVolume) const override;
  int32_t MinMicrophoneVolume(uint32_t* minVolume) const override;
  int32_t MicrophoneVolumeStepSize(uint16_t* stepSize) const override;

  // Speaker mute control
  int32_t SpeakerMuteIsAvailable(bool* available) override;
  int32_t SetSpeakerMute(bool enable) override;
  int32_t SpeakerMute(bool* enabled) const override;

  // Microphone mute control
  int32_t MicrophoneMuteIsAvailable(bool* available) override;
  int32_t SetMicrophoneMute(bool enable) override;
  int32_t MicrophoneMute(bool* enabled) const override;

  // Microphone boost control
  int32_t MicrophoneBoostIsAvailable(bool* available) override;
  int32_t SetMicrophoneBoost(bool enable) override;
  int32_t MicrophoneBoost(bool* enabled) const override;

  // Stereo support
  int32_t StereoPlayoutIsAvailable(bool* available) const override;
  int32_t SetStereoPlayout(bool enable) override;
  int32_t StereoPlayout(bool* enabled) const override;
  int32_t StereoRecordingIsAvailable(bool* available) const override;
  int32_t SetStereoRecording(bool enable) override;
  int32_t StereoRecording(bool* enabled) const override;
  int32_t SetRecordingChannel(const ChannelType channel) override;
  int32_t RecordingChannel(ChannelType* channel) const override;

  // Delay information and control
  int32_t SetPlayoutBuffer(const BufferType type, uint16_t sizeMS = 0) override;
  int32_t PlayoutBuffer(BufferType* type, uint16_t* sizeMS) const override;
  int32_t PlayoutDelay(uint16_t* delayMS) const override;
  int32_t RecordingDelay(uint16_t* delayMS) const override;

  // CPU load
  int32_t CPULoad(uint16_t* load) const override;

  // Recording of raw PCM data
  int32_t StartRawOutputFileRecording(
      const char pcmFileNameUTF8[kAdmMaxFileNameSize]) override;
  int32_t StopRawOutputFileRecording() override;
  int32_t StartRawInputFileRecording(
      const char pcmFileNameUTF8[kAdmMaxFileNameSize]) override;
  int32_t StopRawInputFileRecording() override;

  // Native sample rate controls (samples/sec)
  int32_t SetRecordingSampleRate(const uint32_t samplesPerSec) override;
  int32_t RecordingSampleRate(uint32_t* samplesPerSec) const override;
  int32_t SetPlayoutSampleRate(const uint32_t samplesPerSec) override;
  int32_t PlayoutSampleRate(uint32_t* samplesPerSec) const override;

  // Mobile device specific functions
  int32_t ResetAudioDevice() override;
  int32_t SetLoudspeakerStatus(bool enable) override;
  int32_t GetLoudspeakerStatus(bool* enabled) const override;

  bool BuiltInAECIsEnabled() const override;
  bool BuiltInAECIsAvailable() const override;
  int32_t EnableBuiltInAEC(bool enable) override;
  bool BuiltInAGCIsAvailable() const override;
  int32_t EnableBuiltInAGC(bool enable) override;
  bool BuiltInNSIsAvailable() const override;
  int32_t EnableBuiltInNS(bool enable) override;

  int GetPlayoutAudioParameters(AudioParameters* params) const override;
  int GetRecordAudioParameters(AudioParameters* params) const override;

  void VolumeOverloud(int16_t level) override;

 private:
  int32_t CreateCustomizedAudioDevice(
      std::unique_ptr<AudioFrameGeneratorInterface> frame_generator);
  int32_t AttachAudioBuffer();

  CriticalSectionWrapper& _critSect;
  CriticalSectionWrapper& _critSectEventCb;
  CriticalSectionWrapper& _critSectAudioCb;

  AudioDeviceObserver* _ptrCbAudioDeviceObserver;

  AudioDeviceGeneric* _ptrAudioDevice;

  AudioDeviceBuffer _audioDeviceBuffer;

  int32_t _id;
  int64_t _lastProcessTime;
  bool _initialized;
  mutable ErrorCode _lastError;

  // Default internal adm for playout.
  rtc::scoped_refptr<webrtc::AudioDeviceModule> _outputAdm;
};
}
}

#endif  // defined(WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE)

#endif  // WOOGEEN_BASE_CUSTOMIZEDAUDIODEVICEMODULE_H_
