// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: id.proto

#include "id.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace protobuf_id_2eproto {
extern PROTOBUF_INTERNAL_EXPORT_protobuf_id_2eproto ::google::protobuf::internal::SCCInfo<0> scc_info_IDResponse_EitherPartTsnEntry_DoNotUse;
}  // namespace protobuf_id_2eproto
namespace IDIncrement {
class IDRequestDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<IDRequest>
      _instance;
} _IDRequest_default_instance_;
class IDResponse_EitherPartTsnEntry_DoNotUseDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<IDResponse_EitherPartTsnEntry_DoNotUse>
      _instance;
} _IDResponse_EitherPartTsnEntry_DoNotUse_default_instance_;
class IDResponseDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<IDResponse>
      _instance;
} _IDResponse_default_instance_;
}  // namespace IDIncrement
namespace protobuf_id_2eproto {
static void InitDefaultsIDRequest() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::IDIncrement::_IDRequest_default_instance_;
    new (ptr) ::IDIncrement::IDRequest();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::IDIncrement::IDRequest::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_IDRequest =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsIDRequest}, {}};

static void InitDefaultsIDResponse_EitherPartTsnEntry_DoNotUse() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::IDIncrement::_IDResponse_EitherPartTsnEntry_DoNotUse_default_instance_;
    new (ptr) ::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse();
  }
  ::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_IDResponse_EitherPartTsnEntry_DoNotUse =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsIDResponse_EitherPartTsnEntry_DoNotUse}, {}};

static void InitDefaultsIDResponse() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::IDIncrement::_IDResponse_default_instance_;
    new (ptr) ::IDIncrement::IDResponse();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::IDIncrement::IDResponse::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<1> scc_info_IDResponse =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 1, InitDefaultsIDResponse}, {
      &protobuf_id_2eproto::scc_info_IDResponse_EitherPartTsnEntry_DoNotUse.base,}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_IDRequest.base);
  ::google::protobuf::internal::InitSCC(&scc_info_IDResponse_EitherPartTsnEntry_DoNotUse.base);
  ::google::protobuf::internal::InitSCC(&scc_info_IDResponse.base);
}

::google::protobuf::Metadata file_level_metadata[3];
const ::google::protobuf::ServiceDescriptor* file_level_service_descriptors[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDRequest, page_table_no_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse, key_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse, value_),
  0,
  1,
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDResponse, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDResponse, part_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDResponse, s_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDResponse, m_id_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::IDIncrement::IDResponse, either_part_tsn_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::IDIncrement::IDRequest)},
  { 6, 13, sizeof(::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse)},
  { 15, -1, sizeof(::IDIncrement::IDResponse)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::IDIncrement::_IDRequest_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::IDIncrement::_IDResponse_EitherPartTsnEntry_DoNotUse_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::IDIncrement::_IDResponse_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "id.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, file_level_service_descriptors);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 3);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\010id.proto\022\013IDIncrement\"\"\n\tIDRequest\022\025\n\r"
      "page_table_no\030\001 \001(\t\"\264\001\n\nIDResponse\022\017\n\007pa"
      "rt_id\030\001 \001(\005\022\014\n\004s_id\030\002 \001(\003\022\014\n\004m_id\030\003 \001(\003\022"
      "C\n\017either_part_tsn\030\004 \003(\0132*.IDIncrement.I"
      "DResponse.EitherPartTsnEntry\0324\n\022EitherPa"
      "rtTsnEntry\022\013\n\003key\030\001 \001(\005\022\r\n\005value\030\002 \001(\003:\002"
      "8\0012E\n\tIDService\0228\n\005IDInc\022\026.IDIncrement.I"
      "DRequest\032\027.IDIncrement.IDResponseB\003\200\001\001b\006"
      "proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 326);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "id.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_id_2eproto
namespace IDIncrement {

// ===================================================================

void IDRequest::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int IDRequest::kPageTableNoFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

IDRequest::IDRequest()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_id_2eproto::scc_info_IDRequest.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:IDIncrement.IDRequest)
}
IDRequest::IDRequest(const IDRequest& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  page_table_no_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.page_table_no().size() > 0) {
    page_table_no_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.page_table_no_);
  }
  // @@protoc_insertion_point(copy_constructor:IDIncrement.IDRequest)
}

