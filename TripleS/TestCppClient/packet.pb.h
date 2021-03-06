// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: packet.proto

#ifndef PROTOBUF_packet_2eproto__INCLUDED
#define PROTOBUF_packet_2eproto__INCLUDED

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable: 4127 4244 4267)
#endif

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2006000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_packet_2eproto();
void protobuf_AssignDesc_packet_2eproto();
void protobuf_ShutdownFile_packet_2eproto();

class EchoPacket;
class StringPacket;

enum PACKET_TYPE {
  eEchoPacket = 0,
  eStringPacket = 1
};
bool PACKET_TYPE_IsValid(int value);
const PACKET_TYPE PACKET_TYPE_MIN = eEchoPacket;
const PACKET_TYPE PACKET_TYPE_MAX = eStringPacket;
const int PACKET_TYPE_ARRAYSIZE = PACKET_TYPE_MAX + 1;

const ::google::protobuf::EnumDescriptor* PACKET_TYPE_descriptor();
inline const ::std::string& PACKET_TYPE_Name(PACKET_TYPE value) {
  return ::google::protobuf::internal::NameOfEnum(
    PACKET_TYPE_descriptor(), value);
}
inline bool PACKET_TYPE_Parse(
    const ::std::string& name, PACKET_TYPE* value) {
  return ::google::protobuf::internal::ParseNamedEnum<PACKET_TYPE>(
    PACKET_TYPE_descriptor(), name, value);
}
// ===================================================================

class EchoPacket : public ::google::protobuf::Message {
 public:
  EchoPacket();
  virtual ~EchoPacket();

  EchoPacket(const EchoPacket& from);

  inline EchoPacket& operator=(const EchoPacket& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const EchoPacket& default_instance();

  void Swap(EchoPacket* other);

  // implements Message ----------------------------------------------

  EchoPacket* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const EchoPacket& from);
  void MergeFrom(const EchoPacket& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required int32 id = 1;
  inline bool has_id() const;
  inline void clear_id();
  static const int kIdFieldNumber = 1;
  inline ::google::protobuf::int32 id() const;
  inline void set_id(::google::protobuf::int32 value);

  // required bytes name = 2;
  inline bool has_name() const;
  inline void clear_name();
  static const int kNameFieldNumber = 2;
  inline const ::std::string& name() const;
  inline void set_name(const ::std::string& value);
  inline void set_name(const char* value);
  inline void set_name(const void* value, size_t size);
  inline ::std::string* mutable_name();
  inline ::std::string* release_name();
  inline void set_allocated_name(::std::string* name);

  // @@protoc_insertion_point(class_scope:EchoPacket)
 private:
  inline void set_has_id();
  inline void clear_has_id();
  inline void set_has_name();
  inline void clear_has_name();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* name_;
  ::google::protobuf::int32 id_;
  friend void  protobuf_AddDesc_packet_2eproto();
  friend void protobuf_AssignDesc_packet_2eproto();
  friend void protobuf_ShutdownFile_packet_2eproto();

  void InitAsDefaultInstance();
  static EchoPacket* default_instance_;
};
// -------------------------------------------------------------------

class StringPacket : public ::google::protobuf::Message {
 public:
  StringPacket();
  virtual ~StringPacket();

  StringPacket(const StringPacket& from);

  inline StringPacket& operator=(const StringPacket& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const StringPacket& default_instance();

  void Swap(StringPacket* other);

  // implements Message ----------------------------------------------

  StringPacket* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const StringPacket& from);
  void MergeFrom(const StringPacket& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string str = 1;
  inline bool has_str() const;
  inline void clear_str();
  static const int kStrFieldNumber = 1;
  inline const ::std::string& str() const;
  inline void set_str(const ::std::string& value);
  inline void set_str(const char* value);
  inline void set_str(const char* value, size_t size);
  inline ::std::string* mutable_str();
  inline ::std::string* release_str();
  inline void set_allocated_str(::std::string* str);

  // @@protoc_insertion_point(class_scope:StringPacket)
 private:
  inline void set_has_str();
  inline void clear_has_str();

  ::google::protobuf::UnknownFieldSet _unknown_fields_;

  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::std::string* str_;
  friend void  protobuf_AddDesc_packet_2eproto();
  friend void protobuf_AssignDesc_packet_2eproto();
  friend void protobuf_ShutdownFile_packet_2eproto();

  void InitAsDefaultInstance();
  static StringPacket* default_instance_;
};
// ===================================================================


// ===================================================================

// EchoPacket

// required int32 id = 1;
inline bool EchoPacket::has_id() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void EchoPacket::set_has_id() {
  _has_bits_[0] |= 0x00000001u;
}
inline void EchoPacket::clear_has_id() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void EchoPacket::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 EchoPacket::id() const {
  // @@protoc_insertion_point(field_get:EchoPacket.id)
  return id_;
}
inline void EchoPacket::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:EchoPacket.id)
}

