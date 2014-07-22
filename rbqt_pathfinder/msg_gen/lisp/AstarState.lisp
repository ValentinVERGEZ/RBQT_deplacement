; Auto-generated. Do not edit!


(cl:in-package rbqt_pathfinder-msg)


;//! \htmlinclude AstarState.msg.html

(cl:defclass <AstarState> (roslisp-msg-protocol:ros-message)
  ((id
    :reader id
    :initarg :id
    :type cl:fixnum
    :initform 0)
   (state
    :reader state
    :initarg :state
    :type cl:fixnum
    :initform 0))
)

(cl:defclass AstarState (<AstarState>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <AstarState>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'AstarState)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name rbqt_pathfinder-msg:<AstarState> is deprecated: use rbqt_pathfinder-msg:AstarState instead.")))

(cl:ensure-generic-function 'id-val :lambda-list '(m))
(cl:defmethod id-val ((m <AstarState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbqt_pathfinder-msg:id-val is deprecated.  Use rbqt_pathfinder-msg:id instead.")
  (id m))

(cl:ensure-generic-function 'state-val :lambda-list '(m))
(cl:defmethod state-val ((m <AstarState>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader rbqt_pathfinder-msg:state-val is deprecated.  Use rbqt_pathfinder-msg:state instead.")
  (state m))
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql '<AstarState>)))
    "Constants for message type '<AstarState>"
  '((:EN_COURS . 0)
    (:LIBRE . 1)
    (:SUCCES . 2)
    (:ECHEC . 3))
)
(cl:defmethod roslisp-msg-protocol:symbol-codes ((msg-type (cl:eql 'AstarState)))
    "Constants for message type 'AstarState"
  '((:EN_COURS . 0)
    (:LIBRE . 1)
    (:SUCCES . 2)
    (:ECHEC . 3))
)
(cl:defmethod roslisp-msg-protocol:serialize ((msg <AstarState>) ostream)
  "Serializes a message object of type '<AstarState>"
  (cl:let* ((signed (cl:slot-value msg 'id)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 65536) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    )
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <AstarState>) istream)
  "Deserializes a message object of type '<AstarState>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'id) (cl:if (cl:< unsigned 32768) unsigned (cl:- unsigned 65536))))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'state)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<AstarState>)))
  "Returns string type for a message object of type '<AstarState>"
  "rbqt_pathfinder/AstarState")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'AstarState)))
  "Returns string type for a message object of type 'AstarState"
  "rbqt_pathfinder/AstarState")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<AstarState>)))
  "Returns md5sum for a message object of type '<AstarState>"
  "6c8af539274ee760816fa034d4811aac")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'AstarState)))
  "Returns md5sum for a message object of type 'AstarState"
  "6c8af539274ee760816fa034d4811aac")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<AstarState>)))
  "Returns full string definition for message of type '<AstarState>"
  (cl:format cl:nil "uint8 EN_COURS = 0  ~%uint8 LIBRE    = 1  # Il faut attendre l'etat LIBRE, SUCCES ou ECHEC avant de redemander un chemin~%uint8 SUCCES  = 2 ~%uint8 ECHEC  = 3~%~%int16 id~%uint8 state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'AstarState)))
  "Returns full string definition for message of type 'AstarState"
  (cl:format cl:nil "uint8 EN_COURS = 0  ~%uint8 LIBRE    = 1  # Il faut attendre l'etat LIBRE, SUCCES ou ECHEC avant de redemander un chemin~%uint8 SUCCES  = 2 ~%uint8 ECHEC  = 3~%~%int16 id~%uint8 state~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <AstarState>))
  (cl:+ 0
     2
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <AstarState>))
  "Converts a ROS message object to a list"
  (cl:list 'AstarState
    (cl:cons ':id (id msg))
    (cl:cons ':state (state msg))
))