void IDRequest::SharedCtor() {
  page_table_no_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

IDRequest::~IDRequest() {
  // @@protoc_insertion_point(destructor:IDIncrement.IDRequest)
  SharedDtor();
}

void IDRequest::SharedDtor() {
  page_table_no_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void IDRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* IDRequest::descriptor() {
  ::protobuf_id_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_id_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const IDRequest& IDRequest::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_id_2eproto::scc_info_IDRequest.base);
  return *internal_default_instance();
}


void IDRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:IDIncrement.IDRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  page_table_no_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  _internal_metadata_.Clear();
}

bool IDRequest::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:IDIncrement.IDRequest)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // string page_table_no = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_page_table_no()));
          DO_(::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
            this->page_table_no().data(), static_cast<int>(this->page_table_no().length()),
            ::google::protobuf::internal::WireFormatLite::PARSE,
            "IDIncrement.IDRequest.page_table_no"));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:IDIncrement.IDRequest)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:IDIncrement.IDRequest)
  return false;
#undef DO_
}

void IDRequest::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:IDIncrement.IDRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string page_table_no = 1;
  if (this->page_table_no().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->page_table_no().data(), static_cast<int>(this->page_table_no().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "IDIncrement.IDRequest.page_table_no");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->page_table_no(), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:IDIncrement.IDRequest)
}

::google::protobuf::uint8* IDRequest::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:IDIncrement.IDRequest)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string page_table_no = 1;
  if (this->page_table_no().size() > 0) {
    ::google::protobuf::internal::WireFormatLite::VerifyUtf8String(
      this->page_table_no().data(), static_cast<int>(this->page_table_no().length()),
      ::google::protobuf::internal::WireFormatLite::SERIALIZE,
      "IDIncrement.IDRequest.page_table_no");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->page_table_no(), target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:IDIncrement.IDRequest)
  return target;
}

size_t IDRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:IDIncrement.IDRequest)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // string page_table_no = 1;
  if (this->page_table_no().size() > 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::StringSize(
        this->page_table_no());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void IDRequest::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:IDIncrement.IDRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const IDRequest* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const IDRequest>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:IDIncrement.IDRequest)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:IDIncrement.IDRequest)
    MergeFrom(*source);
  }
}

void IDRequest::MergeFrom(const IDRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:IDIncrement.IDRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.page_table_no().size() > 0) {

    page_table_no_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.page_table_no_);
  }
}

void IDRequest::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:IDIncrement.IDRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void IDRequest::CopyFrom(const IDRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:IDIncrement.IDRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool IDRequest::IsInitialized() const {
  return true;
}

void IDRequest::Swap(IDRequest* other) {
  if (other == this) return;
  InternalSwap(other);
}
void IDRequest::InternalSwap(IDRequest* other) {
  using std::swap;
  page_table_no_.Swap(&other->page_table_no_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata IDRequest::GetMetadata() const {
  protobuf_id_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_id_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

IDResponse_EitherPartTsnEntry_DoNotUse::IDResponse_EitherPartTsnEntry_DoNotUse() {}
IDResponse_EitherPartTsnEntry_DoNotUse::IDResponse_EitherPartTsnEntry_DoNotUse(::google::protobuf::Arena* arena) : SuperType(arena) {}
void IDResponse_EitherPartTsnEntry_DoNotUse::MergeFrom(const IDResponse_EitherPartTsnEntry_DoNotUse& other) {
  MergeFromInternal(other);
}
::google::protobuf::Metadata IDResponse_EitherPartTsnEntry_DoNotUse::GetMetadata() const {
  ::protobuf_id_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_id_2eproto::file_level_metadata[1];
}
void IDResponse_EitherPartTsnEntry_DoNotUse::MergeFrom(
    const ::google::protobuf::Message& other) {
  ::google::protobuf::Message::MergeFrom(other);
}


// ===================================================================

void IDResponse::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int IDResponse::kPartIdFieldNumber;
const int IDResponse::kSIdFieldNumber;
const int IDResponse::kMIdFieldNumber;
const int IDResponse::kEitherPartTsnFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

IDResponse::IDResponse()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_id_2eproto::scc_info_IDResponse.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:IDIncrement.IDResponse)
}
IDResponse::IDResponse(const IDResponse& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  either_part_tsn_.MergeFrom(from.either_part_tsn_);
  ::memcpy(&s_id_, &from.s_id_,
    static_cast<size_t>(reinterpret_cast<char*>(&part_id_) -
    reinterpret_cast<char*>(&s_id_)) + sizeof(part_id_));
  // @@protoc_insertion_point(copy_constructor:IDIncrement.IDResponse)
}

void IDResponse::SharedCtor() {
  ::memset(&s_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&part_id_) -
      reinterpret_cast<char*>(&s_id_)) + sizeof(part_id_));
}

