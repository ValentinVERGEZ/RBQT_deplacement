; Auto-generated. Do not edit!


(cl:in-package rbqt_pathfinder-srv)


;//! \htmlinclude GeneratePath-request.msg.html

(cl:defclass <GeneratePath-request> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (Arrivee
    :reader Arrivee
    :initarg :Arrivee
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (Depart
    :reader Depart
    :initarg :Depart
    :type geometry_msgs-msg:Pose
    :initform (cl:make-instance 'geometry_msgs-msg:Pose))
   (utilisePositionOdometry
    :reader utilisePositionOdometry
    :initarg :utilisePositionOdometry
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GeneratePath-request (<GeneratePath-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GeneratePath-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GeneratePath-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbqt_pathfinder-srv:<GeneratePath-request> is deprecated: use rbqt_pathfinder-srv:GeneratePath-request instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <GeneratePath-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbqt_pathfinder-srv:id-val is deprecated.  Use rbqt_pathfinder-srv:id instead.")
  (id m))

(cl:ensure-generic-function 'Arrivee-val :lambda-list '(m))
(cl:defmethod Arrivee-val ((m <GeneratePath-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbqt_pathfinder-srv:Arrivee-val is deprecated.  Use rbqt_pathfinder-srv:Arrivee instead.")
  (Arrivee m))

(cl:ensure-generic-function 'Depart-val :lambda-list '(m))
(cl:defmethod Depart-val ((m <GeneratePath-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbqt_pathfinder-srv:Depart-val is deprecated.  Use rbqt_pathfinder-srv:Depart instead.")
  (Depart m))

(cl:ensure-generic-function 'utilisePositionOdometry-val :lambda-list '(m))
(cl:defmethod utilisePositionOdometry-val ((m <GeneratePath-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbqt_pathfinder-srv:utilisePositionOdometry-val is deprecated.  Use rbqt_pathfinder-srv:utilisePositionOdometry instead.")
  (utilisePositionOdometry m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GeneratePath-request>) ostream)
  "Serializes a message object of type '<GeneratePath-request>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'Arrivee) ostream)
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'Depart) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'utilisePositionOdometry) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GeneratePath-request>) istream)
  "Deserializes a message object of type '<GeneratePath-request>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'Arrivee) istream)
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'Depart) istream)
    (cl:setf (cl:slot-value msg 'utilisePositionOdometry) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GeneratePath-request>)))
  "Returns string type for a service object of type '<GeneratePath-request>"
  "rbqt_pathfinder/GeneratePathRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GeneratePath-request)))
  "Returns string type for a service object of type 'GeneratePath-request"
  "rbqt_pathfinder/GeneratePathRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GeneratePath-request>)))
  "Returns md5sum for a message object of type '<GeneratePath-request>"
  "c87f6c6dcb2875066c4354235cdff733")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GeneratePath-request)))
  "Returns md5sum for a message object of type 'GeneratePath-request"
  "c87f6c6dcb2875066c4354235cdff733")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GeneratePath-request>)))
  "Returns full string definition for message of type '<GeneratePath-request>"
  (cl:format cl:nil "int16  id~%geometry_msgs/Pose  Arrivee~%geometry_msgs/Pose  Depart~%bool    utilisePositionOdometry~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GeneratePath-request)))
  "Returns full string definition for message of type 'GeneratePath-request"
  (cl:format cl:nil "int16  id~%geometry_msgs/Pose  Arrivee~%geometry_msgs/Pose  Depart~%bool    utilisePositionOdometry~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GeneratePath-request>))
  (cl:+ 0
     2
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'Arrivee))
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'Depart))
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GeneratePath-request>))
  "Converts a ROS message object to a list"
  (cl:list 'GeneratePath-request
    (cl:cons ':id (id msg))
    (cl:cons ':Arrivee (Arrivee msg))
    (cl:cons ':Depart (Depart msg))
    (cl:cons ':utilisePositionOdometry (utilisePositionOdometry msg))
))
;//! \htmlinclude GeneratePath-response.msg.html

(cl:defclass <GeneratePath-response> (roslisp-msg-protocol:ros-message)
  ((requeteAcceptee
    :reader requeteAcceptee
    :initarg :requeteAcceptee
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass GeneratePath-response (<GeneratePath-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <GeneratePath-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'GeneratePath-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbqt_pathfinder-srv:<GeneratePath-response> is deprecated: use rbqt_pathfinder-srv:GeneratePath-response instead.")))

(cl:ensure-generic-function 'requeteAcceptee-val :lambda-list '(m))
(cl:defmethod requeteAcceptee-val ((m <GeneratePath-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbqt_pathfinder-srv:requeteAcceptee-val is deprecated.  Use rbqt_pathfinder-srv:requeteAcceptee instead.")
  (requeteAcceptee m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <GeneratePath-response>) ostream)
  "Serializes a message object of type '<GeneratePath-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'requeteAcceptee) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <GeneratePath-response>) istream)
  "Deserializes a message object of type '<GeneratePath-response>"
    (cl:setf (cl:slot-value msg 'requeteAcceptee) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<GeneratePath-response>)))
  "Returns string type for a service object of type '<GeneratePath-response>"
  "rbqt_pathfinder/GeneratePathResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GeneratePath-response)))
  "Returns string type for a service object of type 'GeneratePath-response"
  "rbqt_pathfinder/GeneratePathResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<GeneratePath-response>)))
  "Returns md5sum for a message object of type '<GeneratePath-response>"
  "c87f6c6dcb2875066c4354235cdff733")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'GeneratePath-response)))
  "Returns md5sum for a message object of type 'GeneratePath-response"
  "c87f6c6dcb2875066c4354235cdff733")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<GeneratePath-response>)))
  "Returns full string definition for message of type '<GeneratePath-response>"
  (cl:format cl:nil "bool    requeteAcceptee~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'GeneratePath-response)))
  "Returns full string definition for message of type 'GeneratePath-response"
  (cl:format cl:nil "bool    requeteAcceptee~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <GeneratePath-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <GeneratePath-response>))
  "Converts a ROS message object to a list"
  (cl:list 'GeneratePath-response
    (cl:cons ':requeteAcceptee (requeteAcceptee msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'GeneratePath)))
  'GeneratePath-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'GeneratePath)))
  'GeneratePath-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'GeneratePath)))
  "Returns string type for a service object of type '<GeneratePath>"
  "rbqt_pathfinder/GeneratePath")