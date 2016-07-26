; Auto-generated. Do not edit!


(cl:in-package scarborough-msg)


;//! \htmlinclude Vision_objects.msg.html

(cl:defclass <Vision_objects> (roslisp-msg-protocol:ros-message)
  ((object
    :reader object
    :initarg :object
    :type cl:string
    :initform "")
   (color
    :reader color
    :initarg :color
    :type cl:string
    :initform "")
   (rotation
    :reader rotation
    :initarg :rotation
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0))
   (depth
    :reader depth
    :initarg :depth
    :type cl:float
    :initform 0.0)
   (in_sight
    :reader in_sight
    :initarg :in_sight
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Vision_objects (<Vision_objects>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Vision_objects>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Vision_objects)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name scarborough-msg:<Vision_objects> is deprecated: use scarborough-msg:Vision_objects instead.")))

(cl:ensure-generic-function 'object-val :lambda-list '(m))
(cl:defmethod object-val ((m <Vision_objects>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:object-val is deprecated.  Use scarborough-msg:object instead.")
  (object m))

(cl:ensure-generic-function 'color-val :lambda-list '(m))
(cl:defmethod color-val ((m <Vision_objects>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:color-val is deprecated.  Use scarborough-msg:color instead.")
  (color m))

(cl:ensure-generic-function 'rotation-val :lambda-list '(m))
(cl:defmethod rotation-val ((m <Vision_objects>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:rotation-val is deprecated.  Use scarborough-msg:rotation instead.")
  (rotation m))

(cl:ensure-generic-function 'depth-val :lambda-list '(m))
(cl:defmethod depth-val ((m <Vision_objects>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:depth-val is deprecated.  Use scarborough-msg:depth instead.")
  (depth m))

(cl:ensure-generic-function 'in_sight-val :lambda-list '(m))
(cl:defmethod in_sight-val ((m <Vision_objects>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:in_sight-val is deprecated.  Use scarborough-msg:in_sight instead.")
  (in_sight m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Vision_objects>) ostream)
  "Serializes a message object of type '<Vision_objects>"
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'object))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'object))
  (cl:let ((__ros_str_len (cl:length (cl:slot-value msg 'color))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) __ros_str_len) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) __ros_str_len) ostream))
  (cl:map cl:nil #'(cl:lambda (c) (cl:write-byte (cl:char-code c) ostream)) (cl:slot-value msg 'color))
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-single-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)))
   (cl:slot-value msg 'rotation))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'depth))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'in_sight) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Vision_objects>) istream)
  "Deserializes a message object of type '<Vision_objects>"
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'object) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'object) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
    (cl:let ((__ros_str_len 0))
      (cl:setf (cl:ldb (cl:byte 8 0) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) __ros_str_len) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'color) (cl:make-string __ros_str_len))
      (cl:dotimes (__ros_str_idx __ros_str_len msg)
        (cl:setf (cl:char (cl:slot-value msg 'color) __ros_str_idx) (cl:code-char (cl:read-byte istream)))))
  (cl:setf (cl:slot-value msg 'rotation) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'rotation)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-single-float-bits bits)))))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'depth) (roslisp-utils:decode-single-float-bits bits)))
    (cl:setf (cl:slot-value msg 'in_sight) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Vision_objects>)))
  "Returns string type for a message object of type '<Vision_objects>"
  "scarborough/Vision_objects")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Vision_objects)))
  "Returns string type for a message object of type 'Vision_objects"
  "scarborough/Vision_objects")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Vision_objects>)))
  "Returns md5sum for a message object of type '<Vision_objects>"
  "cc757b2b6dad7807a7e68ec68f3c3641")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Vision_objects)))
  "Returns md5sum for a message object of type 'Vision_objects"
  "cc757b2b6dad7807a7e68ec68f3c3641")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Vision_objects>)))
  "Returns full string definition for message of type '<Vision_objects>"
  (cl:format cl:nil "string object~%string color~%float32[3] rotation~%float32 depth~%bool in_sight~% ~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Vision_objects)))
  "Returns full string definition for message of type 'Vision_objects"
  (cl:format cl:nil "string object~%string color~%float32[3] rotation~%float32 depth~%bool in_sight~% ~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Vision_objects>))
  (cl:+ 0
     4 (cl:length (cl:slot-value msg 'object))
     4 (cl:length (cl:slot-value msg 'color))
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'rotation) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 4)))
     4
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Vision_objects>))
  "Converts a ROS message object to a list"
  (cl:list 'Vision_objects
    (cl:cons ':object (object msg))
    (cl:cons ':color (color msg))
    (cl:cons ':rotation (rotation msg))
    (cl:cons ':depth (depth msg))
    (cl:cons ':in_sight (in_sight msg))
))
