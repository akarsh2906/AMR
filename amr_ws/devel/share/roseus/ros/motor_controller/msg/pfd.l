;; Auto-generated. Do not edit!


(when (boundp 'motor_controller::pfd)
  (if (not (find-package "MOTOR_CONTROLLER"))
    (make-package "MOTOR_CONTROLLER"))
  (shadow 'pfd (find-package "MOTOR_CONTROLLER")))
(unless (find-package "MOTOR_CONTROLLER::PFD")
  (make-package "MOTOR_CONTROLLER::PFD"))

(in-package "ROS")
;;//! \htmlinclude pfd.msg.html


(defclass motor_controller::pfd
  :super ros::object
  :slots (_distance _angle _status ))

(defmethod motor_controller::pfd
  (:init
   (&key
    ((:distance __distance) 0)
    ((:angle __angle) 0)
    ((:status __status) nil)
    )
   (send-super :init)
   (setq _distance (round __distance))
   (setq _angle (round __angle))
   (setq _status __status)
   self)
  (:distance
   (&optional __distance)
   (if __distance (setq _distance __distance)) _distance)
  (:angle
   (&optional __angle)
   (if __angle (setq _angle __angle)) _angle)
  (:status
   (&optional (__status :null))
   (if (not (eq __status :null)) (setq _status __status)) _status)
  (:serialization-length
   ()
   (+
    ;; int8 _distance
    1
    ;; int8 _angle
    1
    ;; bool _status
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; int8 _distance
       (write-byte _distance s)
     ;; int8 _angle
       (write-byte _angle s)
     ;; bool _status
       (if _status (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; int8 _distance
     (setq _distance (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _distance 127) (setq _distance (- _distance 256)))
   ;; int8 _angle
     (setq _angle (sys::peek buf ptr- :char)) (incf ptr- 1)
     (if (> _angle 127) (setq _angle (- _angle 256)))
   ;; bool _status
     (setq _status (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(setf (get motor_controller::pfd :md5sum-) "b2931a42170a1095d7904fa2881d4ca7")
(setf (get motor_controller::pfd :datatype-) "motor_controller/pfd")
(setf (get motor_controller::pfd :definition-)
      "int8 distance
int8 angle
bool status

")



(provide :motor_controller/pfd "b2931a42170a1095d7904fa2881d4ca7")


