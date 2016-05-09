; Auto-generated. Do not edit!


(cl:in-package scarborough-msg)


;//! \htmlinclude Desired_Directions.msg.html

(cl:defclass <Desired_Directions> (roslisp-msg-protocol:ros-message)
  ((address
    :reader address
    :initarg :address
    :type cl:integer
    :initform 0)
   (value
    :reader value
    :initarg :value
    :type cl:integer
    :initform 0))
)

(cl:defclass Desired_Directions (<Desired_Directions>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Desired_Directions>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Desired_Directions)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name scarborough-msg:<Desired_Directions> is deprecated: use scarborough-msg:Desired_Directions instead.")))

(cl:ensure-generic-function 'address-val :lambda-list '(m))
(cl:defmethod address-val ((m <Desired_Directions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:address-val is deprecated.  Use scarborough-msg:address instead.")
  (address m))

(cl:ensure-generic-function 'value-val :lambda-list '(m))
(cl:defmethod value-val ((m <Desired_Directions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:value-val is deprecated.  Use scarborough-msg:value instead.")
  (value m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Desired_Directions>) ostream)
  "Serializes a message object of type '<Desired_Directions>"
  (cl:let* ((signed (cl:slot-value msg 'address)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'value)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Desired_Directions>) istream)
  "Deserializes a message object of type '<Desired_Directions>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'address) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'value) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Desired_Directions>)))
  "Returns string type for a message object of type '<Desired_Directions>"
  "scarborough/Desired_Directions")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Desired_Directions)))
  "Returns string type for a message object of type 'Desired_Directions"
  "scarborough/Desired_Directions")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Desired_Directions>)))
  "Returns md5sum for a message object of type '<Desired_Directions>"
  "f1d1f76242de856e3a44fa6454dab1b8")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Desired_Directions)))
  "Returns md5sum for a message object of type 'Desired_Directions"
  "f1d1f76242de856e3a44fa6454dab1b8")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Desired_Directions>)))
  "Returns full string definition for message of type '<Desired_Directions>"
  (cl:format cl:nil "int32 address~%int32 value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Desired_Directions)))
  "Returns full string definition for message of type 'Desired_Directions"
  (cl:format cl:nil "int32 address~%int32 value~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Desired_Directions>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Desired_Directions>))
  "Converts a ROS message object to a list"
  (cl:list 'Desired_Directions
    (cl:cons ':address (address msg))
    (cl:cons ':value (value msg))
))
