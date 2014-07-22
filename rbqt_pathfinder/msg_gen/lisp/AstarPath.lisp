; Auto-generated. Do not edit!


(cl:in-package rbqt_pathfinder-msg)


;//! \htmlinclude AstarPath.msg.html

(cl:defclass <AstarPath> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (path
    :reader path
    :initarg :path
    :type nav_msgs-msg:Path
    :initform (cl:make-instance 'nav_msgs-msg:Path)))
)

(cl:defclass AstarPath (<AstarPath>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AstarPath>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AstarPath)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbqt_pathfinder-msg:<AstarPath> is deprecated: use rbqt_pathfinder-msg:AstarPath instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <AstarPath>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbqt_pathfinder-msg:id-val is deprecated.  Use rbqt_pathfinder-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'path-val :lambda-list '(m))
(cl:defmethod path-val ((m <AstarPath>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbqt_pathfinder-msg:path-val is deprecated.  Use rbqt_pathfinder-msg:path instead.")
  (path m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AstarPath>) ostream)
  "Serializes a message object of type '<AstarPath>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'path) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AstarPath>) istream)
  "Deserializes a message object of type '<AstarPath>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'path) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AstarPath>)))
  "Returns string type for a message object of type '<AstarPath>"
  "rbqt_pathfinder/AstarPath")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AstarPath)))
  "Returns string type for a message object of type 'AstarPath"
  "rbqt_pathfinder/AstarPath")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AstarPath>)))
  "Returns md5sum for a message object of type '<AstarPath>"
  "14ff3ce65e927005eea9f8e966ad807f")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AstarPath)))
  "Returns md5sum for a message object of type 'AstarPath"
  "14ff3ce65e927005eea9f8e966ad807f")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AstarPath>)))
  "Returns full string definition for message of type '<AstarPath>"
  (cl:format cl:nil "int16 id~%nav_msgs/Path path~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AstarPath)))
  "Returns full string definition for message of type 'AstarPath"
  (cl:format cl:nil "int16 id~%nav_msgs/Path path~%================================================================================~%MSG: nav_msgs/Path~%#An array of poses that represents a Path for a robot to follow~%Header header~%geometry_msgs/PoseStamped[] poses~%~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.secs: seconds (stamp_secs) since epoch~%# * stamp.nsecs: nanoseconds since stamp_secs~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%# 0: no frame~%# 1: global frame~%string frame_id~%~%================================================================================~%MSG: geometry_msgs/PoseStamped~%# A Pose with reference coordinate frame and timestamp~%Header header~%Pose pose~%~%================================================================================~%MSG: geometry_msgs/Pose~%# A representation of pose in free space, composed of postion and orientation. ~%Point position~%Quaternion orientation~%~%================================================================================~%MSG: geometry_msgs/Point~%# This contains the position of a point in free space~%float64 x~%float64 y~%float64 z~%~%================================================================================~%MSG: geometry_msgs/Quaternion~%# This represents an orientation in free space in quaternion form.~%~%float64 x~%float64 y~%float64 z~%float64 w~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AstarPath>))
  (cl:+ 0
     2
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'path))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AstarPath>))
  "Converts a ROS message object to a list"
  (cl:list 'AstarPath
    (cl:cons ':id (id msg))
    (cl:cons ':path (path msg))
))
