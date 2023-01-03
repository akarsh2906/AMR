// Auto-generated. Do not edit!

// (in-package motor_controller.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class pfd {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.distance = null;
      this.angle = null;
    }
    else {
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = 0;
      }
      if (initObj.hasOwnProperty('angle')) {
        this.angle = initObj.angle
      }
      else {
        this.angle = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type pfd
    // Serialize message field [distance]
    bufferOffset = _serializer.int8(obj.distance, buffer, bufferOffset);
    // Serialize message field [angle]
    bufferOffset = _serializer.int8(obj.angle, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type pfd
    let len;
    let data = new pfd(null);
    // Deserialize message field [distance]
    data.distance = _deserializer.int8(buffer, bufferOffset);
    // Deserialize message field [angle]
    data.angle = _deserializer.int8(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 2;
  }

  static datatype() {
    // Returns string type for a message object
    return 'motor_controller/pfd';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9f2f798034d31200675698594323e8ee';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int8 distance
    int8 angle
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new pfd(null);
    if (msg.distance !== undefined) {
      resolved.distance = msg.distance;
    }
    else {
      resolved.distance = 0
    }

    if (msg.angle !== undefined) {
      resolved.angle = msg.angle;
    }
    else {
      resolved.angle = 0
    }

    return resolved;
    }
};

module.exports = pfd;
