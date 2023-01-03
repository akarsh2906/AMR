; Auto-generated. Do not edit!


(cl:in-package motor_controller-msg)


;//! \htmlinclude pfd.msg.html

(cl:defclass <pfd> (roslisp-msg-protocol:ros-message)
  ((distance
    :reader distance
    :initarg :distance
    :type cl:fixnum
    :initform 0)
   (angle
    :reader angle
    :initarg :angle
    :type cl:fixnum
    :initform 0)
   (status
    :reader status
    :initarg :status
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass pfd (<pfd>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <pfd>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'pfd)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name motor_controller-msg:<pfd> is deprecated: use motor_controller-msg:pfd instead.")))

(cl:ensure-generic-function 'distance-val :lambda-list '(m))
(cl:defmethod distance-val ((m <pfd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_controller-msg:distance-val is deprecated.  Use motor_controller-msg:distance instead.")
  (distance m))

(cl:ensure-generic-function 'angle-val :lambda-list '(m))
(cl:defmethod angle-val ((m <pfd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_controller-msg:angle-val is deprecated.  Use motor_controller-msg:angle instead.")
  (angle m))

(cl:ensure-generic-function 'status-val :lambda-list '(m))
(cl:defmethod status-val ((m <pfd>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader motor_controller-msg:status-val is deprecated.  Use motor_controller-msg:status instead.")
  (status m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <pfd>) ostream)
  "Serializes a message object of type '<pfd>"
  (cl:let* ((signed (cl:slot-value msg 'distance)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'angle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 256) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'status) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <pfd>) istream)
  "Deserializes a message object of type '<pfd>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'distance) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'angle) (cl:if (cl:< unsigned 128) unsigned (cl:- unsigned 256))))
    (cl:setf (cl:slot-value msg 'status) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<pfd>)))
  "Returns string type for a message object of type '<pfd>"
  "motor_controller/pfd")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'pfd)))
  "Returns string type for a message object of type 'pfd"
  "motor_controller/pfd")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<pfd>)))
  "Returns md5sum for a message object of type '<pfd>"
  "b2931a42170a1095d7904fa2881d4ca7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'pfd)))
  "Returns md5sum for a message object of type 'pfd"
  "b2931a42170a1095d7904fa2881d4ca7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<pfd>)))
  "Returns full string definition for message of type '<pfd>"
  (cl:format cl:nil "int8 distance~%int8 angle~%bool status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'pfd)))
  "Returns full string definition for message of type 'pfd"
  (cl:format cl:nil "int8 distance~%int8 angle~%bool status~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <pfd>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <pfd>))
  "Converts a ROS message object to a list"
  (cl:list 'pfd
    (cl:cons ':distance (distance msg))
    (cl:cons ':angle (angle msg))
    (cl:cons ':status (status msg))
))