IDResponse::~IDResponse() {
  // @@protoc_insertion_point(destructor:IDIncrement.IDResponse)
  SharedDtor();
}

void IDResponse::SharedDtor() {
}

void IDResponse::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* IDResponse::descriptor() {
  ::protobuf_id_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_id_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const IDResponse& IDResponse::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_id_2eproto::scc_info_IDResponse.base);
  return *internal_default_instance();
}


void IDResponse::Clear() {
// @@protoc_insertion_point(message_clear_start:IDIncrement.IDResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  either_part_tsn_.Clear();
  ::memset(&s_id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&part_id_) -
      reinterpret_cast<char*>(&s_id_)) + sizeof(part_id_));
  _internal_metadata_.Clear();
}

bool IDResponse::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:IDIncrement.IDResponse)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // int32 part_id = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &part_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int64 s_id = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(16u /* 16 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &s_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // int64 m_id = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(24u /* 24 & 0xFF */)) {

          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int64, ::google::protobuf::internal::WireFormatLite::TYPE_INT64>(
                 input, &m_id_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // map<int32, int64> either_part_tsn = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u /* 34 & 0xFF */)) {
          IDResponse_EitherPartTsnEntry_DoNotUse::Parser< ::google::protobuf::internal::MapField<
              IDResponse_EitherPartTsnEntry_DoNotUse,
              ::google::protobuf::int32, ::google::protobuf::int64,
              ::google::protobuf::internal::WireFormatLite::TYPE_INT32,
              ::google::protobuf::internal::WireFormatLite::TYPE_INT64,
              0 >,
            ::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 > > parser(&either_part_tsn_);
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
              input, &parser));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:IDIncrement.IDResponse)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:IDIncrement.IDResponse)
  return false;
#undef DO_
}

void IDResponse::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:IDIncrement.IDResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 part_id = 1;
  if (this->part_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(1, this->part_id(), output);
  }

  // int64 s_id = 2;
  if (this->s_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(2, this->s_id(), output);
  }

  // int64 m_id = 3;
  if (this->m_id() != 0) {
    ::google::protobuf::internal::WireFormatLite::WriteInt64(3, this->m_id(), output);
  }

  // map<int32, int64> either_part_tsn = 4;
  if (!this->either_part_tsn().empty()) {
    typedef ::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 >::const_pointer
        ConstPtr;
    typedef ::google::protobuf::internal::SortItem< ::google::protobuf::int32, ConstPtr > SortItem;
    typedef ::google::protobuf::internal::CompareByFirstField<SortItem> Less;

    if (output->IsSerializationDeterministic() &&
        this->either_part_tsn().size() > 1) {
      ::std::unique_ptr<SortItem[]> items(
          new SortItem[this->either_part_tsn().size()]);
      typedef ::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 >::size_type size_type;
      size_type n = 0;
      for (::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 >::const_iterator
          it = this->either_part_tsn().begin();
          it != this->either_part_tsn().end(); ++it, ++n) {
        items[static_cast<ptrdiff_t>(n)] = SortItem(&*it);
      }
      ::std::sort(&items[0], &items[static_cast<ptrdiff_t>(n)], Less());
      ::std::unique_ptr<IDResponse_EitherPartTsnEntry_DoNotUse> entry;
      for (size_type i = 0; i < n; i++) {
        entry.reset(either_part_tsn_.NewEntryWrapper(
            items[static_cast<ptrdiff_t>(i)].second->first, items[static_cast<ptrdiff_t>(i)].second->second));
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            4, *entry, output);
      }
    } else {
      ::std::unique_ptr<IDResponse_EitherPartTsnEntry_DoNotUse> entry;
      for (::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 >::const_iterator
          it = this->either_part_tsn().begin();
          it != this->either_part_tsn().end(); ++it) {
        entry.reset(either_part_tsn_.NewEntryWrapper(
            it->first, it->second));
        ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
            4, *entry, output);
      }
    }
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:IDIncrement.IDResponse)
}

