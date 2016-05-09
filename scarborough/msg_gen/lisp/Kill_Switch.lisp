; Auto-generated. Do not edit!


(cl:in-package scarborough-msg)


;//! \htmlinclude Kill_Switch.msg.html

(cl:defclass <Kill_Switch> (roslisp-msg-protocol:ros-message)
  ((killed
    :reader killed
    :initarg :killed
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Kill_Switch (<Kill_Switch>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Kill_Switch>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Kill_Switch)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name scarborough-msg:<Kill_Switch> is deprecated: use scarborough-msg:Kill_Switch instead.")))

(cl:ensure-generic-function 'killed-val :lambda-list '(m))
(cl:defmethod killed-val ((m <Kill_Switch>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader scarborough-msg:killed-val is deprecated.  Use scarborough-msg:killed instead.")
  (killed m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Kill_Switch>) ostream)
  "Serializes a message object of type '<Kill_Switch>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'killed) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Kill_Switch>) istream)
  "Deserializes a message object of type '<Kill_Switch>"
    (cl:setf (cl:slot-value msg 'killed) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Kill_Switch>)))
  "Returns string type for a message object of type '<Kill_Switch>"
  "scarborough/Kill_Switch")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Kill_Switch)))
  "Returns string type for a message object of type 'Kill_Switch"
  "scarborough/Kill_Switch")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Kill_Switch>)))
  "Returns md5sum for a message object of type '<Kill_Switch>"
  "b9ba423f2d72a3fad589a8f863963a01")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Kill_Switch)))
  "Returns md5sum for a message object of type 'Kill_Switch"
  "b9ba423f2d72a3fad589a8f863963a01")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Kill_Switch>)))
  "Returns full string definition for message of type '<Kill_Switch>"
  (cl:format cl:nil "bool killed~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Kill_Switch)))
  "Returns full string definition for message of type 'Kill_Switch"
  (cl:format cl:nil "bool killed~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Kill_Switch>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Kill_Switch>))
  "Converts a ROS message object to a list"
  (cl:list 'Kill_Switch
    (cl:cons ':killed (killed msg))
))
