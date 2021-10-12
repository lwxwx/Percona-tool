// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: id.proto

#ifndef PROTOBUF_INCLUDED_id_2eproto
#define PROTOBUF_INCLUDED_id_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/service.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_id_2eproto 

namespace protobuf_id_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[2];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_id_2eproto
namespace IDIncrement {
class IDRequest;
class IDRequestDefaultTypeInternal;
extern IDRequestDefaultTypeInternal _IDRequest_default_instance_;
class IDResponse;
class IDResponseDefaultTypeInternal;
extern IDResponseDefaultTypeInternal _IDResponse_default_instance_;
}  // namespace IDIncrement
namespace google {
namespace protobuf {
template<> ::IDIncrement::IDRequest* Arena::CreateMaybeMessage<::IDIncrement::IDRequest>(Arena*);
template<> ::IDIncrement::IDResponse* Arena::CreateMaybeMessage<::IDIncrement::IDResponse>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace IDIncrement {

// ===================================================================

class IDRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:IDIncrement.IDRequest) */ {
 public:
  IDRequest();
  virtual ~IDRequest();

  IDRequest(const IDRequest& from);

  inline IDRequest& operator=(const IDRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  IDRequest(IDRequest&& from) noexcept
    : IDRequest() {
    *this = ::std::move(from);
  }

  inline IDRequest& operator=(IDRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const IDRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const IDRequest* internal_default_instance() {
    return reinterpret_cast<const IDRequest*>(
               &_IDRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(IDRequest* other);
  friend void swap(IDRequest& a, IDRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline IDRequest* New() const final {
    return CreateMaybeMessage<IDRequest>(NULL);
  }

  IDRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<IDRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const IDRequest& from);
  void MergeFrom(const IDRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(IDRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string message = 1;
  bool has_message() const;
  void clear_message();
  static const int kMessageFieldNumber = 1;
  const ::std::string& message() const;
  void set_message(const ::std::string& value);
  #if LANG_CXX11
  void set_message(::std::string&& value);
  #endif
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  ::std::string* mutable_message();
  ::std::string* release_message();
  void set_allocated_message(::std::string* message);

  // @@protoc_insertion_point(class_scope:IDIncrement.IDRequest)
 private:
  void set_has_message();
  void clear_has_message();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr message_;
  friend struct ::protobuf_id_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class IDResponse : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:IDIncrement.IDResponse) */ {
 public:
  IDResponse();
  virtual ~IDResponse();

  IDResponse(const IDResponse& from);

  inline IDResponse& operator=(const IDResponse& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  IDResponse(IDResponse&& from) noexcept
    : IDResponse() {
    *this = ::std::move(from);
  }

  inline IDResponse& operator=(IDResponse&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const IDResponse& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const IDResponse* internal_default_instance() {
    return reinterpret_cast<const IDResponse*>(
               &_IDResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    1;

  void Swap(IDResponse* other);
  friend void swap(IDResponse& a, IDResponse& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline IDResponse* New() const final {
    return CreateMaybeMessage<IDResponse>(NULL);
  }

  IDResponse* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<IDResponse>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const IDResponse& from);
  void MergeFrom(const IDResponse& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(IDResponse* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string message = 1;
  bool has_message() const;
  void clear_message();
  static const int kMessageFieldNumber = 1;
  const ::std::string& message() const;
  void set_message(const ::std::string& value);
  #if LANG_CXX11
  void set_message(::std::string&& value);
  #endif
  void set_message(const char* value);
  void set_message(const char* value, size_t size);
  ::std::string* mutable_message();
  ::std::string* release_message();
  void set_allocated_message(::std::string* message);

  // @@protoc_insertion_point(class_scope:IDIncrement.IDResponse)
 private:
  void set_has_message();
  void clear_has_message();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr message_;
  friend struct ::protobuf_id_2eproto::TableStruct;
};
// ===================================================================

class IDService_Stub;

class IDService : public ::google::protobuf::Service {
 protected:
  // This class should be treated as an abstract interface.
  inline IDService() {};
 public:
  virtual ~IDService();

  typedef IDService_Stub Stub;

  static const ::google::protobuf::ServiceDescriptor* descriptor();

  virtual void IDInc(::google::protobuf::RpcController* controller,
                       const ::IDIncrement::IDRequest* request,
                       ::IDIncrement::IDResponse* response,
                       ::google::protobuf::Closure* done);

  // implements Service ----------------------------------------------

  const ::google::protobuf::ServiceDescriptor* GetDescriptor();
  void CallMethod(const ::google::protobuf::MethodDescriptor* method,
                  ::google::protobuf::RpcController* controller,
                  const ::google::protobuf::Message* request,
                  ::google::protobuf::Message* response,
                  ::google::protobuf::Closure* done);
  const ::google::protobuf::Message& GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const;
  const ::google::protobuf::Message& GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const;

 private:
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(IDService);
};

class IDService_Stub : public IDService {
 public:
  IDService_Stub(::google::protobuf::RpcChannel* channel);
  IDService_Stub(::google::protobuf::RpcChannel* channel,
                   ::google::protobuf::Service::ChannelOwnership ownership);
  ~IDService_Stub();

  inline ::google::protobuf::RpcChannel* channel() { return channel_; }

  // implements IDService ------------------------------------------

  void IDInc(::google::protobuf::RpcController* controller,
                       const ::IDIncrement::IDRequest* request,
                       ::IDIncrement::IDResponse* response,
                       ::google::protobuf::Closure* done);
 private:
  ::google::protobuf::RpcChannel* channel_;
  bool owns_channel_;
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(IDService_Stub);
};


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// IDRequest

// required string message = 1;
inline bool IDRequest::has_message() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void IDRequest::set_has_message() {
  _has_bits_[0] |= 0x00000001u;
}
inline void IDRequest::clear_has_message() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void IDRequest::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_message();
}
inline const ::std::string& IDRequest::message() const {
  // @@protoc_insertion_point(field_get:IDIncrement.IDRequest.message)
  return message_.GetNoArena();
}
inline void IDRequest::set_message(const ::std::string& value) {
  set_has_message();
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IDIncrement.IDRequest.message)
}
#if LANG_CXX11
inline void IDRequest::set_message(::std::string&& value) {
  set_has_message();
  message_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:IDIncrement.IDRequest.message)
}
#endif
inline void IDRequest::set_message(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_message();
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IDIncrement.IDRequest.message)
}
inline void IDRequest::set_message(const char* value, size_t size) {
  set_has_message();
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IDIncrement.IDRequest.message)
}
inline ::std::string* IDRequest::mutable_message() {
  set_has_message();
  // @@protoc_insertion_point(field_mutable:IDIncrement.IDRequest.message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* IDRequest::release_message() {
  // @@protoc_insertion_point(field_release:IDIncrement.IDRequest.message)
  if (!has_message()) {
    return NULL;
  }
  clear_has_message();
  return message_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IDRequest::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    set_has_message();
  } else {
    clear_has_message();
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:IDIncrement.IDRequest.message)
}

// -------------------------------------------------------------------

// IDResponse

// required string message = 1;
inline bool IDResponse::has_message() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void IDResponse::set_has_message() {
  _has_bits_[0] |= 0x00000001u;
}
inline void IDResponse::clear_has_message() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void IDResponse::clear_message() {
  message_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_message();
}
inline const ::std::string& IDResponse::message() const {
  // @@protoc_insertion_point(field_get:IDIncrement.IDResponse.message)
  return message_.GetNoArena();
}
inline void IDResponse::set_message(const ::std::string& value) {
  set_has_message();
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:IDIncrement.IDResponse.message)
}
#if LANG_CXX11
inline void IDResponse::set_message(::std::string&& value) {
  set_has_message();
  message_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:IDIncrement.IDResponse.message)
}
#endif
inline void IDResponse::set_message(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_message();
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:IDIncrement.IDResponse.message)
}
inline void IDResponse::set_message(const char* value, size_t size) {
  set_has_message();
  message_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:IDIncrement.IDResponse.message)
}
inline ::std::string* IDResponse::mutable_message() {
  set_has_message();
  // @@protoc_insertion_point(field_mutable:IDIncrement.IDResponse.message)
  return message_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* IDResponse::release_message() {
  // @@protoc_insertion_point(field_release:IDIncrement.IDResponse.message)
  if (!has_message()) {
    return NULL;
  }
  clear_has_message();
  return message_.ReleaseNonDefaultNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void IDResponse::set_allocated_message(::std::string* message) {
  if (message != NULL) {
    set_has_message();
  } else {
    clear_has_message();
  }
  message_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), message);
  // @@protoc_insertion_point(field_set_allocated:IDIncrement.IDResponse.message)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace IDIncrement

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_id_2eproto