// required bytes name = 2;
inline bool EchoPacket::has_name() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void EchoPacket::set_has_name() {
  _has_bits_[0] |= 0x00000002u;
}
inline void EchoPacket::clear_has_name() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void EchoPacket::clear_name() {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_->clear();
  }
  clear_has_name();
}
inline const ::std::string& EchoPacket::name() const {
  // @@protoc_insertion_point(field_get:EchoPacket.name)
  return *name_;
}
inline void EchoPacket::set_name(const ::std::string& value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set:EchoPacket.name)
}
inline void EchoPacket::set_name(const char* value) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(value);
  // @@protoc_insertion_point(field_set_char:EchoPacket.name)
}
inline void EchoPacket::set_name(const void* value, size_t size) {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  name_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:EchoPacket.name)
}
inline ::std::string* EchoPacket::mutable_name() {
  set_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    name_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:EchoPacket.name)
  return name_;
}
inline ::std::string* EchoPacket::release_name() {
  clear_has_name();
  if (name_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = name_;
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void EchoPacket::set_allocated_name(::std::string* name) {
  if (name_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete name_;
  }
  if (name) {
    set_has_name();
    name_ = name;
  } else {
    clear_has_name();
    name_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:EchoPacket.name)
}

// -------------------------------------------------------------------

// StringPacket

// required string str = 1;
inline bool StringPacket::has_str() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void StringPacket::set_has_str() {
  _has_bits_[0] |= 0x00000001u;
}
inline void StringPacket::clear_has_str() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void StringPacket::clear_str() {
  if (str_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    str_->clear();
  }
  clear_has_str();
}
inline const ::std::string& StringPacket::str() const {
  // @@protoc_insertion_point(field_get:StringPacket.str)
  return *str_;
}
inline void StringPacket::set_str(const ::std::string& value) {
  set_has_str();
  if (str_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    str_ = new ::std::string;
  }
  str_->assign(value);
  // @@protoc_insertion_point(field_set:StringPacket.str)
}
inline void StringPacket::set_str(const char* value) {
  set_has_str();
  if (str_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    str_ = new ::std::string;
  }
  str_->assign(value);
  // @@protoc_insertion_point(field_set_char:StringPacket.str)
}
inline void StringPacket::set_str(const char* value, size_t size) {
  set_has_str();
  if (str_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    str_ = new ::std::string;
  }
  str_->assign(reinterpret_cast<const char*>(value), size);
  // @@protoc_insertion_point(field_set_pointer:StringPacket.str)
}
inline ::std::string* StringPacket::mutable_str() {
  set_has_str();
  if (str_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    str_ = new ::std::string;
  }
  // @@protoc_insertion_point(field_mutable:StringPacket.str)
  return str_;
}
inline ::std::string* StringPacket::release_str() {
  clear_has_str();
  if (str_ == &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    return NULL;
  } else {
    ::std::string* temp = str_;
    str_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
    return temp;
  }
}
inline void StringPacket::set_allocated_str(::std::string* str) {
  if (str_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete str_;
  }
  if (str) {
    set_has_str();
    str_ = str;
  } else {
    clear_has_str();
    str_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  }
  // @@protoc_insertion_point(field_set_allocated:StringPacket.str)
}


// @@protoc_insertion_point(namespace_scope)

#ifndef SWIG
namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::PACKET_TYPE> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::PACKET_TYPE>() {
  return ::PACKET_TYPE_descriptor();
}

}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#endif  // PROTOBUF_packet_2eproto__INCLUDED
