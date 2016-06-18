; Auto-generated. Do not edit!


(cl:in-package scarborough-msg)


;//! \htmlinclude Depth.msg.html

(cl:defclass <Depth> (roslisp-msg-protocol:ros-message)
  ((depth
    :reader depth
    :initarg :depth
    :type cl:float
    :initform 0.0))
)

(cl:defclass Depth (<Depth>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Depth>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Depth)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name scarborough-msg:<Depth> is deprecated: use scarborough-msg:Depth instead.")))

(cl:ensure-generic-function 'depth-val :lambda-list '(m))
(cl:defmethod depth-val ((m <Depth>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:depth-val is deprecated.  Use scarborough-msg:depth instead.")
  (depth m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Depth>) ostream)
  "Serializes a message object of type '<Depth>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'depth))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Depth>) istream)
  "Deserializes a message object of type '<Depth>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'depth) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Depth>)))
  "Returns string type for a message object of type '<Depth>"
  "scarborough/Depth")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Depth)))
  "Returns string type for a message object of type 'Depth"
  "scarborough/Depth")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Depth>)))
  "Returns md5sum for a message object of type '<Depth>"
  "6deb06b7b7183f5581b3362a0cb413b7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Depth)))
  "Returns md5sum for a message object of type 'Depth"
  "6deb06b7b7183f5581b3362a0cb413b7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Depth>)))
  "Returns full string definition for message of type '<Depth>"
  (cl:format cl:nil "float32 depth~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Depth)))
  "Returns full string definition for message of type 'Depth"
  (cl:format cl:nil "float32 depth~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Depth>))
  (cl:+ 0
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Depth>))
  "Converts a ROS message object to a list"
  (cl:list 'Depth
    (cl:cons ':depth (depth msg))
))
