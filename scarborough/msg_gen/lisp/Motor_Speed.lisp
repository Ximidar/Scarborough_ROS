; Auto-generated. Do not edit!


(cl:in-package scarborough-msg)


;//! \htmlinclude Motor_Speed.msg.html

(cl:defclass <Motor_Speed> (roslisp-msg-protocol:ros-message)
  ((motor
    :reader motor
    :initarg :motor
    :type (cl:vector cl:integer)
   :initform (cl:make-array 6 :element-type 'cl:integer :initial-element 0)))
)

(cl:defclass Motor_Speed (<Motor_Speed>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Motor_Speed>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Motor_Speed)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name scarborough-msg:<Motor_Speed> is deprecated: use scarborough-msg:Motor_Speed instead.")))

(cl:ensure-generic-function 'motor-val :lambda-list '(m))
(cl:defmethod motor-val ((m <Motor_Speed>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:motor-val is deprecated.  Use scarborough-msg:motor instead.")
  (motor m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Motor_Speed>) ostream)
  "Serializes a message object of type '<Motor_Speed>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let* ((signed ele) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    ))
   (cl:slot-value msg 'motor))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Motor_Speed>) istream)
  "Deserializes a message object of type '<Motor_Speed>"
  (cl:setf (cl:slot-value msg 'motor) (cl:make-array 6))
  (cl:let ((vals (cl:slot-value msg 'motor)))
    (cl:dotimes (i 6)
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:aref vals i) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Motor_Speed>)))
  "Returns string type for a message object of type '<Motor_Speed>"
  "scarborough/Motor_Speed")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Motor_Speed)))
  "Returns string type for a message object of type 'Motor_Speed"
  "scarborough/Motor_Speed")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Motor_Speed>)))
  "Returns md5sum for a message object of type '<Motor_Speed>"
  "f5f634e2dbc972b6b32d53a35c45b514")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Motor_Speed)))
  "Returns md5sum for a message object of type 'Motor_Speed"
  "f5f634e2dbc972b6b32d53a35c45b514")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Motor_Speed>)))
  "Returns full string definition for message of type '<Motor_Speed>"
  (cl:format cl:nil "int32[6] motor~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Motor_Speed)))
  "Returns full string definition for message of type 'Motor_Speed"
  (cl:format cl:nil "int32[6] motor~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Motor_Speed>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'motor) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Motor_Speed>))
  "Converts a ROS message object to a list"
  (cl:list 'Motor_Speed
    (cl:cons ':motor (motor msg))
))
