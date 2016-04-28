#ifndef Plugin_h
#define Plugin_h

#include <memory>
#include <mutex>

#include "AudioObject.h"

class Device;

class PlugIn : public AudioObject {
  struct PreventDirectConstruction {
    explicit PreventDirectConstruction(int) {}
  };
  
  static void CreateInstance();
  
public:
  static PlugIn& GetInstance();

  explicit PlugIn(const PreventDirectConstruction&);
  
  Boolean HasProperty(pid_t clientProcessID,
                      const AudioObjectPropertyAddress& address) const override;
  
  Boolean IsPropertySettable(pid_t clientProcessID,
                             const AudioObjectPropertyAddress& address) const override;
  
  UInt32 GetPropertyDataSize(pid_t clientProcessID,
                             const AudioObjectPropertyAddress& address,
                             UInt32 qualifierDataSize,
                             const void* qualifierData) const override;
  
  UInt32 GetPropertyData(pid_t clientProcessID,
                         const AudioObjectPropertyAddress& address,
                         UInt32 qualifierDataSize,
                         const void* qualifierData,
                         UInt32 dataSize,
                         void* data) const override;
  
  std::pair<UInt32, ChangedPropertyList>
  SetPropertyData(pid_t clientProcessID,
                  const AudioObjectPropertyAddress& address,
                  UInt32 qualifierDataSize,
                  const void* qualifierData,
                  UInt32 dataSize,
                  const void* data) override;
  
  void SetHost(AudioServerPlugInHostRef host) { host_ = host; }

private:
  static std::shared_ptr<PlugIn> instance_;
  std::shared_ptr<Device> device_;
  AudioServerPlugInHostRef host_;
};

#endif /* Plugin_h */
