// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from mirs_msgs:srv/SimpleCommand.idl
// generated code does not contain a copyright notice

#ifndef MIRS_MSGS__SRV__DETAIL__SIMPLE_COMMAND__STRUCT_H_
#define MIRS_MSGS__SRV__DETAIL__SIMPLE_COMMAND__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in srv/SimpleCommand in the package mirs_msgs.
typedef struct mirs_msgs__srv__SimpleCommand_Request
{
  uint8_t structure_needs_at_least_one_member;
} mirs_msgs__srv__SimpleCommand_Request;

// Struct for a sequence of mirs_msgs__srv__SimpleCommand_Request.
typedef struct mirs_msgs__srv__SimpleCommand_Request__Sequence
{
  mirs_msgs__srv__SimpleCommand_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mirs_msgs__srv__SimpleCommand_Request__Sequence;


// Constants defined in the message

/// Struct defined in srv/SimpleCommand in the package mirs_msgs.
typedef struct mirs_msgs__srv__SimpleCommand_Response
{
  bool success;
} mirs_msgs__srv__SimpleCommand_Response;

// Struct for a sequence of mirs_msgs__srv__SimpleCommand_Response.
typedef struct mirs_msgs__srv__SimpleCommand_Response__Sequence
{
  mirs_msgs__srv__SimpleCommand_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} mirs_msgs__srv__SimpleCommand_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // MIRS_MSGS__SRV__DETAIL__SIMPLE_COMMAND__STRUCT_H_
