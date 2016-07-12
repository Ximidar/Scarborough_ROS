; Auto-generated. Do not edit!


(cl:in-package scarborough-msg)


;//! \htmlinclude Desired_Directions.msg.html

(cl:defclass <Desired_Directions> (roslisp-msg-protocol:ros-message)
  ((rotation
    :reader rotation
    :initarg :rotation
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (throttle
    :reader throttle
    :initarg :throttle
    :type cl:integer
    :initform 0)
   (depth
    :reader depth
    :initarg :depth
    :type cl:float
    :initform 0.0))
)

(cl:defclass Desired_Directions (<Desired_Directions>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Desired_Directions>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Desired_Directions)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name scarborough-msg:<Desired_Directions> is deprecated: use scarborough-msg:Desired_Directions instead.")))

(cl:ensure-generic-function 'rotation-val :lambda-list '(m))
(cl:defmethod rotation-val ((m <Desired_Directions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:rotation-val is deprecated.  Use scarborough-msg:rotation instead.")
  (rotation m))

(cl:ensure-generic-function 'throttle-val :lambda-list '(m))
(cl:defmethod throttle-val ((m <Desired_Directions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:throttle-val is deprecated.  Use scarborough-msg:throttle instead.")
  (throttle m))

(cl:ensure-generic-function 'depth-val :lambda-list '(m))
(cl:defmethod depth-val ((m <Desired_Directions>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:depth-val is deprecated.  Use scarborough-msg:depth instead.")
  (depth m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Desired_Directions>) ostream)
  "Serializes a message object of type '<Desired_Directions>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'rotation))
  (cl:let* ((signed (cl:slot-value msg 'throttle)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'depth))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Desired_Directions>) istream)
  "Deserializes a message object of type '<Desired_Directions>"
  (cl:setf (cl:slot-value msg 'rotation) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'rotation)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'throttle) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'depth) (roslisp-utils:decode-single-float-bits bits)))
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
  "b52e1a589c56fcea3b3260406f15fe61")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Desired_Directions)))
  "Returns md5sum for a message object of type 'Desired_Directions"
  "b52e1a589c56fcea3b3260406f15fe61")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Desired_Directions>)))
  "Returns full string definition for message of type '<Desired_Directions>"
  (cl:format cl:nil "float32[3] rotation~%int32 throttle~%float32 depth~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Desired_Directions)))
  "Returns full string definition for message of type 'Desired_Directions"
  (cl:format cl:nil "float32[3] rotation~%int32 throttle~%float32 depth~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Desired_Directions>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'rotation) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Desired_Directions>))
  "Converts a ROS message object to a list"
  (cl:list 'Desired_Directions
    (cl:cons ':rotation (rotation msg))
    (cl:cons ':throttle (throttle msg))
    (cl:cons ':depth (depth msg))
))
