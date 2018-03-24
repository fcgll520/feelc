// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: lm.HelloWorld.proto

#ifndef PROTOBUF_lm_2eHelloWorld_2eproto__INCLUDED
#define PROTOBUF_lm_2eHelloWorld_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3003000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3003000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace lm {
class HelloWorld;
class HelloWorldDefaultTypeInternal;
extern HelloWorldDefaultTypeInternal _HelloWorld_default_instance_;
}  // namespace lm

namespace lm {

namespace protobuf_lm_2eHelloWorld_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static void InitDefaultsImpl();
  static void Shutdown();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_lm_2eHelloWorld_2eproto

// ===================================================================

class HelloWorld : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:lm.HelloWorld) */ {
 public:
  HelloWorld();
  virtual ~HelloWorld();

  HelloWorld(const HelloWorld& from);

  inline HelloWorld& operator=(const HelloWorld& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const HelloWorld& default_instance();

  static inline const HelloWorld* internal_default_instance() {
    return reinterpret_cast<const HelloWorld*>(
               &_HelloWorld_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(HelloWorld* other);

  // implements Message ----------------------------------------------

  inline HelloWorld* New() const PROTOBUF_FINAL { return New(NULL); }

  HelloWorld* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const HelloWorld& from);
  void MergeFrom(const HelloWorld& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(HelloWorld* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // required string str = 2;
  bool has_str() const;
  void clear_str();
  static const int kStrFieldNumber = 2;
  const ::std::string& str() const;
  void set_str(const ::std::string& value);
  #if LANG_CXX11
  void set_str(::std::string&& value);
  #endif
  void set_str(const char* value);
  void set_str(const char* value, size_t size);
  ::std::string* mutable_str();
  ::std::string* release_str();
  void set_allocated_str(::std::string* str);

  // required int32 id = 1;
  bool has_id() const;
  void clear_id();
  static const int kIdFieldNumber = 1;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // required int32 opt = 3;
  bool has_opt() const;
  void clear_opt();
  static const int kOptFieldNumber = 3;
  ::google::protobuf::int32 opt() const;
  void set_opt(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:lm.HelloWorld)
 private:
  void set_has_id();
  void clear_has_id();
  void set_has_str();
  void clear_has_str();
  void set_has_opt();
  void clear_has_opt();

  // helper for ByteSizeLong()
  size_t RequiredFieldsByteSizeFallback() const;

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::HasBits<1> _has_bits_;
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr str_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 opt_;
  friend struct protobuf_lm_2eHelloWorld_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// HelloWorld

// required int32 id = 1;
inline bool HelloWorld::has_id() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void HelloWorld::set_has_id() {
  _has_bits_[0] |= 0x00000002u;
}
inline void HelloWorld::clear_has_id() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void HelloWorld::clear_id() {
  id_ = 0;
  clear_has_id();
}
inline ::google::protobuf::int32 HelloWorld::id() const {
  // @@protoc_insertion_point(field_get:lm.HelloWorld.id)
  return id_;
}
inline void HelloWorld::set_id(::google::protobuf::int32 value) {
  set_has_id();
  id_ = value;
  // @@protoc_insertion_point(field_set:lm.HelloWorld.id)
}

// required string str = 2;
inline bool HelloWorld::has_str() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void HelloWorld::set_has_str() {
  _has_bits_[0] |= 0x00000001u;
}
inline void HelloWorld::clear_has_str() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void HelloWorld::clear_str() {
  str_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_str();
}
inline const ::std::string& HelloWorld::str() const {
  // @@protoc_insertion_point(field_get:lm.HelloWorld.str)
  return str_.GetNoArena();
}
inline void HelloWorld::set_str(const ::std::string& value) {
  set_has_str();
  str_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:lm.HelloWorld.str)
}
#if LANG_CXX11
inline void HelloWorld::set_str(::std::string&& value) {
  set_has_str();
  str_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:lm.HelloWorld.str)
}
#endif
inline void HelloWorld::set_str(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  set_has_str();
  str_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:lm.HelloWorld.str)
}
inline void HelloWorld::set_str(const char* value, size_t size) {
  set_has_str();
  str_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:lm.HelloWorld.str)
}
inline ::std::string* HelloWorld::mutable_str() {
  set_has_str();
  // @@protoc_insertion_point(field_mutable:lm.HelloWorld.str)
  return str_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* HelloWorld::release_str() {
  // @@protoc_insertion_point(field_release:lm.HelloWorld.str)
  clear_has_str();
  return str_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void HelloWorld::set_allocated_str(::std::string* str) {
  if (str != NULL) {
    set_has_str();
  } else {
    clear_has_str();
  }
  str_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), str);
  // @@protoc_insertion_point(field_set_allocated:lm.HelloWorld.str)
}

// required int32 opt = 3;
inline bool HelloWorld::has_opt() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void HelloWorld::set_has_opt() {
  _has_bits_[0] |= 0x00000004u;
}
inline void HelloWorld::clear_has_opt() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void HelloWorld::clear_opt() {
  opt_ = 0;
  clear_has_opt();
}
inline ::google::protobuf::int32 HelloWorld::opt() const {
  // @@protoc_insertion_point(field_get:lm.HelloWorld.opt)
  return opt_;
}
inline void HelloWorld::set_opt(::google::protobuf::int32 value) {
  set_has_opt();
  opt_ = value;
  // @@protoc_insertion_point(field_set:lm.HelloWorld.opt)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS

// @@protoc_insertion_point(namespace_scope)


}  // namespace lm

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_lm_2eHelloWorld_2eproto__INCLUDED