::google::protobuf::uint8* IDResponse::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:IDIncrement.IDResponse)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 part_id = 1;
  if (this->part_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(1, this->part_id(), target);
  }

  // int64 s_id = 2;
  if (this->s_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(2, this->s_id(), target);
  }

  // int64 m_id = 3;
  if (this->m_id() != 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt64ToArray(3, this->m_id(), target);
  }

  // map<int32, int64> either_part_tsn = 4;
  if (!this->either_part_tsn().empty()) {
    typedef ::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 >::const_pointer
        ConstPtr;
    typedef ::google::protobuf::internal::SortItem< ::google::protobuf::int32, ConstPtr > SortItem;
    typedef ::google::protobuf::internal::CompareByFirstField<SortItem> Less;

    if (deterministic &&
        this->either_part_tsn().size() > 1) {
      ::std::unique_ptr<SortItem[]> items(
          new SortItem[this->either_part_tsn().size()]);
      typedef ::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 >::size_type size_type;
      size_type n = 0;
      for (::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 >::const_iterator
          it = this->either_part_tsn().begin();
          it != this->either_part_tsn().end(); ++it, ++n) {
        items[static_cast<ptrdiff_t>(n)] = SortItem(&*it);
      }
      ::std::sort(&items[0], &items[static_cast<ptrdiff_t>(n)], Less());
      ::std::unique_ptr<IDResponse_EitherPartTsnEntry_DoNotUse> entry;
      for (size_type i = 0; i < n; i++) {
        entry.reset(either_part_tsn_.NewEntryWrapper(
            items[static_cast<ptrdiff_t>(i)].second->first, items[static_cast<ptrdiff_t>(i)].second->second));
        target = ::google::protobuf::internal::WireFormatLite::
                   InternalWriteMessageNoVirtualToArray(
                       4, *entry, deterministic, target);
;
      }
    } else {
      ::std::unique_ptr<IDResponse_EitherPartTsnEntry_DoNotUse> entry;
      for (::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 >::const_iterator
          it = this->either_part_tsn().begin();
          it != this->either_part_tsn().end(); ++it) {
        entry.reset(either_part_tsn_.NewEntryWrapper(
            it->first, it->second));
        target = ::google::protobuf::internal::WireFormatLite::
                   InternalWriteMessageNoVirtualToArray(
                       4, *entry, deterministic, target);
;
      }
    }
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:IDIncrement.IDResponse)
  return target;
}

size_t IDResponse::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:IDIncrement.IDResponse)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // map<int32, int64> either_part_tsn = 4;
  total_size += 1 *
      ::google::protobuf::internal::FromIntSize(this->either_part_tsn_size());
  {
    ::std::unique_ptr<IDResponse_EitherPartTsnEntry_DoNotUse> entry;
    for (::google::protobuf::Map< ::google::protobuf::int32, ::google::protobuf::int64 >::const_iterator
        it = this->either_part_tsn().begin();
        it != this->either_part_tsn().end(); ++it) {
      entry.reset(either_part_tsn_.NewEntryWrapper(it->first, it->second));
      total_size += ::google::protobuf::internal::WireFormatLite::
          MessageSizeNoVirtual(*entry);
    }
  }

  // int64 s_id = 2;
  if (this->s_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->s_id());
  }

  // int64 m_id = 3;
  if (this->m_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int64Size(
        this->m_id());
  }

  // int32 part_id = 1;
  if (this->part_id() != 0) {
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->part_id());
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void IDResponse::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:IDIncrement.IDResponse)
  GOOGLE_DCHECK_NE(&from, this);
  const IDResponse* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const IDResponse>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:IDIncrement.IDResponse)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:IDIncrement.IDResponse)
    MergeFrom(*source);
  }
}

void IDResponse::MergeFrom(const IDResponse& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:IDIncrement.IDResponse)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  either_part_tsn_.MergeFrom(from.either_part_tsn_);
  if (from.s_id() != 0) {
    set_s_id(from.s_id());
  }
  if (from.m_id() != 0) {
    set_m_id(from.m_id());
  }
  if (from.part_id() != 0) {
    set_part_id(from.part_id());
  }
}

