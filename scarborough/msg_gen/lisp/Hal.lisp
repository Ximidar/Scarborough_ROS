; Auto-generated. Do not edit!


(cl:in-package scarborough-msg)


;//! \htmlinclude Hal.msg.html

(cl:defclass <Hal> (roslisp-msg-protocol:ros-message)
  ((state
    :reader state
    :initarg :state
    :type cl:string
    :initform ""))
)

(cl:defclass Hal (<Hal>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Hal>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Hal)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name scarborough-msg:<Hal> is deprecated: use scarborough-msg:Hal instead.")))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <Hal>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:state-val is deprecated.  Use scarborough-msg:state instead.")
  (state m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Hal>) ostream)
  "Serializes a message object of type '<Hal>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'state))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Hal>) istream)
  "Deserializes a message object of type '<Hal>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'state) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'state) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Hal>)))
  "Returns string type for a message object of type '<Hal>"
  "scarborough/Hal")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Hal)))
  "Returns string type for a message object of type 'Hal"
  "scarborough/Hal")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Hal>)))
  "Returns md5sum for a message object of type '<Hal>"
  "af6d3a99f0fbeb66d3248fa4b3e675fb")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Hal)))
  "Returns md5sum for a message object of type 'Hal"
  "af6d3a99f0fbeb66d3248fa4b3e675fb")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Hal>)))
  "Returns full string definition for message of type '<Hal>"
  (cl:format cl:nil "string state~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Hal)))
  "Returns full string definition for message of type 'Hal"
  (cl:format cl:nil "string state~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Hal>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'state))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Hal>))
  "Converts a ROS message object to a list"
  (cl:list 'Hal
    (cl:cons ':state (state msg))
))
