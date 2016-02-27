; Auto-generated. Do not edit!


(cl:in-package scarborough-msg)


;//! \htmlinclude YPR.msg.html

(cl:defclass <YPR> (roslisp-msg-protocol:ros-message)
  ((YPR
    :reader YPR
    :initarg :YPR
    :type (cl:vector cl:float)
   :initform (cl:make-array 3 :element-type 'cl:float :initial-element 0.0)))
)

(cl:defclass YPR (<YPR>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <YPR>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'YPR)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name scarborough-msg:<YPR> is deprecated: use scarborough-msg:YPR instead.")))

(cl:ensure-generic-function 'YPR-val :lambda-list '(m))
(cl:defmethod YPR-val ((m <YPR>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:YPR-val is deprecated.  Use scarborough-msg:YPR instead.")
  (YPR m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <YPR>) ostream)
  "Serializes a message object of type '<YPR>"
  (cl:map cl:nil #'(cl:lambda (ele) (cl:let ((bits (roslisp-utils:encode-double-float-bits ele)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream)))
   (cl:slot-value msg 'YPR))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <YPR>) istream)
  "Deserializes a message object of type '<YPR>"
  (cl:setf (cl:slot-value msg 'YPR) (cl:make-array 3))
  (cl:let ((vals (cl:slot-value msg 'YPR)))
    (cl:dotimes (i 3)
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:aref vals i) (roslisp-utils:decode-double-float-bits bits)))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<YPR>)))
  "Returns string type for a message object of type '<YPR>"
  "scarborough/YPR")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'YPR)))
  "Returns string type for a message object of type 'YPR"
  "scarborough/YPR")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<YPR>)))
  "Returns md5sum for a message object of type '<YPR>"
  "932fd5a1b0efdafe2ac005ed95f2acb3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'YPR)))
  "Returns md5sum for a message object of type 'YPR"
  "932fd5a1b0efdafe2ac005ed95f2acb3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<YPR>)))
  "Returns full string definition for message of type '<YPR>"
  (cl:format cl:nil "float64[3] YPR~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'YPR)))
  "Returns full string definition for message of type 'YPR"
  (cl:format cl:nil "float64[3] YPR~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <YPR>))
  (cl:+ 0
     0 (cl:reduce #'cl:+ (cl:slot-value msg 'YPR) :key #'(cl:lambda (ele) (cl:declare (cl:ignorable ele)) (cl:+ 8)))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <YPR>))
  "Converts a ROS message object to a list"
  (cl:list 'YPR
    (cl:cons ':YPR (YPR msg))
))