void IDResponse::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:IDIncrement.IDResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void IDResponse::CopyFrom(const IDResponse& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:IDIncrement.IDResponse)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool IDResponse::IsInitialized() const {
  return true;
}

void IDResponse::Swap(IDResponse* other) {
  if (other == this) return;
  InternalSwap(other);
}
void IDResponse::InternalSwap(IDResponse* other) {
  using std::swap;
  either_part_tsn_.Swap(&other->either_part_tsn_);
  swap(s_id_, other->s_id_);
  swap(m_id_, other->m_id_);
  swap(part_id_, other->part_id_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata IDResponse::GetMetadata() const {
  protobuf_id_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_id_2eproto::file_level_metadata[kIndexInFileMessages];
}


// ===================================================================

IDService::~IDService() {}

const ::google::protobuf::ServiceDescriptor* IDService::descriptor() {
  protobuf_id_2eproto::protobuf_AssignDescriptorsOnce();
  return protobuf_id_2eproto::file_level_service_descriptors[0];
}

const ::google::protobuf::ServiceDescriptor* IDService::GetDescriptor() {
  return descriptor();
}

void IDService::IDInc(::google::protobuf::RpcController* controller,
                         const ::IDIncrement::IDRequest*,
                         ::IDIncrement::IDResponse*,
                         ::google::protobuf::Closure* done) {
  controller->SetFailed("Method IDInc() not implemented.");
  done->Run();
}

void IDService::CallMethod(const ::google::protobuf::MethodDescriptor* method,
                             ::google::protobuf::RpcController* controller,
                             const ::google::protobuf::Message* request,
                             ::google::protobuf::Message* response,
                             ::google::protobuf::Closure* done) {
  GOOGLE_DCHECK_EQ(method->service(), protobuf_id_2eproto::file_level_service_descriptors[0]);
  switch(method->index()) {
    case 0:
      IDInc(controller,
             ::google::protobuf::down_cast<const ::IDIncrement::IDRequest*>(request),
             ::google::protobuf::down_cast< ::IDIncrement::IDResponse*>(response),
             done);
      break;
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      break;
  }
}

const ::google::protobuf::Message& IDService::GetRequestPrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::IDIncrement::IDRequest::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::google::protobuf::MessageFactory::generated_factory()
          ->GetPrototype(method->input_type());
  }
}

const ::google::protobuf::Message& IDService::GetResponsePrototype(
    const ::google::protobuf::MethodDescriptor* method) const {
  GOOGLE_DCHECK_EQ(method->service(), descriptor());
  switch(method->index()) {
    case 0:
      return ::IDIncrement::IDResponse::default_instance();
    default:
      GOOGLE_LOG(FATAL) << "Bad method index; this should never happen.";
      return *::google::protobuf::MessageFactory::generated_factory()
          ->GetPrototype(method->output_type());
  }
}

IDService_Stub::IDService_Stub(::google::protobuf::RpcChannel* channel)
  : channel_(channel), owns_channel_(false) {}
IDService_Stub::IDService_Stub(
    ::google::protobuf::RpcChannel* channel,
    ::google::protobuf::Service::ChannelOwnership ownership)
  : channel_(channel),
    owns_channel_(ownership == ::google::protobuf::Service::STUB_OWNS_CHANNEL) {}
IDService_Stub::~IDService_Stub() {
  if (owns_channel_) delete channel_;
}

void IDService_Stub::IDInc(::google::protobuf::RpcController* controller,
                              const ::IDIncrement::IDRequest* request,
                              ::IDIncrement::IDResponse* response,
                              ::google::protobuf::Closure* done) {
  channel_->CallMethod(descriptor()->method(0),
                       controller, request, response, done);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace IDIncrement
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::IDIncrement::IDRequest* Arena::CreateMaybeMessage< ::IDIncrement::IDRequest >(Arena* arena) {
  return Arena::CreateInternal< ::IDIncrement::IDRequest >(arena);
}
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse* Arena::CreateMaybeMessage< ::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse >(Arena* arena) {
  return Arena::CreateInternal< ::IDIncrement::IDResponse_EitherPartTsnEntry_DoNotUse >(arena);
}
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::IDIncrement::IDResponse* Arena::CreateMaybeMessage< ::IDIncrement::IDResponse >(Arena* arena) {
  return Arena::CreateInternal< ::IDIncrement::IDResponse >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
